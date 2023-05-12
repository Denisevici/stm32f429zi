#include "gpio.h"
#include "uart.h"
#include "dac.h"
#include "adc.h"
#include "timer.h"
#include "settings.h"

int main(void)
{
	GpioInit();
	UartInit();	
	DacInit();
	AdcInit();
	TimerInit();
	InitLeds();
	
	while(1)
	{
		if(gotNewIntructions)
		{
			ApplyNewInstructions();
			gotNewIntructions = false;
		}		
		
		if(tick && transmittingIsAllowed)
		{
			if(timeFromTransmittingStart > transmittingDurationInMs)
			{
				transmittingIsAllowed = false;
				UartTransmitTime(0xffffff); // transmitting is over signal
			}
			else
			{
				TransmitData();
				tick = false;
			}
		}
	}
}
