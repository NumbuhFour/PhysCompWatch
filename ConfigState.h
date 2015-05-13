/*
  ConfigState.h - Config app for the Lilywatch
  Allows the user to turn on and off config flags
*/

#ifndef ConfigState_h
#define ConfigState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"
#include "Colors.h"
#include "Buttons.h"
#include "Config.h"
#include "Lilywatch.h"

class Lilywatch;

class ConfigState: public WatchState
{
  private:
    Colors * col;
    Buttons * btn;
    Config * cfg;
    byte index = 0;
  public:
    ConfigState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
