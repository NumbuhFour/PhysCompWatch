/*
  ButtonPlayState.h - ButtonPlay app for the Lilywatch
  Shows a white LED in the direction of north
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
