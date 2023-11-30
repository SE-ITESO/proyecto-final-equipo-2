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

typedef enum{
	kDMA_DMA2DAC = 0u,
	kDMA_DMA2MEM = 1u,
	kDMA_DMA2MEMSPI = 2u
}DMA_Config_t;

void DMA_init(void);
void DMA_callbackInit(void (*dma_Handler)(void));
void DMA_config(DMA_Config_t config);
void DMA_ADC_MEM_DAC(uint16_t * receiveDataAddrs,uint16_t * sendDataAddrs);


#endif /* DMA_H_ */
