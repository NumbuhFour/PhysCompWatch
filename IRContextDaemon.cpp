/*
  IRContextDaemon.h - 
  Daemon for acting in context when in range of specific IRContext beacons
*/

#ifndef IRContextDaemon_h
#define IRContextDaemon_h

#include <IRremote.h>
#include "Defines.h"
#include "Arduino.h"
#include "Daemon.h"
#include "Lilywatch.h"
#include "Config.h"
#include "IRDaemon.h"
#include "Accel.h"
#include "Buttons.h"

#define NUM_VALID_IRContext 1
class Lilywatch;
class IRDaemon;

/*
Button codes:
CTX[button],[target]
CTX (header)
B0: Left button released
B1: Right button released
B2: Both buttons released
D0: Left button double pressed
D1: Right button double pressed

example:
CTXB2,tv 
*/

class IRContextDaemon: public Daemon
{
  public:
    IRContextDaemon(Lilywatch * lw): Daemon(lw) {
      cfg = lw->getConfig();
      accel = lw->getAccel();
      buttons = lw->getButtons();
      ir = lw->getIR();
    }
    bool run() { //Loop
      if(cfg->checkFlag(CONFIG_IRCONTEXT)){
        String key = ir->getCurrentKey();
        unsigned long time = millis();
        if(key != ""){ //In range of a beacon
          accel->check();
          float az = accel->getAZ();
          if(az > 5 && az < 15){ //Mostly upside down and sorta resting
            bool doub = lastButtonTime != 0 && time - lastButtonTime <= 300;
            
            if(twoPressDelay > 0){
              twoPressDelay --; //Pressing both sometimes triggers one afterwards
            }else if(buttons->btnRel(2)){
              if(doub) {
                sendMessage(lastButton, false, key);
              }
              sendMessage(2, false, key);
              lastButtonTime = 0;
              twoPressDelay = 10; 
            }else if(buttons->btnRel(0)){
              if(doub && lastButton == 0){ //Double and matches
                sendMessage(0, true, key);
                lastButtonTime = 0;
              }else if(doub){ //Key pressed recent thats not matching
                sendMessage(lastButton, false,key); //Send last button
                lastButton = 0;
                lastButtonTime = time;
              }else{
                lastButton = 0;
                lastButtonTime = time;
              }
            }else if(buttons->btnRel(1)){
              if(doub && lastButton == 1){ //Double and matches
                sendMessage(1, true, key);
                lastButtonTime = 0;
              }else if(doub){ //Key pressed recent thats not matching
                sendMessage(lastButton, false,key); //Send last button
                lastButton = 1;
                lastButtonTime = time;
              }else{
                lastButton = 1;
                lastButtonTime = time;
              }
            }
            
            buttons->clear();
          }
        }
        
        if(lastButtonTime != 0 && time - lastButtonTime > 300){ //No second button pressed for double press
          lastButtonTime = 0;
          sendMessage(lastButton, false, key);
          lastButton = -1;
        }
      }
      return false;
    }
  private:
    Config * cfg;
    Accel * accel;
    Buttons * buttons;
    IRDaemon * ir;
    int lastButton = -1;
    unsigned long lastButtonTime = 0;
    byte twoPressDelay = 0;
    
    void sendMessage(int button, bool doub, String key){
      String msg = "CTX";
      if(doub) msg += "D";
      else msg += "B";
      msg += button;
      msg += ",";
      msg += key;
      Serial.println(msg);
    }
};

#endif
