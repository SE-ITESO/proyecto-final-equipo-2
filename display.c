/*
 * display.c
 *
 *  Created on: 16 nov. 2023
 *      Author: diego
 */

#include "display.h"
#include "LCD_nokia.h"


static uint8_t M0_op1 [] = "1) Manual";
static uint8_t M0_op2 [] = "2) Secuencia";
static uint8_t MManual_msg1 [] = "Manual Mode";
static uint8_t MManual_msg2 [] = "press any";
static uint8_t MManual_msg3 [] = "key";
static uint8_t MSecuence_msg1 [] = "Secuence";
static uint8_t Stopped_msg [] = "Stopped";
static uint8_t Playing_msg [] = "Playing";

static uint8_t wdg_msg [] = "El sistema fallo";

void DISPLAY_display_sound(SOUNDS_sound_t sound)
{
	switch (sound)
	{
	case kSounds_kickSound:
		LCD_nokia_send_string(Kick_char);
	break;
	case kSounds_snareSound:
		LCD_nokia_send_string(Snare_char);
	break;
	case kSounds_bongoSound:
		LCD_nokia_send_string(Bongo_char);
	break;
	case kSounds_hitHatSound:
		LCD_nokia_send_string(HitHat_char);
	break;
	case kSounds_guiroSound:
		LCD_nokia_send_string(Guiro_char);
	break;
	case kSounds_rimShotSound:
		LCD_nokia_send_string(RimShot_char);
	break;
	case kSounds_tamborSound:
		LCD_nokia_send_string(Tambor_char);
	break;
	case kSounds_cynbalSound:
		LCD_nokia_send_string(Cynbal_char);
	break;
	case kSounds_cowbellSound:
		LCD_nokia_send_string(Cowbell_char);
	break;
	default:
	break;
	}
}

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
	case kDisplay_MSecuence:
		DISPLAY_Menu_Secuence();
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
void DISPLAY_Menu_Secuence(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0, 0);
	LCD_nokia_send_string(MSecuence_msg1);
	LCD_nokia_goto_xy(4, 5);
	LCD_nokia_send_string(Stopped_msg);
	LCD_nokia_goto_xy(0, 1);
}

void DISPLAY_Playing_msg(void)
{
	LCD_nokia_goto_xy(4, 5);
	LCD_nokia_send_string(Playing_msg);
}

void DISPLAY_InitialPic(void)
{
	LCD_nokia_clear();
	LCD_nokia_bitmap(LCD_NOKIA_getPicPtr());
}

void DISPLAY_systemError(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(2,2);
	LCD_nokia_send_string(wdg_msg);
}
