/*
 * gpio.h
 *
 *  Created on: 27 sep 2023
 *      Author: MIKE
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "fsl_gpio.h"


typedef struct {
	uint8_t flag_0 :1;
	uint8_t flag_1 :1;
	uint8_t flag_2 :1;
	uint8_t flag_3 :1;
	uint8_t flag_4 :1;
	uint8_t flag_5 :1;
	uint8_t flag_6 :1;
	uint8_t flag_7 :1;
}GPIO_x_ISR_flags;

typedef enum {
	kGPIO_A = 0u,
	kGPIO_B = 1u,
	kGPIO_C = 2u,
	kGPIO_D = 3u,
}GPIO_Port_t;

#define B1_flag 1u
#define B2_flag 2u

#define PTB19 0x80000u
#define PTB18 0x40000u
#define PTC1  0x2u
#define PTC8  0x100u
#define PTB23 0x800000u
#define PTC9  0x200u
#define PTB9  0x200u
#define PTC0  0x1u
#define PTC16 0x10000u
#define PTA1  0x2u
#define PTC2  0x4u
#define PTD3  0x8u

uint8_t GPIO_GetISR_StatusFlags(GPIO_Port_t Port);
void GPIO_CallbackInit(void (*gpio_Handler)(uint8_t));
void GPIO_SetISR_StatusFlags(uint32_t mask, GPIO_x_ISR_flags * g_ISR_flag);
void GPIO_ClearISR_StatusFlags(GPIO_Port_t Port, uint32_t mask);

#endif /* GPIO_H_ */
