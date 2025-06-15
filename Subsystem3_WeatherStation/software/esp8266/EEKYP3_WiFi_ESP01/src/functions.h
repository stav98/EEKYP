#include <ESP8266WiFi.h>
#include <NTPClient_Generic.h>
#include <WiFiUdp.h>
#define TIME_ZONE_OFFSET_HRS          (+3)

String curTime(void);
String curDateTime(void);
String upTime(void);
void print_table(byte*, unsigned short, char);
void blink_led(byte);
void readSettings(void);
void setUserVars(String, String);
void readSettings_wp(void);
void make_wpStates(String);
void readSettings_net(void);
void setNetVars(String, String);
void split(String, byte*, char);
void chkLogSize(void);
void listFS(void);
void cp(String, String);

//Ορισμός NTP Client για συγχρονισμό της ώρας
WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "gr.pool.ntp.org", TIME_ZONE_OFFSET_HRS * 3600);
NTPClient timeClient(ntpUDP, TIME_ZONE_OFFSET_HRS * 3600);

WiFiClient espclient;
//PubSubClient client(mqtt_server, 1883, callback, espclient);
PubSubClient client(espclient);
 
//Επιστρέφει την τρέχουσα ώρα
String curTime()
{
 char t_str[9];
 if (InternAvail == "true") //Αν υπάρχει σύνδεση internet
     //Χρόνος NTP
     sprintf(t_str, "%02d:%02d:%02d", timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());
 else //Αλλιώς
     //Χρόνος browser
     sprintf(t_str, "%02d:%02d:%02d", hour(tim), minute(tim), second(tim));
 //return timeClient.getHours() + String(":") + timeClient.getMinutes() + String(":") + timeClient.getSeconds(); //timeClient.getFormattedDateTime();
 return String(t_str);
}

//Επιστρέφει την τρέχουσα Ημερομηνία - Ώρα
String curDateTime()
{
 char t_str[22];
 if (InternAvail == "true") //Αν υπάρχει σύνδεση internet
     //Χρόνος NTP
     sprintf(t_str, "%02d/%02d/%4d %02d:%02d:%02d", timeClient.getDay(), timeClient.getMonth(), timeClient.getYear(), timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());
 else //Αλλιώς
     //Χρόνος browser
     sprintf(t_str, "%02d/%02d/%4d %02d:%02d:%02d", day(tim), month(tim), year(tim), hour(tim), minute(tim), second(tim));
 return String(t_str);
}

//Επιστρέφει τον χρόνο συνεχόμενης λειτουργίας
String upTime()
{
 char t_str[18];
 sprintf(t_str, "%hhuM-%hhuD-%02d:%02d:%02d", month(uptime)-1, day(uptime)-1, hour(uptime), minute(uptime), second(uptime));
 return String(t_str);
}

//Μόνο για Debuging. Εμφανίζει το περιεχόμενο κάποιου πίνακα
void print_table(byte *table, unsigned short len, char base)
{
 unsigned short i;
 for(i = 0; i < len-1; i++)
    {
     if (base != 'c')
        {
         if (base == 'd')
             Serial.print(table[i]);
         else if (base == 'h')
             Serial.printf("%02X", table[i]);
         Serial.print(':'); 
        }
     else
         Serial.print((char)table[i]);
    }
 if (base != 'c')
    {
     if (base == 'd')
         Serial.println(table[i]);
     else if (base == 'h')
         Serial.printf("%02X\n", table[i]);
    }
 else
    Serial.println((char)table[i]);
}

void blink_led(byte pin)
{
 if (millis() - blink_per > 100)
    {
     byte out = led_pat & 1;
     digitalWrite(pin, out); //Ανάβει
     led_pat >>= 1;
     led_pat += out * 512;
     blink_per = millis();
    }
}

//Διαβάζει τις αποθηκευμένης ρυθμίσεις του αρχείου και θέτει τους διακόπτες σε περίπτωση διακοπής.
//Καλείται κατά το ξεκίνημα και μετά την αποθήκευση.
void readSettings()
{
 String buffer;
 File file = LittleFS.open("/settings.txt", "r");
 //Αν το αρχείο δεν υπάρχει (πρώτη φορά) τότε να βάλει κάποιες προκαθορισμένες τιμές
 if (!file) 
    {
     Serial.println(F("Failed to open file /settings.txt for reading. Loading Defaults ..."));
     //Βάλε αρχικές τιμές στις μεταβλητές
     SetSw1 = "off"; 
     SetSw2 = "off";
     
     //Γράψε το αρχείο την πρώτη φορά μόνο
     File file = LittleFS.open("/settings.txt", "w");
     if (!file) 
        {
         Serial.println(F("Error opening file for writing"));
         return;
        }
     file.print(F("#Automatic created from script\n"));
     file.print("S1::" + SetSw1 + "\n");
     file.print("S2::" + SetSw2 + "\n");
     file.close();
     return;
    }
 String value1, value2;
 while (file.available()) 
       {
        buffer = file.readStringUntil('\n');
        //Serial.println(buffer); //Debug  
        if (buffer.indexOf("::") > 0)
           {
            for (unsigned int i = 0; i < buffer.length(); i++) 
                {
                 if (buffer.substring(i, i+2) == "::") 
                    {
                     value1 = buffer.substring(0, i);
                     value2 = buffer.substring(i + 2);
                     break;
                    }
                }
            setUserVars(value1, value2);
           }
       }
 file.close();
}

//Ανάλογα με το κλειδί του αρχείου V1, V2, ... Vn, βάλε την τιμή στην αντίστοιχη μεταβλητή ώστε να εμφανιστούν οι
//τιμές στην σελίδα setup_wp.html αφού περάσουν από τον processor.
void setUserVars(String key, String value)
{
 if (key == "V1")
     SetMQTT_Per = value;
 //Θέση διακόπτη για επαναφορά μετά από διακοπή
 else if (key == "S1")
     {
      if (value == "off")
         {
          SetSw1 = "off";
          //setSwitchState(1, false); //Αν χρειαστεί χωρίς MQTT βγάλε σχόλια
         }
      else if (value == "on")
         {
          SetSw1 = "on";
          //setSwitchState(1, true);
         }
     }
 else if (key == "S2")
     {
      if (value == "off")
         {
          SetSw2 = "off";
          //setSwitchState(2, false);
         }
      else if (value == "on")
         {
          SetSw1 = "on";
          //setSwitchState(2, true);
         }
     }
}

//Διαβάζει τις αποθηκευμένης ρυθμίσεις του αρχείου και τις βάζει στα controls 
//της σελίδας setup_wp.html. Καλείται κατά το ξεκίνημα και μετά την αποθήκευση.
void readSettings_wp()
{
 String buffer;
 File file = LittleFS.open("/settings_wp.txt", "r");
 //Αν το αρχείο δεν υπάρχει (πρώτη φορά) τότε να βάλει κάποιες προκαθορισμένες τιμές
 if (!file) 
    {
     Serial.println(F("Failed to open file /settings_wp.txt for reading. Loading Defaults ..."));
     //Βάλε αρχικές τιμές στις μεταβλητές
     SetMQTT_Per = "1";
     
     //Γράψε το αρχείο την πρώτη φορά μόνο
     File file = LittleFS.open("/settings_wp.txt", "w");
     if (!file) 
        {
         Serial.println(F("Error opening file for writing"));
         return;
        }
     file.print(F("#Automatic created from script\n"));
     file.print("V1::" + SetMQTT_Per + "\n");
     file.close();
     return;
    }
 String value1, value2;
 while (file.available()) 
       {
        buffer = file.readStringUntil('\n');
        //Serial.println(buffer); //Debug  
        if (buffer.indexOf("::") > 0)
           {
            for (unsigned int i = 0; i < buffer.length(); i++) 
                {
                 if (buffer.substring(i, i+2) == "::") 
                    {
                     value1 = buffer.substring(0, i);
                     value2 = buffer.substring(i + 2);
                     break;
                    }
                }
            setUserVars(value1, value2);
           }
       }
 file.close();
}

//Διαβάζει τις αποθηκευμένης ρυθμίσεις του αρχείου και τις βάζει στα controls ρύθμισης δικτύου 
//της σελίδας setup_net.html. Καλείται κατά το ξεκίνημα και μετά την αποθήκευση.
void readSettings_net()
{
 String buffer;
 File file = LittleFS.open("/settings_net.txt", "r");
 //Αν το αρχείο δεν υπάρχει (πρώτη φορά) τότε να βάλει κάποιες προκαθορισμένες τιμές
 if (!file) 
    {
     Serial.println(F("Failed to open file /settings_net.txt for reading. Loading Defaults ..."));
     //Βάλε αρχικές τιμές στις μεταβλητές
     SetAP = "true"; //<--
     AP_SSID = "EEKYP-3";
     AP_CHANNEL = "6"; 
     AP_ENCRYPT = "false";
     AP_KEY = ""; 
     SetSTA = "false"; //<--
     ST_SSID = ""; //
     ST_KEY = ""; //
     IP_STATIC = "false"; //<--
     IP_ADDR = "192.168.42.130"; //192.168.1.100
     IP_MASK = "255.255.255.0";
     IP_GATE = "192.168.42.6"; //192.168.1.1
     IP_DNS = "192.168.42.6"; //192.168.1.1
     NTP_TZ = TIME_ZONE_OFFSET_HRS;
     BROW_TO = TIME_ZONE_OFFSET_HRS;
     NTP_SRV = "gr.pool.ntp.org";
     MQTT_SRV = "xxxxx.com"; //<--
     MQTT_PORT = "1883";
     MQTT_USER = "";
     MQTT_PASS = "";
     MQTT_CLIENT = "EEKYP-3A";
     LOG_NAME = "admin";
     LOG_PASS = "admin";
     //Γράψε το αρχείο την πρώτη φορά μόνο
     File file = LittleFS.open("/settings_net.txt", "w");
     if (!file) 
        {
         Serial.println(F("Error opening file for writing"));
         return;
        }
     file.print(F("#Automatic created from script\n"));
     file.print("N1::" + SetAP + "\n");
     file.print("N2::" + AP_SSID + "\n");
     file.print("N3::" + AP_CHANNEL + "\n");
     file.print("N4::" + AP_ENCRYPT + "\n");
     file.print("N5::" + AP_KEY + "\n");
     file.print("N6::" + SetSTA + "\n");
     file.print("N7::" + ST_SSID + "\n");
     file.print("N8::" + ST_KEY + "\n");
     file.print("N9::" + IP_STATIC + "\n");
     file.print("N10::" + IP_ADDR + "\n");
     file.print("N11::" + IP_MASK + "\n");
     file.print("N12::" + IP_GATE + "\n");
     file.print("N13::" + IP_DNS + "\n");
     file.print("N14::" + NTP_TZ + "\n");
     file.print("N15::" + BROW_TO + "\n");
     file.print("N16::" + NTP_SRV + "\n");
     file.print("N17::" + MQTT_SRV + "\n");
     file.print("N18::" + MQTT_PORT + "\n");
     file.print("N19::" + MQTT_USER + "\n");
     file.print("N20::" + MQTT_PASS + "\n");
     file.print("N21::" + MQTT_CLIENT + "\n");
     file.print("N22::" + LOG_NAME + "\n");
     file.print("N23::" + LOG_PASS + "\n");
     file.close();
     return;
    }
 String value1, value2;
 while (file.available()) 
       {
        buffer = file.readStringUntil('\n');
        //Serial.println(buffer); //Debug  
        if (buffer.indexOf("::") > 0)
           {
            for (unsigned int i = 0; i < buffer.length(); i++) 
                {
                 if (buffer.substring(i, i+2) == "::") 
                    {
                     value1 = buffer.substring(0, i);
                     value2 = buffer.substring(i + 2);
                     break;
                    }
                }
            setNetVars(value1, value2);
           }
       }
 file.close();
}

//Ανάλογα με το κλειδί του αρχείου N1, N2, ... Nn, βάλε την τιμή στην αντίστοιχη μεταβλητή ώστε να εμφανιστούν οι
//τιμές στην αρχική σελίδα αφού περάσουν από τον processor.
void setNetVars(String key, String value)
{
 if (key == "N1") SetAP = value;
 else if (key == "N2") AP_SSID = value;
 else if (key == "N3") AP_CHANNEL = value;
 else if (key == "N4") AP_ENCRYPT = value;
 else if (key == "N5") AP_KEY = value;
 else if (key == "N6") SetSTA = value;
 else if (key == "N7") ST_SSID = value;
 else if (key == "N8") ST_KEY = value;
 else if (key == "N9") IP_STATIC = value;
 else if (key == "N10") IP_ADDR = value;
 else if (key == "N11") IP_MASK = value;
 else if (key == "N12") IP_GATE = value;
 else if (key == "N13") IP_DNS = value;
 else if (key == "N14") NTP_TZ = value;
 else if (key == "N15") BROW_TO = value;
 else if (key == "N16") NTP_SRV = value;
 else if (key == "N17") MQTT_SRV = value;
 else if (key == "N18") MQTT_PORT = value;
 else if (key == "N19") MQTT_USER = value;
 else if (key == "N20") MQTT_PASS = value;
 else if (key == "N21") MQTT_CLIENT = value;
 else if (key == "N22") LOG_NAME = value;
 else if (key == "N23") LOG_PASS = value;
}

//Η συνάρτηση δέχεται String με τιμές που είναι τιμές χωρισμένες με κάποιο χαρακτήρα και  
//τις βάζει σε ένα πίνακα ακεραίων
void split(String inp, byte * out, char c)
{
 byte s = 0, idx = 0;
 //Χωρίζει το string σε αριθμούς βάσει του χαρακτήρα c
 for (byte i = 0; i < inp.length(); i++)
     {
      if (inp.substring(i, i+1) == String(c))
         {
          out[idx] = inp.substring(s, i).toInt();
          s = i + 1;
          idx++;
         }
     }
 out[idx] = inp.substring(s, inp.length()).toInt(); //Τελευταίος αριθμός μετά το delimiter
 //print_table(out, idx+1, 'd'); //Debug
}

void chkLogSize()
{
 File file1 = LittleFS.open("/log.csv", "r");
 if(!file1)
    return;
 Serial.print(F("Logfile size: "));
 Serial.println(file1.size());
 file1.close();  
}

void listFS()
{
 Dir dir = LittleFS.openDir(""); //ή "/" για root ή "/update" για καταλόγους
 unsigned long tot = 0;
 while (dir.next ())
       {
        Serial.println(dir.fileName() + "  --->  " + dir.fileSize());
        tot += dir.fileSize();
       }
 Serial.println(tot);
}

void cp(String src, String dest)
{
 String line;
 File f1 = LittleFS.open(src, "r");
 if (!f1) 
        {
         Serial.println(F("Error opening source file"));
         return;
        }
 File f2 = LittleFS.open(dest, "w");
 if (!f2) 
        {
         Serial.println(F("Error opening dest file"));
         return;
        }
 while (f1.available()) 
       {
        line = f1.readStringUntil('\n') + "\n";
        f2.print(line);
       }
 f1.close();
 f2.close();
}
