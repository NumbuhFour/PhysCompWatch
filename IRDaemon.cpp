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
    IRDaemon(Lilywatch * lw): Daemon(lw), irrecv(IRSEN_PIN) {
      irrecv.enableIRIn();
      validSignals[0] = 4045713590;
      signalKeys[0] = "tv";
    }
    void run() { //Loop
      unsigned long time = millis();
      if(time-lastCheck > 150 && irrecv.decode(&results)){
          lastCheck = time; //IR Detection gets wonky without a 100ms delay
          Serial.print("GET IRh: ");
          Serial.println(results.value, HEX);
          irrecv.resume();
          for(byte i = 0; i < NUM_VALID_IR; i++){
            if(validSignals[i] == results.value){
              lastValid = signalKeys[i];
              lastValidTime = time;
            }
          }
      }
      
      //Seven seconds since last valid signal
      if(lastValidTime != 0 && time-lastValidTime > 7000){
        lastValid = "";
        lastValidTime = 0;
      }
    }
    
    String getCurrentKey(){
      return lastValid;
    }
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
