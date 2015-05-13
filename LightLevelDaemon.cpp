/*
  LightLevelDaemon.h - 
  Daemon for changing brightness based on light level
*/

#ifndef LightLevelDaemon_h
#define LightLevelDaemon_h

#include "Defines.h"
#include "Arduino.h"
#include "Daemon.h"
#include "Lilywatch.h"
#include "Config.h"
#include "Colors.h"
#include "Light.h"

class Lilywatch;

class LightLevelDaemon: public Daemon
{
  private:
    Config * cfg;
    Colors * col;
    Light * lht;
    float lastLightLevel[3]={0};
    byte lastLightLevelIndex = 0;
  public:
    LightLevelDaemon(Lilywatch * lw): Daemon(lw) {
      cfg = lw->getConfig();
      col = lw->getColors();
      lht = lw->getLight();
    }
    virtual void run() { //Loop
      
      if(!cfg->checkFlag(CONFIG_LIGHTLEVEL))
        return; //Auto light level disabled
      
      lht->check();
      float light = lht->getData();
      lastLightLevel[lastLightLevelIndex] = light;
      lastLightLevelIndex = (lastLightLevelIndex+1)%3;
      
      light = 0;
      for(byte i = 0; i < 3; i++){
        light += lastLightLevel[i];
      }
      light /= 3;
      
      if(light < 0.05) light = 0.05;
      if(light > 1) light = 1;
      col->setStrength(light);
    }
};

#endif
