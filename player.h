/*
 * player.h
 *
 *  Created on: 30 nov 2023
 *      Author: MIKE
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdint.h>
#include "dsp.h"
#include "display.h"
#include "pit.h"

#define BTN0 (1u)
#define BTN1 (2u)
#define BTN2 (3u)

Menu_t PLAYER_checkBtn(uint8_t btn, Menu_t mode);


#endif /* PLAYER_H_ */
