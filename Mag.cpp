#include "Mag.h"
#include "Defines.h"

#include "Colors.h"
#include "Lilywatch.h"

Mag::Mag(Lilywatch* lw): watch(lw), mag(12345){
  
}

void Mag::init(){
  if(!mag.begin())
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

float* Mag::getData(){
  float rtn[] = {mx,my,mz};
  return rtn;
}
