/*
 * dsp.h
 *
 *  Created on: 30 nov 2023
 *      Author: MIKE
 */

#ifndef DSP_H_
#define DSP_H_

#include <stdint.h>

typedef enum{
	kDSP_IR_NoEffect = 0u,
	kDSP_IR_Hall = 1u,
	kDSP_IR_Metallic = 2u,
	kDSP_IR_Box = 3u,
	kDSP_IR_Reverb = 4u,
	kDSP_IR_Cricket = 5u,
}DSP_IR_t;

typedef enum{
	kDSP_IR_Hall_Len = 58014u,
	kDSP_IR_Metallic_Len = 72002u,
	kDSP_IR_Box_Len = 4342u,
	kDSP_IR_Reverb_Len = 41724u,
	kDSP_IR_Cricket_Len= 25756u,
}DSP_IR_Len_t;

#define SAMPLES_PER_SEC 24000u

void DSP_convolution(void);
void DSP_get_IR(DSP_IR_t IR);
void DSP_setDMA(void);
void DSP_setIR(DSP_IR_t impulseResponse);

#endif /* DSP_H_ */
