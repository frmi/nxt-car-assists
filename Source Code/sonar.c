#include "sonar.h"

float calculateMean();
float calculateStdDev(float mean);
void initialiseSonarReadingArrays();
S32 measurementArray[3];
S32 validArray[3];
S32 selectReading(float mean, float deviation);
S32 isValidReading(S32 reading, float oMin, float oMax);
S32 smallestArrayValue();

S32 measurementCount = 0;

void updateSonarReading()
{
    if(measurementCount == NUM_SONAR_READINGS)
    {
        /* gives the effect of cyclic array */
        measurementCount = 0;
    }

    measurementArray[measurementCount] = getSonarSensor();

    float mean = calculateMean();
    float standardDeviation = calculateStdDev(mean);

    vehicle.sonarReading = selectReading(mean, standardDeviation);

    measurementCount++;
}

void initialiseSonarReadingArrays()
{
    int i;

    for(i = 0; i < NUM_SONAR_READINGS; i++)
    {
        measurementArray[i] = 0;
        validArray[i] = 0;
    }
}

S32 selectReading(float mean, float deviation)
{
    S32 i;

    /* 300 is used because sonar sensor can measure max 255 */
    validArray[0] = 300;
    validArray[1] = 300;
    validArray[2] = 300;

    for(i = 0; i < 3; i++)
    {
        if(isValidReading(measurementArray[i], mean - deviation, mean + deviation))
        {
            validArray[i] = measurementArray[i];
        }
    }

    return smallestArrayValue();
}

S32 smallestArrayValue()
{
    U8 i;
    S32 min = validArray[0];

    for(i = 1; i < NUM_SONAR_READINGS; i++)
    {
        if(validArray[i] < min)
        {
            min = validArray[i];
        }
    }

    return min;
}

S32 isValidReading(S32 reading, float oMin, float oMax)
{
    if(reading <= oMax && reading >= oMin)
    {
        return 1;
    }else
    {
        return 0;
    }
}

float calculateMean() 
{
    S32 i;
    float sum = 0.0;

    for (i = 0; i < NUM_SONAR_READINGS; i++) 
    {
        sum += measurementArray[i];
    }

    return sum / NUM_SONAR_READINGS;
}

float calculateStdDev(float mean) 
{
    S32 i;
    float sum = 0.0;

    for (i = 0; i < NUM_SONAR_READINGS; i++) 
    {
        float measurementPow = ((float)measurementArray[i] - mean) * ((float)measurementArray[i] - mean);
        sum += measurementPow;
    }

    return (float)sqrt(sum / (NUM_SONAR_READINGS - 1));
}
