#include "stm32f4xx.h"
#include "stdbool.h"

typedef struct
{
	uint8_t pin;
	uint16_t intensity;
} Led;

extern Led firstChannelLed;
extern Led secondChannelLed;
extern Led thirdChannelLed;
extern Led fourthChannelLed;

extern Led* ledsArray[4]; 

void InitLeds(void);

Led* GetLedByPin(uint8_t pin);
