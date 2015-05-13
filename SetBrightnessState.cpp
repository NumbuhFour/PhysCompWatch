#include "SetBrightnessState.h"


SetBrightnessState::SetBrightnessState(Lilywatch * lw): WatchState(lw){
  col = lw->getColors();
  btn = lw->getButtons();
}
void SetBrightnessState::start(){ //State switched to this
}
void SetBrightnessState::run(){ //Loop
  if(btn->btnRel(2)){ //Confirmation with both buttons
    col->confirmFlash();
    watch->setState(CLOCK_STATE);
  }else{
    if(btn->btnRel(0) && col->getStrength() < 1){ //left button released
      col->setStrength(col->getStrength() + 0.05);
    } 
    if(btn->btnRel(1) && col->getStrength() > 0.05){ //right button released
      col->setStrength(col->getStrength() - 0.05);
    }
    col->setColors(127,255,255,255);
    col->setColor(0, 255,0,0);
    col->setColor(3, 0,255,0);
    col->setColor(6, 0,0,255);
    
    if(col->getStrength() < 0.05) col->setStrength(0.05);
    if(col->getStrength() > 1) col->setStrength(1);
  }
}
void SetBrightnessState::stop(){ //State leaving this
}