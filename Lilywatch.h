#ifndef Lilywatch_h
#define Lilywatch_h

#define NEO_COUNT   7

#define NEO_PIN    12
#define BTN1_PIN   16 //Left button
#define BTN2_PIN    3  //Right button
#define MOTOR_PIN  10 //Vibration motor
#define PHOTO_PIN   0
#define PIEZO_PIN   6

#define STATES      10
#define CLOCK_STATE 0
#define ALARM_STATE 64
#define ANDROID_STATE 63
#define UNITY_STATE 7
#define BATTERY_STATE 3

#include <SoftwareSerial.h>  
#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "Config.h"

class Lilywatch
{
  public:
    Lilywatch();
    void run();
    void setState(byte state);
  private:
    byte state;
    Config * cfg;
    SoftwareSerial fakeSerial;
    Adafruit_NeoPixel pix;
    
    uint32_t colors[NEO_COUNT];
    float ledStrength = 0.05;
    byte tickDelay = 15;
};

#endif
