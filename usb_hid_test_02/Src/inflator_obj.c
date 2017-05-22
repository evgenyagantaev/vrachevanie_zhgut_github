/*
 * inflator_obj.c
 *
 *  Created on: May 19, 2017
 *      Author: root
 */

#include "inflator_obj.h"
#include "input_analizer_obj.h"
#include "gpio.h"

void debug_valve_led_imitation()
{
	input_flags = input_analizer_get_line_flags();

	// check line flags and fill inflaton status array
	int i;
	for(i=0; i<4; i++)
	{
		if((input_flags[2*i] == 1) || (input_flags[2*i + 1] == 1))
		{
			line_inflated[i] = 1;
		}
		else
		{
			line_inflated[i] = 0;
		}
	}

	// turn on/off leds
	if(line_inflated[0] == 1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);// turn on
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);// turn off
	if(line_inflated[0] == 1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);// turn on
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);// turn off
	if(line_inflated[0] == 1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);// turn on
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);// turn off
	if(line_inflated[0] == 1)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);// turn on
	else
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);// turn off


}
