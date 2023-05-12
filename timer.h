#include "stm32f4xx.h"
#include "stdbool.h"

extern uint32_t timeFromTransmittingStart;
extern uint32_t transmittingDurationInMs;
extern uint16_t oneTickInMs;

extern bool tick;

void TimerInit(void);

void TIM3_IRQHandler(void);
