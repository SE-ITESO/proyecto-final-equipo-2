/*
 * gpio.c
 *
 *  Created on: 27 sep 2023
 *      Author: MIKE
 */

#include "gpio.h"
#include "fsl_gpio.h"

typedef enum
{
	kGpio_kick = 0u,
	kGpio_snare = 1u,
	kGpio_bongo = 2u,
	kGpio_hitHat = 3u,
	kGpio_guiro = 4u,
	kGpio_rimShot = 5u,
	kGpio_tambor = 6u,
	kGpio_cynbal = 7u,
	kGpio_cowbell = 8u
}GPIO_Sound_t;


static void (*gpioB_callback)(uint8_t) = 0u;
static void (*gpioC_callback)(uint8_t) = 0u;

/*
 * Port A,B,C interrupt flags
 * */
static GPIO_x_ISR_flags g_A_intr_ISR_flag = {0};
static GPIO_x_ISR_flags g_B_intr_ISR_flag = {0};
static GPIO_x_ISR_flags g_C_intr_ISR_flag = {0};
static GPIO_x_ISR_flags g_D_intr_ISR_flag = {0};

typedef enum {
	False = 0u,
	True = 1u
}bool_t;

/*!
 * GPIO_CallbackInit
 * Callback for GPIOB and GPIOC
 * */
void GPIO_CallbackInit(void (*gpio_Handler)(uint8_t))
{
	gpioB_callback = gpio_Handler;
	gpioC_callback = gpio_Handler;
}

/*!
 * GPIO_ISRFlagsDecode
 * Decoding of the interrupt flags of a specific port
 * and put them in a single variable
 *
 * @param * g_ISR_flag (g_A_intr_ISR_flag, g_B_intr_ISR_flag, etc.)
 * */
static inline uint8_t GPIO_ISRFlagsDecode(GPIO_x_ISR_flags * g_ISR_flag)
{
	uint8_t flags = 0u;
	flags |= g_ISR_flag->flag_0;
	flags |= (g_ISR_flag->flag_1) << 1u;
	flags |= (g_ISR_flag->flag_2) << 2u;
	flags |= (g_ISR_flag->flag_3) << 3u;
	flags |= (g_ISR_flag->flag_4) << 4u;
	flags |= (g_ISR_flag->flag_5) << 5u;
	flags |= (g_ISR_flag->flag_6) << 6u;
	flags |= (g_ISR_flag->flag_7) << 7u;
	return flags;
}

/*!
 * GPIO_GetISR_StatusFlags
 * Gets the status flags of a specific port
 * defaults flags to 0
 * @param Port (kGPIO_A, kGPIO_B, kGPIO_C)
 * */
uint8_t GPIO_GetISR_StatusFlags(GPIO_Port_t Port)
{
	uint8_t flags = 0u;
	switch(Port)
	{
	case kGPIO_A:
		flags = GPIO_ISRFlagsDecode(&g_A_intr_ISR_flag);
		break;
	case kGPIO_B:
		flags = GPIO_ISRFlagsDecode(&g_B_intr_ISR_flag);
		break;
	case kGPIO_C:
		flags = GPIO_ISRFlagsDecode(&g_C_intr_ISR_flag);
		break;
	case kGPIO_D:
		flags = GPIO_ISRFlagsDecode(&g_D_intr_ISR_flag);
		break;
	default:
		flags = 0u;
	}
	return flags;
}

/*!
 * GPIO_SetISR_StatusFlags
 * Sets the value of the interrput flags of a specific port
 *
 * @param mask (PTBC10, PTC11, PTC6 , etc.)
 * @param * g_ISR_flag (g_A_intr_ISR_flag, g_B_intr_ISR_flag, etc.)
 * */
void GPIO_SetISR_StatusFlags(uint32_t mask, GPIO_x_ISR_flags * g_ISR_flag)
{

	if(PTD4 == mask)
	{
		g_ISR_flag->flag_0 = True;
	}
	else if(PTD5 == mask)
	{
		g_ISR_flag->flag_1 = True;
	}
	else if (PTA1 == mask)
	{
		g_ISR_flag->flag_0 = True;
	}
}

/*!
 * GPIO_ClearISR_StatusFlags
 * Clears the interrupt flags of a specific port
 *
 * @param Port (kGPIO_A, kGPIO_B, kGPIO_C)
 * @param mask (PTBC10, PTC11, PTC6 , etc.)
 **/
void GPIO_ClearISR_StatusFlags(GPIO_Port_t Port, uint32_t mask)
{
	switch(Port)
	{
	case kGPIO_A:
		if(PTA1 == mask)
		{
			g_A_intr_ISR_flag.flag_0 = False;
		}
	break;
	case kGPIO_B:
	break;
	case kGPIO_C:
	break;
	case kGPIO_D:
		if(PTD4 == mask)
		{
			g_D_intr_ISR_flag.flag_0 = False;
		}
		else if(PTD5 == mask)
		{
			g_D_intr_ISR_flag.flag_1 = False;
		}
	break;
	}
}

static uint8_t GPIO_getBtn(GPIO_Port_t Port, uint32_t mask)
{
	uint8_t flag = 0;
	if(kGPIO_B == Port)
	{
		switch(mask)
		{
		case PTB19:
			flag = kGpio_kick;
		break;
		case PTB18:
			flag = kGpio_snare;
		break;
		case PTB23:
			flag = kGpio_guiro;
		break;
		case PTB9:
			flag = kGpio_tambor;
		break;
		default:
		break;
		}
	}
	else
	{
		switch (mask)
		{
		case PTC1:
			flag = kGpio_bongo;
		break;
		case PTC8:
			flag = kGpio_hitHat;
		break;
		case PTC9:
			flag = kGpio_rimShot;
		break;
		case PTC0:
			flag = kGpio_cynbal;
		break;
		case PTC16:
			flag = kGpio_cowbell;
		break;
		default:
		break;
		}
	}
	return flag;
}

/*!
 * PORTA_IRQHandler
 * Interrupt Service routine for port A
 * */
void PORTA_IRQHandler(void)
{
	uint32_t Mask = 0;
	Mask = GPIO_PortGetInterruptFlags(GPIOA);
	GPIO_SetISR_StatusFlags(Mask, &g_A_intr_ISR_flag);
	GPIO_PortClearInterruptFlags(GPIOA, 0xFFFFFFFF);
}
/*!
 * PORTB_IRQHandler
 * Interrupt Service routine for port B
 * */
void PORTB_IRQHandler(void)
{
	uint32_t flag = 0u;
	uint8_t sound = 0u;
	flag = GPIO_PortGetInterruptFlags(GPIOB);
	GPIO_PortClearInterruptFlags(GPIOB, 0xFFFFFFFF);
	sound = GPIO_getBtn(kGPIO_B, flag);
	if(gpioB_callback)
	{
		gpioB_callback(sound);
	}
}
/*!
 * PORTC_IRQHandler
 * Interrupt Service routine for port C
 * */
void PORTC_IRQHandler(void)
{
	uint32_t Mask = 0;
	uint8_t sound = 0u;
	Mask = GPIO_PortGetInterruptFlags(GPIOC);
	GPIO_PortClearInterruptFlags(GPIOC, 0xFFFFFFFF);
	sound = GPIO_getBtn(kGPIO_C, Mask);
	if(gpioC_callback)
	{
		gpioC_callback(sound);
	}
}
/*!
 * PORTD_IRQHandler
 * Interrupt Service routine for port D
 * */
void PORTD_IRQHandler(void)
{
	uint32_t Mask = 0u;
	Mask = GPIO_PortGetInterruptFlags(GPIOD);
	GPIO_SetISR_StatusFlags(Mask, &g_D_intr_ISR_flag);
	GPIO_PortClearInterruptFlags(GPIOD, 0xFFFFFFFF);
}
