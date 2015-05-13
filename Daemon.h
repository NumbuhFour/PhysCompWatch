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
    virtual void run() =0; //Loop
};

#endif
