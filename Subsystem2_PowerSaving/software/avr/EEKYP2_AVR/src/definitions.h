#define VERSION                "1.0 beta"

#define RxPin           6 //D6 Software Serial Rx
#define TxPin           7 //D7 Softwate Serial Tx
#define DAYLIGHT1       A0
#define DAYLIGHT2       A1
#define POWERSENSOR     A2
#define BUTTON1        11 //D11
#define LINE1           4 //D4
#define LINE2           5 //D5
#define LINE1_LED       8 //D8
#define LINE2_LED      12 //D12

//Ορισμοί χρονιστών λειτουργίας του συστήματος
#define AQUIRE_MS             1000   //Κάθε 1 δευτερόλεπτα (σε msec) διαβάζει αισθητήρες

//Μεταβλητές χρονιστών λειτουργίας
unsigned long interval1; //Κάθε πότε κάνει μέτρηση από αισθητήρες

//Μεταβλητές αισθητήρων φωτεινότητας
unsigned int daylight1, daylight2;
//float Tground1_S = 0.0, Tground2_S = 0.0; //Αθροίσματα τιμών κάθε 1sec
bool line1_state, line2_state;

#define LINE1_ON()     { digitalWrite(LINE1, LOW); digitalWrite(LINE1_LED, HIGH); line1_state = true;}
#define LINE1_OFF()    { digitalWrite(LINE1, HIGH); digitalWrite(LINE1_LED, LOW); line1_state = false;}
#define LINE2_ON()     { digitalWrite(LINE2, LOW); digitalWrite(LINE2_LED, HIGH); line2_state = true;}
#define LINE2_OFF()    { digitalWrite(LINE2, HIGH); digitalWrite(LINE2_LED, LOW); line2_state = false;}
