#ifndef Mag_h
#define Mag_h

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

class Mag
{
private:
  Adafruit_LSM303_Mag_Unified mag;
  Lilywatch * watch;
  // Calibration offsets
  float magxOffset = 20;//2.55;
  float magyOffset = 0;//27.95;
  float magzOffset = 20;//27.95;
  float mx,my,mz;
public:
  Mag(Lilywatch * lw);
  void init();
  void check();
  
  float* getData();
};

#endif