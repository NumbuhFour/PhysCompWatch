#include "Lilywatch.h"
#include <Time.h>

#include "ButtonPlayState.h"

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
  
  //Making states
  states[0] = new ButtonPlayState(this);
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
  
  lastMin = minute();
  
  colors->startupFlash();
}

void Lilywatch::run(){
  btn->check();
  battery->check();
  
  //Hold both buttons to access app selector
  if(btn->btnDown(0) && btn->btnDown(1)){
    selectorHoldCounter += tickDelay;
  }else{
    selectorHoldCounter = 0;
  }
    
  if(selectorHoldCounter >= 600 && state != -1){// Config accessed!
    colors->setColors(85,255,0,0);
    colors->setColors(42,240,255,0);
    colors->pushColors();
    
    motor->pulseMotorRepeat(1023, 100,50,3);
    
    selectorHoldCounter = 0;
    buttonsReleased = false;
    
    //Serial.println("State picker accessed.");
    setState(-1);
  }
  
  //Return to watch on shake
  /*if(cfg->checkFlag(CONFIG_ACCELRTN) && accelReturnDelay == 0){
    accelCheck();
    if(az > 19.5){
      confirmFlash();
      if(state == CLOCK_STATE)
        setState(BATTERY_STATE);
      else
        setState(CLOCK_STATE);
    }
  }
  accelReturnDelay = max(accelReturnDelay-1,0);*/
  
  if(btn->btnDown(0) || btn->btnDown(1)) messageWaiting = false;
  
  loopState();
  
  /*if(batteryLevel < 0.2 && (configFlags & CONFIG_BATTWARN)==CONFIG_BATTWARN && millis()%4000 < 1000){
    displayBatteryColors();
    pushColors();
    
    pulseMotor(1023, 200);
    delay(50);
    
    pulseMotor(1023, 700);
    delay(300);
    
  }else if(messageWaiting && millis()%4000 < 1000){
    messageFlash();
  }*/
  
  loopDaemons();
  
  //Keep clock mostly up to date in EEPROM
  //So if theres a reset, we wont be too far behind
  byte mins = minute();
  if(lastMin != mins){
    lastMin = mins;
    cfg->writeClockToEEPROM();
  }
  
  colors->pushColors();
  digitalWrite(13,LOW);
  delay(tickDelay);
  
   //Power light. If things are frozen, light should remain on.
   digitalWrite(13,HIGH);
  
}

void Lilywatch::loopState(){
  states[0]->run();
}

void Lilywatch::loopDaemons(){
  
}

void Lilywatch::setState(int s){
  
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