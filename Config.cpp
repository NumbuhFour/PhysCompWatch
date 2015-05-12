
#include "Config.h"


void writer(unsigned long address, uint8_t data)
{
  EEPROM.write(address,data);
}

byte reader(unsigned long address){
  return EEPROM.read(address);
}

Config::Config(Lilywatch lw): wearLeveling(&writer, &reader), watch(lw){
	this->configFlags = 1;
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