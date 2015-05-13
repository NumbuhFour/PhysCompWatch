#include "AlarmState.h"

AlarmState::AlarmState(Lilywatch * lw): WatchState(lw){
  col = lw->getColors();
  btn = lw->getButtons();
}
void AlarmState::start(){ //State switched to this
}
void AlarmState::run(){ //Loop
  uint16_t i;
  for(i=0; i< NEO_COUNT; i++) {
    col->setColor(i, col->Wheel(((i * 256 / NEO_COUNT) + iterator) & 255));
  }
  iterator += 20;
  if(iterator>256*5) iterator=0;
  
  unsigned long mil = millis();
  if(mil%7000 < 5000 && (mil%7000)%2000 < 1000){
     analogWrite(MOTOR_PIN, 1023);
  }else{
     analogWrite(MOTOR_PIN, 0);
  }
  
  if(btn->btnDown(2)){
    Serial.print("ALSTP");
    watch->setState(CLOCK_STATE);
  }
}
void AlarmState::stop(){ //State leaving this
}