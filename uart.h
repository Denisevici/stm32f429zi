#include "stm32f4xx.h"
#include "stdbool.h"

extern uint32_t buffer;
extern uint8_t operationsCount;
extern bool transmittingIsAllowed;
extern bool gotNewIntructions;

void UartInit(void);
void USART3_IRQHandler(void);
void UartTransmitTime(uint32_t time);
void UartTransmitData(uint8_t data);
