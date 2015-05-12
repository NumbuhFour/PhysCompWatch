#ifndef Lilywatch_h
#define Lilywatch_h

#include <SoftwareSerial.h>  
#include "Arduino.h"
#include "Defines.h"
#include "Config.h"
#include "Colors.h"
#include "Motor.h"

#include "Accel.h"
#include "Mag.h"
#include "Buttons.h"
#include "Light.h"
#include "Battery.h"

class Lilywatch
{
  public:
    Lilywatch();
    void setup();
    void run();
    void setState(byte state);
    
    Colors* getColors();
  private:
    byte state;
    SoftwareSerial fakeSerial;
    Config * cfg;
    Colors * colors;
    Motor * motor;
    
    //Sensors
    Accel * accel;
    Mag * mag;
    Buttons * btn;
    Light * light;
    Battery * battery;
    
    byte tickDelay = 15;
};

#endif
