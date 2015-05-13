#include "Battery.h"
#include "Defines.h"


Battery::Battery(): vcc(VCCCORR){
  
}

void Battery::init(){
}

void Battery::check(){
  batteryLevel = vcc.Read_Perc(VCCMIN,VCCMAX)/100.0;
}

float Battery::getData(){
  return batteryLevel;
}
