#include "Motor.h"
#include "Defines.h"

Motor::Motor(){
  
}

void Motor::pulseMotor(int strength, int length){
  analogWrite(MOTOR_PIN, strength);
  delay(length);
  analogWrite(MOTOR_PIN, 0);
}
void Motor::pulseMotorRepeat(int strength, int length, int del, int count){
  for(int i = 0; i < count; i++){
    pulseMotor(strength,length);
    delay(del);
  }
}