#define VERSION       "1.00"
#define FOOTER_LOGO   "(c)2025 <a href=\"https://sv6gmp.blogspot.gr\" target=\"_blank\">E.K. PREVEZAS</a>"
#define BUILTIN_LED    2
#define DEBUG_INFO     0 //1 Enable - 0 Disable

//--------------------- Μεταβλητές σύνδεσης στον MQTT broker ---------------------------------------------
const char *mqtt_server;          //Όνομα του mqtt server π.χ. iot.xxxxx.com
int mqtt_port;                    //Πόρτα π.χ. 1883
const char *mqttuser;             //MQTT Username
const char *mqttpass;             //MQTT Password
byte mqtt_state = 0;

//--------------------- Όνομα του Server για να κάνει έλεγχο σύνδεσης ------------------------------------
const char *testhost = "www.google.com";  //Η διεύθυνση για να κάνει έλεγχο σύνδεσης στο διαδίκτυο

//----------------------------- Μεταβλητές ρυθμίσεων λειτουργίας -----------------------------------------
String SetA1_LABL, SetA1_TOPIC, SetA1_ON, SetA1_OFF, 
       SetA2_LABL, SetA2_TOPIC, SetA2_ON, SetA2_OFF,
       SetMQTT_Per;

//-------------------------- Μεταβλητές σύνδεσης μέσω WiFi -----------------------------------------------
String SetAP, AP_SSID, AP_CHANNEL, AP_ENCRYPT, AP_KEY, SetSTA, ST_SSID, ST_KEY, IP_STATIC, IP_ADDR, IP_MASK,
       IP_GATE, IP_DNS, NTP_TZ, BROW_TO, NTP_SRV, MQTT_SRV, MQTT_PORT, MQTT_USER, MQTT_PASS, MQTT_CLIENT, LOG_NAME, LOG_PASS;
String InternAvail = "false", MQTT_State = "false", S_Strength = "";
String search_net_str, num_net_str;
byte scan_state = 0;
int numSsid, status, wifi_strength;
unsigned long lastScanMillis;
bool conn = false;

//------------------------------ Μεταβλητές αισθητήρων ---------------------------------------------------
unsigned short samples = 0; //Πλήθος δειγμάτων κάθε 1sec
float SgrdTherm1 = 0, SgrdTherm2 = 0, SgrdMoist1 = 0, SgrdMoist2 = 0, Sflow = 0; //Αθροίσματα τιμών κάθε 1sec
//byte hour_cnt = 0; //Πλήθος δειγμάτων κάθε 5min

//------------------------- Θερμόμετρα εδάφους, Υγρασιόμετρα, Μέτρηση κατανάλωσης νερού ---------------------
char groundTherm1[10], groundTherm2[10], groundMoist1[10], groundMoist2[10], flow[10];

//-------------------------------------- Μεταβλητές διακοπτών ------------------------------------------------
String Switch1_status, Switch2_status, Switch1_status_pre, Switch2_status_pre; //Οι τιμές αυτές διαβάζονται από τους διακόπτες
String SetSw1, SetSw2; //Οι τιμές που αποθηκεύονται στο αρχείο για επαναφορά μετά από διακοπή ρεύματος

//----------------------------- Χρονιστές και άλλες μεταβλητές ------------------------------------------
unsigned long blink_per; //Ο χρονιστής για το LED
unsigned long tim; //Χρονιστής epoch αν δεν έχει σύνδεση διαδικτύου
unsigned long uptime; //Χρονιστής uptime για έλεγχο συνεχόμενης λειτουργίας
unsigned short led_pat = 0;
