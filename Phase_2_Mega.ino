
/*
 * This is the main loop for the Automated Soil Weighing System
 * ECE 485 002
 * Cole Craft / Jordan Boerger
 * Rewritten by Katherine Farrelly
 * 
 * Description: This file contains the main loop used to control
 * the Automated Soil Weighing System.
 */

 /*
  * Katherine's Comments
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

    
    int posIndex = 0; //Iterator through pos array

    int row2 = 0;
    int cmdvsval = 0;
    char charstepnum[] = {0,0,0,0,0,0,0,0,0,0};
    char command = 0;
    int numsteps = 0;

// Put all setup functions here, to run once:
void setup() { 
  Serial.begin(SERIALBAUD);     //Begins serial connection
  Serial.println("Booting...");
  row2 = 0;
  cmdvsval = 0;
  charstepnum[0] = 0;
  charstepnum[1] = 0;
  charstepnum[2] = 0;
  charstepnum[3] = 0;
  charstepnum[4] = 0;
  command = 0;
  numsteps = 0;
  motor_pin_setup();            //Sets up all pins
  limitSwitchPinSetup();
  SolenoidPinSetup();
  LoadCellSetup();

  delay(STARTUPDELAY);          //Startup pause to allow pins to settle outputs
  
  //Katherine's Comments - this calls xPath and yPath for position 0.
  
  x = INITIALPOSITION;          //Sets initial positions to 0
  y = INITIALPOSITION;
  
  Serial.println("Welcome");    //Welcome serial output and display commands
  Serial.println("Commands:");
  Serial.println("Start: s, Reset: r");
}

//Main Loop
void loop() {
//Commands: c - calibrate, space - estop, s - start, h - home, p - pause, r - reset
//Katherine's Comments - lol the code literally only implements two of these. I want a lot finer control than just these commands anyway.
  if(Serial.available()){
    if(!cmdvsval){
      command = Serial.read();
      cmdvsval = 1;
    }else{
      charstepnum[cmdvsval - 1] = Serial.read();
      if(charstepnum[cmdvsval-1] < '0' || charstepnum[cmdvsval-1] > '9'){
        charstepnum[cmdvsval-1] = 0;
        strToInt();
        cmdvsval = 0;
      }else if(cmdvsval >= 5){
        strToInt();
        cmdvsval = 0;
      }else{
        cmdvsval++;
      }
    } 
  }
  if(numsteps){
    switch(command){
      case 'i':
        x = xPath(x, x+numsteps);
      break;
  
      case 'k':
        x = xPath(x, x-numsteps);
      break;
  
      case 'j':
        y = yPath(y, y+numsteps);
      break;
  
      case 'l':
        y = yPath(y, y-numsteps);
      break;
  
      case 'u':
      setZUp();
      spin_Z(numsteps,STEPSPEED);
      break;
  
      case 'o':
      setZDown();
      spin_Z(numsteps,STEPSPEED);
      break;
  
      case 'y':
      OpenAllClaws();
      break;
  
      case 'h':
      CloseAllClaws();
      break;
  
      case 'n':
      Serial.print('N');
      break;

      case 'r':
      motorReset();
      x = INITIALPOSITION;
      y = INITIALPOSITION;
      break;

      case 'z':
      ZeroScales();
      PrintZero();
      Serial.print('N');
      break;
      
      case 't':
      calibrate(numsteps - 1);
      Serial.print('N');
      break;
      
      default:
      break;
    }
    Serial.print('D');
    numsteps = 0;
    command = 0;
  }
  
/*    if(temp == 's' || temp == 'S'){
      while(row2 < 12){
        Serial.println("Points: " + sizeof(pos));
        //PathTracking
        x = xPath(x,pos[posIndex][ARRAYXPOS]);
        y = yPath(y,pos[posIndex][ARRAYYPOS]);

        //Tare
        ZeroScales(); //Katherine's Comments - wait why are we taring EVERY SINGLE TIME WE TAKE A SAMPLE???????????????????????
        
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

void strToInt(){
  int i = 0;
  numsteps = 1;
  if(!charstepnum[i]){
    return;
  }
  numsteps = 0;
  while(i < 5){
    if(charstepnum[i] != 0){
      numsteps = numsteps * 10;
      numsteps += (charstepnum[i] - '0');
    }else{
      return;
    }
    i++;
  }
}

