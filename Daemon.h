/*
  Daemon.h - Interface for daemons made for the Lilywatch
*/

#ifndef Daemon_h
#define Daemon_h

#include "Defines.h"
#include "Arduino.h"

class Lilywatch;

class Daemon
{
  protected:
    Lilywatch * watch;
  public:
    explicit
    Daemon(Lilywatch * lw): watch(lw) {}
    virtual bool run() =0; //Loop. Returns true if main loop should skip letting current app act
};

#endif
