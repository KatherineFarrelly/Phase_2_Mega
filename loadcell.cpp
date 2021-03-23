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
int currentCup;
int trayCount;
double Tray[NUMCUPS];
int row;
int calibrationFactor = 52200;

// Sets up loadcell pins
void LoadCellSetup(){
  //Begins scale
  scale1.begin(LC1,CLK);
  scale2.begin(LC2,CLK);
  scale3.begin(LC3,CLK);
  scale4.begin(LC4,CLK);
  scale5.begin(LC5,CLK);

  //Sets scale to found calibration factor
  scale1.set_scale(calibrationFactor);
  scale2.set_scale(calibrationFactor);
  scale3.set_scale(calibrationFactor);
  scale4.set_scale(calibrationFactor);
  scale5.set_scale(calibrationFactor);

  //Zeros scales
  ZeroScales();
}

// Zeros all scales to 0
void ZeroScales(){
  scale1.tare();
  scale2.tare();
  scale3.tare();
  scale4.tare();
  scale5.tare();
}

// Receives weights from all load cells
void CaptureWeight(){
  ZeroScales();
  
  currentCup++;
  if(trayCount > sizeof(Tray)-1)
  {
    Serial.println("PLEASE RESET SYSTEM WITH INPUT 'r' ");
  }
  Tray[trayCount] = MGTOG*scale1.get_units();
 
  trayCount += 3;
  Tray[trayCount] = MGTOG*scale2.get_units();
 
  trayCount += 3;
  Tray[trayCount] = MGTOG*scale3.get_units();
 
  trayCount += 3;
  Tray[trayCount] = MGTOG*scale4.get_units();
  
  trayCount += 3;
  Tray[trayCount] = MGTOG*scale5.get_units();
  
  trayCount -= 11;
  if(trayCount == 3+15*row)
  {
    trayCount += 12;
    row += 1;
  }
  delay(PRINTDELAY);
}

// Resets weigh storage array to 0
void ResetWeight(){
  Serial.println("Weighing new batch of trays");
  for(int r = 0; r < NUMCUPS; r++)
  {
    Tray[r] = 0;
  }
  trayCount = 0;
  currentCup = 1;
  row = 0;
}

// Prints all weights in storage weight
void PrintWeight(){
  int t = 0;
  Serial.println("Tray 1                Tray2                 Tray3                 Tray4                 Tray5");
  for(int j = 0; j < ROWSPERTRAY; j++)
  {
    for(int i = 0; i < TRAYSPERCYCLE; i++)
    {
      for(int h = 0; h < COLUMNSPERTRAY; h++)
      {
        Serial.print(Tray[t],1); 
        Serial.print("g");
        Serial.print(" ");
        t++;
      }
      Serial.print("    ");
     }
     Serial.println();
  }
}

// Grabs single weight from single load cell
void SingleWeight(){
  double SingleTray;
  
  if(Serial.available())
  {
    //temp char for serial input commands
    char temp = Serial.read();

  if(temp == '1')
    {
      SingleTray = MGTOG*scale1.get_units();
      Serial.println();
      Serial.print("Current Weight is: ");
      Serial.print(SingleTray,1);
      Serial.println("g");
    }
  else if(temp == '2')
    {
      SingleTray = MGTOG*scale2.get_units();
      Serial.println();
      Serial.print("Current Weight is: ");
      Serial.print(SingleTray,1);
      Serial.println("g");
    }
  else if(temp == '3')
    {
      SingleTray = MGTOG*scale3.get_units();
      Serial.println();
      Serial.print("Current Weight is: ");
      Serial.print(SingleTray,1);
      Serial.println("g");
    }
  else if(temp == '4')
    {
      SingleTray = MGTOG*scale4.get_units();
      Serial.println();
      Serial.print("Current Weight is: ");
      Serial.print(SingleTray,1);
      Serial.println("g");
    }
  else if(temp == '5')
    {
      SingleTray = MGTOG*scale5.get_units();
      Serial.println();
      Serial.print("Current Weight is: ");
      Serial.print(SingleTray,1);
      Serial.println("g");
    }
  else if (temp == 't'){
    ZeroScales();
    Serial.println("Zeroed");
  }
  
    
  }
}

// Calibrate function **Needs work
void calibrate(double intendedWeight){
  double readWeight;
  float calibration_factor = 0;
  
  scale1.set_scale();
  scale1.tare();
  Serial.println(calibration_factor);
  if(Serial.available()){
    //temp char for serial input commands
    char temp = Serial.read();

    if(temp == 'c'){
      while(readWeight != intendedWeight){
        scale1.set_scale(calibration_factor);
        readWeight = MGTOG*scale1.get_units();
        if(readWeight != intendedWeight){
          calibration_factor += 10;
        }
        Serial.println(readWeight);
      }
      Serial.print("Calibration factor is: ");
      Serial.println(calibration_factor);
    }
  }
}
