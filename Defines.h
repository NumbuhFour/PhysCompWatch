#ifndef Defines_h
#define Defines_h

#define NEO_COUNT   7

#define NEO_PIN    12
#define BTN1_PIN   16 //Left button
#define BTN2_PIN    3  //Right button
#define MOTOR_PIN  10 //Vibration motor
#define PHOTO_PIN   0
#define PIEZO_PIN   6

#define STATES      10
#define DAEMONS     1

#define CLOCK_STATE 0
#define ALARM_STATE 64
#define ANDROID_STATE 63
#define UNITY_STATE 7
#define BATTERY_STATE 3

#define CONFIG_LIGHTLEVEL 1 	//Light level auto-changes
#define CONFIG_BLUETOOTH  2 	//Pay attention to bluetooth messages
#define CONFIG_BATTWARN   4 	//Warn when battery low
#define CONFIG_ACCELRTN   8 	//Go to clock by shake
#define DATA_START 32

#define VCCMIN   3.4           // Minimum expected Vcc level, in Volts.
#define VCCMAX   4.19           // Maximum expected Vcc level, in Volts.
#define VCCCORR  1.0           // Measured Vcc by multimeter divided by reported Vcc

#endif