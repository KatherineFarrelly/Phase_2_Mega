/*
 * This is the lead cell header file for the Automated Soil Weighing System
 * ECE 485 002
 * Cole Craft
 * 
 * Description: This file contains the setup functions for the libraries
 * and for the load cell peripherals connected to the Arduino MCU
 */

#ifndef loadcell_h
#define loadcell_h

  void LoadCellSetup();
  void ZeroScales();
  void PrintZero();

  void calibrate(int loadcell);

#endif
