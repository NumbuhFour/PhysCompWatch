#ifndef Accel_h
#define Accel_h

/*
  Accel.h
  Manages the LSM303 Accelerometer for the Lilywatch
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
  float ax,ay,az;
public:
  Accel(Lilywatch * lw);
  void init();
  
  float* getData();
};

#endif