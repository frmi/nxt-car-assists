#include "edc.h"

S32 edc(S32 power, S32 steeringAngle){

    if (EDC_flag == ON)
    {
        // Multiplying with PI and dividing by 180 to convert degrees into radians
        float diameter = (2 * WHEELBASE) / sin((fabs(steeringAngle) * PI) / 180);
        // take into account that we power can be positive (going backwards) and negative (going forwards)
        float edcRatio = 1 - ((2 * TRACK) / diameter);

        // Multiply by 1.5 to make it work in practice on our vehicle.
        power = (S32) (power * edcRatio * 1.5);

        if (power > 0 && power < 65){
            power = 65;
        }
        else if (power < 0 && power > -65){
            power = -65;
        }
    }

    return power;
}
