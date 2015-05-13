#include "ClockState.h"
#include <Time.h>

ClockState::ClockState(Lilywatch * lw): WatchState(lw){
  col = lw->getColors();
  btn = lw->getButtons();
  showClock = true;
}
void ClockState::start(){ //State switched to this
  showClock = true;
}
void ClockState::run(){ //Loop
  //light 2 will be yellow if am, orange if pm
  //lights 3-6 will be binary for hour in 12-hour format (green)
  //lights 0&1 will represent part of hour: (blue)
  //  light 00 = min<15
  //  light 01 = min<30
  //  light 10 = min<45
  //  light 11 = min<60
  
  if(btn->btnRel(0)) {
    showClock = !showClock;
  }
  
  if(!showClock){
    col->clearColors();
    return;
  }
  
  byte hours = hourFormat12();
  bool isam = isAM();
  byte mins = minute();
  
  if(btn->btnDown(1)){ //Show minutes detail if b2 is pressed
    col->clearColors();
    col->setColors(63, 0,45,30); //minute background
    col->setColors(mins, 0,0,255);
    
    if(second()%2 == 0) col->setColor(6, 0,0,0); //AMPM because a light is not used
    else if(isam) col->setColor(6, 200,255,0);
    else col->setColor(6, 255,50,0);
    
  }else{ //Otherwise show full time
    if(second()%2 == 0) col->setColor(2, 0,0,0);
    else if(isam) col->setColor(2, 200,255,0);
    else col->setColor(2, 255,50,0);
    
    col->setColors(120, 0,0,0); //hour background
    col->setColors(3, 0,0,0); //minute background
    
    hours = hours << 3;
    col->setColors(hours, 0,255,0);
    
    mins = mins/15;
    col->setColors(mins, 0,0,255);
  }
}
void ClockState::stop(){ //State leaving this
}