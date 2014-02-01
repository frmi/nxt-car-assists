#include "tcs.h"

S32 tcs(S32 power, struct MotorStruct motor){
    S32 adjustedPower = power;

    // Check if TCS is activated
    if (TCS_flag == ON && fabs(vehicle.vFront) > ALLOWED_SPEED_WITHOUT_TCS)
    {
        // get ratio between front and rear wheel
        float ratio = (fabs(motor.velocity) - fabs(vehicle.vFront)) / fabs(motor.velocity);
        
        // adjust power on the rear wheel   
        if (ratio > TCS_TARGET_SLIP_RATIO)
        {
            // adjust power to match front wheels rotation speed
            float reducedPowerRatio = 1 - ratio;
            // and increase the power by 20% to allow acceleration
            adjustedPower = (power * reducedPowerRatio) * TCS_SLIP_RATIO;
        } 
    }

    return adjustedPower;
}
