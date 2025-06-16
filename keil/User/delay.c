#include "delay.h"

static __IO uint32_t TimingDelay;

void delay_init(void)
{
    SysTick_Config(SystemCoreClock / 1000);
}

void delay_ms(uint32_t ms)
{
    TimingDelay = ms;
    while (TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
    if (TimingDelay > 0)
        TimingDelay--;
}
