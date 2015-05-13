/*
  AlarmState.h - Alarm app for the Lilywatch
  This is just an annoying state triggered by the connected phone
*/

#ifndef AlarmState_h
#define AlarmState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"
#include "Colors.h"
#include "Buttons.h"
#include "Lilywatch.h"

class Lilywatch;

class AlarmState: public WatchState
{
  byte iterator = 0;
  private:
    Colors * col;
    Buttons * btn;
  public:
    AlarmState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
