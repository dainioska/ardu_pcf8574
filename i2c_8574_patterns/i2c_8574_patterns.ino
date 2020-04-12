//Arduino(UNO/Nano)over I2C communication to PCF8574 example

#include <Wire.h>

// second chip PCF8574 I2C address

//Array of patterns
int datArray[8]={B11111110, B11111101, B11111011, B11110111, B11101111, B11011111, B10111111, B01111111};

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{

for(int i =0; i<8; i++)     //init sequence of patterns from array at first chip PCF8574
{  
Wire.beginTransmission(0x27);  //first chip PCF8574 I2C address 27
Wire.write(datArray[i]);
Wire.endTransmission();
Serial.print("Pattern: ");
Serial.println(i);
delay(500);  
}
Wire.beginTransmission(0x27);  //reset pattern(FF)
Wire.write(B11111111);
Wire.endTransmission();

for(int i =0; i<8; i++)     //init sequence of patterns from array at second chip PCF8574
{  
Wire.beginTransmission(0x21);  // second chip PCF8574 I2C address 21
Wire.write(datArray[i]);
Wire.endTransmission();
Serial.print("Pattern: ");
Serial.println(i+8);
delay(500);
}
Wire.beginTransmission(0x21);  //reset pattern(FF)
Wire.write(B11111111);
Wire.endTransmission();
}
