#include "dac.h"

void DacInit(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_DACEN; // DAC clocking
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // GPIOA clocking
	
	// PA4
	GPIOA->MODER |= (0x3 << 8); // analog mode 8.4.1 p.283
	GPIOA->OSPEEDR |= (0x3 << 8); // very high speed 8.4.3 p.283
	GPIOA->PUPDR &= ~(0x3 << 8); // no pull 8.4.4 p.284
	
	DAC->CR |= DAC_CR_EN1; //dac1 enable
}

void DacSetValue(uint16_t value)
{
	DAC->DHR12R1 = value;
}
