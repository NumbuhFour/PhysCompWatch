#ifndef Colors_h
#define Colors_h

/*
  Colors.h
  Manages the Neopixel colors for the Lilywatch
  Also holds short animation functions
*/
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "Defines.h"

class Lilywatch;

class Colors
{
private:
  Adafruit_NeoPixel pix;
  uint32_t colors[NEO_COUNT] = {0};
  float ledStrength = 0.05;
  Lilywatch * watch;
public:
  Colors(Lilywatch * lw);
  void init();
  void setColor(byte index, uint32_t color);
  void setColor(byte index, byte r, byte g, byte b);
  void setColors(byte indices, byte r, byte g, byte b);
  void clearColors();
  void pushColors();
  float getStrength();
  void setStrength(float);
  
  uint32_t Wheel(byte WheelPos);
  
  //Premade Animations
  void startupFlash();
  void errorFlash();
  void confirmFlash();
  void messageFlash();
  void displayBatteryColors();
};

#endif