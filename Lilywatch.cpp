#include "Lilywatch.h"

Lilywatch::Lilywatch(): fakeSerial(7,8){
  cfg = new Config(this);
  colors = new Colors(this);
  accel = new Accel(this);
  this->state = 1;
}

void Lilywatch::setup(){
  pinMode(BTN1_PIN, INPUT);
  pinMode(BTN2_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); //Power notifier
  
  fakeSerial.begin(9600);
  Serial.begin(9600);
}

void Lilywatch::run(){
  
}

void Lilywatch::setState(byte s){
  
}

Colors* Lilywatch::getColors(){
  return colors;
}
