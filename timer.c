#include "timer.h"
#include "uart.h"
#include "adc.h"
#include "dac.h"

uint16_t timeFromTransmittingStart = 0;

void TimerInit(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // TIM3 clocking
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // GPIOC clocking
	
	//(fclk = 16 MHz)
	// 2 ticks per ms 
	TIM3->PSC = 16000;
	TIM3->ARR = 2;
	
	TIM3->DIER |= TIM_DIER_UIE; // enable being interrupted by timer
	TIM3->CR1 |= TIM_CR1_CEN; // start timer
	
	NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF; // flag down
	
	if(transmittingIsAllowed)
	{
		UartTransmit(timeFromTransmittingStart);
		UartTransmit(AdcGetValue());
		timeFromTransmittingStart+=1;
	}
}
