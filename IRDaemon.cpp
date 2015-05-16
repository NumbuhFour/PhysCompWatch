
#include "IRDaemon.h"
#include "Defines.h"
#include "Lilywatch.h"
#include "Daemon.h"

IRDaemon::IRDaemon(Lilywatch * lw): Daemon(lw), irrecv(IRSEN_PIN) {
  irrecv.enableIRIn();
  validSignals[0] = 4045713590;
  signalKeys[0] = "tv";
}
bool IRDaemon::run() { //Loop
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
  return false;
}

String IRDaemon::getCurrentKey(){
  return lastValid;
}