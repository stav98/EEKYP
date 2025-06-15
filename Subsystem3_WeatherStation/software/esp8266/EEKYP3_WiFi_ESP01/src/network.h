#include "ESPAsyncWebServer.h"
//#include <TimeLib.h> //Για μετατροπή από epoch time υπάρχει στο NTPClient_Generic.h

static void rst(void*);
void reconnect(void);
void callback(String, byte*, unsigned int);
void initNetwork(void);
void startWiFi(void);
void list_wifi_web(void);
String getEncryptionType(int);
void notFound(AsyncWebServerRequest*);
String processor(const String&);
String processor_net(const String&);
void saveSettings(AsyncWebServerRequest*, char*);
static void testcon(void*);
//--------------------- Μεταβλητές σύνδεσης στον MQTT broker ---------------------------------------------
//const char *mqtt_server;          //Όνομα του mqtt server
//int mqtt_port;                    //Πόρτα π.χ. 1883
//const char *mqttuser;             //"user"
//const char *mqttpass;             //"123456"
//byte mqtt_state = 0;

//void setSwitch(AsyncWebServerRequest*, String, byte, bool*);
//void setSwitch(AsyncWebServerRequest*, String, byte);
//void setSwitchState(byte, bool);
void onConnect(void*, AsyncClient*);
static void pubmqtt(void*);

//Δημιουργία αντικειμένων Server και Clients
AsyncWebServer server(80); //Ο τοπικός web server
AsyncClient* test_client = new AsyncClient; //Δοκιμαστική σύνδεση TCP για έλεγχο σύνδεσης με διαδίκτυο

static os_timer_t restartDelay;

//Επανεκκίνηση του ESP
static void rst(void* arg)
{
 os_timer_disarm(&restartDelay);
 ESP.restart();
}

//------------------------------------------- Node RED -----------------------------------------------------
//  (MQTT IN) -----------------------> (SWITCH) ---------------------------------> (MQTT OUT)
//  Topic : room1/light1_stat          Pass Through msg if payload... : Όχι        Topic : room1/light1_cmd
//                                     On payload  : on                            Retain : κενό
//                                     Off payload : off
//                                     Topic : msg.payload
//----------------------------------------------------------------------------------------------------------
//Ενεργεί όταν λάβει μήνυμα mqtt σε κάποιο topic
//Delete retained messages: mosquitto_pub -t room1/light1_sub -u user -P pass -n -r -d
//Κάθε φορά που δημοσιεύεται ένα μήνυμα στα topic που έχει κάνει sub παρακάτω κατά την σύνδεση τότε
//καλείται αυτή η συνάρτηση.
//Για δοκιμή από τερματικό mosquitto_pub -h iot.xxxxxxx.com -u username -P pass -t EEKYP-2A/switch1_sub -m on
void callback(String topic, byte* payload, unsigned int length1)
             {
              //Εμφανίζει το μήνυμα στη κονσόλα
              #if DEBUG_INFO
              Serial.print(F("message arrived["));
              Serial.print(topic);
              Serial.println(F("]"));
              #endif
              String msgg;
              for (unsigned int i = 0; i < length1; i++)
                  {
                   #if DEBUG_INFO
                   Serial.print((char)payload[i]);
                   #endif
                   msgg += (char)payload[i];
                  }
              Serial.println();
             }

//Καλείται μέσα από την loop()
void reconnect()
     {
      bool conn;
      if (MQTT_SRV == "-1")
          MQTT_State = "none";
      else if (InternAvail == "true") //&& (MQTT_SRV != "-1"))
         {
          while (!client.connected() && mqtt_state < 1) //Μία προσπάθεια
                {
                 #if DEBUG_INFO
                 Serial.println(F("Connecting to MQTT..."));
                 #endif
                 if (MQTT_USER == "")
                     conn = client.connect(MQTT_CLIENT.c_str());
                 else
                    {
                     mqttuser = MQTT_USER.c_str();
                     mqttpass = MQTT_PASS.c_str();
                     conn = client.connect(MQTT_CLIENT.c_str(), mqttuser, mqttpass);
                    }
                 if (conn) 
                    {
                     #if DEBUG_INFO
                     Serial.println("connected");
                     #endif
                     mqtt_state = 0;
                     MQTT_State = "true";
                     //Συνδρομή στα παρακάτω topics για τους διακόπτες
                     //client.subscribe((MQTT_CLIENT + "/" + SetA1_TOPIC + "_cmd").c_str());
                     delay(200); //Μικρή καθυστέρηση για να δεχθεί το 1ο interrupt στο retain
                     //client.subscribe((MQTT_CLIENT + "/" + SetA2_TOPIC + "_cmd").c_str());
                    } 
                 else 
                    {
                     #if DEBUG_INFO
                     Serial.print(F("Failed with state "));
                     Serial.println(client.state());
                     #endif
                     mqtt_state++;
                     MQTT_State = "false";
                    }
                }
         }
     }

uint8_t MAC_array[6];
char MAC_char[19];     

//Αρχικοποίηση υπηρεσιών δικτύου
void initNetwork()
     {
      startWiFi(); //Ξεκίνησε το WiFi
      
      //Αρχικά κάνε σύνδεση με τον testhost
      test_client->connect(testhost, 80);
      delay(1000); //Περίμενε λίγο //500
      testcon(NULL); //Δες αν έγινε η σύνδεση
 
      //Ξεκίνησε τον NTP Client
      const char *ntp_name;
      ntp_name = NTP_SRV.c_str(); //Μετατροπή του String σε const char*
      //Άλλαξε το όνομα του Time Server
      timeClient.setPoolServerName(ntp_name);
      timeClient.setTimeOffset(NTP_TZ.toInt() * 3600); //Άλλαξε την ζώνη ώρας  
      timeClient.begin();
      timeClient.setUpdateInterval(SECS_IN_DAY); //Αν καλείται στο Loop θα κάνει update μια φορά την μέρα SECS_IN_DAY ή κάθε ώρα SECS_IN_HR
      //Serial.println(timeClient.getPoolServerName()); //Debug
      bool ntp_OK = false;
      byte ntp_tries = 0;
      if (InternAvail == "true")
         {
          while (!ntp_OK && ntp_tries < 20) //10
                {
                 timeClient.update();
                 delay(100);
                 if (timeClient.updated())
                     ntp_OK = true;
                 ntp_tries++;
                 delay(100);
                }
         }
      if (ntp_OK)
          {
           #if DEBUG_INFO
           Serial.println(F("Time Client Updated"));
           #endif
           asm("nop;"); //Δεν κάνει κάτι
          }
      else
          #if DEBUG_INFO
          Serial.println(F("Time Client Not Updated"));
          #endif
      //Serial.println("UTC : " + timeClient.getFormattedUTCDateTime()); //UTC
      #if DEBUG_INFO
      Serial.println("LOC : " + timeClient.getFormattedDateTime()); //LOCAL
      #else
      timeClient.getFormattedDateTime();
      #endif

      mqtt_server = MQTT_SRV.c_str();
      mqtt_port = MQTT_PORT.toInt();
      client.setServer(mqtt_server, mqtt_port);
      client.setCallback(callback);
      
      delay(200);
      //=====================================================  Συναρτήσεις χειρισμού του Web Server ======================================================================
      //Ζητήθηκε η αρχική σελίδα /
      server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
               {
                if (!request->authenticate(LOG_NAME.c_str(), LOG_PASS.c_str()))
                    return request->requestAuthentication();
                else
                    request->send(LittleFS, "/index.html", String(), false, processor); //Χρήση processor αν στο index.html υπάρχει %ΛΕΞΗ%, τότε θα βάλει στη θέση ότι επιστρέψει η processor σαν ASP
                    //request->send(SPIFFS, "/index.html", "text/html"); //Χωρίς χρήση processor
               });
      //Ζητήθηκε η υποσελίδα /setup_wp.html
      server.on("/setup_wp.html", HTTP_GET, [](AsyncWebServerRequest * request)
               {
                if (!request->authenticate(LOG_NAME.c_str(), LOG_PASS.c_str()))
                    return request->requestAuthentication();
                else
                    request->send(LittleFS, "/setup_wp.html", String(), false, processor); //Χρήση processor αν στην HTML υπάρχει %ΛΕΞΗ%, τότε θα βάλει στη θέση ότι επιστρέψει η processor σαν ASP
               });
      //Ζητήθηκε η υποσελίδα /setup_net.html
      server.on("/setup_net.html", HTTP_GET, [](AsyncWebServerRequest * request)
               {
                if (!request->authenticate(LOG_NAME.c_str(), LOG_PASS.c_str()))
                    return request->requestAuthentication();
                else
                    request->send(LittleFS, "/setup_net.html", String(), false, processor_net); //Χρήση processor αν στην HTML υπάρχει %ΛΕΞΗ%, τότε θα βάλει στη θέση ότι επιστρέψει η processor σαν ASP
               });
      //Ζητήθηκε η υποσελίδα /search_net.html
      server.on("/search_net.html", HTTP_GET, [](AsyncWebServerRequest * request)
               {
                if (!request->authenticate(LOG_NAME.c_str(), LOG_PASS.c_str()))
                    return request->requestAuthentication();
                else
                   {
                    list_wifi_web();
                    if (scan_state == 2)
                       {
                        scan_state = 0;
                        request->send(LittleFS, "/search_net.html", String(), false, processor); //Χρήση processor αν στην HTML υπάρχει %ΛΕΞΗ%, τότε θα βάλει στη θέση ότι επιστρέψει η processor σαν ASP
                       }
                   }
               });
      //Ζητήθηκε η υποσελίδα /log.html
      server.on("/log.html", HTTP_GET, [](AsyncWebServerRequest * request)
               {
                request->send(LittleFS, "/log.html", String(), false, processor); //Χρήση processor αν στην HTML υπάρχει %ΛΕΞΗ%, τότε θα βάλει στη θέση ότι επιστρέψει η processor σαν ASP
               });
      
      //Δεν βρέθηκε αρχείο
      server.onNotFound(notFound);

      //Ζητήθηκε το URL http://ip_address/status και απαντάει με το παρακάτω string σε μορφή text. Αυτό γίνεται κάθε 1sec και ενημερώνει τα στοιχεία span και div.
      server.on("/status", HTTP_GET, [](AsyncWebServerRequest * request)
               {
                String tmp = "<val id=\"therm1\">" + String(Therm1) + "</val>" + \
                             "<val id=\"pressure\">" + String(Pressure) + "</val>" + \
                             "<val id=\"humid\">" + String(Humidity) + "</val>" + \
                             "<val id=\"airspeed\">" + String(AirSpeed) + "</val>" + \
                             "<val id=\"airdir\">" + String(AirDir) + "</val>" + \
                             "<val id=\"rain\">" + String(RainP) + "</val>" + \
                             "<val id=\"uvi\">" + String(UVI) + "</val>" + \
                             "<val id=\"therm2\">" + String(Therm2) + "</val>" + \
                             "<val id=\"irrad\">" + String(Irrad) + "</val>" + \
                             "<val id=\"vline\">" + String(Vline) + "</val>" + \
                             "<val id=\"time\">" + curTime() + "</val>" + \
                             "<val id=\"up_time\">" + upTime() + "</val>" + \
                             "<val id=\"internet\">" + InternAvail + "</val>" + \
                             "<val id=\"mqtt_state\">" + MQTT_State + "</val>" + \
                             "<val id=\"s_strength\">" + S_Strength + "</val>";
                request->send(200, "text/plain", tmp);
               });

      //Ζητήθηκε το αρχείο gauge για όργανα μετρήσεων
      server.on("/gauge.min.js", HTTP_GET, [](AsyncWebServerRequest * request)
            {
             request->send(LittleFS, "/gauge.min.js", "text/javascript");
            });

      //Ζητήθηκε το αρχείο JQuery
      server.on("/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest * request)
            {
             request->send(LittleFS, "/jquery.min.js", "text/javascript");
            });

      //Ζητήθηκε το αρχείο Chart για δημιουργία γραφικών παραστάσεων
      server.on("/chart.min.js", HTTP_GET, [](AsyncWebServerRequest * request)
            {
             request->send(LittleFS, "/chart.min.js", "text/javascript");
            });
  
      //Ζητήθηκε το αρχείο CSS
      server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request)
            {
             request->send(LittleFS, "/style.css", "text/css");
            });

      //========================== Ενέργειες με το πάτημα κουμπιών ========================================
      //Ζητήθηκε η υποσελίδα /update της αρχικής σελίδας με GET κάποιες παραμέτρους π.χ. /update?button1=Ok
      server.on("/update", HTTP_GET, [](AsyncWebServerRequest * request)
            {
             //Όνομα διακόπτη στο GET, Αριθμ. Διακόπτη, Μεταβλητή με την προηγούμενη κατάσταση
             //setSwitch(request, "SW1", 1, &sw1_pre);
             //setSwitch(request, "SW1", 1);
             //setSwitch(request, "SW2", 2, &sw2_pre);
             //setSwitch(request, "SW2", 2);
             //Επέστρεψε πίσω την ιστοσελίδα
             request->send(LittleFS, "/index.html", String(), false, processor);
            });

      //Ζητήθηκε η υποσελίδα /settime της αρχικής σελίδας με GET κάποιες παραμέτρους π.χ. /update?button1=Ok
      server.on("/settime", HTTP_GET, [](AsyncWebServerRequest * request)
            {
             if (request->hasParam("TIME")) //Αν υπάρχει η παράμετρος
                {
                 String t = request->getParam("TIME")->value();
                 //Serial.println(t); //Debug
                 t.remove(t.length() - 3, 3);
                 tim = t.toInt() + (int) BROW_TO.toInt() * 3600;
                 Serial.printf("Set Date to: %4d-%02d-%02d %02d:%02d:%02d\n", year(tim), month(tim), day(tim), hour(tim), minute(tim), second(tim));
                }
             //Επέστρεψε πίσω την ιστοσελίδα
             request->send(LittleFS, "/index.html", String(), false, processor);
            });

      //Ζητήθηκε η υποσελίδα /save_wp με GET κάποιες παραμέτρους για να αποθηκεύει ρυθμίσεις της /setup_wp.html
      server.on("/save_wp", HTTP_GET, [](AsyncWebServerRequest * request)
            {
             saveSettings(request, (char*)("/settings_wp.txt"));
             readSettings_wp(); 
             //Επέστρεψε πίσω την ιστοσελίδα setup_wp.html
             request->send(LittleFS, "/setup_wp.html", String(), false, processor);
            });

      //Ζητήθηκε η υποσελίδα /save_net με GET κάποιες παραμέτρους για να αποθηκεύει ρυθμίσεις της /setup_wp.html
      server.on("/save_net", HTTP_GET, [](AsyncWebServerRequest * request)
            {
             saveSettings(request, (char*)("/settings_net.txt"));
             readSettings_net();
             //Επέστρεψε πίσω την ιστοσελίδα setup_net.html
             request->send(LittleFS, "/setup_net.html", String(), false, processor_net);
             os_timer_setfn(&restartDelay, &rst, NULL);
             os_timer_arm(&restartDelay, 1000, false); //Μετά από 1sec κάνε reset ώστε να φορτώσει τις νέες ρυθμίσεις
            });

      //Ζητήθηκε η υποσελίδα /log της αρχικής σελίδας με GET κάποιες παραμέτρους π.χ. /log?Erase=yes
      server.on("/log", HTTP_GET, [](AsyncWebServerRequest * request)
            {
             if (request->hasParam("Erase")) //Αν υπάρχει η παράμετρος
                {
                 String t = request->getParam("Erase")->value();
                 if (t == "yes")
                    {
                     //Serial.println("Erasing File ..."); //Debug
                     LittleFS.remove("/log.csv");
                    }
                 //Επέστρεψε πίσω την ιστοσελίδα
                 request->send(LittleFS, "/log.html", String(), false, processor);
                }
             else if (request->hasParam("View")) //Αν υπάρχει η παράμετρος save
                {
                 String t = request->getParam("View")->value();
                 if (t == "yes") //εμφάνισε το αρχείο σε άλλο tab
                    {
                     request->send(LittleFS, "/log.csv", "text/plain");
                    }
                 else if (t == "save") //Κατέβασε το αρχείο για αποθήκευση
                    {
                     request->send(LittleFS, "/log.csv", "text/csv");
                    }
                }        
            });

      // Εκκίνηση του Web Server
      server.begin();
     }

void startWiFi()
     {
      char hostname[15]; 
      //--- Στατική IP  ------------------------------------
      byte tmp[4];
      split(IP_ADDR, tmp, '.');
      IPAddress local_IP(tmp[0], tmp[1], tmp[2], tmp[3]);
      split(IP_GATE, tmp, '.');
      IPAddress gateway(tmp[0], tmp[1], tmp[2], tmp[3]);
      split(IP_MASK, tmp, '.');
      IPAddress subnet(tmp[0], tmp[1], tmp[2], tmp[3]);
      split(IP_DNS, tmp, '.');
      IPAddress primaryDNS(tmp[0], tmp[1], tmp[2], tmp[3]);   //optional
        
      WiFi.macAddress(MAC_array);
      MAC_char[18] = 0;
      sprintf(MAC_char,"%02x:%02x:%02x:%02x:%02x:%02x", MAC_array[0],MAC_array[1],MAC_array[2],MAC_array[3],MAC_array[4],MAC_array[5]);
      sprintf(hostname, "%s%02x%02x%02x", "EEKYP1-", MAC_array[3], MAC_array[4], MAC_array[5]);
      wifi_station_set_hostname(hostname); //Βάζει hostname αν έχει δυναμική απόδοση διεύθυνης
      #if DEBUG_INFO
      Serial.println("MAC: " + String(MAC_char));   //", len=" + String(strlen(MAC_char)) );
      Serial.println("HOSTNAME: " + String(hostname));
      #endif
      
      //--------------------------------------------------------------------
      byte retry_cnt = 0;
      if (SetSTA == "true")
         {
          WiFi.mode(WIFI_STA);
          if (IP_STATIC == "true")
             {
              //Αν έχει στατική IP βγάζω το σχόλιο κάτω
              WiFi.config(local_IP, gateway, subnet, primaryDNS);
             }
          //--- Λειτουργία client ----------------------------------------------
          char client_ssid[20];
          ST_SSID.toCharArray(client_ssid, 20);
          char client_password[20];
          ST_KEY.toCharArray(client_password, 20);
          WiFi.begin(client_ssid, client_password);
          //Περίμενε 30sec ή μέχρι να γίνει σύνδεση
          while (WiFi.status() != WL_CONNECTED && retry_cnt < 30) 
                {
                 delay(1000);
                 #if DEBUG_INFO
                 Serial.println("Connecting to WiFi..");
                 #endif
                 retry_cnt++;
                }
          if (WiFi.status() == WL_CONNECTED)  //Αν έγινε σύνδεση
             {
              #if DEBUG_INFO
              Serial.println("Start as Client connected to SSID: " + ST_SSID);
              Serial.print(F("Connect with your browser to "));
              Serial.println(WiFi.localIP());
              #endif
             }
          else //Αλλιώς δεν έγινε σύνδεση
             {
              #if DEBUG_INFO
              Serial.print(F("Unable to connect as Client. Please check SSID and Password"));
              #endif
             }
         }
      else if (SetAP == "true")
         {
          //--- Λειτουργία AP.----------------------------------------------------
          char ap_ssid[20];
          AP_SSID.toCharArray(ap_ssid, 20);
          char ap_password[20];
          AP_KEY.toCharArray(ap_password, 20);
          WiFi.mode(WIFI_AP);
          int chan = AP_CHANNEL.toInt();
          WiFi.softAP(ap_ssid, ap_password, chan, 0, 4); //int channel, int ssid_hidden [0,1], int max_connection [1-4]
          //Δεν λειτουργεί τόσο σωστά με στατική IP. Καλύτερα να αφήνουμε την δυναμική δηλ. 192.168.4.1
          if (IP_STATIC == "true")
              WiFi.softAPConfig (local_IP, gateway, subnet);
          IPAddress IP = WiFi.softAPIP();
          #if DEBUG_INFO
          Serial.println("Start as AP with SSID: " + AP_SSID);
          Serial.print(F("Connect with your browser to "));
          Serial.println(IP);
          #endif
         }
     }

//Αναζητά για διαθέσιμα δίκτυα και τα εμφανίζει στον browser
void list_wifi_web()
     { 
      if (scan_state == 0)
          scan_state = 1;
      else if (scan_state == 2)
         {
          search_net_str = "";
          int n = WiFi.scanComplete();
          if (n >= 0)
             {
              num_net_str = String(n);
              for (int i = 0; i < n; i++)
                  {
                   search_net_str += "<tr bgcolor=\"pink\" align=\"center\"><td>" + \
                                     String(i + 1) + "</td><td><a href=\"javascript:ok('" + WiFi.SSID(i) + "')\">" + WiFi.SSID(i) + \
                                     "</a></td><td>" + WiFi.channel(i) + "</td><td>" + WiFi.RSSI(i) + \
                                     "</td><td>" + getEncryptionType(WiFi.encryptionType(i)) + "</td></tr>\n"; 
                  }
              WiFi.scanDelete();
            }
         }
     }

//Βρίσκει τον τύπο κρυπτογράφησης//---------------------------- Μεταβλητές αρχικής σελίδας ------------------------------------------------
String getEncryptionType(int thisType) 
     {
      String t;
      //Πάρε τον τύπο που είναι ένας αριθμός και εμφάνισε το όνομα
      switch (thisType) 
             {
              case ENC_TYPE_WEP:
                   //Serial.print("WEP");
                   t = "WEP";
                   break;
              case 2:
                   //Serial.print("WPA_PSK");
                   t = "WPA_PSK";
                   break;
              case 4:
                   //Serial.print("WPA2_PSK");
                   t = "WPA2_PSK";
                   break;
              case 8:
                   //Serial.print("AUTO");
                   t = "AUTO";
                   break;
              case ENC_TYPE_NONE:
                   //Serial.print("None");
                   t = "None";
                   break;
             }
       return t;
      }

//Αν δεν υπάρχει κάποιο αρχείο στο σύστημα αρχείων τότε να εμφανίσει 404
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/html", "<!DOCTYPE html><HTML><HEAD><TITLE>RF BRIDGE : File Not Found</TITLE></HEAD><BODY><H1>Not found</H1></BODY></HTML>");
}

//Ψάχνει για placeholders μέσα στο αρχείο HTML με σύνταξη %xxx%, όπως η ASP
String processor(const String& var)
{
  //Serial.println(var); //Debug
  //Σελίδα index.html
  if (var == "VERSION") //Αν το βρήκες
      return String(VERSION); //Γύρνα μια τιμή
  else if (var == "FOOTER")
      return String(FOOTER_LOGO);
  //Σελίδα setup_wp.html και index.html
  else if (var == "SetMqttPeriod")
      return SetMQTT_Per;
  //Σελίδα search_net.html
  else if (var == "SearchNetNum")
       return num_net_str;
  else if (var == "SearchNet")
      return search_net_str;
  return String(); //Αν δεν το βρήκες γύρνα κενό string
}

//Ψάχνει για placeholders μέσα στο αρχείο HTML με σύνταξη %xxx%, όπως η ASP
String processor_net(const String& var)
{
  //Serial.println(var); //Debug
  //Σελίδα setup_net.html
  if (var == "VERSION") //Αν το βρήκες
      return String(VERSION); //Γύρνα μια τιμή
  else if (var == "FOOTER")
      return String(FOOTER_LOGO);
  else if (var == "SetAP")
      return SetAP;
  else if (var == "AP_SSID")
      return AP_SSID;
  else if (var == "AP_CHANNEL")
      return AP_CHANNEL;
  else if (var == "AP_ENCRYPT")
      return AP_ENCRYPT;
  else if (var == "AP_KEY")
      return AP_KEY;
  else if (var == "SetSTA")
      return SetSTA;
  else if (var == "ST_SSID")
      return ST_SSID;
  else if (var == "ST_KEY")
      return ST_KEY;
  else if (var == "IP_STATIC")
      return IP_STATIC;
  else if (var == "IP_ADDR")
      return IP_ADDR;
  else if (var == "IP_MASK")
      return IP_MASK;
  else if (var == "IP_GATE")
      return IP_GATE;
  else if (var == "IP_DNS")
      return IP_DNS;
  else if (var == "NTP_TZ")
      return NTP_TZ;
  else if (var == "BROW_TO")
      return BROW_TO;
  else if (var == "NTP_SRV")
      return NTP_SRV;
  else if (var == "MQTT_SRV")
      return MQTT_SRV;
  else if (var == "MQTT_PORT")
      return MQTT_PORT;
  else if (var == "MQTT_USER")
      return MQTT_USER;
  else if (var == "MQTT_PASS")
      return MQTT_PASS;
  else if (var == "MQTT_CLIENT")
      return MQTT_CLIENT;
  else if (var == "LOG_NAME")
      return LOG_NAME;
  else if (var == "LOG_PASS")
      return LOG_PASS;
  return String(); //Αν δεν το βρήκες γύρνα κενό string
}

//Αποθηκεύει ρυθμίσεις της αρχικής οθόνης που είναι σε μορφή GET
void saveSettings(AsyncWebServerRequest *request, char *Filename)
     {
      File file = LittleFS.open(Filename, "w");
      if (!file) 
         {
          Serial.println("Error opening file for writing");
          return;
         }
      file.print("#Automatic created from script\n");
      int args = request->args();
      for (int i = 0; i < args; i++)
          {
           //Serial.println(String(request->arg(i).c_str()));
           file.print(String(request->argName(i).c_str()) + "::" + String(request->arg(i).c_str()) + "\n");
          }
      file.close();
     }

//Κάθε 30 sec στείλε αίτημα σύνδεσης και ελέγχει αν υπάρχει Internet
static void testcon(void* arg)
{
 test_client->connect(testhost, 80); //Στείλε
 if (conn) //Αν το conn έγινε true μέσα στην onConnect υπάρχει σύνδεση
    {
     conn = false; //Άλλαξέ το για την επόμενη προσπάθεια
     InternAvail = "true"; //Θέσε μεταβλητή που στέλνει στο web interface
     //Serial.println("Internet OK");
    }
 else //Αλλιώς δεν υπάρχει σύνδεση
    {
     InternAvail = "false";
     //Serial.println("Internet BAD");
    }
 //Κάνει έλεγχο για τον τρόπο αναβοσβήματος του status LED (μπλέ)
 if (SetSTA == "true") //Αν συνδέεται σαν client
    {
     if (WiFi.status() == WL_CONNECTED  && InternAvail == "true")
         led_pat = 1023; //Αναμμένο συνέχεια
     else if (WiFi.status() == WL_CONNECTED && InternAvail == "false")
         led_pat = 0b1111100000; //Duty cycle 50%
     else if (WiFi.status() != WL_CONNECTED)
        {
         led_pat = 0b1000000000; //Μία σύντομη αναλαμπή
         char client_ssid[20];
         ST_SSID.toCharArray(client_ssid, 20);
         char client_password[20];
         ST_KEY.toCharArray(client_password, 20);
         WiFi.begin(client_ssid, client_password);
         #if DEBUG_INFO
         Serial.println("Trying to reconnected as client to SSID: " + ST_SSID);
         #endif
        }
    }
 else if (SetAP == "true") //Αν λειτουργεί σαν AP
     led_pat = 0b1111011110; //Δύο σύντομες διακοπές
}

//Αν έγινε σύνδεση με τον testhost
void onConnect(void* arg, AsyncClient* client) 
{
  //Serial.println("client has been connected");
  if (client->connected()) //Αν είναι συνδεμένο
     {
      conn = true; //Θέσε το conn ώστε να ανιχνευθεί στην testcon κατά την επόμενη προσπάθεια
      client->stop(); //Αποσύνδεση
     }
}

//Σε τακτά χρονικά διαστήματα μπαίνει εδώ και κάνει δημοσίευση στον MQTT broker την κατάσταση αισθητήρων και διακοπτών
//Για δοκιμή από τερματικό γράφουμε:
//mosquitto_sub -h iot.xxxxxxx.com -u username -P pass -t EEKYP-1A/data_pub
//Και κάθε 1-5 λεπτά εμφανίζεται το νέο μήνυμα
//Αν θέλουμε να στείλουμε κάτι ανοίγουμε άλλο τερματικό και γράφουμε:
//mosquitto_pub -h iot.xxxxxxx.com -u username -P password -t EEKYP-1A/data_pub -m 23.0
//Τότε στο 1ο τερματικό θα δούμε την τιμή 23
static void pubmqtt(void* arg)
{
 int MOAirDir, MOIrrad; 
 float MOTherm1, MOTherm2, MOPressure, MOHumidity, MOAirSpeed, MOUVI, MOVline, MORain;
 char t[60]; //Προσωρινό string το οποίο κρατάει το αποτέλεσμα
 MOTherm1 = STherm1 / samples;
 MOTherm2 = STherm2 / samples;
 MOPressure = SPressure / samples;
 MOHumidity = SHumidity / samples;
 MOAirSpeed = SAirSpeed / samples;
 MOUVI = SUVI / samples;
 MOVline = SVline / samples;
 MORain = SRainH / samples;
 MOAirDir = SAirDir; //MOAirDir = SAirDir / samples;
 MOIrrad = SIrrad / samples;
 
 samples = 0; //Μηδένισε μετρητή δειγμάτων
 STherm1 = SPressure = SHumidity = SAirSpeed = SUVI = STherm2 = SVline = 0; //Μηδένισε αθροιστές
 SAirDir = SRainH = SIrrad = 0;
 mqtt_state = 0;
 //Ετοίμασε μορφή CSV για δημοσίευση στον Broker
 sprintf(t, "%3.1f;%3.1f;%4.1f;%2.1f;%2.1f;%d;%2.1f;%2.1f;%d;%2.1f;%d", 
        MOTherm1, MOTherm2, MOPressure, MOHumidity, MOAirSpeed, MOAirDir, MORain, MOUVI, MOIrrad, MOVline, wifi_strength);
 //Δημοσίευση τώρα
 if (client.connected())
     client.publish((MQTT_CLIENT + "/data_pub").c_str(), t, true); //Αν θέλω να είναι retain βάζω true, διαφορετικά κενό (σβήνω το ,)
}
