#include "aeb.h"

void aebInitialise(){
    aeb.activated = 0;
    aeb.lastTimeReadPath = 0;
    aeb.lastReadTick = 0;
    aeb.distanceToObj1 = -1;
    aeb.distanceToObj2 = -1;
    aeb.distanceFromPath = -1;
    aeb.distanceIndex = 0;
    aeb.eaebState = 0;

    int i;
    for(i = 0; i < SAMPLE_COUNT; i++){
        aeb.distances[i] = -1;
    }
}

float getBrakeDistance () {
    float brakeDistance = (pow(vehicle.vFront,2) / (2 * COEF_OF_FRICTION * STD_GRAVITY)) * CM_PER_M;

    return brakeDistance;
}

float getDistanceTravelled () 
{
    float newRead = tickCounter.frontDegreesArray[tickCounter.newIndexFront];
    float diff = newRead - aeb.lastReadTick;
    aeb.lastReadTick = newRead;

    return diff / (360 / (WHEEL_DIAMETER * 100));
}

int updateDistanceFromPath() {
    U32 currentTime = getSysTime();

    int result = -1;
    //  fetch the first distance to distanceToObj1
    //  update variable for when distance was last read
    //  return -1 to indicate no distance was calculated
    
    if (aeb.lastTimeReadPath == 0)
    {
        aeb.distanceToObj1 = vehicle.sonarReading;
        aeb.lastTimeReadPath = currentTime;
        result = -1;
    }
    else if (currentTime - aeb.lastTimeReadPath >= AEB_TIME_BETWEEN_READINGS)
    {
        //  time since last read is above or equal TIME_BETWEEN_READINGS
        //  read new distance, calculate distanceTravelled
        //  reset the variable for when distance was last read
        //  return distance form object
        
        aeb.distanceToObj2 = vehicle.sonarReading;
        
        if (aeb.distanceToObj2 < 255)
        {
            float distanceTravelled = getDistanceTravelled();

            float angleToObj2 = acos((pow(aeb.distanceToObj2,2) + pow(distanceTravelled,2) - pow(aeb.distanceToObj1,2)) / (2 * aeb.distanceToObj2 * distanceTravelled));
            aeb.distanceFromPath = aeb.distanceToObj2 * sin(PI - angleToObj2);

            aeb.distanceToObj1 = aeb.distanceToObj2;
            aeb.lastTimeReadPath = currentTime;

            if(aeb.distanceFromPath <= VEHICLE_WIDTH)
            {
                result = 1;
            }
        }
    }

    return result;
}

float getDistanceToImpact(){
    float result;
    if (updateDistanceFromPath() > -1)
    {
        result = sqrt(pow(aeb.distanceToObj2,2) - pow(aeb.distanceFromPath,2));
    }
    else
    {
        result = -1;
    }
    return result;
}

void runAEB()
{
    if (vehicle.vFront < 0.01 || AEB_flag == OFF) 
    {
        aeb.activated = 0;
        return;
    }

    int i;
    U8 criticalDistance = 0;

    float brakeDistance = getBrakeDistance() + SONAR_ERROR_MARGIN;

    for (i = 0; i < SAMPLE_COUNT; i++)
    {   
        if ((aeb.distances[i] <= (brakeDistance + BRAKE_SAFE_ZONE)) && aeb.distances[i] > -1)
        {
            criticalDistance++;
        }

    }

    if (criticalDistance >= 2 || aeb.eaebState != STATE_NOT_ACTIVATED)
    {
        aeb.activated = 1;   // run AEB system
        if(EAEB_flag == ON)
        {
            runEAEB(); // run EAEB system
        }
    }
    else 
    {
        aeb.activated = 0;
    }
}

void addDistanceToArray(float item){
    aeb.distances[aeb.distanceIndex] = item;
    aeb.distanceIndex = (aeb.distanceIndex + 1) % SAMPLE_COUNT;
}
