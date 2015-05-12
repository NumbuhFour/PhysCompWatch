#ifndef Light_h
#define Light_h

/*
  Accel.h
  Manages the LSM303 Accelerometer for the Lilywatch
*/
#include "Arduino.h"
#include "Defines.h"

class Lilywatch;

class Light
{
private:
  float lightLevel;
public:
  Light();
  void init();
  void check();
  
  float getData();
};

#endif