#include "kernel.h"
#include "kernel_id.h"
#include "nxt_interface.h"
#include "controller.h"
#include "datalog.h"
#include "aeb.h"
#include "speedometer.h"
#include "ecrobot_interface.h"
#include "constants.h"
#include "abs.h"
#include "laneControl.h"
#include "sonar.h"

/* Task and counter declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(InitializeTask);
DeclareTask(DataLoggingTask);
DeclareTask(AEBTask);
DeclareTask(ControllerTask);
DeclareTask(ReadRawDataTask);
DeclareTask(CalculateVehicleSpeedTask);
DeclareTask(LaneControl);
DeclareTask(AdaptiveCruiseControlTask);
DeclareTask(SonarTask);
DeclareResource(RES_STEERING_MOTOR);
DeclareResource(RES_OVERRIDE_BT);

U8 drive = 1;

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ 
    StatusType ercd;

    ercd = SignalCounter(SysTimerCnt);
    if(ercd != E_OK){
        ShutdownOS(ercd);
    }
}


/* Initialize bluetooth connection when NXT is started */
void ecrobot_device_initialize()
{
    initRotationSensor();
    initBtConnection();
    initSonarSensor();
    aebInitialise();
    initTurnStruct();
    speedometerInitialise();
    initLightSensor();
}

/* Run when NXT is shut down */
void ecrobot_device_terminate()
{ 
    // nxt_motor_set_speed(PORT, speed, brake on / off)
    motorSetSpeed(STEERING_MOTOR, 0, 1);
    motorSetSpeed(RIGHT_MOTOR, 0, 1);
    motorSetSpeed(LEFT_MOTOR, 0, 1);
    termLightSensor();

    termRotationSensor();
    termBtConnection();
    termSonarSensor();
}

TASK(InitializeTask)
{
    motorSetSpeed(STEERING_MOTOR, 0, 1);
    motorSetSpeed(RIGHT_MOTOR, 0, 1);
    motorSetSpeed(LEFT_MOTOR, 0, 1);

    calibrateSteering();
    motorSetCount(RIGHT_MOTOR, 0);
    motorSetCount(LEFT_MOTOR, 0);

    initACCStruck();

    TerminateTask();
}

TASK(ControllerTask)
{
    displayClear(0);
    GetResource(RES_OVERRIDE_BT);
    receiveBT();
    ReleaseResource(RES_OVERRIDE_BT);
    updateAssistStates();
    displayAssists();
    S32 throttle = getThrottleAmount();

    GetResource(RES_STEERING_MOTOR);
    controlSteering();


    if ((vehicle.vFront < 0.0 && throttle < 0) || (vehicle.vFront > 0.0 && throttle > 0) || 
        (aeb.eaebState == STATE_BRAKING) || (aeb.activated && aeb.eaebState == STATE_NOT_ACTIVATED) || drive == 0)
    {
        drive = 0;
        brake();
    } else 
    {
        if (ACC_flag == OFF)
        {
            controlMotors(throttle, BRAKE_OFF);
        }
    }

    if(getButtonY() == 1 || nxtEnterButton() == 1){
        drive = 1;
        aebInitialise();
    }

    if (drive == 0)
    {
        displayGotoXY(2,7);
        displayString("BRAKING");
    }
    displayUpdate();

    ReleaseResource(RES_STEERING_MOTOR);

    TerminateTask();
}

TASK(DataLoggingTask)
{
    sendData();

    TerminateTask();
}



TASK(AEBTask)
{
    float dti = getDistanceToImpact();
    addDistanceToArray(dti);
    runAEB();

    TerminateTask();
}


TASK(CalculateVehicleSpeedTask)
{
    calculateVelocity();

    TerminateTask();
}


TASK(ReadRawDataTask)
{
    updateSpeedometerData();

    TerminateTask();
}
U8 previousMarking = 0;
TASK(LaneControlTask)
{
    if (LKA_flag == ON)
    {
        // If sensors are not calibrated, calibrate them
        if(calibratedLaneControl != LANE_CONTROL_CALIBRATED)
        {
            calibrateLaneControlSensor();
            calibratedLaneControl = LANE_CONTROL_CALIBRATED;
        }

        U8 currentMarking = detectRoadMarking();

        // If road marking detected, adjust vehicle 
        if (previousMarking > 0 && currentMarking == 0)
        {

            GetResource(RES_STEERING_MOTOR);
            GetResource(RES_OVERRIDE_BT);

            adjustVehicle(previousMarking);

            ReleaseResource(RES_OVERRIDE_BT);
            ReleaseResource(RES_STEERING_MOTOR);
        }

        previousMarking = currentMarking;
    }
    
    TerminateTask();
}

TASK(AdaptiveCruiseControlTask)
{
    if(ACC_flag == ON)
    {
        S32 distanceToVehicle = vehicle.sonarReading;

        float leadVehicleVelocity = calculateLeadVehicleVelocity(distanceToVehicle);
        float actualTimeBetweenVehicles = convertDistanceToTime(distanceToVehicle);

        ACC(actualTimeBetweenVehicles, distanceToVehicle, leadVehicleVelocity);
    }

    TerminateTask();
}

TASK(SonarTask)
{
    updateSonarReading();

    TerminateTask();
}
