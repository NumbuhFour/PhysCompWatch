
#include "Config.h"
#include "Defines.h"


void writer(unsigned long address, uint8_t data)
{
  EEPROM.write(address,data);
}

byte reader(unsigned long address){
  return EEPROM.read(address);
}

Config::Config(Lilywatch* lw): wearLeveling(&writer, &reader), watch(lw){
  this->configFlags = 1;  //Loading EEPROM data
  
  TIMEEEVAR_START = DATA_START;
  if(wearLeveling.exists(TIMEEEVAR_START) == WL_NOK){
    //Serial.println("Time var does not exist");
    //Create it at timeEEVar_Start position with WL_XX length where XX is status length 8,16,24,32,64
    wearLeveling.create(TIMEEEVAR_START, WL_16, sizeof(_timeEEVar));
    wearLeveling.clear();
    
    //Write new data to the var
    _timeEEVar.hours = hour();
    _timeEEVar.mins = minute();
    wearLeveling.open(TIMEEEVAR_START);
    wearLeveling.writeRec(WL_REC _timeEEVar);
  }else{
    //Serial.println("Time var exists.");
    wearLeveling.open(TIMEEEVAR_START);
    wearLeveling.readRec(WL_REC _timeEEVar);
    
    //Serial.print("Time set to ");
    //Serial.print(_timeEEVar.hours);
    //Serial.print(":");
    //Serial.println(_timeEEVar.mins);
    setTime(_timeEEVar.hours, _timeEEVar.mins,0,0,0,0);
  }
  
  CONFIGVAR_START = TIMEEEVAR_START + wearLeveling.memSize();
  if(wearLeveling.exists(CONFIGVAR_START)==WL_NOK){
    //Serial.println("configVar does not exist");
    wearLeveling.create(CONFIGVAR_START, WL_8, sizeof(configFlags));
    wearLeveling.clear();
    
    configFlags = 1;
    wearLeveling.open(CONFIGVAR_START);
    wearLeveling.writeRec(WL_REC configFlags); 
  }else{
    //Serial.println("Config var exists");
    wearLeveling.open(CONFIGVAR_START);
    wearLeveling.readRec(WL_REC configFlags);
  }
}


void Config::writeClockToEEPROM(){
  _timeEEVar.hours = hour();
  _timeEEVar.mins = minute();
  //Serial.print("Writing time to EEPROM ");
  //Serial.print(_timeEEVar.hours);
  //Serial.print(":");
  //Serial.println(_timeEEVar.mins);
  wearLeveling.open(TIMEEEVAR_START);
  wearLeveling.writeRec(WL_REC _timeEEVar);
}
void Config::writeConfigToEEPROM(){
    wearLeveling.open(CONFIGVAR_START); //Save to eeprom
    wearLeveling.writeRec(WL_REC configFlags);
}


byte Config::getFlags(){
  return configFlags;
}
bool Config::checkFlag(int flag){
  return ( (configFlags & flag) == flag );
}
void Config::setFlags(byte flags){
  configFlags = flags
  writeConfigToEEPROM();
}