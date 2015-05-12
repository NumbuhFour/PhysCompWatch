#include "Lilywatch.h"

Lilywatch::Lilywatch(): fakeSerial(7,8){
  cfg = new Config(this);
  colors = new Colors(this);
  accel = new Accel(this);
  mag = new Mag(this);
  this->state = 1;
}

void Lilywatch::setup(){
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); //Power notifier
  
  fakeSerial.begin(9600);
  Serial.begin(9600);
  
  colors->init();
  accel->init();
  mag->init();
  btn->init();
}

void Lilywatch::run(){
  
}

void Lilywatch::setState(byte s){
  
}

Colors* Lilywatch::getColors(){
  return colors;
}
