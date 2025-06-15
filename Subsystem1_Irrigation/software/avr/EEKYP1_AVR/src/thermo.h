#include <OneWire.h>
#include <DallasTemperature.h>
//#include <Adafruit_Sensor.h>

//-------------------- Θερμόμετρα One Wire --------------------------
#define OW_PIN1               4  //D4
#define OW_PIN2               5  //D5
#define RESOLUTION            9  //9, 10, 11, 12 bit

#define PERIOD                1000 //Περίοδος μετρήσεων

void printAddress(DeviceAddress);

OneWire ow_temp1(OW_PIN1);
OneWire ow_temp2(OW_PIN2);
DallasTemperature ground_temp1(&ow_temp1);
DallasTemperature ground_temp2(&ow_temp2);
DeviceAddress ground_temp1_addr, ground_temp2_addr;

void init_thermo()
 {
  //Αρχικοποίηση του 1ου θερμομέτρου
  ground_temp1.begin();
  if (!ground_temp1.getAddress(ground_temp1_addr, 0)) 
      Serial.println(F("Unable to find probe 1."));
  else
     {
      Serial.print(F("Found Ground Temp1 probe: "));
      printAddress(ground_temp1_addr);
      Serial.println();
     } 
  ground_temp1.setResolution(ground_temp1_addr, RESOLUTION);
  ground_temp1.setWaitForConversion(false);
  ground_temp1.requestTemperatures();
  
  //Αρχικοποίηση του 2ου θερμομέτρου
  ground_temp2.begin();
  if (!ground_temp2.getAddress(ground_temp2_addr, 0)) 
      Serial.println(F("Unable to find probe 2."));
  else
     {
      Serial.print(F("Found Ground Temp2 probe: "));
      printAddress(ground_temp2_addr);
      Serial.println();
     } 
  ground_temp2.setResolution(ground_temp2_addr, RESOLUTION);
  ground_temp2.setWaitForConversion(false);
  ground_temp2.requestTemperatures();
 }

void printAddress(DeviceAddress deviceAddress)
 {
  for (byte i = 0; i < 8; i++)
      {
       //Βάλε μπροστά '0' αν είναι μικρότερο από 16
       if (deviceAddress[i] < 16) 
           Serial.print("0");
       Serial.print(deviceAddress[i], HEX);
      }
 }