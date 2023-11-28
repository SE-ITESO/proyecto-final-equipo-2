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
	kDisplay_MRecord = 2u
}Menu_t;

void DISPLAY_MenuSelec(Menu_t MenuSel);
void DISPLAY_Menu0(void);
void DISPLAY_Menu_RealT(void);
void DISPLAY_Menu_Record(void);
void DISPLAY_Recording_msg(void);
void DISPLAY_systemError(void);

#endif /* DISPLAY_H_ */
