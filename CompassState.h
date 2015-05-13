/*
  CompassState.h - Compass app for the Lilywatch
  Shows a white LED in the direction of north
*/

#ifndef CompassState_h
#define CompassState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"
#include "Colors.h"
#include "Buttons.h"
#include "Lilywatch.h"

class Lilywatch;

class CompassState: public WatchState
{
  private:
    Colors * col;
    Buttons * btn;
  public:
    CompassState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
