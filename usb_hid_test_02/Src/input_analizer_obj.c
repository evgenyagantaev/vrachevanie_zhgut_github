/*
 * input_analizer_obj.c
 *
 *  Created on: May 18, 2017
 *      Author: root
 */

#include "input_analizer_obj.h"
#include "usart_obj.h"
#include "gpio.h"

void input_analizer_check_lines()
{
	// turn on high level on input lines (pc8 high)
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	// pause
	HAL_Delay(10);
	// check input lines and fill flags array
	int i;
	for(i=0; i<8; i++)
	{
		if(HAL_GPIO_ReadPin(GPIOC, input_pins[i]) == GPIO_PIN_RESET)
			line_flags[i] = 0;
		else
			line_flags[i] = 1;
	}
	// turn off high level on input lines (pc8 low)
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);

	debug_valve_led_imitation();

	// create message
	char aux_string[8];
	message[0] = 0;	// reset string
	for(i=0; i<8; i++)
	{
		sprintf(aux_string, "%c%d", delimeters[i], line_flags[i]);
		strncat(message, aux_string, 2);
	}
	strncat(message, "x\r\n", 3);

}

void input_analizer_send_status()
{
	//sprintf(message, "a0b0c1d0e0f0g0h0x\r\n");
	usart_send_message(message);
}

int *input_analizer_get_line_flags()
{
	return line_flags;
}
