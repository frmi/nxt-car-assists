#include "controller.h"

// has to be run in initialiseTask
void calibrateSteering()
{
    S32 leftMost;
    S32 rightMost;
    U32 currentTime = getSysTime();

    motorSetSpeed(STEERING_MOTOR, -50, 1);
    while(currentTime + 500 > getSysTime())
    {
        
    }
    leftMost = motorGetCount(STEERING_MOTOR);

    motorSetSpeed(STEERING_MOTOR, 50, 1);
    currentTime = getSysTime();
    while(currentTime + 500 > getSysTime())
    {
        
    }
    rightMost = motorGetCount(STEERING_MOTOR);

    S32 mid = leftMost + rightMost;

    while(motorGetCount(STEERING_MOTOR) != mid){
        motorSetSpeed(STEERING_MOTOR, -30, 1);
    }
    motorSetCount(STEERING_MOTOR, 0);
}

void receiveBT(){
    static U8 btReceiveBuf[ARRAY_SIZE];

    readBtPacket(btReceiveBuf, ARRAY_SIZE);

    controller.steeringAmount  = (S8) btReceiveBuf[0];
    controller.throttleAmount  = (S8) btReceiveBuf[1];
    controller.throttleAmount *= -1; /* Invert this variable, to go in the right direction*/
    controller.buttonA         = btReceiveBuf[2];
    controller.buttonB         = btReceiveBuf[3];
    controller.buttonX         = btReceiveBuf[4];
    controller.buttonY         = btReceiveBuf[5];
    controller.buttonLB        = btReceiveBuf[6];
    controller.buttonRB        = btReceiveBuf[7];
    controller.abs             = btReceiveBuf[8];
    controller.tcs             = btReceiveBuf[9];
    controller.edc             = btReceiveBuf[10];
    controller.aeb             = btReceiveBuf[11];
    controller.eaeb            = btReceiveBuf[12];
    controller.acc             = btReceiveBuf[13];
    controller.lka             = btReceiveBuf[14];
}

void controlMotors (S32 speed, S32 mode) {
    if (speed > MAX_SPEED) 
        appliedPower = MAX_SPEED;
    else if (speed < -MAX_SPEED)
        appliedPower = -MAX_SPEED;
    else
        appliedPower = speed;
    
    S32 appliedPowerLeft = appliedPower;
    S32 appliedPowerRight = appliedPower;

    // Determine whether we are going straight or not to activate EDC
    if (steer.steeringAngle > NEUTRAL_DEAD_ZONE) // turn right with EDC ON
    {
        appliedPowerLeft = appliedPower;
        appliedPowerRight = edc(appliedPower, steer.steeringAngle);
    }
    else if (steer.steeringAngle < -NEUTRAL_DEAD_ZONE) // turn left with EDC ON
    {        
        appliedPowerLeft = edc(appliedPower, steer.steeringAngle);
        appliedPowerRight = appliedPower;
    }
    else // go straight 
    {
        appliedPowerLeft = appliedPower;
        appliedPowerRight = appliedPower;
    }

    appliedPowerLeft = tcs(appliedPowerLeft, vehicle.leftMotor);
    appliedPowerRight = tcs(appliedPowerRight, vehicle.rightMotor);
    
    motorSetSpeed(LEFT_MOTOR, appliedPowerLeft, mode);
    motorSetSpeed(RIGHT_MOTOR, appliedPowerRight, mode);
}

void controlSteering(){
    S32 steeringErr;
    S8 steeringAmountAdjusted;

    if(steer.turnDegreesActivated == 0) // don't turn while another task is using the motor for turning
    {
        // 10 corresponds to 0.1 on the C# side - this is the dead zone of the joystick
        if(controller.steeringAmount < JOYSTICK_LASH && controller.steeringAmount > -JOYSTICK_LASH)
        {
            steeringAmountAdjusted = 0;
        }
        else
        {
            steeringAmountAdjusted = controller.steeringAmount;
        }
    }
    else
    {
        steeringAmountAdjusted = steer.turnDegrees;
    }

    /* steering control */
    steer.steeringAngle = motorGetCount(STEERING_MOTOR);
    steeringErr = (STEERING_LIMIT * steeringAmountAdjusted) / 100 - steer.steeringAngle;
    
    appliedSteering = STEERING_P_GAIN * steeringErr;
    
    motorSetSpeed(STEERING_MOTOR, appliedSteering, 1);
}

S8 getSteeringAmount(){
    return controller.steeringAmount;
}

S8 getThrottleAmount(){
    return controller.throttleAmount;
}

U8 getButtonA(){
    return controller.buttonA;
}

U8 getButtonB(){
    return controller.buttonB;
}

U8 getButtonX(){
    return controller.buttonX;
}

U8 getButtonY(){
    return controller.buttonY;
}

U8 getButtonLB(){
    return controller.buttonLB;
}

U8 getABS(){
    return controller.abs;
}

U8 getEDC(){
    return controller.edc;
}

U8 getTCS(){
    return controller.tcs;
}

U8 getAEB(){
    return controller.aeb;
}

U8 getEAEB(){
    return controller.eaeb;
}

U8 getLKA(){
    return controller.lka;
}

U8 getACC(){
    return controller.acc;
}

void turnDegrees(S32 degrees) // remember to set turnDegreeActivated = 1 before and  = 0 after call!
{

    float deg = degrees;

    if(deg > 40)
    {
        deg = 40;
    }
    else if(deg < -40)
    {
        deg = -40;
    }

    steer.turnDegrees = (S32)(deg * 2.5);
}

void turnDegreesLaneControl(S32 degrees) // remember to set turnDegreeActivated = 1 before and  = 0 after call!
{
    float deg = degrees;

    if(deg > MAX_TURNING_ANGLE)
    {
        deg = MAX_TURNING_ANGLE;
    }
    else if(deg < -MAX_TURNING_ANGLE)
    {
        deg = -MAX_TURNING_ANGLE;
    }

    steer.turnDegrees = (S32)(deg * (100 / MAX_TURNING_ANGLE));
}

void initTurnStruct()
{
    steer.turnDegrees = 0;
    steer.turnDegreesActivated = 0;
}
