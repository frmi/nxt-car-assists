#ifndef LANE_CONTROL_H
#define LANE_CONTROL_H

#include "nxt_interface.h"
#include "eaeb.h"
#include "controller.h"

static U8 calibratedLaneControl;

typedef struct ColourStruct
{
    U16 roadMarkingRight;
    U16 roadMarkingLeft;
    U16 floorRight;
    U16 floorLeft;

}ColourStruct;
ColourStruct colour;


S8 LKA_flag = OFF;

void calibrateLaneControlSensor();

void calibrateRoadMarkingColour();

void calibrateFloorColour();

U8 detectRoadMarking();

void adjustVehicle(U8 roadMarking);

S32 calculateTurnAngle(U8 roadMarking);

void emptyArray(U8 array[ARRAY_SIZE]);

#endif
