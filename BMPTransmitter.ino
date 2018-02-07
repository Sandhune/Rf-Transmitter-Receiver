#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <SFE_BMP180.h>
#include <Wire.h>

RH_ASK driver(2000, 2, 3, 10); // ESP8266 or ESP32: do not use pin 11
SFE_BMP180 pressure;
#define ALTITUDE 1655.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");

          if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }

}

void loop()
{
  char status;
  double T,p0,a,P;

    const char *msg =  "           ";  
           
    dtostrf(ALTITUDE,3,2, msg);
    driver.send((uint8_t *)msg, strlen(msg));     
    driver.waitPacketSent();
    delay(200);
 status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);
      status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Print out the measurement:
       dtostrf(T,3,2, msg);
    driver.send((uint8_t *)msg, strlen(msg));     
    driver.waitPacketSent();
    delay(200);
    status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

       
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          dtostrf(P,3,2, msg);
          driver.send((uint8_t *)msg, strlen(msg));     
          driver.waitPacketSent();
          delay(200);
          
          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          dtostrf(p0,3,2, msg);
          driver.send((uint8_t *)msg, strlen(msg));     
          driver.waitPacketSent();
          delay(200);
          
           a = pressure.altitude(P,p0);
           dtostrf(a,3,2, msg);
          driver.send((uint8_t *)msg, strlen(msg));     
          driver.waitPacketSent();
          delay(200);
                 
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
}
  else Serial.println("error starting temperature measurement\n");

  delay(1000);  // Pause for 5 seconds.
}

