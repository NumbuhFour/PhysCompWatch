/*
  SetBrightnessState.h - SetBrightness app for the Lilywatch
  Allows configuration of the brightness level
*/

#ifndef SetBrightnessState_h
#define SetBrightnessState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"
#include "Colors.h"
#include "Buttons.h"
#include "Lilywatch.h"

class Lilywatch;

class SetBrightnessState: public WatchState
{
  private:
    Colors * col;
    Buttons * btn;
  public:
    SetBrightnessState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
