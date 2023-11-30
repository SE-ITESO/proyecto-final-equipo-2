/*
 * display.h
 *
 *  Created on: 16 nov. 2023
 *      Author: diego
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

typedef enum {
	kDisplay_M0 = 0u,
	kDisplay_MRealT = 1u,
	kDisplay_MSetReTime = 2u,
	kDisplay_MPlay = 3u,
	kDisplay_MSetSoundEffect = 4u,
	kDisplay_MRecording =5u

}Menu_t;

void DISPLAY_MenuSelec(Menu_t MenuSel);
void DISPLAY_Menu0(void);
void DISPLAY_Menu_RealT(void);
void DISPLAY_Menu_Record(void);
void DISPLAY_Recording_msg(void);
void DISPLAY_systemError(void);
void DISPLAY_SetRecordingTime(void);
void DISPLAY_PlayMode(void);
void DISPLAY_SoundEffects(void);
void DISPLAY_EffectSelect (uint8_t sel);

#endif /* DISPLAY_H_ */
