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

float* Accel::getData(){
  float rtn[] = {ax,ay,az};
  return rtn;
}
