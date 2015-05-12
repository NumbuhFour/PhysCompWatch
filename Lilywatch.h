#ifndef Lilywatch_h
#define Lilywatch_h

#include <SoftwareSerial.h>  
#include "Arduino.h"
#include "Defines.h"
#include "Config.h"
#include "Colors.h"

#include "Accel.h"
#include "Mag.h"

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
    
    Accel * accel;
    Mag * mag;
    
    byte tickDelay = 15;
};

#endif
