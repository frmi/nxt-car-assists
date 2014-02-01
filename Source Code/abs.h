#ifndef ABS_H
#define ABS_H
#include "controller.h"
#include "speedometer.h"
#include "constants.h"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Contains a single function that slows down the engines,    *
* braking the engines at an optimal ratio.                   *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Global variables */
S8 ABS_flag = OFF;

//Slows down the vehicle at a rate optimizing braking distance
//If vehicle is stationary it applies brake mode to the motors
void brake();

#endif
