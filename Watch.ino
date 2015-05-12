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
	watch.run();
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

void flashlight(){
  if(genNum == 0){
    float previousBrightness = ledStrength;
    ledStrength = 1;
    setColors(127, 255,255,255);
    pushColors();
    ledStrength = previousBrightness;
    genNum = 1;//Used to make sure this doesn't happen twice
  }
  
}

byte minSet=1;
byte hourSet=1;
void setTimeState(){
  if(genNum == 0){
    minSet = minute();
    hourSet = hour();
    genNum++;
  }if(genNum == 1){//Setting hour
    if(bothbtnrel){ //right button released
      genNum ++;
    }else if(btn1rel){ //left button released
      hourSet ++;
      if(hourSet >= 24) hourSet = 1;
    } else if(btn2rel){ //right button released
      hourSet --;
      if(hourSet < 1) hourSet = 24;
    }
    setColors(127, 100,100,100);
    setColors(hourSet, 255,255,0);
    
  }else if(genNum == 2){//Waiting for both buttons released
    if(!btn1 && !btn2 && !lbtn1 && !lbtn2)
      genNum ++;
  }else if(genNum == 3){//Setting minute
    if(bothbtnrel){ //right button released
      setTime(hourSet, minSet, 0,0,0,0);
      setState(CLOCK_STATE);
      
      hourSet = 1;
      minSet = 1;
    }else  if(btn1rel){ //left button released
      minSet ++;
      if(minSet >= 60) minSet = 1;
    }else if(btn2rel){ //right button released
      minSet --;
      if(minSet < 1) minSet = 59;
    }
    setColors(127, 100,100,100);
    setColors(minSet, 0,255,255);
  }
}

bool showClock = true;
void clockState(){
  //light 2 will be yellow if am, orange if pm
  //lights 3-6 will be binary for hour in 12-hour format (green)
  //lights 0&1 will represent part of hour: (blue)
  //  light 00 = min<15
  //  light 01 = min<30
  //  light 10 = min<45
  //  light 11 = min<60
  
  if(btn1rel) {
    genNum ++;
    //showClock = !showClock;
  }
  showClock = genNum%2==0;
  if(!showClock){
    clearColors();
    return;
  }
  
  byte hours = hourFormat12();
  bool isam = isAM();
  byte mins = minute();
  
  if(btn2){ //Show minutes detail if b2 is pressed
    clearColors();
    setColors(63, 0,45,30); //minute background
    setColors(mins, 0,0,255);
    
    if(second()%2 == 0) setColor(6, 0,0,0); //AMPM because a light is not used
    else if(isam) setColor(6, 200,255,0);
    else setColor(6, 255,50,0);
    
  }else{ //Otherwise show full time
    if(second()%2 == 0) setColor(2, 0,0,0);
    else if(isam) setColor(2, 200,255,0);
    else setColor(2, 255,50,0);
    
    setColors(120, 0,0,0); //hour background
    setColors(3, 0,0,0); //minute background
    
    hours = hours << 3;
    setColors(hours, 0,255,0);
    
    mins = mins/15;
    setColors(mins, 0,0,255);
  }
}

void setBrightnessState(){
  if(bothbtnrel){ //Confirmation with both buttons
    confirmFlash();
    setState(CLOCK_STATE);
  }else{
    if(btn1rel && ledStrength < 1){ //left button released
      ledStrength += 0.05;
    } 
    if(btn2rel && ledStrength > 0.05){ //right button released
      ledStrength -= 0.05;
    }
    setColors(127,255,255,255);
    setColor(0, 255,0,0);
    setColor(3, 0,255,0);
    setColor(6, 0,0,255);
    
    if(ledStrength < 0.05) ledStrength = 0.05;
    if(ledStrength > 1) ledStrength = 1;
  }
}

void configState(){
  setColors(127, 100,170,170);
  setColors(configFlags,  255,60,0);
  
  if(millis() % 1000 > 500)
    setColors(1<<genNum, 255,255,0);
  
  if(bothbtnrel){
    configFlags ^= 1 << genNum;
    
    wearLeveling.open(CONFIGVAR_START); //Save to eeprom
    wearLeveling.writeRec(WL_REC configFlags);
  }else if(btn1rel){
    genNum = (genNum+1)%7;
  }else if(btn2rel){
    genNum --;
    if(genNum < 0) genNum = 6;
  }
}

void alarmState(){
  uint16_t i;
  for(byte i=0; i< NEO_COUNT; i++) {
    setColor(i, Wheel(((i * 256 / NEO_COUNT) + genNum) & 255));
  }
  genNum += 20;
  if(genNum>256*5) genNum=0;
  
  unsigned long mil = millis();
  if(mil%7000 < 5000 && (mil%7000)%2000 < 1000){
     analogWrite(MOTOR_PIN, 1023);
  }else{
     analogWrite(MOTOR_PIN, 0);
  }
  
  if(btn1 && btn2){
    Serial.print("ALSTP");
    setState(CLOCK_STATE);
  }
}

void showBatteryState(){
  displayBatteryColors();
  Serial.print("Battery ");
  Serial.println(batteryLevel);
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

float lastLightLevel[3];
byte lastLightLevelIndex = 0;
void autoLightLevel(){
  if((configFlags & CONFIG_LIGHTLEVEL) != CONFIG_LIGHTLEVEL) 
    return; //Auto light level disabled
  
  float light = checkLightLevel();
  lastLightLevel[lastLightLevelIndex] = light;
  lastLightLevelIndex = (lastLightLevelIndex+1)%3;
  
  light = 0;
  for(byte i = 0; i < 3; i++){
    light += lastLightLevel[i];
  }
  light /= 3;
  
  if(light < 0.05) light = 0.05;
  if(light > 1) light = 1;
  ledStrength = light;
}

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
