#ifndef NXT_INTERFACE_H
#define NXT_INTERFACE_H

#include "mytypes.h"
#include "constants.h"
#include "tcs.h"
#include "edc.h"
#include "abs.h"
#include "aeb.h"
#include "eaeb.h"
#include "acc.h"
#include "laneControl.h"
#include "controller.h"
#include <math.h>

typedef enum {
	PORT_A,
	PORT_B,
	PORT_C
}MY_MOTOR_PORT_T;

typedef enum {
	PORT_1,
	PORT_2,
	PORT_3,
	PORT_4
}MY_SENSOR_PORT_T;

typedef struct RotationSensor
{
    S16 ticks;
    S16 secondToLastTick;
    S16 lastTick;
} RotationSensor;
RotationSensor rotationSensor;

S32 motorGetCount(U8 port);

void motorSetCount(U8 port, S32 count);

void motorSetSpeed(U8 port, S32 speed, S32 mode);

U32 sendBtPacket(U8 *buf, U32 bufLen);

U32 readBtPacket(U8 *buf, U32 bufLen);

U32 getSysTime();

void initBtConnection();

void termBtConnection();

/* LCD Display */
void displayUpdate();

void displayClear(U32 updateToo);

void displayGotoXY(S32 x, S32 y);

void displayString(const char *str);

void displayInt(S32 val, U32 places);

void displayFloat(float val);

void displayAssists();

/* Ultrasonic */
S32 getSonarSensor();

void initSonarSensor();

void termSonarSensor();

/* RotationSensor */
S16 getRotationSensor();

void termRotationSensor();

void initRotationSensor();

/* Light sensor */
void initLightSensor ();

void termLightSensor ();

U16 getLightSensorRight ();

U16 getLightSensorLeft ();

void waitMs(U32 ms);

/* Touch sensor */
U8 getTouchSensor(U8 port);

/* Sonic sensor */
S32 getSonarSensor();

/* NXT internal API */
U8 nxtEnterButton();

/* MISC */
void updateAssistStates();

#endif
