#ifndef Motor_h
#define Motor_h

/*
  Motor.h
  Manages the Vibration motor for the Lilywatch
*/
#include "Arduino.h"
#include "Defines.h"

class Lilywatch;

class Motor
{
private:
public:
  Motor();
  void init();
  
  void pulseMotor(int, int);
  void pulseMotorRepeat(int, int, int, int);
};

#endif