/*
 * This is the pin assignment file for the Automated Soil Weighing System
 * ECE 485 002
 * Jordan Boerger
 * 
 * Description: This file contains the pin definitions for the Arduino UNO 
 * GPIO pins used by the source code. This file should be included in all 
 * files where GPIO pins are used.
 */


#ifndef pins_h
#define pins_h

// Motor pins
  #define STEPX 2
  #define DIRX 5
  #define ENPIN 8

// Limit switch pins
  #define SWITCH1 9
  
// Load cell pins
#define DOUT  3
#define CLK  2

// Solenoid pins

// Test pins
#define LEDPIN 13

#endif
