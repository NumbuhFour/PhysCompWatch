#include "ButtonPlayState.h"

#include "Lilywatch.h"
#include "Colors.h"

ButtonPlayState::ButtonPlayState(Lilywatch * lw): WatchState(lw){
  
}
void ButtonPlayState::start(){ //State switched to this
}
void ButtonPlayState::run(){ //Loop
  bool btn1 = watch->getButtons()->btnDown(0);
  bool btn2 = watch->getButtons()->btnDown(1);
  Colors * col = watch->getColors();
  if(btn1) {
    col->setColor(0, 255,0,255);
    col->setColor(1, 255,0,255);
  }else{
    col->setColor(0, 0,0,0);
    col->setColor(1, 0,0,0);
  }
  if(btn2){
    col->setColor(5, 255,0,255);
    col->setColor(6, 255,0,255);
  }else{
    col->setColor(5, 0,0,0);
    col->setColor(6, 0,0,0);
  }
}
void ButtonPlayState::stop(){ //State leaving this
}