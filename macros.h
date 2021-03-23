/*
 * This is contains the number definitions
 * ECE 485 002
 * Jordan Boerger
 * 
 * Description: This file contains any extra definitions for numbers used consistantly
 * throughout the code.s
 */

#ifndef macros_h
#define macros_h

//Main
#define SERIALBAUD 9600
#define STARTUPDELAY 3000
#define ZLIFTDISTANCE 2500
#define INVALIDPOSVALUE -1
#define PATHPOINTS 5
#define XY 2
#define INITIALPOSITION 0
#define ARRAYXPOS 0
#define ARRAYYPOS 1
#define YROWSTEPDISTANCE 1530;

//Motors
#define STEPSPEED 500
#define RESETDISTANCE 30000
#define MINSTEPS 0
#define MOTORTESTDELAY 1000

//Loadcells
#define NUMCUPS 180
#define MGTOG 100
#define PRINTDELAY 1000
#define ROWSPERTRAY 12
#define TRAYSPERCYCLE 5
#define COLUMNSPERTRAY 3

//Solenoids
#define SOLENOIDTESTDELAY 1000

//Limit Switch
#define LIMITSWITCHRESET 0

#define SWITCH1MASK B1
#define SWITCH2MASK B10
#define SWITCH3MASK B100
#define SWITCH4MASK B1000
#define SWITCH5MASK B10000
#define SWITCH6MASK B100000
#define SWITCH7MASK B1000000
#define SWITCH8MASK B10000000
#define SWITCH9MASK B100000000
#define SWITCH10MASK B1000000000
#define SWITCH11MASK B10000000000
#define SWITCH12MASK B100000000000

#endif
