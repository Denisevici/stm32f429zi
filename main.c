#include "gpio.h"
#include "uart.h"
#include "dac.h"
#include "adc.h"
#include "timer.h"

int main(void)
{
	GpioInit();
	UartInit();	
	DacInit();
	AdcInit();
	TimerInit();
	
	LedOn(8);
	DacSetValue(2040);
	
	while(1)
	{	
	}
}
