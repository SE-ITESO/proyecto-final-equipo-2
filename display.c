/*
 * display.c
 *
 *  Created on: 16 nov. 2023
 *      Author: diego
 */

#include "display.h"
#include "LCD_nokia.h"


static uint8_t M0_op1 [] = "1) Manual";
static uint8_t M0_op2 [] = "2) Record";
static uint8_t MManual_msg1 [] = "Manual Mode";
static uint8_t MManual_msg2 [] = "press any";
static uint8_t MManual_msg3 [] = "key";
static uint8_t MRecord_msg1 [] = "Press b1 to record";
static uint8_t Playing_msg [] = "Playing";

static uint8_t wdg_msg [] = "El sistema fallo";


void DISPLAY_MenuSelec(Menu_t MenuSel)
{
	/* Funcion que nos permite mostrar el menu que necesitamos dependiendo de l selector que le mandemos*/
	switch(MenuSel)
	{
	case kDisplay_M0:
		DISPLAY_Menu0();
	break;
	case kDisplay_MManual:
		DISPLAY_Menu_Manual();
	break;
	case kDisplay_MRecord:
		DISPLAY_Menu_Record();
	break;
	}
}

void DISPLAY_Menu0(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(1, 2);
	LCD_nokia_send_string(M0_op1);
	LCD_nokia_goto_xy(1, 3);
	LCD_nokia_send_string(M0_op2);
}
void DISPLAY_Menu_Manual(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(3, 2);
	LCD_nokia_send_string(MManual_msg1);
	LCD_nokia_goto_xy(3, 3);
	LCD_nokia_send_string(MManual_msg2);
	LCD_nokia_goto_xy(6, 4);
	LCD_nokia_send_string(MManual_msg3);
}
void DISPLAY_Menu_Record(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0, 4);
	LCD_nokia_send_string(MRecord_msg1);
}

void DISPLAY_Recording_msg(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(4, 5);
	LCD_nokia_send_string(Playing_msg);
	/*FALTA PONER EL CONTADOR*/
}


void DISPLAY_systemError(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(2,2);
	LCD_nokia_send_string(wdg_msg);
}
