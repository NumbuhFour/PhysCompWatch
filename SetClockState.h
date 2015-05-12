/*
  SetClockState.h - SetClock app for the Lilywatch
  Sets the time
*/

#ifndef SetClockState_h
#define SetClockState_h

#include <Time.h>
#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"
#include "Colors.h"
#include "Buttons.h"
#include "Lilywatch.h"

class Lilywatch;

class SetClockState: public WatchState
{
  private:
    Colors * col;
    Buttons * btn;
    byte index=0;
    byte minSet=1;
    byte hourSet=1;
  public:
    SetClockState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
