/*
 * This is the motor implementation file for the Automated Soil Weighing System
 * ECE 485 002
 * Cole Craft
 * 
 * Description: This file contains the functions pertaining
 * to driving the attached stepper motors through their external controllers
 */

 /*
  * Patrick's Comments
  * 
  * There's 5 functions of interest here. xPath and yPath (identical),
  * Spin_X and Spin_Y (identical), and Spin_Z.
  * All of these seem fine right now, but I don't think the way Spin_X and Spin_Y 
  * handle limit switches can be trusted.
  * If a limit switch is hit, the robot will move 300 steps in the opposite direction
  * WHICH ARE NOT TRACKED by xPath and yPath afaik.
  * 
  * IMO at some point the return value of the xPath and yPath functions should be changed
  * to reflect the actual number of steps the robot takes in Spin_X and Spin_Y.
  * 
  * ALSO, Spin_X and Spin_Y get called one at a time which seems slow. We should be able to 
  * move both motors at the same time. Why don't we? Considering making this change as well.
  * 
  * NOTE: since the tray motor has no limit switches, Spin_Z is handled with no limit
  * switch cases. This means we have no idea where the tray height is until we zero it ourselves.
  * 
  * This means we'll need a height zeroing routine for the tray table motor. This should be easy -
  * We can just move the tray table up until we see the claws can reach it, tell the robot to stop,
  * and set that as the calibration point. This is the main thing that needs to be added here.
  * 
  * X is forward/backward, Y is sideways
  */

#include "motors.h"
#include "pins_mega.h"
#include "limitswitch.h"
#include "macros.h"
// X
// 194 = 1 mm ish

// Y
// 255 = 1 mm ish

int xDir;
int yDir;

// Sets up motor pins
void motor_pin_setup() {
  //Connection for the X axis motor 
  pinMode(X_PUL,OUTPUT);
  pinMode(X_DIR,OUTPUT);
  pinMode(X_EN,OUTPUT);
    
  //Connection for the Y axis motor
  pinMode(Y_PUL,OUTPUT);
  pinMode(Y_DIR,OUTPUT);
  pinMode(Y_EN,OUTPUT);

  //Connection for the Z1 axis motor
  pinMode(Z1_PUL,OUTPUT);
  pinMode(Z1_DIR,OUTPUT);
  pinMode(Z1_EN,OUTPUT);

  //Connection for the Z2 axis motor
  pinMode(Z2_PUL,OUTPUT);
  pinMode(Z2_DIR,OUTPUT);
  pinMode(Z2_EN,OUTPUT);

  //Enable pin
  digitalWrite(X_EN,HIGH);
  digitalWrite(Y_EN,HIGH);
  digitalWrite(Z1_EN,HIGH);
  digitalWrite(Z2_EN,HIGH);
}

//PATH TRACKING FUNCTIONS
  // X path tracking function
  int xPath(int currentPosition, int desiredPosition){
    if(currentPosition > desiredPosition){
      // set direction (-)
      // while position is > move backwards
      // if limit switch hit, stop
      // once position is = intended or within threshold, stop
      
      setXLeft();
      int event = spin_X(currentPosition-desiredPosition,STEPSPEED);
      if(!event){
        desiredPosition = MINSTEPS; //Min steps
      }
    }
    
    else if(currentPosition < desiredPosition){
      // set direction (+)
      // while position is < move forwards
      // if limit switch hit, stop
      // once position is = intended or within threshold, stop
  
      setXRight();
      int event = spin_X(desiredPosition-currentPosition,STEPSPEED);
      if(!event){
        desiredPosition = XMAXSTEPS; //Max steps
      }
    }
    return desiredPosition; 
    //Patrick's comments - both path functions return the position that was inputted to the function.
    //I think this works fine.
  }

  // Y path tracking
  int yPath(int currentPosition, int desiredPosition){
    if(currentPosition > desiredPosition){
      // set direction (-)
      // while position is > move backwards
      // if limit switch hit, stop
      // once position is = intended or within threshold, stop
      
      setYReverse;
      int event = spin_Y(currentPosition-desiredPosition,STEPSPEED);
      if(!event){
        desiredPosition = MINSTEPS; //Min steps
      }
    }
    
    else if(currentPosition < desiredPosition){
      // set direction (+)
      // while position is < move forwards
      // if limit switch hit, stop
      // once position is = intended or within threshold, stop
  
      setYForward();
      int event = spin_Y(desiredPosition-currentPosition,STEPSPEED);
      if(!event){
        desiredPosition = YMAXSTEPS; //Max steps
      }
    }
    return desiredPosition;
  }
  
//SPIN MOTOR
  //Makes motor spin until limit switch is hit. Returns current step value to set the position variables with
  int spin_X(int Steps, int Speed)
  {
    int switches;
    digitalWrite(X_EN,LOW); //Enables motor controller
    for(int x = 0; x < Steps; x++) {  //Loop that moves motor until limit switch is hit or step count is reached
      switches = readLimitSwitches();
      if((switches & SWITCH4MASK)) //Patrick's Comments - these two if statements check if a switch was hit. Otherwise, it just moves to the specified position.
      {
        setXRight();
        for(int i = 0; i < 300; i++){
          digitalWrite(X_PUL,HIGH);
          delayMicroseconds(Speed);
          digitalWrite(X_PUL,LOW);
          delayMicroseconds(Speed);
        }
        return 0;
      }
      else if((switches & SWITCH3MASK)){
        setXLeft();
        for(int i = 0; i < 300; i++){
          digitalWrite(X_PUL,HIGH);
          delayMicroseconds(Speed);
          digitalWrite(X_PUL,LOW);
          delayMicroseconds(Speed);
        }
        return 0;
      }
      digitalWrite(X_PUL,HIGH);
      delayMicroseconds(Speed);
      digitalWrite(X_PUL,LOW);
      delayMicroseconds(Speed);
    }
    digitalWrite(X_EN,HIGH);
    return 1;
  }

  int spin_Y(int Steps, int Speed)
  {
    int switches;
    digitalWrite(Y_EN,LOW);
    for(int y = 0; y < Steps; y++) {
      switches = readLimitSwitches();
      if((switches & SWITCH5MASK))
      {
        setYForward();
        for(int i = 0; i < 300; i++){
          digitalWrite(Y_PUL,HIGH);
          delayMicroseconds(Speed);
          digitalWrite(Y_PUL,LOW);
          delayMicroseconds(Speed);
        }
        return 0;
      }
      else if((switches & SWITCH6MASK))
      {
        setYReverse();
        for(int i = 0; i < 300; i++){
          digitalWrite(Y_PUL,HIGH);
          delayMicroseconds(Speed);
          digitalWrite(Y_PUL,LOW);
          delayMicroseconds(Speed);
        }
        return 0;
      }
      digitalWrite(Y_PUL,HIGH);
      delayMicroseconds(Speed);
      digitalWrite(Y_PUL,LOW);
      delayMicroseconds(Speed);
    }
    digitalWrite(Y_EN,HIGH);
    return 1;
  }

  int spin_Z(int Steps, int Speed)
  {
    digitalWrite(Z1_EN,LOW);
    digitalWrite(Z2_EN,LOW);
    for(int z = 0; z < Steps; z++) {
      if(readLimitSwitches()) //Patrick's Comments - this was clearly meant to be implemented as a way to zero the height.
      {
        //return 0;
      }
      digitalWrite(Z1_PUL,HIGH);
      digitalWrite(Z2_PUL,HIGH);
      delayMicroseconds(Speed);
      digitalWrite(Z1_PUL,LOW);
      digitalWrite(Z2_PUL,LOW);
      delayMicroseconds(Speed);
    }
    digitalWrite(Z1_EN,HIGH);
    digitalWrite(Z2_EN,HIGH);
    return 1;
  }

//RESET  
  // Reset Motor position to initial position
  void motorReset(){
    setXLeft();
    setYReverse();
    int x = 1;
    int y = 1;
    while(x || y){
      if(x){
        x = spin_X(RESETDISTANCE,500);
      }
      if(y){
        y = spin_Y(RESETDISTANCE,500);
      }
  }
}

//UNIT TEST
  // Spins each motor. Be careful as all motors spin at once
  void motorUT(){
    spin_X(1000,500);
    spin_Y(1000,500);
    spin_Z(1000,500);
    delay(MOTORTESTDELAY);
  }

//SET DIRECTION
  //set direction of X motor to be clockwise, Right
  void setXRight()
  {
    digitalWrite(X_DIR,HIGH);
    xDir = 1;
  }

  //set direction of X motor to be counter-clockwise, Left
  void setXLeft()
  {
    digitalWrite(X_DIR,LOW);
    xDir = 0;
  }

  //set direction of Y motor to be clockwise, Reverse
  void setYReverse()
  {
    digitalWrite(Y_DIR,HIGH);
    yDir = 1;
  }

  //set direction of Y motor to be counter-clockwise, Forward
  void setYForward()
  {
    digitalWrite(Y_DIR,LOW);
    yDir = 0;
  }

  //set direction of Z to be clockwise
  void setZUp()
  {
    digitalWrite(Z1_DIR,HIGH);
    digitalWrite(Z2_DIR,HIGH);
  }

  //set direction of Z to be counter-clockwise
  void setZDown()
  {
    digitalWrite(Z1_DIR,LOW);
    digitalWrite(Z2_DIR,LOW);
  }
