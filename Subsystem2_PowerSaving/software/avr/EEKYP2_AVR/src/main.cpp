#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <SoftwareSerial.h>
#include <ACS712.h>
#include "definitions.h"
#include "functions.h"
#include "cmd.h"
#include "commands.h"
#include "buttons.h"

ACS712 sensor(ACS712_20A, POWERSENSOR);
double flow;

void setup() 
 {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LINE1, OUTPUT);
  pinMode(LINE2, OUTPUT);
  pinMode(LINE1_LED, OUTPUT);
  pinMode(LINE2_LED, OUTPUT);
  LINE1_OFF();
  LINE2_OFF();
  SetupButtons();
  Serial.begin(9600);
  cmdInit(9600);
  while (!Serial);        //Περίμενε
  Serial.println(F("***** EEKYP - LIGHT AUTOMATION (c)2025 [1o EPAL PREVEZAS - EK PREVEZAS] *****"));
  Serial1.begin(9600);
  //cmdInit(9600);
  sensor.calibrate();
  init_commands(); //Αρχικοποίησε εντολές για την σειριακή γραμμή εντολών
  interval1 = millis();
 }

void loop() 
 {
  but_prog.CheckBP();
  cmdPoll(); //Έλεγξε για εντολή στην κονσόλα
  if ((millis() - interval1) > AQUIRE_MS)
     {
      daylight1 = analogRead(DAYLIGHT1);
      daylight2 = analogRead(DAYLIGHT2);
      daylight1 = map(daylight1, 0, 1023, 0, 100);
      daylight2 = map(daylight2, 0, 1023, 0, 100);
      char tmp[70], current_cstr[6];
      flow = sensor.getCurrentAC();
      if (flow <= .07)
          flow = 0.0;
      dtostrf(flow, 2, 2, current_cstr);
      sprintf(tmp,"s_raw %d %d %s %d %d", daylight1, daylight2, current_cstr, line1_state, line2_state);
      //Serial.println(tmp); //Debug
      if (Serial1.available() == 0)
          Serial1.println(tmp);
      interval1 = millis();
     }
 }
