#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

 RH_ASK driver(2000, 2, 3, 10); // (Speed,rec pin,trans pin,ptt)  
 int j = 0;
void setup()
{
  
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
        
}

void loop()
{
  int D = 0;
  
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
  
String str = "";

for(int i = 0; i < buflen; i++){
  str += (char)buf[i];
  
}
j++;
if(j == 1){
 Serial.print("provided altitude: ");
Serial.print(str);
   Serial.print(" meters");
   Serial.print( "");
  Serial.println();
}
if(j == 2){
 Serial.print("temperature: ");
Serial.print(str);
   Serial.print(" deg C");
    Serial.print("" );
  Serial.println();
}
if(j == 3){
 Serial.print("absolute pressure ");
Serial.print(str);
   Serial.print(" mb");
    Serial.print("" );
  Serial.println();
}
if(j == 4){
 Serial.print("relative (sea-level) pressure: ");
Serial.print(str);
   Serial.print(" mb");
    Serial.print( "");
  Serial.println();
}
if(j == 5){
 Serial.print("computed altitude: ");
Serial.print(str);
   Serial.print(" meters");
    Serial.print("" );
  Serial.println();
   }
  
if(j == 5){
  Serial.print( j);
   Serial.println();
    
  j = 0;
  }

}

}
