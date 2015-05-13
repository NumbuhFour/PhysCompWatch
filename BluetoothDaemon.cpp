/*
  BluetoothDaemon.h - 
  Daemon for recieving and handling bluetooth data
*/

#ifndef BluetoothDaemon_h
#define BluetoothDaemon_h

#include "Defines.h"
#include "Arduino.h"
#include "Daemon.h"
#include "Lilywatch.h"
#include "Config.h"
#include "Colors.h"
#include <Time.h>

class Lilywatch;

class BluetoothDaemon: public Daemon
{
  public:
    BluetoothDaemon(Lilywatch * lw): Daemon(lw) {
      cfg = lw->getConfig();
      col = lw->getColors();
      msgBuild = "";
    }
    void run() { //Loop
      while(Serial.available()>0){
        char c = (char)Serial.read();
        Serial.print(c);
        Serial.println("#");
        if(c == ';'){
          handleMessage(msgBuild);
          msgBuild = "";
        }else{
          msgBuild.concat(c);
        }
      }
    }
  private:
    Config * cfg;
    Colors * col;
    String msgBuild;
    void handleMessage(String msg){
      if(cfg->checkFlag(CONFIG_BLUETOOTH)){
        col->confirmFlash();
        if(msg.startsWith("TIM=")){
          int dot = msg.indexOf(".");
          int h = msg.substring(4,dot).toInt();
          int m = msg.substring(dot+1).toInt();
          
          setTime(h,m, 0,0,0,0);
          Serial.print("Time set to ");
          Serial.print(h);
          Serial.print(":");
          Serial.println(m);
        }else if(msg.startsWith("ALR")){
          Serial.println("ALARM!!!!");
          watch->setState(ALARM_STATE);
        }else if(msg.startsWith("SMS")){
          Serial.println("SMS!!!");
          watch->setMessageWaiting(true);
        }else if(msg.startsWith("AST")){
          if(watch->getState() == ALARM_STATE) watch->setState(CLOCK_STATE);
        }/*else if(msg.startsWith("AND")){
          if(state != ANDROID_STATE) watch->setState(ANDROID_STATE);
        }else if(state == ANDROID_STATE){
          
        }*/
        Serial.println("Thanks! [" + msg + "]");
      }else{
        Serial.println("Bluetooth signal ignored.");
      }
    }
};

#endif
