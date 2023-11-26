/*
 * buttons.h
 *
 *  Created on: 27 sep 2023
 *      Author: MIKE
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "fsl_port.h"
#include "fsl_gpio.h"


void BUTTONS_init(void);
void BUTTONS_interrupt_enable(void);



#endif /* BUTTONS_H_ */
