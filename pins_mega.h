/*
 * This is the pin assignment file for the Automated Soil Weighing System
 * ECE 485 002
 * Jordan Boerger
 * 
 * Description: This file contains the pin definitions for the Arduino MEGA 
 * GPIO pins used by the source code. This file should be included in all 
 * files where GPIO pins are used.
 */


#ifndef pins_mega_h
#define pins_mega_h

// Motor pins
  // X MC1
  #define X_DIR   32  //PC5
  #define X_PUL   30  //PC7
  #define X_EN    28  //PA6

  // Y MC2
  #define Y_DIR   33  //PC4
  #define Y_PUL   31  //PC6
  #define Y_EN    29  //PA7

  // Z1 MC3
  #define Z1_DIR  38 //PD7
  #define Z1_PUL  36 //PC1
  #define Z1_EN   34  //PC3

  // Z2 MC4
  #define Z2_DIR  39 //PG2
  #define Z2_PUL  37 //PC0
  #define Z2_EN   35  //PC2

// Limit switch pins
  #define SWITCH1   22  //PA0
  #define SWITCH2   10  //PB4
  #define SWITCH3   11  //PB5
  #define SWITCH4   12  //PB6
  #define SWITCH5   26  //PA4
  #define SWITCH6   27  //PA5
  #define SWITCH7   49  //PL0
  #define SWITCH8   50  //PB3
  #define SWITCH9   48  //PL1
  #define SWITCH10  47  //PL2
  #define SWITCH11  46  //PL3
  #define SWITCH12  45  //PL4
  
// Load cell pins
  #define LC1 13  //PB7
  #define LC2 6   //PH3
  #define LC3 4   //PG5
  #define LC4 5   //PE3
  #define LC5 3   //PE5
  
  #define CLK 2   //PE4
  
// Solenoid pins
  #define SN1 44  //PH6
  #define SN2 43  //PG0
  #define SN3 9   //PL7
  #define SN4 42  //PL6
  #define SN5 41  //PL5

//Timer Relay
  #define TR  0   //PF0

// Test pins
  #define LEDPIN 13

#endif
