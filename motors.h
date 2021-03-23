/*
 * This is the motor header file for the Automated Soil Weighing System
 * ECE 485 002
 * Cole Craft
 * 
 * Description: This file contains the setup functions for the libraries
 * and for the motor peripherals connected to the Arduino MCU
 */

#ifndef motors_h
#define motors_h

#include <Arduino.h>

#define XMAXSTEPS 1000
#define YMAXSTEPS 1000

void motor_pin_setup(); //The motor_pin_setup function declares the pins for the peripherals
  
void setXLeft();
void setXRight();

void setYReverse();
void setYForward();

void setZUp();
void setZDown();
  
int spin_X(int Steps, int Speed);
int spin_Y(int Steps, int Speed);
int spin_Z(int Steps, int Speed);

void motorReset();

int xPath(int currentPosition, int desiredPosition);
int yPath(int currentPosition, int desiredPosition);

void motorUT();

#endif
