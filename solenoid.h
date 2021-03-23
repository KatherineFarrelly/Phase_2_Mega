/*
 * This is the solenoid header file for the Automated Soil Weighing System
 * ECE 485 002
 * Cole Craft
 * 
 * Description: This file contains the setup functions for the solenoids
 * attached to the Arduino
 */

#ifndef solenoid_h
#define solenoid_h

#include <Arduino.h>

void SolenoidPinSetup(); //The solenoid_pin_setup function declares the pins for the peripherals

void OpenClaw(int pin); //Extend solenoid to open claw

void CloseClaw(int pin); //Retract solenoid to close claw

void OpenAllClaws(); //Extend solenoid to open claw

void CloseAllClaws(); //Retract solenoid to close claw

void SolenoidUT(int pin);

void SolenoidWSwitch(int solenoidPin, int switchPin);

#endif
