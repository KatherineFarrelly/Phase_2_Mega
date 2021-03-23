
/*
 * This is the main loop for the Automated Soil Weighing System
 * ECE 485 002
 * Cole Craft / Jordan Boerger
 * 
 * Description: This file contains the main loop used to control
 * the Automated Soil Weighing System.
 */

#include "pins_mega.h"
#include "motors.h"
#include "limitswitch.h"
#include "solenoid.h"
#include "loadcell.h"
#include "macros.h"

    int x = INVALIDPOSVALUE; //Starts position values at -1
    int y = INVALIDPOSVALUE;
    int z = INVALIDPOSVALUE;
    
    char serialtmp; //Serial input value

    int pos[PATHPOINTS][XY] = {{0,0},{1400,0},{3000,0}}; //2D array containing each point you want gantry to move to. Will be restricted by limit switch

    int posIndex = 0; //Iterator through pos array

    int row = 0;
    
// Put all setup functions here, to run once:
void setup() { 
  Serial.begin(SERIALBAUD);     //Begins serial connection
  Serial.println("Booting...");
  
  motor_pin_setup();            //Sets up all pins
  limitSwitchPinSetup();
  SolenoidPinSetup();
  LoadCellSetup();

  delay(STARTUPDELAY);          //Startup pause to allow pins to settle outputs
  
  motorReset();                 //Resets motor position to back left
  x = INITIALPOSITION;          //Sets initial positions to 0
  y = INITIALPOSITION;
  
  Serial.println("Welcome");    //Welcome serial output and display commands
  Serial.println("Commands:");
  Serial.println("Start: s, Reset: r");
}

//Main Loop
void loop() {
//Commands: c - calibrate, space - estop, s - start, h - home, p - pause, r - reset
  if(Serial.available()){
    char temp = Serial.read();
    if(temp == 's' || temp == 'S'){
      while(row < 12){
        Serial.println("Points: " + sizeof(pos));
        //PathTracking
        x = xPath(x,pos[posIndex][ARRAYXPOS]);
        y = yPath(y,pos[posIndex][ARRAYYPOS]);

        //Tare
        ZeroScales();
        
        //Claw open
        OpenAllClaws();
        
        //Raise Z
        setZUp();
        spin_Z(ZLIFTDISTANCE,STEPSPEED);
  
        //Claw close
        CloseAllClaws();
          
        //Lower Z
        setZDown();
        spin_Z(ZLIFTDISTANCE,STEPSPEED);
        
        //Weigh
        CaptureWeight();
        
        //Raise Z
        setZUp();
        spin_Z(ZLIFTDISTANCE,STEPSPEED);
        
        //Claw open
        OpenAllClaws();
        
        //Lower Z
        setZDown();
        spin_Z(ZLIFTDISTANCE,STEPSPEED);
        
        //Claw close
        CloseAllClaws();

        //Increment Y axis
        pos[0][ARRAYYPOS] += YROWSTEPDISTANCE;
        
        //Repeat
        if(posIndex <= 2)
          posIndex++;
        else{
          posIndex = 0;
          row++;
        }
      }
    }
    else if(temp == 'r'){
      //Resets motor positions
      motorReset();
    }
  }
}
