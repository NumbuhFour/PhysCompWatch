/*
  IRDaemon.h - 
  Daemon for recieving and handling IR signals
  Changes context accordingly
*/

#ifndef IRDaemon_h
#define IRDaemon_h

#include "Defines.h"
#include "Arduino.h"
#include "Daemon.h"
#include "Lilywatch.h"
#include "Config.h"
#include <IRremote.h>

class Lilywatch;

class IRDaemon: public Daemon
{
  public:
    IRDaemon(Lilywatch * lw): Daemon(lw), irrecv(IRSEN_PIN) {
      cfg = lw->getConfig();
    }
    void run() { //Loop
    }
  private:
    Config * cfg;
    IRrecv irrecv;
};

#endif
