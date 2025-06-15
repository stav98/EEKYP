#include "cmd.h"

void init_commands(void);
void printErr1(void);
void printErr2(void);
void s_raw(int, char**);
void soft_reset(int, char**);
void list_wifi(int, char**);
void get_ip(int, char**);
void ls(int, char**);
void cat(int, char**);
void df(int, char**);
void print_version(int, char **);
void free(int, char **);
void defaults(int, char **);
void help(int, char**);

//Οι εντολές όπως δίνονται από το τερματικό
const char \
   //        1         |           2         |         3            |         4            |          5          |
   ct01[] = "s_raw"    , ct02[] = "rst"      , ct03[] = "listwifi"  , ct04[] = "ip"        , ct05[] = "ls"       , 
   ct06[] = "cat"      , ct07[] = "df"       , ct08[] = "vers"      , ct09[] = "free"      , ct10[] = "defaults" ,
   ct11[] = "?"        ;

//Δομή συνδεδεμένης λίστας [όνομα εντολής στο τερματικό, όνομα κλήσης, επόμενη εντολή στην λίστα]
const L_cmd  cmd11 = {(char*) ct11   , help,             NULL}; //? Παρουσίασε εντολές
const L_cmd  cmd10 = {(char*) ct10   , defaults,       &cmd11}; //Αρχικές ρυθμίσεις
const L_cmd  cmd09 = {(char*) ct09   , free,           &cmd10}; //Εμφανίζει ελεύθερη μνήμη RAM
const L_cmd  cmd08 = {(char*) ct08   , print_version,  &cmd09}; //Εμφανίζει αριθμό έκδοσης FW
const L_cmd  cmd07 = {(char*) ct07   , df,             &cmd08}; //Εμφανίζει χώρο (ελεύθερο - δεσμευμένο στο FS)
const L_cmd  cmd06 = {(char*) ct06   , cat,            &cmd07}; //Εμφανίζει το περιεχόμενο αρχείου
const L_cmd  cmd05 = {(char*) ct05   , ls,             &cmd06}; //List files
const L_cmd  cmd04 = {(char*) ct04   , get_ip,         &cmd05}; //Εμφανίζει την διεύθυνση IP
const L_cmd  cmd03 = {(char*) ct03   , list_wifi,      &cmd04}; //Εμφανίζει τα διαθέσιμα δίκτυα WiFi
const L_cmd  cmd02 = {(char*) ct02   , soft_reset,     &cmd03}; //Κάνει reset
const L_cmd  cmd01 = {(char*) ct01   , s_raw,          &cmd02}; //Εμφάνισε κατάσταση αισθητήρων

//Αρχικοποίηση εντολών
void init_commands(void)
{
 cmd_tbl = (L_cmd*) &cmd01;
}

//Μήνυμα λάθους για λιγότερα ορίσματα
void printErr1()
{
 Serial.println(F("Too few arguments"));
}

//Μήνυμα λάθους σύνταξης της εντολής
void printErr2()
{
 Serial.println(F("Syntax error"));
}

//Η εντολή έρχεται από τον expander σε τακτά χρονικά διαστήματα συνήθως 1sec και περιέχει τις τιμές των αισθητήρων
//Οι τιμές αντιγράφονται στις αντίστοιχες μεταβλητές
void s_raw(int arg_cnt, char **args)
{
 static float airSpeedAVG = 0;
 int adcIrr, Pirr;
 float voltsIrr, p;
 float q = 5.0 / 1024;
 if (arg_cnt > 10)
    {
     strcpy(Therm1, (char*) args[1]);
     strcpy(Pressure, (char*) args[2]);
     strcpy(Humidity, (char*) args[3]);
     //strcpy(AirSpeed, (char*) args[4]);
     airSpeedAVG = (2 * airSpeedAVG + atoi(args[4])) / 3; //AVG της ταχύτητας αέρα
     dtostrf(airSpeedAVG, 2, 1, AirSpeed);
     strcpy(AirDir, (char*) args[5]);
     strcpy(RainP, (char*) args[6]);
     strcpy(UVI, (char*) args[7]);
     strcpy(Therm2, (char*) args[8]);
     //strcpy(Irrad, (char*) args[9]);
     adcIrr = atoi(args[9]); //Υπολογισμός Irradiation
     voltsIrr = adcIrr * q;
     p = voltsIrr * voltsIrr / 100; //P = V^2 / R (100Ω)
     p = p * 1111.11 * 100 / 3.5; //Συντελεστής εμβαδού 1m^2 / (3x3cm)  - 3.5 βαθμός απόδοσης
     Pirr = (int) p;
     Irrad = String(Pirr);
     strcpy(Vline, (char*) args[10]); //Τάση γραμμής 9-25V
     if (String(Pressure) == "NAN" || atoi(Pressure) < 950) //Αν η πίεση είναι 0 ή NAN να γίνει 950
         strcpy(Pressure, "950");
     //Για υπολογισμό Μέσων τιμών πενταλέπτου για MQTT
     STherm1 += atof(Therm1);
     SPressure += atof(Pressure);
     SHumidity += atof(Humidity);
     SAirSpeed += atof(AirSpeed);
     SAirDir = atoi(AirDir); //SAirDir += atoi(AirDir);
     SRainH += atoi(RainP);
     SUVI += atof(UVI);
     STherm2 += atof(Therm2);
     SIrrad += Pirr;
     SVline += atof(Vline);
     samples++;
    }
 else
     printErr1();
}

//Επανεκκίνηση του ESP8266
void soft_reset(int arg_cnt, char **args)
{
   //ESP.restart();
   os_timer_setfn(&restartDelay, &rst, NULL);
   os_timer_arm(&restartDelay, 500, false); //Μετά από 0,5sec κάνε reset
}

//Εμφανίζει λίστα των διαθέσιμων δικτύων wifi στο τερματικό
void list_wifi(int arg_cnt, char **args)
{
 int numSsid = WiFi.scanNetworks(false, true); //Async = όχι, Δείξε τα κρυφά
 while (numSsid == -1) 
       {
        Serial.println("Couldn't get a wifi connection");
        delay(5000);
        numSsid = WiFi.scanNetworks();
       }
 //Εμφανίζει μια λίστα με τα διαθέσιμα δίκτυα
 Serial.print(F("Αριθμός ανιχνεύσιμων δικτύων:"));
 Serial.println(numSsid);
 //Εμφάνισε Α/Α και όνομα δικτύου με το σήμα και την κρυπτογράφηση
 for (int thisNet = 0; thisNet < numSsid; thisNet++) 
     {
      Serial.print(thisNet + 1);
      Serial.print(") ");
      Serial.print(WiFi.SSID(thisNet));
      if (WiFi.SSID(thisNet).length() < 13)
          Serial.print("\t");
      Serial.print("\t\tSignal: ");
      Serial.print(WiFi.RSSI(thisNet));
      Serial.print(" dBm");
      Serial.print("\tEncryption: ");
      Serial.println(getEncryptionType(WiFi.encryptionType(thisNet)));
     }
}

//Εμφανίζει την τρέχουσα διεύθυνση IP
void get_ip(int arg_cnt, char **args)
{
 Serial.println(WiFi.localIP());
}

//Εμφανίζει τα αρχεία στο Filesystem
void ls(int arg_cnt, char **args)
{
 listFS();
}

//Εμφανίζει το περιεχόμενο ενός αρχείου κειμένου
void cat(int arg_cnt, char **args)
{
 if (arg_cnt > 1)
    {
     String buffer;
     File file = LittleFS.open(args[1], "r");
     //Αν το αρχείο δεν υπάρχει
     if (!file) 
        {
         Serial.println(F("File not found."));
        }
     else
        {
         while (file.available()) 
               {
                buffer = file.readStringUntil('\n');
                Serial.println(buffer); //Debug  
               }
        }
    file.close();
    }
 else
     printErr1();
}

//Πληροφορίες του συστήματος αρχείων
void df(int arg_cnt, char **args)
{
 FSInfo fs_info;
 LittleFS.info(fs_info);
 float fileTotalKB = (float)fs_info.totalBytes / 1024.0; 
 float fileUsedKB = (float)fs_info.usedBytes / 1024.0; 
 char tmp[40];
 sprintf(tmp, "Used %.1fKb of total %.1fKb", fileUsedKB, fileTotalKB);
 Serial.println(tmp);
}

//Έκδοση FW
void print_version(int arg_cnt, char **args)
{
 Serial.print(F("Version: "));
 Serial.println(VERSION);
}

//Εμφανίζει ελεύθερη διαθέσιμη μνήμη RAM
void free(int arg_cnt, char **args)
{
 Serial.print(F("Free RAM: "));
 Serial.print(system_get_free_heap_size());
 Serial.println(F(" bytes"));
}

//Σβήνει τα αρχεία ρυθμίσεων και επανέρχεται στις αρχικές προκαθορισμένες ρυθμίσεις
void defaults(int arg_cnt, char **args)
{
 Serial.println(F("--- Loading Defaults ... ---")); //Debug
 LittleFS.remove("/settings.txt");
 LittleFS.remove("/settings_wp.txt");
 LittleFS.remove("/settings_net.txt");
 ESP.restart();
}

//Όλες οι εντολές - Βοήθεια
void help(int arg_cnt, char **args)
{
 char buf[10];
 L_cmd *cmd_entry;
 for (cmd_entry = cmd_tbl; cmd_entry != NULL; cmd_entry = (L_cmd*) cmd_entry->next)
     {
      strcpy(buf, (char*) cmd_entry->cmd);
      Serial.println(buf);
     }
}
