#include "timer250hz.h"
#include "gpio.h"



void timer250hz_start(void)
{
    timer250hz_tick = 0;

    /* Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /*Configure the TIM3 IRQ priority */
    HAL_NVIC_SetPriority(TIM3_IRQn, 2 ,0);

    /* Enable the TIM3 global Interrupt */
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    // enable update irq
    TIM3->DIER |= TIM_DIER_UIE;

    // prescaler value 79; counter frequency = 1MHz
    TIM3->PSC = (uint32_t)79;
    // auto reload value 4000; period = 4 mSec
    TIM3->ARR = (uint16_t)15000;  // 15 msec !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // enable timer counter (start count)
    TIM3->CR1 |= TIM_CR1_CEN;
}

void timer250hz_increment_tick()
{
    timer250hz_tick++;
    volatile long i;

    // pwm high
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);// high
	// pause
	for(i=0; i<8000; i++);
	// pwm low
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);// low
}

uint32_t timer250hz_get_tick()
{
    return timer250hz_tick;
}






