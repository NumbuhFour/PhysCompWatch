#ifndef Lilywatch_h
#define Lilywatch_h

#include "Arduino.h"

class Lilywatch
{
  public:
    Lilywatch();
    void run();
    void setState(byte state);
  private:
};

#endif
