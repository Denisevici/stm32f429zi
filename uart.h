#include "stm32f4xx.h"
#include "stdbool.h"

extern bool transmittingIsAllowed;

void UartInit(void);
void USART3_IRQHandler(void);
void UartTransmit(uint16_t data);
