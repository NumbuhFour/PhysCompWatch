#include "Colors.h"
#include "Defines.h"

Colors::Colors(Lilywatch* lw): watch(lw), pix(NEO_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800){
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