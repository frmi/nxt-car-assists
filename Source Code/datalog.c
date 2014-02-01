#include "datalog.h"
#include <string.h>

S16 lastFront = 0;
S16 lastBack = 0;
S16 lastLeft = 0;
S16 lastRight = 0;

U8* createDatalogArray() 
{
	static U8 dataArray[PACKETSIZE];
	
	U32 time = getSysTime();
	S16 vFront = vehicle.vFront * 100; //Turn value into int, to avoid complications of sending float values via Bluetooth
	S16 vBack = vehicle.vBack * 100;
	S16 vLeft = vehicle.leftMotor.velocity * 100; //Turn value into int, to avoid complications of sending float values via Bluetooth
	S16 vRight = vehicle.rightMotor.velocity * 100;

	if (vFront > 400 || vFront < -400)
	{
		vFront = lastFront;
	}
	else
	{
		lastFront = vFront;
	}

	if (vBack > 400 || vBack < -400)
	{
		vBack = lastBack;
	}
	else
	{
		lastBack = vBack;
	}

	if (vLeft > 400 || vLeft < -400)
	{
		vLeft = lastLeft;
	}
	else
	{
		lastLeft = vLeft;
	}

	if (vRight > 400 || vRight < -400)
	{
		vRight = lastRight;
	}
	else
	{
		lastRight = vRight;
	}

	memcpy(&dataArray[0], &time, sizeof(U32));					// 4 bytes
	memcpy(&dataArray[4], &vLeft, sizeof(S16));					// 2 bytes
	memcpy(&dataArray[6], &vRight, sizeof(S16));				// 2 bytes
	memcpy(&dataArray[8], &vFront, sizeof(S16));				// 2 bytes
	memcpy(&dataArray[10], &vBack, sizeof(S16));					// 2 bytes
	memcpy(&dataArray[12], &appliedPower, sizeof(S8));			// 1 byte
	memcpy(&dataArray[13], &appliedSteering, sizeof(S32));		// 4 bytes
																// = 17 bytes

	return dataArray;
}

void sendData() 
{
	U8 *dataArray = createDatalogArray();
    sendBtPacket(dataArray, PACKETSIZE);
}
