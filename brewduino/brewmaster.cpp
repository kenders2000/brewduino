/* brewmaster.cpp - Brewmaster version 2.0
   code to monitor temperature and operate
   heating / cooling for beer brewing
   written by Rob Dick
   v2.0 Sun 17 May 2020
   v1.0 00:18 Wed 26 June 2018
*/

#include "Arduino.h"
#include "brewmaster.h"
#include "rgb_lcd.h"

rgb_lcd lcd;

void brewmaster::clearDisplay()
{
  lcd.begin(16, 2);
  lcd.setRGB(255, 255, 255);
  lcd.clear();
}

void brewmaster::innit() {
  lcd.clear();
  lcd.print("Brewmaster v2.0");
  delay(1000);
  lcd.clear();

}

void brewmaster::lcdDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print("B=");
  lcd.print(temp[0]);
  lcd.setCursor(8, 0);
  lcd.print("F=");
  lcd.print(temp[1]);
  lcd.setCursor(0, 1);
  lcd.print("A=");
  lcd.print(temp[2]);
}


void brewmaster::sendTemp1()
{
  Serial.print(brewmaster::temp[0]);
}

 void brewmaster::sendTemp2()
{
  Serial.print(brewmaster::temp[1]);
}

void brewmaster::sendTemp3()
{
  Serial.print(brewmaster::temp[2]);
}


float tmp36::readTemp(int x)
{
  int reading = analogRead(x);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100;
  return temperatureC;
}
