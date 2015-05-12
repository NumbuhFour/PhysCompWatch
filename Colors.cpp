#include "Colors.h"
#include "Defines.h"
#include "Lilywatch.h"
#include "Battery.h"

Colors::Colors(Lilywatch* lw): watch(lw), pix(NEO_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800){
}

void Colors::init(){
  for(byte i = 0; i < NEO_COUNT; i++) colors[0] = this->pix.Color(0,0,0);
  this->pix.begin();
  this->pix.show(); // Initialize all pixels to 'off'
}

float Colors::getStrength(){
  return this->ledStrength;
}

void Colors::setStrength(float stren){
  this->ledStrength = stren;
}

void Colors::setColor(byte index, uint32_t color){
  colors[index] = color;
}
void Colors::setColor(byte index, byte r, byte g, byte b){
  this->colors[index] = this->pix.Color((byte)((float)r * this->ledStrength),
                            (byte)((float)g * this->ledStrength),
                            (byte)((float)b * this->ledStrength));
}
void Colors::setColors(byte indicies, byte r, byte g, byte b){
  for(byte i = 0; i < NEO_COUNT; i++){
    if(indicies & 1 == 1){ //Lit at that index
      this->colors[i] = this->pix.Color((byte)((float)r * this->ledStrength),
                                (byte)((float)g * this->ledStrength),
                                (byte)((float)b * this->ledStrength));
    }
    indicies = indicies >> 1;
  }
}

void Colors::clearColors(){
  this->setColors(127, 0,0,0);
}

void Colors::pushColors(){
  for(byte i = 0; i < NEO_COUNT; i++){
    this->pix.setPixelColor(i, this->colors[i]);
  }
  pix.show();
}


// Premade animations

void Colors::startupFlash(){
  for(byte i = 0; i < NEO_COUNT+3; i++){
    if(i > 2) setColor(i-3, 0,0,0);
    if(i > 1 && i-2 < NEO_COUNT) setColor(i-2, 0,0,255);
    if(i > 0 && i-1 < NEO_COUNT) setColor(i-1, 0,255,0);
    if(i < NEO_COUNT) setColor(i, 255,0,0);

    pushColors();
    delay(100);
  }
  for(int i = NEO_COUNT+2; i >= 0; i--){
    if(i > 2) setColor(i-3, 255,0,0);
    if(i > 1 && i-2 < NEO_COUNT) setColor(i-2, 0,255,0);
    if(i > 0 && i-1 < NEO_COUNT) setColor(i-1, 0,0,255);
    if(i < NEO_COUNT) setColor(i, 0,0,0);

    pushColors();
    delay(100);
  }
  displayBatteryColors();
  pushColors();
  delay(80);
  setColor(NEO_COUNT-1, 0,0,0);
  pushColors();
  watch->getMotor()->pulseMotorRepeat(1023,150,100,2);
}

void Colors::errorFlash(){
    
    for(byte i = 1; i <= 16; i++){
      analogWrite(MOTOR_PIN,1023/ i);
      
      byte mod = i%8;
      if(mod == 0){
        clearColors();
        setColors(85,255,128,0);
        pushColors();
      }else if(mod == 4){
        clearColors();
        setColors(42,255,128,0);
        pushColors();
      }
      
      delay(50);
    }
    analogWrite(MOTOR_PIN,0);
}

void Colors::confirmFlash(){
    clearColors();
    setColors(42,0,255,0);
    pushColors();
    watch->getMotor()->pulseMotor(1023, 150);
    delay(50);
}

void Colors::messageFlash(){
  for(byte i = 0; i < NEO_COUNT; i++)
    setColor(i, Wheel(((i * 256 / NEO_COUNT) + 5) & 255));
  pushColors();
  watch->getMotor()->pulseMotorRepeat(1023,150,50,2);
  watch->getMotor()->pulseMotor(1023, 250);
  delay(50);
}

void Colors::displayBatteryColors(){
  Battery * battery = watch->getBattery();
  battery->check();
  float batt = battery->getData();
  for(float i = 0; i < NEO_COUNT; i++){
    float p = (i+1)/NEO_COUNT;
    if(p <= batt){ //Light on!
      if(p < 0.4){ //first 2 leds
        setColor((byte)i, 255,0,0);
      }else if(p > 0.8){//Last 2 leds
        setColor((byte)i, 0,255,0);
      }else{
        setColor((byte)i, 255,255,0);
      }
    }else{
      setColor((byte)i, 0,0,0);
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Colors::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  byte r,g,b;
  if(WheelPos < 85) {
   r = 255 - WheelPos * 3;
   g = 0;
   b = WheelPos * 3;
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    r = 0;
    g = WheelPos * 3;
    b = 255 - WheelPos * 3;
  } else {
   WheelPos -= 170;
   r = WheelPos * 3;
   g = 255 - WheelPos * 3;
   b = 0;
  }
  
  return pix.Color((byte)((float)r * ledStrength),
                   (byte)((float)g * ledStrength),
                   (byte)((float)b * ledStrength));
}