
/*
 * This is the main loop for the Automated Soil Weighing System
 * ECE 485 002
 * Cole Craft / Jordan Boerger
 * 
 * Description: This file contains the main loop used to control
 * the Automated Soil Weighing System.
 */

 /*
  * Patrick's Comments
  * 
  * ECE 484 Spring 2021
  * 
  * There are only two functions here. The setup sets up pins,
  * sets the arm (but not the tray table for the smaples!) to the initial position,
  * and starts up the serial comm port.
  * 
  * The loop checks for serial commands and runs them.
  * 
  * To Do:
  * -change command scheme so that the arm position and tray position can be directly controlled
  * -remove the 2D array, literally pointless
  * -actually have the tray set to the correct height during setup
  * 
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
    
    //Patrick's Comments - wait so every point for each sample is stored seperately? Why?
    //IMO this should be moved to the actual UI, not something done on the robot.
    //The robot can just move to positions commanded, it doesn't really need to store specific positions like this.
    //This way if theres an issue with the robot moving to specific positions, it can be tuned on the UI params instead of having to fix the Arduino code.
    
    int posIndex = 0; //Iterator through pos array

    int row2 = 0;
    int whatamidoing;
    
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
  
  //Patrick's Comments - this calls xPath and yPath for position 0.
  
  x = INITIALPOSITION;          //Sets initial positions to 0
  y = INITIALPOSITION;
  
  Serial.println("Welcome");    //Welcome serial output and display commands
  Serial.println("Commands:");
  Serial.println("Start: s, Reset: r");
}

//Main Loop
void loop() {
//Commands: c - calibrate, space - estop, s - start, h - home, p - pause, r - reset
//Patrick's Comments - lol the code literally only implements two of these. I want a lot finer control than just these commands anyway.
  if(Serial.available()){
    char temp = Serial.read();

    switch(temp){
      case 'i':
        x = xPath(x, x+100);
      break;

      case 'k':
        x = xPath(x, x-100);
      break;

      case 'j':
        y = yPath(y, y+100);
      break;

      case 'l':
        y = yPath(y, y-100);
      break;

      case 'u':
      setZUp();
      spin_Z(100,STEPSPEED);
      break;

      case 'o':
      setZDown();
      spin_Z(100,STEPSPEED);
      break;

      case 'y':
      OpenAllClaws();
      break;

      case 'h':
      CloseAllClaws();
      break;
      
      default:

      break;
    }
/*    if(temp == 's' || temp == 'S'){
      while(row2 < 12){
        Serial.println("Points: " + sizeof(pos));
        //PathTracking
        x = xPath(x,pos[posIndex][ARRAYXPOS]);
        y = yPath(y,pos[posIndex][ARRAYYPOS]);

        //Tare
        ZeroScales(); //Patrick's Comments - wait why are we taring EVERY SINGLE TIME WE TAKE A SAMPLE???????????????????????
        
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
          row2++;
        }
      }
    }
    else if(temp == 'r'){
      //Resets motor positions
      motorReset();
    }*/
  }
}
