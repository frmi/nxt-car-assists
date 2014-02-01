#include "eaeb.h"


void runEAEB()
{   
	float distanceToImpact = 0;

	if (vehicle.vFront < 0.1) 
	{
		aeb.eaebState = STATE_NOT_ACTIVATED;
		steer.turnDegreesActivated = 0;

	} else if(aeb.eaebState == STATE_NOT_ACTIVATED)
	{
		aeb.distance = 0.0;
		aeb.eaebState = STATE_BRAKING;
		
		// prevents user from steering while the EAEB is running
		steer.turnDegreesActivated = 1;

	} else if(aeb.eaebState == STATE_BRAKING)
	{
		distanceToImpact = getDistanceToImpact();

		if(distanceToImpact < BRAKE_WAIT_DIST)
		{
			aeb.eaebState = STATE_TURNING;
			aeb.distance = 0.0;
			aeb.lastReadTick = tickCounter.frontDegreesArray[tickCounter.newIndexFront];
			turnDegrees(MAX_LEFT_TURN);
		}			

	} else if (aeb.eaebState == STATE_TURNING) 
	{
		aeb.distance += getDistanceTravelled();

		if (aeb.distance > TURN_DISTANCE)
		{
			aeb.eaebState = STATE_STRAIGHTENING;
			aeb.distance = 0.0;
			aeb.lastReadTick = tickCounter.frontDegreesArray[tickCounter.newIndexFront];
			turnDegrees(0);
		}

	} else if (aeb.eaebState == STATE_STRAIGHTENING)
	{
		aeb.distance += getDistanceTravelled();

		if (aeb.distance > STRAIGHTENING_WAIT_DIST)
		{
			aeb.distance = 0.0;
			aeb.eaebState = STATE_BRAKING;

			// allow the user to steer again
    		steer.turnDegreesActivated = 0;
		}
	}
}
