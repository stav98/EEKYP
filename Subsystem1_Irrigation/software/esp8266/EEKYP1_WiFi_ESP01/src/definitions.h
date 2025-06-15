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
       SetA2_LABL, SetA2_TOPIC, SetA2_ON, SetA2_OFF;

//-------------------------- Μεταβλητές σύνδεσης μέσω WiFi -----------------------------------------------
String SetAP, AP_SSID, AP_CHANNEL, AP_ENCRYPT, AP_KEY, SetSTA, ST_SSID, ST_KEY, IP_STATIC, IP_ADDR, IP_MASK,
       IP_GATE, IP_DNS, NTP_TZ, BROW_TO, NTP_SRV, MQTT_SRV, MQTT_PORT, MQTT_USER, MQTT_PASS, MQTT_CLIENT, LOG_NAME, LOG_PASS;
String InternAvail = "false", MQTT_State = "false", S_Strength = "";
String search_net_str, num_net_str;
byte scan_state = 0;
int numSsid, status;
unsigned long lastScanMillis;
bool conn = false;

//------------------------------ Μεταβλητές αισθητήρων ---------------------------------------------------
//unsigned short adcval;
//short cur_Irrad, cur_Irrad_avg = 0, max_Irrad = -50;
//char cur_Irrad_str[6];
//float t_ext, t_int, max_t_ext = -40.0, max_t_int = -40.0, min_t_ext = 100.0, min_t_int = 100.0;
//float dht_temp = 0.0;
//char dht_temp_str[6];
//float humidity = 0.0, humWet = 0.0, max_humidity = -10.0, min_humidity = 200.0;
//char hum_str[6]; //Εδώ αποθηκεύει την τιμή της υγρασίας
//char wet_str[6];
//char max_t_ext_timestamp[35], min_t_ext_timestamp[35], max_t_int_timestamp[35], min_t_int_timestamp[35], max_Irrad_timestamp[42], max_Humidity_timestamp[35], min_Humidity_timestamp[35];
//float T_int_S = 0, T_ext_S = 0, dht_temp_S = 0, humidity_S = 0; //Αθροίσματα τιμών κάθε 1sec
//float T_int_SHr = 0, T_ext_SHr = 0, humidity_SHr = 0, dht_temp_SHr = 0; //Αθροίσματα τιμών κάθε 5min
//unsigned long Irrad_S = 0; //Άθροισμα τιμών ηλιοφάνειας κάθε 1sec
//unsigned short Irrad_SHr = 0; //Άθροισμα ηλιοφάνειας κάθε 5min
unsigned short samples = 0; //Πλήθος δειγμάτων κάθε 1sec
float SgrdTherm1 = 0, SgrdTherm2 = 0, SgrdMoist1 = 0, SgrdMoist2 = 0, Sflow = 0; //Αθροίσματα τιμών κάθε 1sec
//byte hour_cnt = 0; //Πλήθος δειγμάτων κάθε 5min

//------------------------- Θερμόμετρα εδάφους, Υγρασιόμετρα, Μέτρηση κατανάλωσης νερού ---------------------
char groundTherm1[10], groundTherm2[10], groundMoist1[10], groundMoist2[10], flow[10];

//-------------------------------------- Μεταβλητές βαλβίδων ------------------------------------------------
String Switch1_status, Switch2_status, Switch1_status_pre, Switch2_status_pre; //Οι τιμές αυτές διαβάζονται από τους διακόπτες
String SetSw1, SetSw2; //Οι τιμές που αποθηκεύονται στο αρχείο για επαναφορά μετά από διακοπή ρεύματος
//bool sw1_pre = false, sw2_pre = false; //Προηγούμενες τιμές 

//----------------------------- Χρονιστές και άλλες μεταβλητές ------------------------------------------
unsigned long blink_per; //Ο χρονιστής για το LED
unsigned long tim; //Χρονιστής epoch αν δεν έχει σύνδεση διαδικτύου
unsigned long uptime; //Χρονιστής uptime για έλεγχο συνεχόμενης λειτουργίας
//float LoopTime; //Ο χρόνος ελέγχου και δράσης π.χ. κάθε 10', παίρνει τιμή από το String SetLoopTime.
//unsigned short time2next; //Μετρητής σε sec που μετράει αντίστροφα μέχρι το 0. Γίνεται set από το LoopTime.
//unsigned short max_win_time; //Ο χρόνος που χρειάζεται να τερματίσει την διαδρομή, παίρνει τιμή από το String FullOpenTime
//unsigned short win_time; //Μετρητής ανά sec ο οποίος μετράει την διάρκεια της διαδρομής για άνοιγμα ή κλείσιμο.
//String win_state = "unknown"; //Η εντολή που δίνεται για να ανοίξει ή να κλείσει
//String cur_win_state = "unknown"; //Η τρέχουσα θέση της κουρτίνας
//byte open_percent = 0; //Τρέχων συνολικό ποσοστό μαζέματος
unsigned short led_pat = 0;
