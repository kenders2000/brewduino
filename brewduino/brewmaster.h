/* brewmaster.h - Brewmaster version 1.0
   code to monitor temperature and operate
   heating / cooling for beer brewing
   written by Rob Dick
   v2.0 Sun 17 May 2020
   v1.0 00:18 Wed 26 June 2018
*/
#ifndef brewmaster_h
#define brewmaster_h
#include "Arduino.h"
#include "rgb_lcd.h"


const int numReadings = 10; //number of readings to average for smoothing - not implemented yet


class brewmaster
{
  public:
    float temp[3];
    void clearDisplay();
    void lcdDisplay();
    void innit();
    void sendTemp1();
    void sendTemp2();
    void sendTemp3();
    void establishContact();
  private:
};

class tmp36
{
  public:
    float readTemp(int);
  private:
    int reading[numReadings];
    int readIndex = 0;
    int total = 0;
    int average = 0;
};

#endif
