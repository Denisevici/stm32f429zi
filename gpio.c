#include "gpio.h"

void GpioInit(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // GPIOC clocking
	
	// PC6 
	GPIOC->MODER |= (0x1 << 12); // output mode 8.4.1 p.283
	//GPIOC->OTYPER &= ~(0x1 << 6); // output push-pull mode 8.4.2 p.283
	GPIOC->OSPEEDR |= (0x3 << 12); // very high speed 8.4.3 p.284
	GPIOC->PUPDR |= (0x1 << 12); // pull up 8.4.4 p.284
	
	// PC7
	GPIOC->MODER |= (0x1 << 14); // output mode 8.4.1 p.283
	//GPIOC->OTYPER &= ~(0x1 << 7); // output push-pull mode 8.4.2 p.283
	GPIOC->OSPEEDR |= (0x3 << 14); // very high speed 8.4.3 p.284
	GPIOC->PUPDR |= (0x1 << 14); // pull up 8.4.4 p.284
	
	// PC8
	GPIOC->MODER |= (0x1 << 16); // output mode 8.4.1 p.283
	//GPIOC->OTYPER &= ~(0x1 << 8); // output push-pull mode 8.4.2 p.283
	GPIOC->OSPEEDR |= (0x3 << 16); // very high speed 8.4.3 p.284
	GPIOC->PUPDR |= (0x1 << 16); // pull up 8.4.4 p.284
	
	// PC9
	GPIOC->MODER |= (0x1 << 18); // output mode 8.4.1 p.283
	//GPIOC->OTYPER &= ~(0x1 << 9); // output push-pull mode 8.4.2 p.283
	GPIOC->OSPEEDR |= (0x3 << 18); // very high speed 8.4.3 p.284
	GPIOC->PUPDR |= (0x1 << 18); // pull up 8.4.4 p.284
}

void LedOn(uint8_t pin)
{
	if(pin >= 6 && pin <= 9) { GPIOC->ODR |= (0x1 << pin); }
}

void LedOff(uint8_t pin)
{
	GPIOC->ODR &= ~(0x1 << pin);
}
