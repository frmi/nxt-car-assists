#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "nxt_interface.h"
#include "tcs.h"
#include "edc.h"
#include "abs.h"
#include "acc.h"
#include "aeb.h"
#include "eaeb.h"
#include "laneControl.h"

enum {
    BRAKE_OFF,
    BRAKE_ON
};

enum {
    BUTTON_RELEASED,
    BUTTON_PRESSED
};

typedef struct ControllerStruct{
    S32 steeringAmount;
    S32 throttleAmount;
    U8 buttonA;
    U8 buttonB;
    U8 buttonX;
    U8 buttonY;
    U8 buttonLB;
    U8 buttonRB;
    U8 abs;
    U8 edc;
    U8 tcs;
    U8 aeb;
    U8 eaeb;
    U8 acc;
    U8 lka;
} ControllerStruct;
ControllerStruct controller;

typedef struct TurnStruct
{
    S32 steeringAngle;
    S32 turnDegrees;
    S8 turnDegreesActivated;
} TurnStruct;
TurnStruct steer;

S8 appliedPower;
S32 appliedMode;
S32 appliedSteering;
U8 btReceiveBuf[ARRAY_SIZE];

void calibrateSteering();
void receiveBT();
void controlSteering();
void controlMotors (S32 speed, S32 mode);
S8 getSteeringAmount();
S8 getThrottleAmount();
U8 getButtonA();
U8 getButtonB();
U8 getButtonX();
U8 getButtonY();
U8 getButtonLB();
U8 getButtonRB();
U8 getABS();
U8 getEDC();
U8 getTCS();
U8 getAEB();
U8 getEAEB();
U8 getLKA();
U8 getACC();
void initTurnStruct();
void turnDegrees(S32 degrees);
void turnDegreesLaneControl(S32 degrees);

#endif
