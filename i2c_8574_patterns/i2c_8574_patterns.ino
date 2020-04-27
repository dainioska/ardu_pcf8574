//Arduino(UNO/Nano)over I2C communication to PCF8574 example
//How to use long time period (from 1 to 60sec.) millis() and class TimeOut_I2C
//Function millis() results serial printout and display on LCD(16x4)
//VERSION(2020-04-27)tested

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  //LCD_4 line port 27

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
  unsigned long currentMillis = millis()+8000; 
  if((pinState == HIGH) && (currentMillis -prevMillis >= OnTime))
  {
    pinState = LOW;
    prevMillis = currentMillis; 
    Serial.print("  OnTime:");
    Serial.println(prevMillis);
   
    lcd.setCursor(0,1);         // data display on LCD
    lcd.print("TimeOn: ");
    lcd.print(prevMillis); 

    Wire.beginTransmission(0x22); 
    Wire.write(0xFF); 
    Wire.endTransmission();
   
  }
  else if((pinState ==LOW) && (currentMillis -prevMillis >= OffTime))
  {
    pinState = HIGH;
    prevMillis = currentMillis;
    Serial.print("Offtime:");
    Serial.print(prevMillis);
    Serial.print("  print i:");
    Serial.print(i);

    lcd.setCursor(0,2);       // data display on LCD
    lcd.print("TimeOff: ");
    lcd.print(prevMillis); 
    
    Wire.beginTransmission(0x22); 
    Wire.write(datArray[i]); 
    Wire.endTransmission();
    if(i < 7)
    {
      i++;
    }
    else
    {
      i=0;
    } 
  }    
 }
};

 TimeOut patternsH(3000, 10000);   //class instance ( HIGH timeout(milisec.) ,LOW timeout(milisec.))

void setup() {
  Serial.begin(9600);
  Serial.println("PCF8574 begin >>>");
  Wire.begin();  
  Wire.beginTransmission(0x22);  //setup port 22(hex)
  Wire.write(0xFF);              //reset all pins
  Wire.endTransmission();
  
  lcd.init();
  lcd.backlight();
  lcd.print("PCF8574 begin >>>");
   
  delay(2000);
}

void loop() {
 patternsH.Update();
}
