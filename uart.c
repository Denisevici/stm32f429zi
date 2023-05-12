#include "uart.h"

uint32_t buffer = 0;
uint8_t operationsCount = 0;
bool transmittingIsAllowed = false;
bool gotNewIntructions = false;

void UartInit(void)
{	
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // USART3 clocking
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // GPIOC clocking
	
	// PC10 - TX
	GPIOC->MODER |= (0x2 << 20); // alternate function 8.4.1 p.283
	//GPIOC->OTYPER &= ~(0x1 << 10); // push-pull 8.4.2 p.283
	GPIOC->OSPEEDR |= (0x3 << 20); // very high speed 8.4.3 p.284
	GPIOC->PUPDR |= (0x1 << 20); // pull up 8.4.4 p.283
	GPIOC->AFR[1] |= (7 << 8); //AF7 8.4.10 p.288 
	
	// PC11 - RX
	GPIOC->MODER |= (0x2 << 22); // alternate function 8.4.1 p.283
	//GPIOC->OTYPER &= ~(0x1 << 11); // push-pull 8.4.2 p.283
	GPIOC->OSPEEDR |= (0x3 << 22); // very high speed 8.4.3 p.284
	GPIOC->PUPDR |= (0x1 << 22); // pull up 8.4.4 p.283
	GPIOC->AFR[1] |= (7 << 12); //AF7 8.4.10 p.288 

	// usart3 enable
	USART3->CR1 = USART_CR1_UE; //bit 13 p.1003
	
	// p.974-975
	// 19200 baud (fclk = 16 MHz) 52(dec) = 34(hex); 1/16 = 0.0625; => 341
	USART3->BRR = 0x341;
	//115200 baud (fclk = 16 MHz) 8(dec) = 8(hex); 11/16 = 0.6875 => 8B
	//USART3->BRR = 0x8B;

	// usart3 transmit and receive enable
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;	
	
	// enable interrupts
	USART3->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART3_IRQn);
}

void USART3_IRQHandler(void)
{
	buffer = USART3->DR;
	gotNewIntructions = true;
}

void UartTransmitTime(uint32_t time)
{
	while ((USART3->SR & USART_SR_TXE) == 0) {} // wait transfer to end
	USART3->DR = (time >> 16) & 0xff;
	while ((USART3->SR & USART_SR_TXE) == 0) {} 
	USART3->DR = (time >> 8) & 0xff;
	while ((USART3->SR & USART_SR_TXE) == 0) {}
	USART3->DR = time & 0xff;
}

void UartTransmitData(uint8_t data)
{
	while ((USART3->SR & USART_SR_TXE) == 0) {}
	USART3->DR = data;
}
