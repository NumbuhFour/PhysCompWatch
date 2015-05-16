/*
  IRDaemon.h - 
  Daemon for recieving and handling IR signals
  Changes context accordingly
*/

#ifndef IRDaemon_h
#define IRDaemon_h

#include <IRremote.h>
#include "Defines.h"
#include "Arduino.h"
#include "Daemon.h"
#include "Lilywatch.h"

#define NUM_VALID_IR 1
class Lilywatch;

class IRDaemon: public Daemon
{
  public:
    IRDaemon(Lilywatch * lw);
    bool run(); //Loop
    String getCurrentKey();
  private:
    IRrecv irrecv;
    decode_results results;
    unsigned long validSignals[NUM_VALID_IR];
    String signalKeys[NUM_VALID_IR];
    
    String lastValid = "";
    unsigned long lastValidTime = 0;
    unsigned long lastCheck = 0;
};

#endif
