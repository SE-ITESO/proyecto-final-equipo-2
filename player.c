/*
 * player.c
 *
 *  Created on: 30 nov 2023
 *      Author: MIKE
 */

#include "player.h"


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
		}
		else if(BTN1 == btn)
		{
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
	case kDisplay_MRecording:
		DISPLAY_Recording_msg();
		if(BTN0 == btn)
		{
			retval = kDisplay_M0;
		}
		if(BTN2 == btn)
		{
			retval = kDisplay_MRecording;
			/*Empezar a grabar*/
		}
	}
	return retval;
}
