/*
 * This is the load cell implementation file for the Automated Soil Weighing System
 * ECE 485 002
 * Cole Craft
 * 
 * Description: This file contains the functions pertaining
 * to setting up and using the load cell for weight measurements.
 * 
 * pins for Arduino Uno R3
 * 2 -> HX711 CLK
 * 3 -> DOUT
 * 5V -> VCC
 * GND -> GND 
 */

//#include "Arduino.h"
#include "HX711.h"  // You must have this library in your arduino library folder
#include "pins_mega.h"
#include "loadcell.h"
#include "macros.h"

HX711 scale1, scale2, scale3, scale4, scale5;
long loadcellzero[] = {0,0,0,0,0}; //these are the zero values of each load cell

// Sets up loadcell pins
void LoadCellSetup(){
  //Begins scale
  scale1.begin(LC1,CLK);
  scale2.begin(LC2,CLK);
  scale3.begin(LC3,CLK);
  scale4.begin(LC4,CLK);
  scale5.begin(LC5,CLK);

  //Zeros scales
  ZeroScales();
}

// This sets the zero values of all the load cells.
void ZeroScales(){
  loadcellzero[0] = scale1.read();
  loadcellzero[1] = scale2.read();
  loadcellzero[2] = scale3.read();
  loadcellzero[3] = scale4.read();
  loadcellzero[4] = scale5.read();
}

// Calibrates load cells given an input weight
void calibrate(int loadcell){
  long outweight;
  switch(loadcell){
    case 0:
    outweight = scale1.read();
    break;

    case 1:
    outweight = scale2.read();
    break;

    case 2:
    outweight = scale3.read();
    break;
    
    case 3:
    outweight = scale4.read();
    break;

    case 4:
    outweight = scale5.read();
    break;

    default:
    break;
  }
  Serial.print(outweight);
}

// Prints all zeros
void PrintZero(){
  for(int j = 0; j < 5; j++){
    Serial.print(loadcellzero[j]);
    Serial.print(" ");
  }
}
