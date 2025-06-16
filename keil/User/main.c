#include "stm32f10x.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

#define SYSCLK_FREQ_72MHz

// ??? printf ??? USART1
int fputc(int ch, FILE *f) {
     USART_SendData(USART1, (uint8_t)ch);
     while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
     return ch;
 }

void delay(uint32_t num)
{
	uint32_t i_cnt,j_cnt;
	for(i_cnt=0;i_cnt<3000;i_cnt++);
	for(j_cnt=0;j_cnt<num;j_cnt++);
}

void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_SetBits(GPIOA, GPIO_Pin_8);  // ????:???(LED?)
}

void USART_SendByte(uint8_t Byte) {
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); // ?? TC ??
}

void USART1_IRQHandler(void)
{
    static char buffer[16];
    static uint8_t index = 0;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        char c = USART_ReceiveData(USART1);
        if (c == '\n' || c == '\r')
        {
            buffer[index] = '\0';
            index = 0;

            if (strcmp(buffer, "ON") == 0)
            {
                GPIO_SetBits(GPIOA, GPIO_Pin_8);
                printf("LED ON \r");
            }
            else if (strcmp(buffer, "OFF") == 0)
            {
                GPIO_ResetBits(GPIOA, GPIO_Pin_8);
                printf("LED OFF \r");
            }
        }
        else
        {
            if (index < sizeof(buffer) - 1)
                buffer[index++] = c;
        }
    }
}

int main(void)
{
	  SystemInit();
    USART1_Init();
    LED_Init();
	  printf("Hello Qt!\r\n");
	  //RCC_ClocksTypeDef RCC_Clocks;
    // RCC_GetClocksFreq(&RCC_Clocks);
    // printf("SYSCLK: %d Hz\n", RCC_Clocks.SYSCLK_Frequency);
    while (1)
    {
         
			  // USART_SendString("A");
        // GPIOA->ODR ^= GPIO_Pin_8;  // ??PA8??
			  // USART_SendByte('A');
			  // USART_SendData(USART1, 'A'); // ?????? 'A'
        // while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
			  // USART_SendData(USART1, 'A'); // ?????? 'A'
			  // delay(99000);
    }
}
