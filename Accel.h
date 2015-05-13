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
  sensors_event_t event;
  float ax=0,ay=0,az=0;
public:
  Accel(Lilywatch * lw);
  void init();
  void check();
  
  float* getData();
  float getAX();
  float getAY();
  float getAZ();
};

#endif