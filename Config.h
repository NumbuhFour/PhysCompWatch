#ifndef Config_h
#define Config_h

#include "Arduino.h"
#include <EEPROM.h>
#include <wl.h>
#include <Time.h>
#define CONFIG_LIGHTLEVEL 1 	//Light level auto-changes
#define CONFIG_BLUETOOTH  2 	//Pay attention to bluetooth messages
#define CONFIG_BATTWARN   4 	//Warn when battery low
#define CONFIG_ACCELRTN   8 	//Go to clock by shake
#define DATA_START 32

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
};

#endif
