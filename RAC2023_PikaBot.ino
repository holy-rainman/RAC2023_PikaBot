/*  DON'T FORGET TO INSTALL ARDUINO LIBRARY FOR:
    1. Cytron Motor Driver Library
    2. HCSR04
*/

#include "CytronMotorDriver.h"
CytronMD motorLeft(PWM_DIR,11,10);  
CytronMD motorRight(PWM_DIR,9,3); 

#include <HCSR04.h>
UltraSonicDistanceSensor distanceSensor(5,4);

#define BUTTON    2
#define IR_LEFT   A0
#define IR_RIGHT  A1
#define BUZZER    8

void setup() 
{ 
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(IR_LEFT,INPUT);
  pinMode(IR_RIGHT,INPUT);  
  pinMode(BUZZER,OUTPUT);
  Serial.begin(9600);
}

void loop() 
{ 
  Serial.println(distanceSensor.measureDistanceCm()); //Paparkan nilai ultrasonik
  //Jika jarak objek KURANG 10cm dari PikaBot 
  if(distanceSensor.measureDistanceCm()<10 && distanceSensor.measureDistanceCm()!=-1) 
  { //PikaBot henti
    motorLeft.setSpeed(0);
    motorRight.setSpeed(0); 
  }
  //Jika jarak objek MELEBIHI 10cm dari PikaBot -> IKUT GARISAN
  if(distanceSensor.measureDistanceCm()>=10)
  { //Pernyataan logik bagi MAJU mengikut garisan hitam
    if(digitalRead(IR_LEFT)==LOW && digitalRead(IR_RIGHT)==LOW) 
    { //PikaBot maju
      motorLeft.setSpeed(120);
      motorRight.setSpeed(120);
    }
    if(digitalRead(IR_LEFT)==HIGH)  
    { //Belok kiri jika IR kiri atas garisan
      motorLeft.setSpeed(-200);
      motorRight.setSpeed(120);
    }
    if(digitalRead(IR_RIGHT)==HIGH)
    { //Belok kanan jika IR kanan atas garisan
      motorLeft.setSpeed(120);
      motorRight.setSpeed(-200);
    }
  }
}
