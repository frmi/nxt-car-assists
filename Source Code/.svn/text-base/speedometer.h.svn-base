#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "nxt_interface.h"
#include "constants.h"

typedef struct MotorStruct
{
    U8 id;
    U8 lockState; // Tells if the wheel is locked
    float velocity; // applied velocity
    S32 brakeLockedTick; // total amount of ticks rotated when the wheel was last locked by the brake
} MotorStruct;

typedef struct VehicleStruct
{
    float vFront;  // real velocity
    float vBack; // applied average velocity
    float vFrontRounds;
    S32 sonarReading;
    MotorStruct leftMotor;
    MotorStruct rightMotor;
} VehicleStruct;
VehicleStruct vehicle;

typedef struct TickCounter
{
    S8 oldIndexFront;
    S8 newIndexFront;
    S8 oldIndexBack;
    S8 newIndexBack;
    S32 backDegreesArrayLeft[TICK_ARRAY_SIZE];
    S32 backDegreesArrayRight[TICK_ARRAY_SIZE];
    float frontDegreesArray[TICK_ARRAY_SIZE];
} TickCounter;
TickCounter tickCounter;

void speedometerInitialise();

void updateSpeedometerData();

void calculateVelocity();

void addToArrayFront(float item);

void addToArrayBack(S32 leftItem, S32 rightItem);

S16 convertRawDataToTicks(S16 rawData);

#endif
