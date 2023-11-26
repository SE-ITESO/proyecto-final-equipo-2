/*
 * display.h
 *
 *  Created on: 16 nov. 2023
 *      Author: diego
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include "sounds.h"

typedef enum {
	kDisplay_M0 = 0u,
	kDisplay_MManual = 1u,
	kDisplay_MSecuence = 2u
}Menu_t;

void DISPLAY_display_sound(SOUNDS_sound_t sound);
void DISPLAY_MenuSelec(Menu_t MenuSel);
void DISPLAY_Menu0(void);
void DISPLAY_Menu_Manual(void);
void DISPLAY_Menu_Secuence(void);
void DISPLAY_Playing_msg(void);
void DISPLAY_InitialPic(void);
void DISPLAY_systemError(void);

#endif /* DISPLAY_H_ */
