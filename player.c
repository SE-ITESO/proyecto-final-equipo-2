/*
 * player.c
 *
 *  Created on: 30 nov 2023
 *      Author: MIKE
 */

#include "player.h"

static uint8_t g_effect_Sel = 0u;

static void PLAYER_setRealTime(void)
{
	PIT_startxTimer(kPit_0, PERIOD_16KHz);
	PIT_startxTimer(kPit_1, PERIOD_16KHz);
	DSP_setDMA();
}
static void PLAYER_setEffect(uint8_t Sel)
{
	DSP_IR_t impulse = kDSP_IR_NoEffect;
	switch(Sel)
	{
	case 0:
		impulse = kDSP_IR_NoEffect;
	break;
	case 1:
		impulse = kDSP_IR_Hall;
	break;
	case 2:
		impulse = kDSP_IR_Metallic;
	break;
	case 3:
		impulse = kDSP_IR_Box;
	break;
	case 4:
		impulse = kDSP_IR_Reverb;
	break;
	case 5:
		impulse = kDSP_IR_Cricket;
	break;
	}
	DSP_setIR(impulse);
}

//static void PLAYER_setRecording(void);
//static void PLAYER_playRecording(void);


Menu_t PLAYER_checkBtn(uint8_t btn, Menu_t mode)
{
	/*Funcion que checa que resive el boton que fue presionado y el modo actual para saber que hacer*/
	Menu_t retval = 0u;
	switch(mode)
	{
	case kDisplay_M0:
		DISPLAY_Menu0();
		if(BTN0 == btn)
		{
			retval = kDisplay_MRealT;
			PLAYER_setRealTime();
		}
		else if(BTN1 == btn)
		{
			retval = kDisplay_MSetReTime;
		}
		else if(BTN2 == btn)
		{
			retval = kDisplay_MPlay;
		}
	break;
	case kDisplay_MRealT:
		DISPLAY_Menu_RealT();
		if(BTN0 == btn)
		{
			retval = kDisplay_M0;
			//PIT_stopxTimer(kPit_0);
			//PIT_stopxTimer(kPit_1);
		}
	break;
	case kDisplay_MSetReTime:
		DISPLAY_SetRecordingTime();
		if(BTN0 == btn)
		{
			retval = kDisplay_M0;
		}
		else if(BTN1 == btn)
		{
			retval = kDisplay_MRecording;
		}
		else if(BTN2 == btn)
		{
			retval = kDisplay_MRecording;
		}
	break;
	case kDisplay_MPlay:
		DISPLAY_PlayMode();
		if(BTN0 == btn)
		{
			retval = kDisplay_M0;
		}
		else if(BTN1 == btn)
		{
			retval = kDisplay_MPlay;
			/*Reproducir msg1*/
		}
		else if(BTN2 == btn)
		{
			retval = kDisplay_MPlay;
			/*Reproducir msg2*/
		}
	break;
	case kDisplay_MSetSoundEffect:
		DISPLAY_SoundEffects();
		if(BTN0 == btn)
		{
			retval = kDisplay_M0;
			g_effect_Sel = 0u;
		}
		else if(BTN1 == btn)
		{
			retval = kDisplay_MSetSoundEffect;
			g_effect_Sel++;
			if(g_effect_Sel > 5u)
			{
				g_effect_Sel = 0;
			}
			DISPLAY_EffectSelect(g_effect_Sel);
		}
		else if(BTN2 == btn)
		{
			retval = kDisplay_MSetSoundEffect;
			PLAYER_setEffect(g_effect_Sel);
		}
	break;
	case kDisplay_MRecording:
		DISPLAY_Recording_msg();
		if(BTN0 == btn)
		{
			retval = kDisplay_M0;
			g_effect_Sel = 0u;
		}
		if(BTN2 == btn)
		{
			retval = kDisplay_MSetReTime;
			g_effect_Sel = 0u;
		}
	}
	return retval;
}
