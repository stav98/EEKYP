#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_VEML6075.h>

#define DHTTYPE         DHT11    // DHT 11
#define DHTPIN          12       //D12 Ο αισθητήρας DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp; // I2C Interface
Adafruit_VEML6075 uv = Adafruit_VEML6075();

void init_bmp280()
{
 Serial.println(F("BMP280 test"));
 unsigned status;
 status = bmp.begin(BMP280_ADDRESS_ALT);
 if (!status) 
    {
     Serial.println(F("BMP280 not found!!!"));
    }
 else
    {
     Serial.println(F("BMP280 OK"));
     /* Default settings from datasheet. */
     bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                     Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                     Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                     Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                     Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    }
}

void init_VEML6075()
{
 if (! uv.begin()) 
    {
     Serial.println(F("VEML6075 UV sensor not found!!!"));
     while (1) { delay(100); }
    }
 else
    {
     Serial.println(F("VEML6075 UV sensor OK"));
     // Set the integration constant
     uv.setIntegrationTime(VEML6075_100MS);
     // Get the integration constant and print it!
     Serial.print(F("Integration time set to "));
     switch (uv.getIntegrationTime()) 
            {
             case VEML6075_50MS: Serial.print("50"); break;
             case VEML6075_100MS: Serial.print("100"); break;
             case VEML6075_200MS: Serial.print("200"); break;
             case VEML6075_400MS: Serial.print("400"); break;
             case VEML6075_800MS: Serial.print("800"); break;
            }
     Serial.println("ms");

     // Set the high dynamic mode
     uv.setHighDynamic(true);
     // Get the mode
     if (uv.getHighDynamic()) 
         Serial.println(F("High dynamic reading mode"));
     else 
         Serial.println(F("Normal dynamic reading mode"));
     // Set the mode
     uv.setForcedMode(false);
     // Get the mode
     if (uv.getForcedMode())
         Serial.println(F("Forced reading mode"));
     else 
         Serial.println(F("Continuous reading mode"));

     // Set the calibration coefficients
     uv.setCoefficients(2.22, 1.33,  // UVA_A and UVA_B coefficients
                        2.95, 1.74,  // UVB_C and UVB_D coefficients
                        0.001461, 0.002591); // UVA and UVB responses
    }
}