#ifndef Config_h
#define Config_h

/*
  Config.h
  Manages the EEPROM stored configuration and time information
*/


#include "Arduino.h"
#include <EEPROM.h>
#include <wl.h>
#include <Time.h>
#include "Defines.h"

class Lilywatch;

class Config
{
private:
	Lilywatch * watch;
	long TIMEEEVAR_START;
	long CONFIGVAR_START;
	byte configFlags;
	wl wearLeveling;

	struct timeEEVar{
	  byte hours;
	  byte mins;
	} _timeEEVar;
public:
    Config(Lilywatch * lw);
	
	void writeConfigToEEPROM();
	void writeClockToEEPROM();
  
  byte getFlags();
  bool checkFlag(int);
  void setFlags(byte);
};

#endif
