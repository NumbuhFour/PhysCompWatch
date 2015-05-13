#include "SetClockState.h"


SetClockState::SetClockState(Lilywatch * lw): WatchState(lw){
  col = lw->getColors();
  btn = lw->getButtons();
}
void SetClockState::start(){ //State switched to this
  index = 0;
  minSet = 1;
  hourSet = 1;
}
void SetClockState::run(){ //Loop
  if(index == 0){
    minSet = minute();
    hourSet = hour();
    index++;
  }if(index == 1){//Setting hour
    if(btn->btnRel(2)){ //both button released
      index ++;
    }else if(btn->btnRel(0)){ //left button released
      hourSet ++;
      if(hourSet >= 24) hourSet = 1;
    } else if(btn->btnRel(1)){ //right button released
      hourSet --;
      if(hourSet < 1) hourSet = 24;
    }
    col->setColors(127, 100,100,100);
    col->setColors(hourSet, 255,255,0);
    
  }else if(index == 2){//Waiting for both buttons released
    if(!btn->btnDown(0) && !btn->btnDown(1))
      index ++;
  }else if(index == 3){//Setting minute
    if(btn->btnRel(2)){ //right button released
      setTime(hourSet, minSet, 0,0,0,0);
      watch->setState(CLOCK_STATE);
      
      hourSet = 1;
      minSet = 1;
    }else  if(btn->btnRel(0)){ //left button released
      minSet ++;
      if(minSet >= 60) minSet = 1;
    }else if(btn->btnRel(1)){ //right button released
      minSet --;
      if(minSet < 1) minSet = 59;
    }
    col->setColors(127, 100,100,100);
    col->setColors(minSet, 0,255,255);
  }
}
void SetClockState::stop(){ //State leaving this
}