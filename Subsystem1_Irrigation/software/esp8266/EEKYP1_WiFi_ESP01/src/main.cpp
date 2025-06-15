#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#include <Arduino.h>
#include <PubSubClient.h>
#include <LittleFS.h>
#include "definitions.h"
#include "functions.h"
#include "network.h"
#include "commands.h"

//Ορισμός Timer
static os_timer_t intervalTimer;
static os_timer_t mqttTimer;

byte five_secs;    //Μετρητής σε sec που μετράει αντίστροφα μέχρι το 0.
unsigned long interval = 0;

void setup() 
{
 pinMode(BUILTIN_LED, OUTPUT); //pin 2
 Serial.begin(9600);
 delay(200);
 #if DEBUG_INFO
 Serial.println(F("\n\nEEKYP Irigation WiFi Module (c)2025 Stavros S. Fotoglou"));
 #endif
 //Προετοιμασία συστήματος αρχείων 256 Kbyte
 if (!LittleFS.begin()) 
    {
     #if DEBUG_INFO
     Serial.println(F("LittleFS initialisation failed!"));
     #endif
     while (1) yield(); // Stay here twiddling thumbs waiting
    }
 #if DEBUG_INFO
 Serial.println(F("\r\nLittleFS available!"));
 #endif
 LittleFS.begin();
 //Αν ξεκίνησε το σύστημα αρχείων στην εσωτερική Flash 4Mbyte
 //Εμφάνισε ελεύθερο χώρο από το σύστημα LittleFS
 FSInfo fs_info;
 LittleFS.info(fs_info);
 float fileTotalKB = (float)fs_info.totalBytes / 1024.0; 
 float fileUsedKB = (float)fs_info.usedBytes / 1024.0; 
 char tmp[40];
 sprintf(tmp, "Used %.1fKb of total %.1fKb", fileUsedKB, fileTotalKB);
 #if DEBUG_INFO
 Serial.println(tmp);
 #endif
 readSettings_net(); //Διάβασε ρυθμίσεις δικτύου από αρχείο
 //Ρουτίνα εξυπηρέτησης αν γίνει σύνδεση TCP με τον server π.χ. www.google.com 
 test_client->onConnect(&onConnect, test_client); //Στο network.h
 led_pat = 0b1000000000; //Αρχική κατάσταση
 initNetwork();  //Αρχικοποίηση δικτύου WiFi, IP, NTP και WebServer
 
 blink_per = millis();
 readSettings_wp(); //Διάβασε ρυθμίσεις λειτουργίας όπως ενέργειες βάσει των τιμών των αισθητήρων
 //Αρχική σύνδεση στον mqtt broker
 reconnect();
 five_secs = 5; //Κάθε 5 δευτερόλεπτα
 init_commands(); //Αρχικοποίησε εντολές για την σειριακή γραμμή εντολών
 //Κάθε 30 sec κάνε έλεγχο σύνδεσης
 os_timer_disarm(&intervalTimer); //Απενεργοποίηση Timer
 os_timer_setfn(&intervalTimer, &testcon, NULL); //Ορισμός ρουτίνας εξυπηρέτησης χωρίς ορίσματα στο network.h
 os_timer_arm(&intervalTimer, 30000, true);  //Ενεργοποίηση με επανάληψη κλήσης κάθε 30 sec
 //Κάθε 5 min κάνε έλεγχο σύνδεσης στον mqtt broker
 os_timer_disarm(&mqttTimer); //Απενεργοποίηση Timer
 os_timer_setfn(&mqttTimer, &pubmqtt, NULL); //Ορισμός ρουτίνας εξυπηρέτησης χωρίς ορίσματα στο network.h
 os_timer_arm(&mqttTimer, 60000, true);  //Ενεργοποίηση με επανάληψη κλήσης ώστε να κάνει έλεγχο κάθε 1 λεπτό
 cmdInit(115200); //Η παράμετρος δεν λαμβάνεται υπόψη γιατί έχει οριστεί στην αρχή
 Switch1_status = Switch2_status = Switch1_status_pre = Switch2_status_pre = "IsOff";
 readSettings(); //Διάβασε ρυθμίσεις αρχικής οθόνης από LittleFS και θέσε τις μεταβλητές λειτουργίας
}

void loop() 
{
 if (InternAvail == "true")
     timeClient.update(); //Όταν φτάσει η στιγμή ανανέωσε την ώρα από τον NTP Server
 blink_led(BUILTIN_LED);
 cmdPoll();
 //===================== Κάθε 1 sec επανάλαβε =====================================
 if ((millis() - interval) >= 1000)
    {
     interval = millis();
     tim += 1; //Ενημέρωσε το epoch time κατά 1 sec αν δεν λειτουργεί το NTP
     uptime += 1; //Ενημέρωσε το uptime κατά 1 sec
     //Serial.printf("Time: %02d:%02d:%02d\n", hour(tim)+2, minute(tim), second(tim)); //Debug Εμφάνισε ώρα από epoch local
     //Αν πέρασαν 5 δευτερόλεπτα μέτρησε την ένταση του σήματος
     if (five_secs < 1)
        {
         five_secs = 5; //Φόρτωσε πάλι την τιμή για τον επόμενο κύκλο
         if (WiFi.status() == WL_CONNECTED)
             S_Strength = String(WiFi.RSSI()) + "dBm";
         else
             S_Strength = "";
        }
     else
         five_secs--;
    }
 //===================================================================================================
   
 //Αναζήτηση δικτύων wifi ασύγχρονο για την list_wifi_web()
 if (scan_state == 1)
    {
     if (millis() - lastScanMillis > 10000)
        {
         WiFi.scanNetworks(true, true); //Async = ναι, Δείξε τα κρυφά
         //Serial.print("\nScan start ... ");
         lastScanMillis = millis();
        }
     scan_state = 2;
    }
   
 //Αν υπάρχει σύνδεση στο διαδίκτυο τότε
 if (InternAvail == "true")
    {
     if (!client.connected()) //Αν δεν έχει συνδεθεί στον mqtt broker
         reconnect();         //Προσπάθησε να κάνεις σύνδεση
     if (client.connected())  //Αν υπάρχει σύνδεση στον broker
         client.loop();       //Έλεγξε για μηνύματα
    }
}
