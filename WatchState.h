/*
  WatchState.h - Interface for apps made for the Lilywatch
*/

#ifndef WatchState_h
#define WatchState_h

#include "Defines.h"
#include "Arduino.h"

class Lilywatch;

class WatchState
{
  protected:
    Lilywatch * watch;
  public:
    explicit
    WatchState(Lilywatch * lw): watch(lw) {}
    virtual void start() =0; //State switched to this
    virtual void run() =0; //Loop
    virtual void stop() =0; //State leaving this
};

#endif
