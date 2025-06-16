#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

void USART1_Init(void);
void USART_SendString(const char* str);  

#endif
