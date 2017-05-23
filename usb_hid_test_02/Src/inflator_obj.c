/*
 * inflator_obj.c
 *
 *  Created on: May 19, 2017
 *      Author: root
 */

#include "inflator_obj.h"
#include "input_analizer_obj.h"
#include "gpio.h"
#include "timer_1hz_obj.h"
#include "timer_100hz_obj.h"

void debug_valve_led_imitation()
{
	input_flags = input_analizer_get_line_flags();

	// check line flags and fill inflation status array
	int i;
	for(i=0; i<4; i++)
	{
		if(((input_flags[2*i] == 1) || (input_flags[2*i + 1] == 1)) && (line_inflated[i] == 0))
		{
			//inflate_line(i);
			inflate_line_flag = 1;
			line_inflated[i] = 1;
		}
	}

	// turn on/off leds
	if(line_inflated[0] == 1)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);// turn on
	else
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);// turn off
	if(line_inflated[1] == 1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);// turn on
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);// turn off
	if(line_inflated[2] == 1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);// turn on
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);// turn off
	if(line_inflated[3] == 1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);// turn on
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);// turn off


}


void inflate_line(int line_number)
{
	volatile long i;

	// pitanie na servoprivod on

	// pwm na otkrytie ***********
	// stop 1 Hz timer
	timer1hz_stop();
	// start 67 Hz timer
	timer100hz_start(1); // 67 HZ;  1 - flag otkrytiya

	//pauza
	HAL_Delay(2000);
	//for(i=0; i<50000000; i++);

	// pwm na zakrytie
	timer100hz_start(0); // 67 HZ;  0 - flag zakrytiya

	//pauza
	HAL_Delay(2000);
	//for(i=0; i<50000000; i++);

	// pitanie na servoprivod off
	// stop 67 Hz timer
	timer100hz_stop(); // 67 HZ
	// start 1 Hz timer
	timer1hz_start();
}
