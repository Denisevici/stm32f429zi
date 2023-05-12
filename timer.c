#include "timer.h"

uint32_t timeFromTransmittingStart = 0;
uint32_t transmittingDurationInMs = 0;
uint16_t oneTickInMs = 0;
bool tick = false;

void TimerInit(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // TIM3 clocking
	
	//(fclk = 16 MHz)
	// 1 ticks per s 
	TIM3->PSC = 16000;
	TIM3->ARR = 1000;
	
	TIM3->DIER |= TIM_DIER_UIE; // enable being interrupted
	
	TIM3->CR1 |= TIM_CR1_CEN; // start timer
	
	NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF; // flag down
	
	timeFromTransmittingStart += oneTickInMs;
	tick = true;
}
