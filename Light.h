#ifndef Light_h
#define Light_h

/*
  Light.h
  Manages the photoresistor for the Lilywatch
*/
#include "Arduino.h"
#include "Defines.h"

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