#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>

#define LEFT_MOTOR         			PORT_C
#define RIGHT_MOTOR        			PORT_B
#define STEERING_MOTOR     			PORT_A
				
#define SONAR_SENSOR 				PORT_1
#define LIGHT_SENSOR_LEFT   		PORT_2
#define ROTATION_SENSOR 			PORT_3
#define LIGHT_SENSOR_RIGHT  		PORT_4

#define STEERING_LIMIT                  40   	// Degree
#define STEERING_P_GAIN                1.5	  	// Proportional gain
#define MAX_SPEED                      100   	// Max speed backwards
#define ARRAY_SIZE                      15   	// Size of array received over bluetooth
#define VEHICLE_WIDTH                   25      // Half of the actual width + safe zone
#define JOYSTICK_LASH                   10   	// dead zone of joystick - 0.1 on C# side

/* Vehicle */
#define WHEELBASE                       18   	// Distance between center front and center back
#define TRACK                           19   	// Distance between back wheels
#define WHEEL_DIAMETER               0.082      // Wheel size is in m.
#define WHEEL_CIRC                 0.25761      // WHEEL_DIAMETER*PI
#define GEAR_RATIO                       5      // LARGE_GEAR / SMALL_GEAR

/* Units */
#define SEC_PER_MIN                     60      // seconds
#define MS_PER_MIN                   60000      // milliseconds
#define CM_PER_M                       100      // number of centimetres per meter
#define MS_PER_SEC                  1000.0      // milliseconds

/* AEB Constants */				
#define COEF_OF_FRICTION              0.12	  	// was changed from original of 0.158
#define STD_GRAVITY                9.80665   	// meter / seconds ^ 2
#define AEB_TIME_BETWEEN_READINGS       25   	// in milliseconds
#define BRAKE_SAFE_ZONE                 42   	// in cm 42
#define SONAR_ERROR_MARGIN               4   	// in cm
#define SAMPLE_COUNT                     5   	// number of samples taken for the error correction array

/* EAEB constants */				
#define TURN_DISTANCE 			         5   	// distance to let the vehicle drive while evading
#define MAX_LEFT_TURN 		           -25   	// max number of degrees possible to turn left
#define BRAKE_WAIT_DIST 	            35   	// distance to impact at which the vehicle should start turning
#define STRAIGHTENING_WAIT_DIST			 5 		// distance for straightening the wheels

/* LaneControl constants */             
#define MAX_TURNING_ANGLE               35   	// Turn angle every third turn
#define MIN_TURNING_ANGLE               25   	// Turn angle for first and second turn
#define CALIBRATE_COLOUR_DIST           50   	// Distance to drive after reading colour for road marking to read colour for floor
#define COLOUR_SAFETY                   25      // Acceptable deviation in readings due to lighting etc. Should be changed when used in new environment
#define LEFT_ROADMARKING_VALUE           1   	// Value used when road marking on left side is detected
#define RIGHT_ROADMARKING_VALUE          2   	// Value used when road marking on right side is detected
#define LANE_CONTROL_CALIBRATED          1   	// Value used when sensors are calibrated
#define BUSY_WAIT_TIME_LANECONTROL       2   	// Time in ms to allow the vehicle to turn before continuing execution
#define ADJUSTING_SPEED_FORWARD        -80   	// The speed at which the vehicle is driving away from road marking
#define TURNS_BEFORE_ANGLE_INCREASE      3   	// Number of turns before approach angle to road marking becomes too great

/* Speedometer */
#define PI                            M_PI      // Use PI defined in Math.h
#define SPEED_TIME_BETWEEN_READINGS     10     	// milliseconds
#define TICKS_PER_ROUND                 16     	// ticks per round on rotation sensor
#define TICK_ARRAY_SIZE                 50      // Size of tick history arrays

/* TCS */
#define ALLOWED_SPEED_WITHOUT_TCS      0.2     // Minimum allowed speed without TCS
#define TCS_TARGET_SLIP_RATIO          0.2     // The back wheels are allowed to rotate 20% faster than front wheels
#define TCS_SLIP_RATIO                 1.2     // 20% slip allowed to accelerate

/* EDC */
#define NEUTRAL_DEAD_ZONE                5     // Steering motors dead zone is 5 degrees

/* ACC */
#define INITIAL_MOTOR_POWER            -75      // Motor power at ACC start
#define MOTOR_POWER_ADJUST               1      // Motor power change in percent when adjusting speed
#define MINIMUM_TIME_BETWEEN_VEHICLES  0.5      // Minimum distance between vehicles measured in seconds
#define DESIRED_TIME_BETWEEN_VEHICLES 0.85      // Desired distance between vehicles measured in seconds
#define MAXIMUM_DEVIATION             0.25      // Maximum deviation between desired and actual distance measured in seconds
#define MAXIMUM_TIME_BETWEEN_VEHICLES    5      // Maximum distance between vehicles measured in seconds
#define MINIMUM_DISTANCE_FOR_ACC        15      // Minimum distance before activating ACC
#define MAINTAIN_TIMES_BEFORE_ACTION    40      // Number of times maintain needs to be called before adjusting speed
#define MINIMUM_POWER_FOR_DRIVE        -65      // Minimum power for the vehicle to drive forward
#define MINIMUM_VELOCITY_FOR_CONVERT   0.4      // The value which is used for keeping the converter from dividing with 0

/* sonar sensor constants */
#define NUM_SONAR_READINGS 				 3				/* number of readings the sonar sensor does each time updateSonarReading() is called */		

#define ON   						     1
#define OFF		  						 0

#endif
