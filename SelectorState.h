/*
  SelectorState.h - Selector app for the Lilywatch
  Lets you pick which app to go to
*/

#ifndef SelectorState_h
#define SelectorState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"

class Lilywatch;

class SelectorState: public WatchState
{
  private:
    byte selection;
  public:
    SelectorState(Lilywatch *);
    void start(); //State switched to this
    void run(); //Loop
    void stop(); //State leaving this
};

#endif
