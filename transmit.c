#include "transmit.h"
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "gpio.h"
#include "dac.h"

bool singleLedAlwaysOn = true;
bool useOnlyOneLed = false;

Led *singleLed;

void TransmitData(void)
{
	if(useOnlyOneLed)
	{
		if(singleLedAlwaysOn) 
		{
			UartTransmitTime(timeFromTransmittingStart);
			UartTransmitData(AdcGetValue());
		}
		else
		{
			LedOn(singleLed->pin);
			UartTransmitTime(timeFromTransmittingStart);
			UartTransmitData(AdcGetValue());
			LedOff(singleLed->pin);
		}
	}
	else
	{
		for(int i = 0; i < 4; i++)
		{
			if(ledsArray[i]->intensity != 0)
			{
				LedOn(ledsArray[i]->pin);
				DacSetValue(ledsArray[i]->intensity);
				UartTransmitTime(timeFromTransmittingStart);
				UartTransmitData(AdcGetValue());
				LedOff(ledsArray[i]->pin);
			}
		}
	}
}

void CheckIfIsOnlyOneLedOn(void)
{
	uint8_t count = 0;
	uint8_t index = 0;
	for (int i = 0; i < 4; i++)
	{
		if(ledsArray[i]->intensity != 0)
		{
			index = i;
			count++;
		}
	}
	
	if(count == 1)
	{
		useOnlyOneLed = true;
		singleLed = ledsArray[index];
		DacSetValue(singleLed->intensity);
	}
}
