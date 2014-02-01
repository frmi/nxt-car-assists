#include "speedometer.h"

/* Local prototypes */
float calculateVelocityBack(U8 id);

void speedometerInitialise(){
    int i; 

    vehicle.vFront = 0;
    vehicle.vBack  = 0;
    vehicle.leftMotor.id = LEFT_MOTOR;
    vehicle.leftMotor.velocity  = 0;
    vehicle.rightMotor.id = RIGHT_MOTOR;
    vehicle.rightMotor.velocity  = 0;
    vehicle.vFrontRounds = 0;

    tickCounter.oldIndexFront = 0;
    tickCounter.newIndexFront = -1;
    tickCounter.oldIndexBack = 0;
    tickCounter.newIndexBack = -1;

     for (i = 0; i < TICK_ARRAY_SIZE; i++) {
        tickCounter.frontDegreesArray[i] = 0.0;
        tickCounter.backDegreesArrayLeft[i] = 0;
        tickCounter.backDegreesArrayRight[i] = 0;
    }
}

void updateSpeedometerData()
{

    S16 rawData = getRotationSensor();
    S16 currentTick = convertRawDataToTicks(rawData);

    // Handling bad data from rotation sensor
    if (currentTick == -1)
    {
        currentTick = rotationSensor.lastTick;
    }

    if((currentTick+2) % 4 == rotationSensor.secondToLastTick)
    {
        if ((currentTick+1) % 4 == rotationSensor.lastTick)
        {
            rotationSensor.ticks++;
            rotationSensor.secondToLastTick = rotationSensor.lastTick;
        }
        else if ((currentTick+3) % 4 == rotationSensor.lastTick)
        {
            rotationSensor.ticks--;
            rotationSensor.secondToLastTick = rotationSensor.lastTick;
        }
    }
    rotationSensor.lastTick = currentTick;

    addToArrayFront(rotationSensor.ticks * (360 / 16.0));
    addToArrayBack(-motorGetCount(LEFT_MOTOR), -motorGetCount(RIGHT_MOTOR));
}

void calculateVelocity()
{
    /* BackWheel speedometer */
    vehicle.rightMotor.velocity = calculateVelocityBack(vehicle.rightMotor.id);
    vehicle.leftMotor.velocity = calculateVelocityBack(vehicle.leftMotor.id);

    vehicle.vBack = (vehicle.leftMotor.velocity + vehicle.rightMotor.velocity) / 2;

    /* FrontWheel speedometer */
    float degreeDiff = tickCounter.frontDegreesArray[tickCounter.newIndexFront] 
                        - tickCounter.frontDegreesArray[tickCounter.oldIndexFront];
    float degreePerMs = degreeDiff / 250.0;
    float roundsPerSec = (degreePerMs * 1000) / 360.0;
    vehicle.vFront = roundsPerSec * WHEEL_CIRC;

}

float calculateVelocityBack(U8 id)
{
    S32 degreeDiff;
    if(id == LEFT_MOTOR){
        degreeDiff = tickCounter.backDegreesArrayLeft[tickCounter.newIndexBack] 
                            - tickCounter.backDegreesArrayLeft[tickCounter.oldIndexBack];
    } else
    {
        degreeDiff = tickCounter.backDegreesArrayRight[tickCounter.newIndexBack] 
                            - tickCounter.backDegreesArrayRight[tickCounter.oldIndexBack];
    }
    float degreePerMs = degreeDiff / 250.0;
    float roundsPerSec = (degreePerMs * 1000) / 360.0;
    float metersPerSecond = roundsPerSec * WHEEL_CIRC * GEAR_RATIO;

    return metersPerSecond;
}

void addToArrayFront(float item){
    tickCounter.newIndexFront = tickCounter.oldIndexFront;
    tickCounter.oldIndexFront = (tickCounter.oldIndexFront+1) % TICK_ARRAY_SIZE;
    tickCounter.frontDegreesArray[tickCounter.newIndexFront] = item;
}

void addToArrayBack(S32 leftItem, S32 rightItem){
    tickCounter.newIndexBack = tickCounter.oldIndexBack;
    tickCounter.oldIndexBack = (tickCounter.oldIndexBack+1) % TICK_ARRAY_SIZE;
    tickCounter.backDegreesArrayLeft[tickCounter.newIndexBack] = leftItem;
    tickCounter.backDegreesArrayRight[tickCounter.newIndexBack] = rightItem;
}

S16 convertRawDataToTicks(S16 rawData)
{
    if(950 < rawData && rawData < 1050)
    {
        return 0;
    }
    else if(500 < rawData && rawData < 575)
    {
        return 1;
    }
    else if (300 < rawData && rawData < 400)
    {
        return 2;
    }
    else if (700 < rawData && rawData < 850)
    {
        return 3;
    }
    else
    {
        return -1;
    }
}

