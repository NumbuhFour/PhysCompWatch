/*
  ShowBatteryState.h - ShowBattery app for the Lilywatch
  Shows the current battery level
*/

#ifndef ShowBatteryState_h
#define ShowBatteryState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"
#include "Colors.h"
#include "Lilywatch.h"

class Lilywatch;

class ShowBatteryState: public WatchState
{
  private:
    Colors * col;
  public:
    ShowBatteryState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
