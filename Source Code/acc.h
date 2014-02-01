#ifndef ACC_H
#define ACC_H

#include "nxt_interface.h"
#include "constants.h"
#include "speedometer.h"
#include "abs.h"
#include "sonar.h"

S8 ACC_flag = OFF;

typedef struct ACCStruct
{
    U8 lastTimeRead;
    S16 firstDistanceMeasurement;
    S16 secondDistanceMeasurement;
    S16 distanceSinceBrake;
    S32 throttleAmount;
    U8 maintainCounter;
    U8 speedUpCounter;
    U8 slowDownCounter;
} ACCStruct;
ACCStruct acc;

void ACC(float actualTimeBetweenVehicles, S32 distanceToVehicle, float leadVehicleVelocity);

float convertDistanceToTime(S32 distance);

float calculateLeadVehicleVelocity(S32 distanceToVehicle);

void slowDown(U8 motorPowerAdjust);

void speedUp(U8 motorPowerAdjust);

void maintainDistance();

void setThrottleAmount(S32 throttle);

void initACCStruck();

#endif
