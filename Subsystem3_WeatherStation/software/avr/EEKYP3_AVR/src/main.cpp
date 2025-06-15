#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <SoftwareSerial.h>

#include "definitions.h"
#include "sensors.h"
#include "functions.h"
#include "cmd.h"
#include "commands.h"
#include "buttons.h"

unsigned long airp, rainp;
int UVanalog_val, air_dir, irradiation;
float UVsensor_val, pressure, temp1, temp2, humidity, air_speed, Vline;

//I.S.R. 1
void air_pulse () // Interrupt function
 {
  noInterrupts();
  airp++;
  interrupts();
 }

//I.S.R. 2
void rain_pulse () // Interrupt function
 {
  noInterrupts();
  rainp++;
  interrupts();
 }

void setup() 
 {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(AIR_SPEED, INPUT_PULLUP);
  pinMode(RAIN_FALL, INPUT_PULLUP);
  pinMode(AIR_DIR_B0, INPUT);
  pinMode(AIR_DIR_B1, INPUT);
  pinMode(AIR_DIR_B2, INPUT);
  pinMode(AIR_DIR_B3, INPUT);
  pinMode(AIR_DIR_B4, INPUT);
  SetupButtons();
  Serial.begin(9600);
  cmdInit(9600);
  while (!Serial);        //Περίμενε
  Serial.println(F("***** EEKYP - WEATHER STATION (c)2025 [1o EPAL PREVEZAS - EK PREVEZAS] *****"));
  Serial1.begin(9600);
  dht.begin(); //Αρχικοποίησε το DHT11
  init_bmp280(); //Αρχικοποίησε το BMP280
  #ifdef USE_VEML6075
  init_VEML6075();
  #endif
  attachInterrupt(0, air_pulse, RISING);
  attachInterrupt(1, rain_pulse, FALLING);
  init_commands(); //Αρχικοποίησε εντολές για την σειριακή γραμμή εντολών
  interval1 = millis();
 }

void loop() 
 {
  but_prog.CheckBP();
  cmdPoll(); //Έλεγξε για εντολή στην κονσόλα
  
  if ((millis() - interval1) > AQUIRE_MS)
     {
      //Υπολογισμός δείκτη UV  
      #ifndef USE_VEML6075 //Αναλογικός αισθητήρας
      UVanalog_val = analogRead(UV_Pin); //Διάβασε αναλογική τιμή
      //Serial.println(UVanalog_val);
      if (UVanalog_val < 20) 
          UVsensor_val = 0;
      else
          UVsensor_val = 0.05 * UVanalog_val - 1;
      #else
      UVsensor_val = uv.readUVI(); //Ψηφιακός αισθητήρας IIC VEML6075
      #endif
      //Υπολογισμός ταχύτητας ανέμου
      air_speed = (float)airp;
      airp = 0;
      //Διάβασμα ύψους βροχής
      //Είναι οι παλμοί rainp
      //Διάβασμα θερμοκρασίας 1 από το BMP280
      temp1 = bmp.readTemperature();
      //Διάβασμα ατμοσφαιρικής πίεσης από το BMP280
      pressure = bmp.readPressure() / 100; //Διαίρεση με 100 επειδή ο αισθητήρας μετράει σε Pascal
      //Διάβασμα υγρασίας από το DHT11
      humidity = dht.readHumidity();
      //Διάβασμα θερμοκρασίας 2 από το DHT11
      temp2 = dht.readTemperature(); //default σε °C
      temp2 -= 2.5;
      //Διάβασμα κατεύθυνσης ανέμου
      air_dir = readAirVane();
      //Υπολογισμός τάσης γραμμής
      Vline = analogRead(V_LINE_Pin) * (float) QUANT * DIV_RATIO * 1.025; //Συντελεστής διόρθωσης το 1.025
      //Διάβασμα ηλιακής ακτινοβολίας
      irradiation = analogRead(IRRAD_Pin); //Στέλνει ακέραια τιμή του ADC, ο υπολογισμός γίνεται στο ESP
      
      #if DEBUG_INFO
      Serial.println(F("========================================"));
      Serial.print(F("UV Index: ")); Serial.println(UVsensor_val);
      Serial.print(F("Air speed = ")); Serial.println(air_speed);
      Serial.print(F("Rain pulses = ")); Serial.println(rainp);
      Serial.print(F("Temper1 = ")); Serial.print(temp1); Serial.println(" °C");
      Serial.print(F("Pressure = ")); Serial.print(pressure); Serial.println(" hPa");
      Serial.print(F("Humidity = ")); Serial.print(humidity); Serial.println(" %");
      Serial.print(F("Temper2 = ")); Serial.print(temp2); Serial.println(" °C");
      Serial.print(F("Air angle = ")); Serial.println(air_dir);
      Serial.print(F("Vline: ")); Serial.println(Vline);
      #endif

      //Προετοιμασία μηνύματος με τιμές χωρισμένες με κενά
      char tmp[70], air_speed_cstr[6], temp1_cstr[6], temp2_cstr[6], pressure_cstr[8], humidity_cstr[6], vline_cstr[5], uvidx_cstr[5];
      dtostrf(air_speed, 2, 1, air_speed_cstr); dtostrf(temp1, 2, 1, temp1_cstr);
      dtostrf(temp2, 2, 1, temp2_cstr); dtostrf(pressure, 4, 1, pressure_cstr); dtostrf(humidity, 2, 1, humidity_cstr);
      dtostrf(Vline, 2, 1, vline_cstr); dtostrf(UVsensor_val, 2, 1, uvidx_cstr);
      sprintf(tmp,"s_raw %s %s %s %s %d %ld %s %s %d %s", temp1_cstr, pressure_cstr, humidity_cstr, air_speed_cstr, air_dir, rainp, uvidx_cstr, temp2_cstr, irradiation, vline_cstr);
      //Serial.println(tmp); //Debug
      
      if (Serial1.available() == 0)
          Serial1.println(tmp);
      interval1 = millis();
     }
 }
