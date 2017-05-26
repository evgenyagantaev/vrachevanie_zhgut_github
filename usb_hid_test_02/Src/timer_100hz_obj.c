/*
 * timer_100hz_obj.c
 *
 *  Created on: Sep 12, 2016
 *      Author: root
 */

#include "timer_100hz_obj.h"
#include "tim.h"


void timer100hz_start(int Flag)
{
	flag = Flag;

    timer100hz_tick = 0;

    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /*Configure the TIM2 IRQ priority */
    HAL_NVIC_SetPriority(TIM2_IRQn, 2 ,0);

    /* Enable the TIM2 global Interrupt */
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    // enable update irq
    TIM2->DIER |= TIM_DIER_UIE;

    // prescaler value 79; counter frequency = 1MHz
    TIM2->PSC = (uint32_t)79;
    // auto reload value 15000; period = 15 mSec
    TIM2->ARR = (uint16_t)15000;

    // enable timer counter (start count)
    TIM2->CR1 |= TIM_CR1_CEN;
}

void timer100hz_stop(void)
{
	// disable timer counter (stop count)
	TIM2->CR1 &= ~TIM_CR1_CEN;
}

void timer100hz_increment_tick()
{
    timer100hz_tick++;
    volatile long i;

    if(flag) // otkrytie
    {
    	// pwm high
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);// high
		// pause
		for(i=0; i<8200; i++);     //   for(i=0; i<8600; i++);
		// pwm low
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);// low
    }
    else // zakrytie
	{
    	// pwm high
    		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);// high
    		// pause
    		for(i=0; i<18000; i++);   // for(i=0; i<17800; i++);
    		// pwm low
    		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);// low
	}


}

uint32_t timer100hz_get_tick()
{
    return timer100hz_tick;
}

void timer100hz_get_flag()
{
	return flag;
}
