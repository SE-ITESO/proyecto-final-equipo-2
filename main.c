/*
 * Proyecto Final
 * Equipo 2
 * José Miguel Castellanos Padilla
 * Diego Moran Vergara
 *
 * Sistemas Embebidos Basados en Microcontroladores 1
 *
 * */
#include <stdint.h>
#include "buttons.h"
#include "dac.h"
#include "display.h"
#include "gpio.h"
#include "LCD_nokia.h"
#include "NVIC.h"
#include "pit.h"
#include "port.h"
#include "SPI.h"
#include "wdog.h"

//State machine data type
typedef struct{
	uint8_t out;
	uint8_t next[3];
}State_t;

//State machine Array of states
const State_t FSM_Moore [3] =
{
	{kDisplay_M0,{kDisplay_M0, kDisplay_MRealT, kDisplay_MRecord}},
	{kDisplay_MRealT,{kDisplay_M0, kDisplay_MRealT, kDisplay_MRecord}},
	{kDisplay_MRecord,{kDisplay_M0, kDisplay_MRealT, kDisplay_MRecord}}

};

int main(void)
{

	Menu_t current_state = kDisplay_M0;
	uint8_t input = 0u;						//Machine input
	uint8_t output = 0u;					//Machine output
	uint8_t last_output = 0u;				//Machine last output
	uint8_t btn = 0u;						//Used to know the input button B1 or B2

	//Interrupt priorites setup
	NVIC_set_basepri_threshold(PRIORITY_6);
	NVIC_enable_interrupt_and_priotity(DMA_CH0_IRQ, PRIORITY_1);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_2);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_2);
	NVIC_enable_interrupt_and_priotity(PIT_CH2_IRQ, PRIORITY_2);
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ, PRIORITY_3);
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ, PRIORITY_3);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_3);
	NVIC_enable_interrupt_and_priotity(PORTD_IRQ, PRIORITY_3);
	NVIC_global_enable_interrupts;

	PORT_init();
	BUTTONS_init();
	BUTTONS_interrupt_enable();
	PIT_init();
	SPI_config();
	LCD_nokia_init();
	DISPLAY_MenuSelec(kDisplay_M0);

	while (1)
	{
		//Getting the output value of the current SM state
		output = FSM_Moore[current_state].out;

		//If the last output is different from the current one, change the state
		if(last_output != output)
		{
			DISPLAY_MenuSelec(output);
			last_output = output;
		}

		//If the Port A 1 switch has been depressed, go back to the main menu
		if(GPIO_GetISR_StatusFlags(kGPIO_A))
		{
			input = kDisplay_M0;
			GPIO_ClearISR_StatusFlags(kGPIO_A, PTA1);
		}
		//If the Port D 3 switch has been depressed, go  to the real Time menu
		if(GPIO_GetISR_StatusFlags(kGPIO_D) && (kDisplay_M0 == output))
		{
			input = kDisplay_MRealT;
			GPIO_ClearISR_StatusFlags(kGPIO_D, PTD3);

		}
		//If the Port C 2 switch has been depressed, go  to the Recording menu
		if(GPIO_GetISR_StatusFlags(kGPIO_C) && (kDisplay_M0 == output))
		{
			input = kDisplay_MRecord;
			GPIO_ClearISR_StatusFlags(kGPIO_C, PTC2);

		}

		if(kDisplay_MRecord == output)
		{
			if(GPIO_GetISR_StatusFlags(kGPIO_D))
			{
				DISPLAY_Recording_msg();
				GPIO_ClearISR_StatusFlags(kGPIO_D, PTD3);
			}
			if(GPIO_GetISR_StatusFlags(kGPIO_C))
			{
				DISPLAY_Menu_Record();
				GPIO_ClearISR_StatusFlags(kGPIO_C, PTC2);
			}
		}
		//change the state of the machine depending on the input
		current_state = FSM_Moore[current_state].next[input];
	}
	return 0 ;
}
