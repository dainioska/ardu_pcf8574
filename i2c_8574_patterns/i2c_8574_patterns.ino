//Arduino(UNO/Nano)over I2C communication to PCF8574 example
//how to use millis() and class TimeOut_I2C example(2020-04-19)
//
#include <Wire.h>

class TimeOut
{
  long OnTime;    //time selected pin"On"
  long OffTime;   //time selected pin"Off"
  int pinState;
  unsigned long prevMillis;
  
  int i=0;
  //Array of patterns (hex)
  const int datArray[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};

public:
TimeOut(long on, long off)   //init constructor
{ 
  OnTime = on;
  OffTime = off;
  pinState =LOW;
  prevMillis = 0;
}

void Update()
{
  unsigned long currentMillis = millis(); 
  if((pinState == HIGH) && (currentMillis -prevMillis >= OnTime))
  {
    pinState = LOW;
    prevMillis = currentMillis;  
    Wire.beginTransmission(0x27); 
    Wire.write(0xFF); 
    Wire.endTransmission();
  }
  else if((pinState ==LOW) && (currentMillis -prevMillis >= OffTime))
  {
    pinState = HIGH;
    prevMillis = currentMillis;
    if(i < 8)
    { 
    Wire.beginTransmission(0x27); 
    Wire.write(datArray[i]); 
    Wire.endTransmission();
    i++;
    }
    else
    {
      i =0;
    }   
  }    
 }
};

 TimeOut patternsH(1000, 5000);   //class instance ( HIGH timeout(milisec.) ,LOW timeout(milisec.))

void setup() {
  Serial.begin(9600);
  Wire.begin();  
  Wire.beginTransmission(0x27);  //setup port 27(hex)
  Wire.write(0xFF);              //reset all pins
  Wire.endTransmission();
  delay(2000);
}

void loop() {
 patternsH.Update();

}
