#ifndef Buttons_h
#define Buttons_h

/*
  Buttons.h
  Manages the buttons for the Lilywatch
*/
#include "Arduino.h"
#include "Defines.h"

class Buttons
{
private:
  bool btn1=false, btn2=false; //Button values
  bool lbtn1=false, lbtn2=false; //Last values
  bool btn1rel=false, btn2rel=false; //Was released
  bool bothbtnrel=false; //Both buttons released
  bool cleared=false;
public:
  Buttons();
  void init();
  void check();
  //Clear button data for the rest of this loop
  //Used to make states after daemons ignore input
  void clear(); 
  
  bool btnDown(int btn); //0 or 1 for respective buttons, 2 for both
  bool btnRel(int btn); 
};

#endif