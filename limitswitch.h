/*
 * This is the limit switch header for the Automated Soil Weighing System
 * ECE 485 002
 * Jordan Boerger
 * 
 * Description: This file contains the setup functions for the limit switch
 * peripherals used by the Arduino
 */

#ifndef limitswitch_h
#define limitswitch_h

#include <Arduino.h>

void limitSwitchPinSetup();

int readLimitSwitches();

#endif
