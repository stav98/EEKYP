#define DEBUG_INFO       0  //1 Enable - 0 Disable
#define USE_VEML6075         //Σχολίαστε // για να ενεργοποιηθεί ο αναλογικός αισθητήρας UV
#define VERSION                "1.0 beta"

#define RxPin            6  //D6 Software Serial Rx
#define TxPin            7  //D7 Softwate Serial Tx
//Pin   DHTPIN          12  //D12 Ο αισθητήρας DHT11
//Pin   SDA             A4
//Pin   SCL             A5
#define UV_Pin          A0  //Αναλογικός αισθητήρας UVI
#define IRRAD_Pin       A1  //Φωτοβολταϊκό μέτρησης έντασης της ηλιακής ακτινοβολίας
#define V_LINE_Pin      A2  //Τάση τροφοδοσίας

#define AIR_SPEED        2 //D2  EXT INT
#define RAIN_FALL        3 //D3  EXT INT
#define AIR_DIR_B0       4 //D4
#define AIR_DIR_B1       5 //D5
#define AIR_DIR_B2       8 //D8
#define AIR_DIR_B3       9 //D9
#define AIR_DIR_B4      10 //D10
#define BUTTON1         11 //D11

//Ορισμοί χρονιστών λειτουργίας του συστήματος
#define AQUIRE_MS             1000   //Κάθε 1 δευτερόλεπτα (σε msec) διαβάζει αισθητήρες
#define QUANT                 5 / 1024 //Vref / 10bit ADC
#define R1                    5.6  //5K6
#define R2                    1.2  //1K2
#define DIV_RATIO             (R1 + R2) / R2
//Μεταβλητές χρονιστών λειτουργίας
unsigned long interval1; //Κάθε πότε κάνει μέτρηση από αισθητήρες

//Μεταβλητές αισθητήρων φωτεινότητας
//unsigned int daylight1, daylight2;
//float Tground1_S = 0.0, Tground2_S = 0.0; //Αθροίσματα τιμών κάθε 1sec


