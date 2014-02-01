#include "laneControl.h"
#include <math.h>

U32 currentTime;
U8 turnTimes = 0;


//Adskilt funktion - Skal kun køres 1 gang!
void calibrateLaneControlSensor()
{
    colour.roadMarkingRight = 0;
    colour.roadMarkingLeft = 0;
    colour.floorRight = 0;
    colour.floorLeft = 0;

    // detects color of road marking
    calibrateRoadMarkingColour();

    /* gets motor count to be used when checking how much 
       to drive forward when calibrating */

    S32 tempMotorCount = motorGetCount(LEFT_MOTOR);

    while((motorGetCount(LEFT_MOTOR)) >= tempMotorCount - CALIBRATE_COLOUR_DIST)
    {
        controlMotors(-100, BRAKE_OFF); // drive forward
    }

    // detects color of floor
    calibrateFloorColour();    
}

void calibrateRoadMarkingColour()
{
    colour.roadMarkingRight = getLightSensorRight();
    colour.roadMarkingLeft = getLightSensorLeft();
}

void calibrateFloorColour()
{
    colour.floorRight = getLightSensorRight();
    colour.floorLeft = getLightSensorLeft();
}

U8 detectRoadMarking() 
{
    /* detect whether we are on the left or the right road marking */
    if (getLightSensorLeft() >= (colour.roadMarkingLeft - COLOUR_SAFETY) && getLightSensorLeft() <= (colour.roadMarkingLeft + COLOUR_SAFETY))
    {
        return LEFT_ROADMARKING_VALUE;
    }
    else if (getLightSensorRight() >= (colour.roadMarkingRight - COLOUR_SAFETY) && getLightSensorRight() <= (colour.roadMarkingRight + COLOUR_SAFETY))
    {
        return RIGHT_ROADMARKING_VALUE;
    }
    else
    {
        return 0;
    }
}


void adjustVehicle(U8 roadMarking)
{
    S32 turnAngle = calculateTurnAngle(roadMarking);
    
    if(turnAngle != 0)
    {
        steer.turnDegreesActivated = 1;

        /* Turn times is incremented each time the vehicle detects a marking.
           The third time it is incremented the vehicle turns with a greater angle to compensate for previous turns. */
        turnDegrees(turnAngle);
        turnTimes++;
        controlSteering();

        currentTime = getSysTime();

        while(getSysTime() - currentTime < BUSY_WAIT_TIME_LANECONTROL)
        {
            // busy wait - keep turning
        }

        currentTime = getSysTime();

        /* Not sure BUSY_WAIT_TIME_LANECONTROL is high enough (2ms) to actually drive forward. */
        while(getSysTime() - currentTime < BUSY_WAIT_TIME_LANECONTROL)
        {
           controlMotors(ADJUSTING_SPEED_FORWARD, BRAKE_OFF); //Drives forward.
        }

        aeb.activated = 1;
        emptyArray(btReceiveBuf);

        steer.turnDegreesActivated = 0;
    }
}

/* Not sure it has any effect but test before removal */
void emptyArray(U8 array[ARRAY_SIZE])
{
    int i = 0;
    for(i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = 0;
    }
}

S32 calculateTurnAngle(U8 roadMarking)
{
    S32 turnAngle = 0;

    /* if the car is driving fast, it will turn less than if it is driving slow
       this is to prevent crashing */
    
    if(turnTimes >= TURNS_BEFORE_ANGLE_INCREASE)
    {
        turnAngle = MAX_TURNING_ANGLE; //Every third turn the turnAngle increases.
        turnTimes = 0; //Resets turnTimes.
    }else
    {
        turnAngle = MIN_TURNING_ANGLE; //Standard turn.
    }

    /* if the car has a lane on the left side, turn right
       else if the car has a lane on the right turn left */

    if (roadMarking == LEFT_ROADMARKING_VALUE)
    {
        return turnAngle; // turn right
    }
    else if (roadMarking == RIGHT_ROADMARKING_VALUE)
    {
        return -turnAngle; // turn left
    }
    else
    {
        return 0; // does not turn if already on the road
    }
}
