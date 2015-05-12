#include "Lilywatch.h"

Lilywatch::Lilywatch(): fakeSerial(7,8){
  cfg = new Config(this);
  colors = new Colors(this);
  motor = new Motor();
  
  //Sensors
  accel = new Accel(this);
  mag = new Mag(this);
  btn = new Buttons();
  light = new Light();
  battery = new Battery();
  
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
  light->init();
  battery->init();
}

void Lilywatch::run(){
  
}

void Lilywatch::setState(byte s){
  
}

Config* Lilywatch::getConfig(){
  return cfg;
}
Colors* Lilywatch::getColors(){
  return colors;
}
Motor* Lilywatch::getMotor(){
  return motor;
}

//Sensors
Accel* Lilywatch::getAccel(){
  return accel;
}
Mag* Lilywatch::getMag(){
  return mag;
}
Buttons* Lilywatch::getButtons(){
  return btn;
}
Light* Lilywatch::getLight(){
  return light;
}
Battery* Lilywatch::getBattery(){
  return battery;
}