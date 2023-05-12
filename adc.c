#include "adc.h"

void AdcInit(void)
{
	uint32_t delay = 10000;
	
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; //ADC1 clocking
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // GPIOA clocking
	
	// PA5
	GPIOA->MODER |= (0x3 << 10); // analog mode 8.4.1 p.283
	GPIOA->OSPEEDR |= (0x3 << 10); // very high speed 8.4.3 p.283
	//GPIOA->PUPDR &= ~(0x3 << 10); // no pull 8.4.4 p.284
	
	//13.13.3 p. 421
	ADC1->CR2 |= ADC_CR2_ADON; // enable adc
	ADC1->CR2 |= ADC_CR2_CONT; // continuous mode	
	
	ADC1->SMPR2 |= (0x6 << 15); // 144 cycles 13.13.4 p.423
	
	ADC1->SQR3 |= 5; // 5 channel 13.13.11 p.426
	
	ADC1->CR2 |= ADC_CR2_SWSTART; // start adc
	
	while (delay != 0) { delay--; }
}

uint8_t AdcGetValue(void)
{
	while(!(ADC1->SR & ADC_SR_EOC)) {}
	return ADC1->DR;
}
