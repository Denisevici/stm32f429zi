#include "leds.h"

Led firstChannelLed;
Led secondChannelLed;
Led thirdChannelLed;
Led fourthChannelLed;
Led *ledsArray[] = {&firstChannelLed, &secondChannelLed, &thirdChannelLed, &fourthChannelLed};

void InitLeds(void)
{
	firstChannelLed.pin = 6;
	firstChannelLed.intensity = 2048;
	secondChannelLed.pin = 7;
	thirdChannelLed.pin = 8;
	fourthChannelLed.pin = 9;
}

Led* GetLedByPin(uint8_t pin)
{
	if(pin == firstChannelLed.pin) { return &firstChannelLed; }
	else if(pin == secondChannelLed.pin) { return &secondChannelLed; }
	else if(pin == thirdChannelLed.pin) { return &thirdChannelLed; }
	else { return &fourthChannelLed; } 
}

