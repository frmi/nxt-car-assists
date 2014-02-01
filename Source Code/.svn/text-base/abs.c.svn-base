#include "abs.h"

/* Private prototypes */
void updateLockState(MotorStruct* motor);
void brakeMotor(MotorStruct* motor);

//Slows down the vehicle at a rate optimizing braking distance
//If vehicle is stationary it applies brake mode to the motors
void brake() {
	if (ABS_flag == ON)
	{
		brakeMotor(&vehicle.leftMotor);
		brakeMotor(&vehicle.rightMotor);
	}
	else
	{
		motorSetSpeed(vehicle.leftMotor.id, 0, BRAKE_ON);
		motorSetSpeed(vehicle.rightMotor.id, 0, BRAKE_ON);
	}
}

void brakeMotor(MotorStruct* motor){
	// check lock state of the motor
	updateLockState(motor);

	if (motor->lockState == 0){
		// Brake motors
		motorSetSpeed(motor->id, 0, BRAKE_ON);
	}
	else
	{
		/* Motor is locked. Save the current ticks of the motor
		 * and make the motor float to release the brake
		 */
		motor->brakeLockedTick = motorGetCount(motor->id);
		motorSetSpeed(motor->id, 0, BRAKE_OFF);
	}
}

void updateLockState(MotorStruct* motor) {
	// Check only if the vehicle is moving
	if (fabs(vehicle.vFront) > 0.0) {
		// Calculate the slip ratio
		float slipRatio = (fabs(vehicle.vFront) - fabs(motor->velocity)) / fabs(vehicle.vFront);
		if (fabs(slipRatio) > 0.2){
			// Slip ratio above 0.2, the wheel is locked
			motor->lockState = 1;
		}
		else if (fabs(slipRatio) < 0.1)
		{
			// Wheel is not locked
			motor->lockState = 0;
		}
	}
}

