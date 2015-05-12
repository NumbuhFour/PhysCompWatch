#ifndef Lilywatch_h
#define Lilywatch_h

#include <SoftwareSerial.h>  
#include "Arduino.h"
#include "Config.h"
#include "Colors.h"
#include "Defines.h"

class Lilywatch
{
  public:
    Lilywatch();
    void run();
    void setState(byte state);
    
  private:
    byte state;
    Config * cfg;
    SoftwareSerial fakeSerial;
    Colors * colors;
    
    byte tickDelay = 15;
};

#endif
