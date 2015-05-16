#include "Lilywatch.h"
#include <Time.h>

#include "ButtonPlayState.h"
#include "ClockState.h"
#include "SetClockState.h"
#include "ConfigState.h"
#include "FlashlightState.h"
#include "AlarmState.h"
#include "SetBrightnessState.h"
#include "ShowBatteryState.h"
#include "ScreensaverState.cpp"


#include "LightLevelDaemon.cpp"
#include "BluetoothDaemon.cpp"
#include "IRDaemon.h"

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
  
  this->state = 0;
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
  
  //Making states
  selState = new SelectorState(this);
  states[0] = new ClockState(this);
  states[1] = new ButtonPlayState(this);
  states[2] = new FlashlightState(this);
  states[3] = new ShowBatteryState(this);
  states[4] = new ConfigState(this);
  states[5] = new SetClockState(this);
  states[6] = new SetBrightnessState(this);
  states[7] = new ScreensaverState(this);
  states[8] = new AlarmState(this);
  
  //Daemons
  daemons[0] = new LightLevelDaemon(this);
  daemons[1] = new BluetoothDaemon(this);
  ir = new IRDaemon(this);
  daemons[2] = ir;
  
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
  if(cfg->checkFlag(CONFIG_ACCELRTN)){
    accel->check();
    float az = accel->getAZ();
    if(az > 19.5 && accelReturnDelay == 0){
      accelReturnDelay = 200;
      colors->confirmFlash();
      if(state == CLOCK_STATE)
        setState(BATTERY_STATE);
      else
        setState(CLOCK_STATE);
    }
  }
  accelReturnDelay = max(accelReturnDelay-tickDelay,0);
  
  if(btn->btnDown(0) || btn->btnDown(1)) messageWaiting = false;
  
  if(!loopDaemons()){
    loopState();
  }
  
  if(battery->getData() < 0.2 && cfg->checkFlag(CONFIG_BATTWARN) && millis()%4000 < 1000){
    colors->displayBatteryColors();
    colors->pushColors();
    
    motor->pulseMotor(1023, 200);
    delay(50);
    
    motor->pulseMotor(1023, 700);
    delay(300);
    
  }else if(messageWaiting && millis()%4000 < 1000){
    colors->messageFlash();
  }
  
  //Keep clock mostly up to date in EEPROM
  //So if theres a reset, we wont be too far behind
  byte mins = minute();
  if(lastMin != mins){
    lastMin = mins;
    cfg->writeClockToEEPROM();
  }
  
  colors->pushColors();
  
}

void Lilywatch::loopState(){
  if(state == -1) selState->run();
  else if(states[state] != 0){
    states[state]->run();
  }else{
    colors->errorFlash();
    setState(-1);//Move back to selector if problem
  }
}

bool Lilywatch::loopDaemons(){
  bool doSkip = false;
  for(byte i = 2; i < DAEMONS; i++){
    Daemon * d = daemons[i];
    if(d != 0)
      doSkip |= d->run();
  }
  return doSkip;
}

//Handles switching between state
void Lilywatch::setState(int s){
  if(state != -1 && states[state] != 0){
    states[state]->stop();
  }
  
  state = s;
  colors->clearColors();

  analogWrite(MOTOR_PIN,0);
  
  //Wait until buttons are released
  //So that the new state won't come in with a button already down
  while(btn->btnDown(0) || btn->btnDown(1)) {
    btn->check(); 
    delay(tickDelay);
  }
  btn->check(); //To make sure none are set as just released
  
  if(s == -1){
    selState->start();
  } else if(states[s] != 0){
    states[s]->start();
  }
}

//Setters

void Lilywatch::setMessageWaiting(bool val){
  messageWaiting = val;
}

//Getters

int Lilywatch::getState(){
  return state;
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
IRDaemon* Lilywatch::getIR(){
  return ir;
}