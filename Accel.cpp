#include "Accel.h"
#include "Defines.h"

#include "Colors.h"
#include "Lilywatch.h"

Accel::Accel(Lilywatch* lw): watch(lw), accel(54321){
  
}

void Accel::init(){
  if(!accel.begin())
  {
    // There was a problem detecting the LSM303 ... check your connections 
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    
    Colors * color = watch->getColors();
    while(1){
      color->setColors(127, 255,0,0);
      color->pushColors();
      delay(500);
      color->clearColors();
      color->pushColors();
      delay(500);
    }
  }
}

void Accel::check(){
  accel.getEvent(&event);
  
  ax = event.acceleration.x;
  ay = event.acceleration.y;
  az = event.acceleration.z;
}
float Accel::getAX(){return ax;}
float Accel::getAY(){return ay;}
float Accel::getAZ(){return az;}
float* Accel::getData(){ //BOOOORKED
  float* rtn = new float[3];
  rtn[0] = ax;
  rtn[1] = ay;
  rtn[2] = az;
  return rtn;
}
