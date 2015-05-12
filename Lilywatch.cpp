#include "Lilywatch.h"

Lilywatch::Lilywatch(): fakeSerial(7,8),
                        pix(NEO_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800){
  cfg = new Config(this);
  this->state = 1;
  
  pinMode(BTN1_PIN, INPUT);
  pinMode(BTN2_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); //Power notifier
  
  fakeSerial.begin(9600);
  Serial.begin(9600);
  
  for(byte i = 0; i < NEO_COUNT; i++) colors[0] = this->pix.Color(0,0,0);
}

void Lilywatch::run(){
  
}

void Lilywatch::setState(byte s){
  
}