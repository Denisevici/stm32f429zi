#include "stm32f4xx.h"
#include "stdbool.h"
#include "transmit.h"

extern bool isTimeToConfigureLed;
extern bool isTimeToSetIntensityToLed;
extern bool isTimeToSetTransmittingDuration;
extern bool isTimeToSetWorkingModeOfSingleLed;
	
extern Led *led;
extern uint8_t configuredLeds;

extern uint16_t multiplyNumber;

void ApplyNewInstructions(void);

uint16_t GetIntensity(uint8_t);
