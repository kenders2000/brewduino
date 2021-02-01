/* Brewmaster version 2.0
   code to monitor temperature and operate
   heating / cooling for beer brewing
   written by Rob Dick
   v2.0 Sun 17 May 2020
   v1.0 00:18 Wed 26 June 2018
*/

#include "brewmaster.h"
#include "rgb_lcd.h"

brewmaster brewmaster;
tmp36 tmp36;


void setup()
{
  brewmaster.clearDisplay();
  Serial.begin(9600);
  brewmaster.innit();
}


void loop()
{
  for (int i = 0; i <= 2; i++) { brewmaster.temp[i] = tmp36.readTemp(i); }
  
  if (Serial.available() > 0) {
    
    int inByte = Serial.read();
    
    if (inByte == 'a') {
      brewmaster.sendTemp1();
    }
    else if (inByte == 'b') {
      brewmaster.sendTemp2();
    }
    else if (inByte == 'c') {
      brewmaster.sendTemp3();
    }

  }

  delay(100);

  brewmaster.lcdDisplay();
  
}
