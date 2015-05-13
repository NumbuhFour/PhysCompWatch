/*
  BluetoothDaemon.h - 
  Daemon for recieving and handling bluetooth data
*/

#ifndef BluetoothDaemon_h
#define BluetoothDaemon_h

#include "Defines.h"
#include "Arduino.h"
#include "Daemon.h"
#include "Lilywatch.h"

class Lilywatch;

class BluetoothDaemon: public Daemon
{
  public:
    BluetoothDaemon(Lilywatch * lw): Daemon(lw) {}
    virtual void run() { //Loop
      
    }
};

#endif
