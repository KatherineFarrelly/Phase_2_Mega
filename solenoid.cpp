/*
 * This is the solenoid implementation file for the Automated Soil Weighing System
 * ECE 485 002
 * Jordan Boerger
 * 
 * Description: This file contains the functions pertaining
 * to triggering the attatched solenoids
 */

#include <Arduino.h>
#include "pins_mega.h"
#include "macros.h"

// Sets up pins for solenoids
void SolenoidPinSetup(){ 
  pinMode(SN1,OUTPUT);
  pinMode(SN2,OUTPUT);
  pinMode(SN3,OUTPUT);
  pinMode(SN4,OUTPUT);
  pinMode(SN5,OUTPUT);
}

// Opens single claw defined by pin
void OpenClaw(int pin){
  digitalWrite(pin,HIGH);
}

// Closes single claw defined by pin
void CloseClaw(int pin){
  digitalWrite(pin,LOW);
}

// Opens all claws
void OpenAllClaws(){
  OpenClaw(SN1);
  OpenClaw(SN2);
  OpenClaw(SN3);
  OpenClaw(SN4);
  OpenClaw(SN5);
}

// Closes all claws
void CloseAllClaws(){
  //delay(500);
  CloseClaw(SN1);
  CloseClaw(SN2);
  CloseClaw(SN3);
  CloseClaw(SN4);
  CloseClaw(SN5);
}

// Allows you to extend solenoid by pressing a limit switch
void SolenoidWSwitch(int solenoidPin, int switchPin){
  if(digitalRead(switchPin) == LOW){
    OpenClaw(solenoidPin);
  }
  else{
    CloseClaw(solenoidPin);
  }
}

// Solenoid unit test based on pin, extends and retracts defined solenoid
void SolenoidUT(int pin){
  digitalWrite(pin,HIGH);
  delay(SOLENOIDTESTDELAY);
  digitalWrite(pin,LOW);
  delay(SOLENOIDTESTDELAY);
}
