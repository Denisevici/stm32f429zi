#include "settings.h"
#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "dac.h"

bool isTimeToConfigureLed = false;
bool isTimeToSetIntensityToLed = false;
bool isTimeToSetTransmittingDuration = false;
bool isTimeToSetWorkingModeOfSingleLed = false;

Led *led;
uint8_t configuredLeds = 0;

uint16_t multiplyNumber = 1;

void ApplyNewInstructions(void)
{   
	if(isTimeToConfigureLed)
	{
		led = GetLedByPin(buffer & 0xf);
		ledsArray[configuredLeds] = led;
		isTimeToConfigureLed = false;			
		isTimeToSetIntensityToLed = true;
		return;
	}
	if(isTimeToSetIntensityToLed)
	{
		led->intensity = GetIntensity(buffer & 0xf);
		isTimeToSetIntensityToLed = false;
		configuredLeds++;
		if(configuredLeds == 4) 
		{
			isTimeToSetWorkingModeOfSingleLed = true;
			isTimeToConfigureLed = false;
			configuredLeds = 0;	
		}
		else { isTimeToConfigureLed = true; }
		return;
	}
		if(isTimeToSetWorkingModeOfSingleLed)
	{
		singleLedAlwaysOn = (buffer & 0x1) == 1;
		CheckIfIsOnlyOneLedOn();
		isTimeToSetWorkingModeOfSingleLed = false;
		return;
	}
	if(isTimeToSetTransmittingDuration)
	{
		transmittingDurationInMs += (buffer & 0xf) * multiplyNumber;
		if(multiplyNumber == 10000) 
		{
			transmittingDurationInMs *= 1000;
			isTimeToSetTransmittingDuration = false; 
		}
		else { multiplyNumber *= 10; }
		return;
	}
		
	switch(buffer & 0xf)
	{
		case 0x00: // transmitting disable
		{
			transmittingIsAllowed = false;
			break;
		}
		case 0x01: // transmitting enable
		{
			transmittingIsAllowed = true;
			break;
		}
		case 0x02: // 1 tick per ms
		{
			TIM3->PSC = 16000;
			TIM3->ARR = 1;
			TIM3->EGR = 1;
			oneTickInMs = 1;
			break;
		}
		case 0x03: // 1 tick per 10 ms
		{
			TIM3->PSC = 16000;
			TIM3->ARR = 10;
			TIM3->EGR = 1;
			oneTickInMs = 10;
			break;
		}
		case 0x04: // 1 tick per 100 ms
		{
			TIM3->PSC = 16000;
			TIM3->ARR = 100;
			TIM3->EGR = 1;
			oneTickInMs = 100;
			break;
		}
		case 0x05: // 1 tick per 1000 ms
		{
			TIM3->PSC = 16000;
			TIM3->ARR = 1000;
			TIM3->EGR = 1;
			oneTickInMs = 1000;
			break;
		}
		case 0x06: // time to zero
		{
			timeFromTransmittingStart = 0;
			break;
		}
		case 0x07: // prepare to choose led
		{
			isTimeToConfigureLed = true;
			break;
		}
		case 0x08: // prepare to set transmitting time duration
		{
			isTimeToSetTransmittingDuration = true;
			transmittingDurationInMs = 0;
			multiplyNumber = 1;
			break;
		}
	}
}

uint16_t GetIntensity(uint8_t value)
{
	switch(value)
	{
		case 0: return 0;    //  0    V
		case 1: return 1737; //  1.4  V
		case 2: return 1861; //  1.5  V
		case 3: return 1985; //  1.6  V
		case 4: return 2109; //  1.7  V
		case 5: return 2233; //  1.8  V
		case 6: return 2357; //  1.9  V
		case 7: return 2481; //  2.0  V
		default: return 2048; // 1.65 V
	}
}
