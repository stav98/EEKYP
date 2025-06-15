#define VERSION                "1.0 beta"

#define RxPin           6 //D6 Software Serial Rx
#define TxPin           7 //D7 Softwate Serial Tx
#define SOIL_MOISTURE1  A0
#define SOIL_MOISTURE2  A1
#define FLOW            2 //D2
#define BUTTON1        11 //D11
#define VALVE1_PIN      9 //D9
#define VALVE2_PIN     10 //D10
#define VALVE1_LED      8 //D8
#define VALVE2_LED     12 //D12

//Ορισμοί χρονιστών λειτουργίας του συστήματος
#define AQUIRE_MS             1000   //Κάθε 1 δευτερόλεπτα (σε msec) διαβάζει αισθητήρες

Servo valve1, valve2;

//Μεταβλητές χρονιστών λειτουργίας
unsigned long interval1; //Κάθε πότε κάνει μέτρηση από αισθητήρες

#define VALVE1LED_ON()     { digitalWrite(VALVE1_LED, HIGH); }
#define VALVE1LED_OFF()    { digitalWrite(VALVE1_LED, LOW); }
#define VALVE2LED_ON()     { digitalWrite(VALVE2_LED, HIGH); }
#define VALVE2LED_OFF()    { digitalWrite(VALVE2_LED, LOW); }

//Μεταβλητές αισθητήρων θερμοκρασίας - υγρασίας
float Tground1, max_Tground1 = 0.0;
float Tground2, max_Tground2 = 0.0;
float Tground1_S = 0.0, Tground2_S = 0.0; //Αθροίσματα τιμών κάθε 1sec
String Tground1_str, Tground2_str;
bool valve1_state, valve2_state;

void VALVE1_ON()
 {
  valve1.attach(VALVE1_PIN);
  delay(300);
  valve1.write(3);
  delay(500);
  valve1_state = true;
  valve1.detach();
  VALVE1LED_ON()
 }

 void VALVE1_OFF()
 {
  valve1.attach(VALVE1_PIN);
  delay(300);
  valve1.write(99);
  delay(500);
  valve1_state = false;
  valve1.detach();
  VALVE1LED_OFF()
 }

 void VALVE2_ON()
 {
  valve2.attach(VALVE2_PIN);
  delay(300);
  valve2.write(0);
  delay(500);
  valve2_state = true;
  valve2.detach();
  VALVE2LED_ON()
 }

 void VALVE2_OFF()
 {
  valve2.attach(VALVE2_PIN);
  delay(300);
  valve2.write(90);
  delay(500);
  valve2_state = false;
  valve2.detach();
  VALVE2LED_OFF()
 }
