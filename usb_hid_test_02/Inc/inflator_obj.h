/*
 * inflator_obj.h
 *
 *  Created on: May 19, 2017
 *      Author: root
 */

#ifndef INFLATOR_OBJ_H_
#define INFLATOR_OBJ_H_

#include "gpio.h"

static int line_inflated[4] = {0,0,0,0};
static int *input_flags;


void debug_valve_led_imitation();
void inflate_line(int line_number);

extern int inflate_line_flag;

#endif /* INFLATOR_OBJ_H_ */
