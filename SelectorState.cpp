#include "SelectorState.h"

#include "Lilywatch.h"
#include "Buttons.h"

SelectorState::SelectorState(Lilywatch * lw): WatchState(lw){
  
}
void SelectorState::start(){ //State switched to this
  selection = 0;
}
void SelectorState::run(){ //Loop
  Buttons * btn = watch->getButtons();
  if(btn->btnRel(2)){ //both buttons released
    if(selection < STATES){
      watch->getColors()->confirmFlash();
      watch->setState(selection);
    }else{
      watch->getColors()->errorFlash();
      selection = 0;
      watch->getColors()->clearColors();
    }
  }else if(btn->btnRel(0)){ //left button released
    selection ++;
    if(selection > 127) selection = 0;
  }else if(btn->btnRel(1)){ //right button released
    selection --;
    if(selection < 0) selection = 127;
  } 
  watch->getColors()->setColors(127, 100,100,100);
  watch->getColors()->setColors(selection, 255,0,255);
}
void SelectorState::stop(){ //State leaving this
}