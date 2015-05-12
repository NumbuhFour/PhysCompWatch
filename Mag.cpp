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

void Mag::check(){
  sensors_event_t event; 
  mag.getEvent(&event);

  float Pi = 3.14159;
  
  mx = event.magnetic.x+magxOffset;
  my = event.magnetic.y+magyOffset;
  mz = event.magnetic.z+magzOffset;
  float heading = (atan2(my + magyOffset,mx + magxOffset) * 180) / Pi;
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  compassReading = heading; 
}

float* Mag::getData(){
  float rtn[] = {mx,my,mz};
  return rtn;
}

float Mag::getCompassReading(){
  return compassReading;
}