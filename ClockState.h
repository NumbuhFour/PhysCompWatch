/*
  ClockState.h - Clock app for the Lilywatch
  Shows the time on the LEDs
*/

#ifndef ClockState_h
#define ClockState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"
#include "Colors.h"
#include "Buttons.h"
#include "Lilywatch.h"

class Lilywatch;

class ClockState: public WatchState
{
  private:
    Colors * col;
    Buttons * btn;
    bool showClock = true;
    bool showMinute = false;
  public:
    ClockState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
