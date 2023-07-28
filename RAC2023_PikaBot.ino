#include "CytronMotorDriver.h"
CytronMD motorLeft  (PWM_PWM, 11, 10);
CytronMD motorRight (PWM_PWM, 9, 3);
#define IR_LEFT   A0
#define IR_RIGHT  A1
#define TRIGPIN   5
#define ECHOPIN   4

//Declare variable
long duration;
long distance;

void robotStop() {
  motorLeft.setSpeed(0);
  motorRight.setSpeed(0);
}
void robotMove(int speedLeft, int speedRight) {
  motorLeft.setSpeed(speedLeft);
  motorRight.setSpeed(speedRight);
}
void readUltrasonic(){ 
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = duration * 0.017;
}

void setup() {
  pinMode(IR_LEFT,  INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(TRIGPIN,  OUTPUT);
  pinMode(ECHOPIN,  INPUT);
}

void loop(){ 
  readUltrasonic();

  if(distance < 10) {
    robotStop();
  }
  if(distance >=10) {
    if (digitalRead(IR_LEFT)==LOW && digitalRead(IR_RIGHT)==LOW) {
      robotMove(200, 200);  //Robot moves forward
    }
    else if (digitalRead(IR_LEFT)==HIGH) {
      robotMove(0, 200);      //Robot turns left
    }
    else if (digitalRead(IR_RIGHT)==HIGH) {
      robotMove(200, 0);      //Robot turns right
    }
  }
}
