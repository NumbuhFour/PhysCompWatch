/*
  FlashlightState.h - Flashlight app for the Lilywatch
  Shines a bright light
*/

#ifndef FlashlightState_h
#define FlashlightState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"
#include "Colors.h"
#include "Lilywatch.h"

class Lilywatch;

class FlashlightState: public WatchState
{
  private:
    Colors * col;
    float previousBrightness;
  public:
    FlashlightState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
