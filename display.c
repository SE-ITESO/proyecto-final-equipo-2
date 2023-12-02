/*
 * display.c
 *
 *  Created on: 16 nov. 2023
 *      Author: diego
 */

#include "display.h"
#include "LCD_nokia.h"


static uint8_t M0_op1 [] = "1) Microphone";
static uint8_t M0_op2 [] = "2) Record";
static uint8_t M0_op3 [] = "3) Play";

static uint8_t MManual_msg1 [] = "Microphone mode";
static uint8_t MRecord_msg1 [] = "b1 record";

static uint8_t MManual_msg1 [] = "Microphone  mode";

static uint8_t Playing_msg [] = "Press b2 to record";


static uint8_t Recording_time_msg [] = "Record Mode";
static uint8_t Recording_time_msg1 [] = "msg1";
static uint8_t Recording_time_msg2 [] = "msg2";

static uint8_t PlayMode_msg []= "Play Mode";
static uint8_t PlayMode_msg1 []= "msg1";
static uint8_t PlayMode_msg2 []= "msg2";



static uint8_t wdg_msg [] = "El sistema fallo";


void DISPLAY_MenuSelec(Menu_t MenuSel)
{
	/* Funcion que nos permite mostrar el menu que necesitamos dependiendo de l selector que le mandemos*/
	switch(MenuSel)
	{
	case kDisplay_M0:
		DISPLAY_Menu0();
	break;
	case kDisplay_MRealT:
		DISPLAY_Menu_RealT();
	break;
	case kDisplay_MPlay:
		DISPLAY_PlayMode();
	break;
	case kDisplay_MSetReTime:
		DISPLAY_SetRecordingTime();
	break;
	case kDisplay_MSetSoundEffect:
		DISPLAY_SoundEffects();
	break;
	case kDisplay_MRecording:
		DISPLAY_Recording_msg();
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
	LCD_nokia_goto_xy(1, 4);
	LCD_nokia_send_string(M0_op3);
}
void DISPLAY_Menu_RealT(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0, 0);
	LCD_nokia_send_string(MManual_msg1);
}

void DISPLAY_Recording_msg(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0, 2);
	LCD_nokia_send_string(Playing_msg);
}

void DISPLAY_SetRecordingTime(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0, 0);
	LCD_nokia_send_string(Recording_time_msg);
	LCD_nokia_goto_xy(0, 2);
	LCD_nokia_send_string(Recording_time_msg1);
	LCD_nokia_goto_xy(0, 4);
	LCD_nokia_send_string(Recording_time_msg2);

}

void DISPLAY_PlayMode(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0, 0);
	LCD_nokia_send_string(PlayMode_msg);
	LCD_nokia_goto_xy(0, 2);
	LCD_nokia_send_string(PlayMode_msg1);
	LCD_nokia_goto_xy(0, 4);
	LCD_nokia_send_string(PlayMode_msg2);
}

void DISPLAY_SoundEffects()
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0, 0);
	LCD_nokia_send_string(Sound_effect_msg);
	LCD_nokia_goto_xy(0, 1);
	LCD_nokia_send_string(Sound_effect_msg1);
	LCD_nokia_goto_xy(0, 2);
	LCD_nokia_send_string(Sound_effect_msg2);
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(Sound_effect_msg3);
	LCD_nokia_goto_xy(0, 4);
	LCD_nokia_send_string(Sound_effect_msg4);
	LCD_nokia_goto_xy(0, 5);
	LCD_nokia_send_string(Sound_effect_msg5);
	LCD_nokia_goto_xy(0, 0);
}

void DISPLAY_EffectSelect (uint8_t sel)
{
	switch(sel)
	{
		case 0:
			LCD_nokia_goto_xy(0,1);
			LCD_nokia_send_string(Sound_cursor_msg);
		break;
		case 1:
			LCD_nokia_goto_xy(0,2);
			LCD_nokia_send_string(Sound_cursor_msg1);
		break;
		case 2:
			LCD_nokia_goto_xy(0,3);
			LCD_nokia_send_string(Sound_cursor_msg2);
		break;
		case 3:
			LCD_nokia_goto_xy(0,4);
			LCD_nokia_send_string(Sound_cursor_msg3);
		break;
		case 4:
			LCD_nokia_goto_xy(0,5);
			LCD_nokia_send_string(Sound_cursor_msg4);
		break;
	}

}
void DISPLAY_systemError(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(2,2);
	LCD_nokia_send_string(wdg_msg);
}
