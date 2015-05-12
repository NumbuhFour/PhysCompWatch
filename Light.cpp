#include "Light.h"
#include "Defines.h"

#include "Lilywatch.h"

Light::Light() {
  
}

void Light::init(){
}

void Light::check(){
  float light = analogRead(PHOTO_PIN);
  
  light = (light/1024)*2;
  if(light > 1) light = 1;
  if(light <= 0.05) light = 0.05;
  
  lightLevel = light;
}

float Light::getData(){
  return lightLevel;
}
