#include "stm32f4xx.h"
#include "stdbool.h"
#include "leds.h"

extern bool singleLedAlwaysOn;
extern bool useOnlyOneLed;

extern Led *singleLed;

void TransmitData(void);

void CheckIfIsOnlyOneLedOn(void);
