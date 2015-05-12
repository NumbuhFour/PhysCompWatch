/*
  ButtonPlayState.h - ButtonPlay app for the Lilywatch
  A test app that has the LEDs react to the buttons
*/

#ifndef ButtonPlayState_h
#define ButtonPlayState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"

class Lilywatch;

class ButtonPlayState: public WatchState
{
  public:
    ButtonPlayState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
