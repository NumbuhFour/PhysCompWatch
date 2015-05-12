#include "ConfigState.h"


ConfigState::ConfigState(Lilywatch * lw): WatchState(lw){
  col = lw->getColors();
  btn = lw->getButtons();
  cfg = lw->getConfig();
}
void ConfigState::start(){ //State switched to this
  index = 0;
}
void ConfigState::run(){ //Loop
  byte configFlags = cfg->getFlags();
  col->setColors(127, 100,170,170);
  col->setColors(configFlags,  255,60,0);
  
  if(millis() % 1000 > 500)
    col->setColors(1<<index, 255,255,0);
  
  if(btn->btnRel(2)){
    configFlags ^= 1 << index;
    cfg->setFlags(configFlags);
  }else if(btn->btnRel(0)){
    index = (index+1)%7;
  }else if(btn->btnRel(1)){
    index --;
    if(index < 0) index = 6;
  }
}
void ConfigState::stop(){ //State leaving this
}