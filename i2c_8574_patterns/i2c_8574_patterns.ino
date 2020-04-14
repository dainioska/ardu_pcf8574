//Arduino(UNO/Nano)over I2C communication to PCF8574 example
#include <Wire.h>

//Array of patterns version "bin"
//int datArray[8]={B11111110, B11111101, B11111011, B11110111, B11101111, B11011111, B10111111, B01111111};
//Array of patterns  version "hex"
int datArray[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{

for(int i =0; i<8; i++)     //init parallel sequence of patterns from array at first and second chips PCF8574
{  
Wire.beginTransmission(0x27);  //first chip PCF8574 I2C address 27
Wire.write(datArray[i]);
Wire.endTransmission();
Serial.print("Pattern FIRST: ");
Serial.println(i);

Wire.beginTransmission(0x21);  //second chip PCF8574 I2C address 21
Wire.write(datArray[i]);
Wire.endTransmission();
Serial.print("Pattern SECOND: ");
Serial.println(i);

delay(500);  
}
Wire.beginTransmission(0x27);  //reset pattern(FF) 
Wire.write(0xFF);
Wire.endTransmission();
Wire.beginTransmission(0x21);  //reset pattern(FF) 
Wire.write(0xFF);
Wire.endTransmission();
}
