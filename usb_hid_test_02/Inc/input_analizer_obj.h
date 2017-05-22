/*
 * input_analizer_obj.h
 *
 *  Created on: May 18, 2017
 *      Author: root
 */

#ifndef INPUT_ANALIZER_OBJ_H_
#define INPUT_ANALIZER_OBJ_H_

#include "gpio.h"

static char message[64];
static int line_flags[8] = {0,0,0,0,0,0,0,0};
static uint16_t input_pins[] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7};
static char delimeters[] = {'a','b','c','d','e','f','g','h'};

void input_analizer_check_lines();
void input_analizer_send_status();
int *input_analizer_get_line_flags();

#endif /* INPUT_ANALIZER_OBJ_H_ */
