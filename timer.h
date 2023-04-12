#include "stm32f4xx.h"

extern uint16_t timeFromTransmittingStart;

void TimerInit(void);

void TIM3_IRQHandler(void);
