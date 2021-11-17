/*
 * This is the limit switch implementation file for the Automated Soil Weighing System
 * ECE 485 002
 * Jordan Boerger
 * 
 * Description: This file contains the functions pertaining
 * to reading in the attached limit switches
 */

/*
 * Katherine's Comments
 * 
 * nothing to say here really it just bitmasks the switches.
 * should probably remove the test code with the LED.
 * I have no idea if all these switches actually work.
 * 
 * Using digitalRead is slow compared to reading port IO directly but it may not
 * matter too much.
 */
 
#include <Arduino.h>
#include "pins_mega.h"
#include "motors.h"
#include "macros.h"

// Setup for limit switches. INPUT_PULLUP use to generate output when connected to gnd
void limitSwitchPinSetup() {
   pinMode(SWITCH1, INPUT_PULLUP);
   pinMode(SWITCH2, INPUT_PULLUP);
   pinMode(SWITCH3, INPUT_PULLUP);
   pinMode(SWITCH4, INPUT_PULLUP);
   pinMode(SWITCH5, INPUT_PULLUP);
   pinMode(SWITCH6, INPUT_PULLUP);
   pinMode(SWITCH7, INPUT_PULLUP);
   pinMode(SWITCH8, INPUT_PULLUP);
   pinMode(SWITCH9, INPUT_PULLUP);
   pinMode(SWITCH10, INPUT_PULLUP);
   pinMode(SWITCH11, INPUT_PULLUP);
   pinMode(SWITCH12, INPUT_PULLUP);
   pinMode(LEDPIN, OUTPUT);
}

// Reads all limit switches at once. You can then & the function output with the mask respective to the desired switch
int readLimitSwitches() {
  int base = LIMITSWITCHRESET;
  //Bit shifts to allow masks to retrieve appropriate bit
  base = base | !digitalRead(SWITCH1);
  base = base | !digitalRead(SWITCH2)  << 1;
  base = base | !digitalRead(SWITCH3)  << 2;
  base = base | !digitalRead(SWITCH4)  << 3;
  base = base | !digitalRead(SWITCH5)  << 4;
  base = base | !digitalRead(SWITCH6)  << 5;
  base = base | !digitalRead(SWITCH7)  << 6;
  base = base | !digitalRead(SWITCH8)  << 7;
  base = base | !digitalRead(SWITCH9)  << 8;
  base = base | !digitalRead(SWITCH10) << 9;
  base = base | !digitalRead(SWITCH11) << 10;
  base = base | !digitalRead(SWITCH12) << 11;
  
  return base;
}

// Unit test for limit switch. Turns on LED
void limitSwitchUT(int pin){
  if(digitalRead(pin) == LOW){
    digitalWrite(LEDPIN,HIGH);
  }
  else{
    digitalWrite(LEDPIN,LOW);
  }
}
