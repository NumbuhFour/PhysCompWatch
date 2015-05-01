#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_NeoPixel.h>
#include <Time.h>
#include <EEPROM.h>
#include <wl.h>

#define NEO_PIN    12
#define NEO_COUNT   7

#define BTN1_PIN   16 //Left button
#define BTN2_PIN    3  //Right button

#define MOTOR_PIN  10 //Vibration motor

#define PHOTO_PIN   0

#define STATES      8
#define CLOCK_STATE 0

#define DATA_START 32

#define CONFIG_LIGHTLEVEL 1

Adafruit_NeoPixel pix = Adafruit_NeoPixel(NEO_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

// Calibration offsets
float magxOffset = 2.55;
float magyOffset = 27.95;

uint32_t colors[NEO_COUNT];
float ledStrength = 0.05;

byte tickDelay = 50;

bool btn1 = false;
bool lbtn1 = false; //Last value of btn1
bool btn2 = false;
bool lbtn2 = false; //Last value of btn2
bool btn1rel = false; //Buttons released
bool btn2rel = false;
bool bothbtnrel = false; //Both buttons released at about the same time

//Counts how long you're holding config access
int configHoldCounter = 0;

int state = 0;//What function state we are currently in

//Config waits for buttons to be released first
bool buttonsReleased = false;

int compassReading;

byte lastMin = 0;

struct timeEEVar{
  byte hours;
  byte mins;
} _timeEEVar;
long TIMEEEVAR_START;

byte configFlags = 1;
long CONFIGVAR_START;

wl wearLeveling(&writer, &reader);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for(byte i = 0; i < NEO_COUNT; i++) colors[0] = pix.Color(0,0,0);
  
  pinMode(BTN1_PIN, INPUT);
  pinMode(BTN2_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); //Power notifier
  
  pix.begin();
  pix.show(); // Initialize all pixels to 'off'
  
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    
    while(1){
      setColors(127, 255,0,0);
      pushColors();
      delay(500);
      clearColors();
      pushColors();
      delay(500);
    }
  }
  
  //Loading EEPROM data
  
  TIMEEEVAR_START = DATA_START;
  if(wearLeveling.exists(TIMEEEVAR_START) == WL_NOK){
    Serial.println("Time var does not exist");
    //Create it at timeEEVar_Start position with WL_XX length where XX is status length 8,16,24,32,64
    wearLeveling.create(TIMEEEVAR_START, WL_16, sizeof(_timeEEVar));
    wearLeveling.clear();
    
    //Write new data to the var
    _timeEEVar.hours = hour();
    _timeEEVar.mins = minute();
    wearLeveling.open(TIMEEEVAR_START);
    wearLeveling.writeRec(WL_REC _timeEEVar);
  }else{
    Serial.println("Time var exists.");
    wearLeveling.open(TIMEEEVAR_START);
    wearLeveling.readRec(WL_REC _timeEEVar);
    
    Serial.print("Time set to ");
    Serial.print(_timeEEVar.hours);
    Serial.print(":");
    Serial.println(_timeEEVar.mins);
    setTime(_timeEEVar.hours, _timeEEVar.mins,0,0,0,0);
  }
  
  CONFIGVAR_START = TIMEEEVAR_START + wearLeveling.memSize();
  if(wearLeveling.exists(CONFIGVAR_START)==WL_NOK){
    Serial.println("configVar does not exist");
    wearLeveling.create(CONFIGVAR_START, WL_8, sizeof(configFlags));
    wearLeveling.clear();
    
    configFlags = 1;
    wearLeveling.open(CONFIGVAR_START);
    wearLeveling.writeRec(WL_REC configFlags); 
  }else{
    Serial.println("Config var exists");
    wearLeveling.open(CONFIGVAR_START);
    wearLeveling.readRec(WL_REC configFlags);
  }
  
  lastMin = minute();
  
  startupFlash();
  Serial.println("Startup complete.");
}
uint32_t compassTimer = millis();

void loop() {
  checkButtons();
  
  if(btn1 && btn2){
    configHoldCounter += tickDelay;
  }else{
    configHoldCounter = 0;
  }
  
  if(configHoldCounter >= 1000 && state != -1){// Config accessed!
    setColors(85,255,0,0);
    setColors(42,240,255,0);
    pushColors();
    
    analogWrite(MOTOR_PIN, 1023);
    delay(100);
    analogWrite(MOTOR_PIN, 0);
    delay(50);
    
    analogWrite(MOTOR_PIN, 1023);
    delay(100);
    analogWrite(MOTOR_PIN, 0);
    delay(50);
    
    analogWrite(MOTOR_PIN, 1023);
    delay(100);
    analogWrite(MOTOR_PIN, 0);
    delay(50);
    
    configHoldCounter = 0;
    buttonsReleased = false;
    
    Serial.println("State picker accessed.");
    setState(-1);
    
  }
  
  loopDaemons();
  loopState();
    
  byte mins = minute();
  if(lastMin != mins){
    lastMin = mins;
    writeClockToEEPROM();
  }
  
  pushColors();
  digitalWrite(13,LOW);
  delay(tickDelay);
  lbtn1 = btn1;
  lbtn2 = btn2;
  
   //Power light. If things are frozen, light should remain on.
   digitalWrite(13,HIGH);
}

void writer(unsigned long address, byte data)
{
  EEPROM.write(address,data);
}

byte reader(unsigned long address){
  return EEPROM.read(address);
}

void writeClockToEEPROM(){
  _timeEEVar.hours = hour();
  _timeEEVar.mins = minute();
  Serial.print("Writing time to EEPROM ");
  Serial.print(_timeEEVar.hours);
  Serial.print(":");
  Serial.println(_timeEEVar.mins);
  wearLeveling.open(TIMEEEVAR_START);
  wearLeveling.writeRec(WL_REC _timeEEVar);
}

void setColor(byte index, uint32_t color){
  colors[index] = color;
}
void setColor(byte index, byte r, byte g, byte b){
  colors[index] = pix.Color((byte)((float)r * ledStrength),
                            (byte)((float)g * ledStrength),
                            (byte)((float)b * ledStrength));
}
void setColors(byte indicies, byte r, byte g, byte b){
  for(byte i = 0; i < NEO_COUNT; i++){
    if(indicies & 1 == 1){ //Lit at that index
      colors[i] = pix.Color((byte)((float)r * ledStrength),
                                (byte)((float)g * ledStrength),
                                (byte)((float)b * ledStrength));
    }
    indicies = indicies >> 1;
  }
}

void clearColors(){
  setColors(127, 0,0,0);
}

void pushColors(){
  for(byte i = 0; i < NEO_COUNT; i++){
    pix.setPixelColor(i, colors[i]);
  }
  pix.show();
}

void loopDaemons(){
  autoLightLevel();
}

void loopState(){
  switch(state){
    case -1: statePicker(); break;
    case CLOCK_STATE: clockState(); break;
    case 1: compassState(); break;
    case 2: flashlight(); break;
    case 3: screensaver(); break;
    case 4: configState(); break;
    case 5: setTimeState(); break;
    case 6: setBrightnessState(); break;
    case 7: buttonPlay(); break;
    default:
      state = CLOCK_STATE;
      break;
  }
}

void checkButtons(){
  btn1 = digitalRead(BTN1_PIN)==HIGH;
  btn2 = digitalRead(BTN2_PIN)==HIGH;
  btn1rel = lbtn1 && !btn1;
  btn2rel = lbtn2 && !btn2;
  bothbtnrel = ((btn1rel && btn2) || (btn2rel && btn1));
}

float checkLightLevel(){
  float light = analogRead(PHOTO_PIN);
  
  light = (light/1024)*2;
  if(light > 1) light = 1;
  if(light <= 0.05) light = 0.05;
  
  return light;
}

/************************************************************************************************ Rando Funcs *************************************************************************************************/
void startupFlash(){
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
 delay(80);
 setColor(NEO_COUNT-1, 0,0,0);
 pushColors();
 analogWrite(MOTOR_PIN, 1023);
 delay(150);
 analogWrite(MOTOR_PIN, 0);
 delay(100);
 analogWrite(MOTOR_PIN, 1023);
 delay(150);
 analogWrite(MOTOR_PIN, 0);
}

void errorFlash(){
    
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

void confirmFlash(){
    
    clearColors();
    setColors(42,0,255,0);
    pushColors();
    analogWrite(MOTOR_PIN,1023);
    delay(150);
    analogWrite(MOTOR_PIN,0);
    delay(50);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
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


void compassCheck() {
  // if millis() or timer wraps around, we'll just reset it
  //if (compassTimer > millis()) compassTimer = millis();

  // approximately every 10 seconds or so, update time
  //if (millis() - compassTimer > 50) {
    /* Get a new sensor event */
    sensors_event_t event; 
    mag.getEvent(&event);

    float Pi = 3.14159;

    //compassTimer = millis(); // reset the timer

    // Calculate the angle of the vector y,x
    float heading = (atan2(event.magnetic.y + magyOffset,event.magnetic.x + magxOffset) * 180) / Pi;

  Serial.print("Compass: x");
  Serial.print(event.magnetic.x);
  Serial.print(" y");
  Serial.print(event.magnetic.y);
    // Normalize to 0-360
    if (heading < 0)
    {
      heading = 360 + heading;
    }
    compassReading = heading; 
  //}  
}  

void compassDirection(int compassHeading) 
{
  Serial.print(" Direction: ");
  Serial.println(compassHeading);
  
  compassHeading -= 70; //Calibration;
  if(compassHeading>=360) compassHeading -= 360;
  clearColors();

  unsigned int ledDir = 2;
  
  //Use this part of the code to determine which way you need to go.
  //Remember: this is not the direction you are heading, it is the direction to the destination (north = forward).

  if (compassHeading > 280) {
      setColor(0, 255,0,0);
      setColor(6, 255,0,0);
      return;
  }
  
  ledDir = compassHeading / 20;
  
  if(ledDir >= NEO_COUNT){
    Serial.print("LED ERROR ");
    Serial.println(ledDir);
    setColors(127, 255,0,0);
    return;
  }
  setColor(ledDir, 255, 255, 255);
}


/************************************************** STATES **************************************************/
//Generic global number, reset each state switch
int genNum = 0;

//NOT A STATE. Defined here for access to state globals
void setState(int s){
  genNum = 0;
  state = s;
  clearColors();
  btn1rel = btn2rel = false;
  analogWrite(MOTOR_PIN,0);
  Serial.print("State changed to ");
  Serial.println(s);
  
  while(btn1 || btn2) {
    checkButtons(); 
    delay(tickDelay);
  }
  lbtn1 = lbtn2 = false;
  bothbtnrel = false;
  btn1rel = btn2rel = false;
}

void statePicker(){
  if(!buttonsReleased){
    buttonsReleased = !btn1 && !lbtn1 && !btn2 && !lbtn2;
    return;
  }
  
  
  if(bothbtnrel){ //both buttons released
    if(genNum < STATES){
      confirmFlash();
      setState(genNum);
    }else{
      errorFlash();
      genNum = 0;
      clearColors();
    }
  }else if(btn1rel){ //left button released
    genNum ++;
    if(genNum > 127) genNum = 0;
  }else if(btn2rel){ //right button released
    genNum --;
    if(genNum < 0) genNum = 127;
  } 
  setColors(127, 100,100,100);
  setColors(genNum, 255,0,255);
}

//Test state. LEDs react to buttons
void buttonPlay(){
  if(btn1) {
    setColor(0, 255,0,255);
    setColor(1, 255,0,255);
  }else{
    setColor(0, 0,0,0);
    setColor(1, 0,0,0);
  }
  if(btn2){
    setColor(5, 255,0,255);
    setColor(6, 255,0,255);
  }else{
    setColor(5, 0,0,0);
    setColor(6, 0,0,0);
  }
}

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
    showClock = !showClock;
  }
  if(!showClock){
    clearColors();
    return;
  }
  
  byte hours = hourFormat12();
  bool isam = isAM();
  byte mins = minute();
  
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

/************************************************** DAEMONS **************************************************/

float lastLightLevel[3];
byte lastLightLevelIndex = 0;
void autoLightLevel(){
  if((configFlags & CONFIG_LIGHTLEVEL) != 1) 
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