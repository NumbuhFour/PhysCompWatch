#ifndef Battery_h
#define Battery_h

/*
  Battery.h
  Manages the LSM303 Accelerometer for the Lilywatch
*/
#include "Arduino.h"
#include "Defines.h"
#include <Vcc.h>

class Battery
{
private:
  float batteryLevel;
  Vcc vcc;
public:
  Battery();
  void init();
  void check();
  
  float getData();
};

#endif