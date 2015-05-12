#ifndef Accel_h
#define Accel_h

/*
  Accel.h
  Manages the Neopixel Accel for the Lilywatch
  Also holds short animation functions
*/
#include "Arduino.h"
#include "Defines.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

class Lilywatch;

class Accel
{
private:
  Adafruit_LSM303_Accel_Unified accel;
  Lilywatch * watch;
public:
  Accel(Lilywatch * lw);
  void init();
};

#endif