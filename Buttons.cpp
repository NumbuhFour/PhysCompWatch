
#include "Buttons.h"
#include "Arduino.h"
#include "Defines.h"

Buttons::Buttons(){
  
}

void Buttons::init(){
  pinMode(BTN1_PIN, INPUT);
  pinMode(BTN2_PIN, INPUT);
}

void Buttons::check(){
  btn1 = digitalRead(BTN1_PIN)==HIGH;
  btn2 = digitalRead(BTN2_PIN)==HIGH;
  btn1rel = lbtn1 && !btn1;
  btn2rel = lbtn2 && !btn2;
  bothbtnrel = ((btn1rel && btn2) || (btn2rel && btn1));
  
  lbtn1 = btn1;
  lbtn2 = btn2;
}
  
bool Buttons::btnDown(int btn){ //0 or 1 for respective buttons, 2 for both
  switch(btn){
    case 0: return btn1;
    case 1: return btn2;
    case 2: return (btn1 && btn2);
    default: return false;
  }
}
bool Buttons::btnRel(int btn){
  switch(btn){
    case 0: return btn1rel;
    case 1: return btn2rel;
    case 2: return bothbtnrel;
    default: return false;
  }
}