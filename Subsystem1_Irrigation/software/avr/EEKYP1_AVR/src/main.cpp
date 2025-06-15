#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
//#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "definitions.h"
#include "thermo.h"
#include "functions.h"
#include "cmd.h"
#include "commands.h"
#include "buttons.h"

unsigned long pulse_freq;
double flow;
unsigned int moist1, moist2;
float fmoist1, fmoist2;

//I.S.R.
void pulse () // Interrupt function
 {
  pulse_freq++;
 }

void setup() 
 {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(FLOW, INPUT);
  pinMode(VALVE1_LED, OUTPUT);
  pinMode(VALVE2_LED, OUTPUT);
  SetupButtons();
  Serial.begin(9600);
  cmdInit(9600);
  while (!Serial);        //Περίμενε
  Serial.println(F("***** EEKYP - IRIGATION (c)2025 [EK PREVEZAS] *****"));
  init_thermo();  //Αρχικοποίηση θερμομέτρων 1-wire
  Serial1.begin(9600);
  //cmdInit(9600);
  init_commands(); //Αρχικοποίησε εντολές για την σειριακή γραμμή εντολών
  VALVE1_OFF();
  VALVE2_OFF();
  attachInterrupt(0, pulse, RISING);
  interval1 = millis();
 }

void loop() 
 {
  but_prog.CheckBP();
  cmdPoll(); //Έλεγξε για εντολή στην κονσόλα
  /*if (Serial1.available())
     Serial.write(Serial1.read());
 
  if (Serial.available())
      Serial1.write(Serial.read());
  */

  if ((millis() - interval1) > AQUIRE_MS)
     {
      ReadSensors();
      flow = (pulse_freq / 7.5); //Λίτρα / λεπτό 
      pulse_freq = 0;
      moist1 = analogRead(SOIL_MOISTURE1); //<200 μέσα στο νερό, 270-400 οκ, 800 νωπό, 950 και πανω θέλει πότισμα 
      moist2 = analogRead(SOIL_MOISTURE2);
      //Serial.println(moist1);
      fmoist1 = fmap(moist1, 1023, 250, 0, 10);
      fmoist2 = fmap(moist2, 1023, 250, 0, 10);
      char tmp[70], moist1_cstr[6], moist2_cstr[6], flow_str[6];
      dtostrf(fmoist1, 2, 1, moist1_cstr);
      dtostrf(fmoist2, 2, 1, moist2_cstr);  
      dtostrf(flow, 4, 2, flow_str);
      sprintf(tmp,"s_raw %s %s %s %s %s %d %d", Tground1_str.c_str(), Tground2_str.c_str(), moist1_cstr, moist2_cstr, flow_str, valve1_state, valve2_state);
      //Serial.println(tmp); //Debug
      //Serial.println(pulse_freq);
      //Serial.println(flow);
      if (Serial1.available() == 0)
          Serial1.println(tmp);
      interval1 = millis();
     }
 }
