#include "acc.h"

void ACC(float actualTimeBetweenVehicles, S32 distanceToVehicle, float leadVehicleVelocity)
{
    if(actualTimeBetweenVehicles > MAXIMUM_TIME_BETWEEN_VEHICLES) //No vehicle to follow or too far away. (Zone A)
    {
        controlMotors(INITIAL_MOTOR_POWER, BRAKE_OFF);
        /*Drive accordingly to normal Cruise Control*/
    }
    else if(actualTimeBetweenVehicles < MINIMUM_TIME_BETWEEN_VEHICLES) //Vehicle too close. (Zone E)
    {
        //brake();
        slowDown(MOTOR_POWER_ADJUST);
    }
    else
    {
        if(leadVehicleVelocity > vehicle.vFront)
        {//Vehicle in front drives faster than set speed.
            if((DESIRED_TIME_BETWEEN_VEHICLES - MAXIMUM_DEVIATION) > actualTimeBetweenVehicles &&
                MINIMUM_TIME_BETWEEN_VEHICLES < actualTimeBetweenVehicles)
            {//Vehicle in front is too close to cruise but not close enought to brake. (Zone D)
                slowDown(MOTOR_POWER_ADJUST);
            }
            else
            {  //(Zone C)
                maintainDistance();
            }
        }
        else //Vehicle in front drives slower than set speed.
        {
            if((DESIRED_TIME_BETWEEN_VEHICLES + MAXIMUM_DEVIATION) >= actualTimeBetweenVehicles &&
               (DESIRED_TIME_BETWEEN_VEHICLES - MAXIMUM_DEVIATION) <= actualTimeBetweenVehicles)
            {//Within tolerance. (Zone C)
                maintainDistance();
            }
            else
            {//(Zone B)
                speedUp(MOTOR_POWER_ADJUST);
            }
        }
        acc.firstDistanceMeasurement = acc.secondDistanceMeasurement;
    }
}


float convertDistanceToTime(S32 distance)
{
    float resultTime;

    if(vehicle.vFront > MINIMUM_VELOCITY_FOR_CONVERT)
    {
        resultTime = (distance / CM_PER_M) / vehicle.vFront;
    }
    else if (vehicle.sonarReading > MINIMUM_DISTANCE_FOR_ACC) //Read
    {
        resultTime = (distance / CM_PER_M) / MINIMUM_VELOCITY_FOR_CONVERT;
    }
    else
    {
        resultTime = 0.0;
    }

    return resultTime;
}

float calculateLeadVehicleVelocity(S32 distanceToVehicle)
{
    float velocityOfLeadVehicle = 0;
    S32 currentTime = getSysTime();

    if(acc.lastTimeRead == 0)
    {
        acc.firstDistanceMeasurement = distanceToVehicle;
        acc.lastTimeRead = currentTime;
    }
    else
    {
        acc.secondDistanceMeasurement = distanceToVehicle;

        velocityOfLeadVehicle = ((float)(acc.secondDistanceMeasurement - acc.firstDistanceMeasurement) / 
                                 (float)(currentTime - acc.lastTimeRead) * (float)MS_PER_SEC / (float)CM_PER_M) + vehicle.vFront;
    }

    acc.lastTimeRead = currentTime;

    return velocityOfLeadVehicle;
}

void slowDown(U8 motorPowerAdjust)
{
    S32 adjustedThrottle = (acc.throttleAmount - (floor((acc.throttleAmount - 1) / 100.0) * motorPowerAdjust));

    setThrottleAmount(adjustedThrottle);

    controlMotors(acc.throttleAmount, BRAKE_OFF);
}

void speedUp(U8 motorPowerAdjust)
{
    S32 adjustedThrottle = (acc.throttleAmount + (floor((acc.throttleAmount - 1) / 100.0) * motorPowerAdjust));

    setThrottleAmount(adjustedThrottle);

    controlMotors(acc.throttleAmount, BRAKE_OFF);
}

void maintainDistance()
{
    acc.maintainCounter ++;

    if(acc.maintainCounter > MAINTAIN_TIMES_BEFORE_ACTION)
    {
        /*Within accepted boundries - Maybe calibrate (very litte) to better match leading vehicle*/
        if(acc.throttleAmount <= MINIMUM_POWER_FOR_DRIVE)
        {
            if(acc.firstDistanceMeasurement > acc.secondDistanceMeasurement) //Mindre afstand
            {
                setThrottleAmount(acc.throttleAmount - 1);
                controlMotors(acc.throttleAmount, BRAKE_OFF);
            }
            else if(acc.firstDistanceMeasurement < acc.secondDistanceMeasurement)
            {
                setThrottleAmount(acc.throttleAmount + 1);
                controlMotors(acc.throttleAmount, BRAKE_OFF);
            }
        }
        acc.maintainCounter = 0;
    }
}

void setThrottleAmount(S32 throttle)
{
    if(throttle > 0)
    {
        acc.throttleAmount = 0;
    }
    else if(throttle < INITIAL_MOTOR_POWER)
    {
        acc.throttleAmount = INITIAL_MOTOR_POWER;
    }
    else
    {
        acc.throttleAmount = throttle;        
    }
}

void initACCStruck()
{
    acc.lastTimeRead = 0;
    acc.firstDistanceMeasurement = 0;
    acc.secondDistanceMeasurement = 0;
    acc.throttleAmount = INITIAL_MOTOR_POWER;
    acc.distanceSinceBrake = 0;
}
