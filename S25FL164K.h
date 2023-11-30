/*
 * S25FL164K.h
 *
 *  Created on: 12 nov 2023
 *      Author: MIKE
 */

#ifndef S25FL164K_H_
#define S25FL164K_H_

#include <stdint.h>

void MEMORY_Read(uint8_t* dataArr, uint32_t readAddrs);

void MEMORY_ReadSR(void);

void MEMORY_ERASE_Block(uint32_t memAddrs);


#endif /* S25FL164K_H_ */
