#ifndef Buttons_h
#define Buttons_h

/*
  Mag.h
  Manages the LSM303 Magnetometer for the Lilywatch
*/
#include "Arduino.h"
#include "Defines.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

class Lilywatch;

class Buttons
{
private:
  bool btn1, btn2; //Button values
  bool lbtn1, lbtn2; //Last values
  bool btn1rel, btn2rel; //Was released
  bool bothbtnrel; //Both buttons released
public:
  Buttons();
  void init();
  void check();
  
  bool btnDown(int btn); //0 or 1 for respective buttons, 2 for both
  bool btnRel(int btn); 
};

#endif