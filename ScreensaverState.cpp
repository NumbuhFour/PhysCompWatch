/*
  ScreensaverState.h - Screensaver app for the Lilywatch
  Loops pretty colors
*/

#ifndef ScreensaverState_h
#define ScreensaverState_h

#include "Defines.h"
#include "Arduino.h"
#include "WatchState.h"
#include "Colors.h"
#include "Lilywatch.h"

class Lilywatch;

class ScreensaverState: public WatchState
{
  private:
    Colors * col;
    byte iter = 0;
  public:
    ScreensaverState(Lilywatch * lw): WatchState(lw){
      col = lw->getColors();
    }
    void start(){} //State switched to this
    void run(){ //Loop
      uint16_t i;
      for(i=0; i< NEO_COUNT; i++) {
        col->setColor(i, col->Wheel(((i * 256 / NEO_COUNT) + iter) & 255));
      }
      iter++;
      if(iter>256*5) iter=0;
    }
    void stop(){} //State leaving this
};

#endif
