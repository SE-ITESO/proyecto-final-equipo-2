/*
 * dma.h
 *
 *  Created on: 15 nov 2023
 *      Author: MIKE
 */

#ifndef DMA_H_
#define DMA_H_

#include <stdint.h>
#include "fsl_dmamux.h"
#include "fsl_edma.h"

void DMA_init(void);
void DMA_callbackInit(void (*dma_Handler)(void));
void DMA_xfer2DAC(uint8_t* dataAddrs, uint16_t dataLen);

#endif /* DMA_H_ */
