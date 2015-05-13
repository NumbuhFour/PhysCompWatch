#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Time.h>
#include <EEPROM.h>
#include <wl.h>
#include <Vcc.h>
#include <SoftwareSerial.h>  

#include "Lilywatch.h"

Lilywatch watch;

void setup(){
	watch.setup();
}

void loop(){
	digitalWrite(13,HIGH);
	watch.run();
  
	//Power light. If things are frozen, light should remain on.
	digitalWrite(13,LOW);
	delay(15);
}
/*


byte tickDelay = 15;


//Generic global number, reset each state switch
int genNum = 0;

void setup() {
  

  //Serial.println("Startup complete.");
}

void loop() {
}



void loopDaemons(){
  autoLightLevel();
  checkBluetooth();
}

void loopState(){
  switch(state){
    case -1: statePicker(); break;
    case CLOCK_STATE: clockState(); break;
    case 1: compassState(); break;
    case 2: flashlight(); break;
    case BATTERY_STATE: showBatteryState(); break;
    case 4: configState(); break;
    case 5: setTimeState(); break;
    case 6: setBrightnessState(); break;
    case 7: unityState(); break;
    case 8: screensaver(); break;
    case 9: buttonPlay(); break;
    
    case ALARM_STATE: alarmState(); break;//Over statecount, ignored by state chooser.
    case ANDROID_STATE: androidState(); break;//Over statecount, ignored by state chooser.
    default:
      errorFlash();
      int s = state;
      setState(-1);
      genNum = s;
      break;
  }
}

// ************************************************************************************************ Rando Funcs ************************************************************************************************* /


void IRCheck(){
  if (irrecv.decode(&ir_results)) {
    //Serial.println(results.value, HEX);
    haveIRResults = true;
    irrecv.resume(); // Receive the next value
  }
}

int cali = 200;
void compassDirection(int compassHeading) 
{
  / *Serial.print(" Direction: ");
  Serial.print(compassHeading);
  Serial.print(" Calibration: ");
  Serial.print(cali);
  Serial.print(" Doop: ");
  Serial.println(compassHeading + cali);* /
  
  if(btn1rel){
    cali += 10;
  }else if(btn2rel){
    cali -= 10;
  }
  
  compassHeading += cali; //Calibration;
  if(compassHeading>=360) compassHeading -= 360;
  if(compassHeading< 0) compassHeading += 360;
  clearColors();

  unsigned int ledDir = 2;
  
  //Use this part of the code to determine which way you need to go.
  //Remember: this is not the direction you are heading, it is the direction to the destination (north = forward).

  if (compassHeading > 280) {
      setColor(0, 255,0,0);
      setColor(6, 255,0,0);
      return;
  }
  
  ledDir = compassHeading / 25;
  
  if(ledDir >= NEO_COUNT){
    / *Serial.print("LED ERROR ");
    Serial.println(ledDir);* /
    setColor(0, 255,0,0);
    setColor(6, 255,0,0);
    //setColors(127, 255,0,0);
    return;
  }
  setColor(ledDir, 255, 255, 255);
}


// ************************************************** STATES ************************************************************************************************************************ /


//Sets pretty colors. Taken from neopixel example
void screensaver(){
  uint16_t i;
  for(byte i=0; i< NEO_COUNT; i++) {
    setColor(i, Wheel(((i * 256 / NEO_COUNT) + genNum) & 255));
  }
  genNum++;
  if(genNum>256*5) genNum=0;
}

void compassState(){
  compassCheck();
  compassDirection(compassReading);
}

void androidState(){
  if(btn1rel) Serial.println("btn1");
  if(btn2rel) Serial.println("btn2");
}

void unityState(){
  accelCheck();
  compassCheck();
  String axs = String(ax);
  String ays = String(ay);
  String azs = String(az);
  String output = "ACL:" + axs + "," + ays + "," + azs;
  Serial.println(output);
  
  String mxs = String(mx);
  String mys = String(my);
  String mzs = String(mz);
  output = "MAG:" + mxs + "," + mys + "," + mzs;
  //Serial.println(output);
}

/ ************************************************** DAEMONS ************************************************** /

String msgBuild = "";
void checkBluetooth(){
//  fakeSerial.println("Checky");
  while(Serial.available()>0){
    setColor(0, 0,255,255);
    pushColors();
    //delay(1000);
    char c = (char)Serial.read();
    fakeSerial.print(c);
    fakeSerial.print('#');
    if(c == ';'){
      handleMessage(msgBuild);
      msgBuild = "";
    }else{
      msgBuild.concat(c);
//      msgBuild += c;
    }
  }
}

void handleMessage(String msg){
  Serial.println(configFlags&CONFIG_BLUETOOTH);
  if((configFlags & CONFIG_BLUETOOTH) == CONFIG_BLUETOOTH){
    //confirmFlash();
    if(msg.startsWith("TIM=")){
      //Serial.print("TIME");
      int dot = msg.indexOf(".");
      int h = msg.substring(4,dot).toInt();
      int m = msg.substring(dot+1).toInt();
      
      setTime(h,m, 0,0,0,0);
      Serial.print("Time set to ");
      Serial.print(h);
      Serial.print(":");
      Serial.println(m);
    }else if(msg.startsWith("ALR")){
      Serial.println("ALARM!!!!");
      setState(ALARM_STATE);
    }else if(msg.startsWith("SMS")){
      Serial.println("SMS!!!");
      messageWaiting = true;
      messageFlash();
    }else if(msg.startsWith("AST")){
      if(state == ALARM_STATE) setState(CLOCK_STATE);
    }else if(msg.startsWith("AND")){
      if(state != ANDROID_STATE) setState(ANDROID_STATE);
    }else if(state == ANDROID_STATE){
      
    }
    Serial.println("Thanks! [" + msg + "]");
  }else{
    Serial.println("Bluetooth signal ignored.");
  }
}
*/
