/*
 * dsp.c
 *
 *  Created on: 30 nov 2023
 *      Author: MIKE
 */

#include "dsp.h"
#include "impulses.h"
#include "dma.h"



static DSP_IR_t g_IR_select = kDSP_IR_NoEffect;
static uint16_t past_auxArr[kDSP_IR_Metallic_Len];

static uint16_t Read_samples[SAMPLES_PER_SEC];
static uint16_t Play_samples[kDSP_IR_Metallic_Len + SAMPLES_PER_SEC - 1u];


static void ArrayShift(uint16_t* Arr,uint16_t Newdata,uint16_t count)
{
	uint16_t index = 0;
	uint16_t aux = Arr[index];
	Arr[index] = Newdata;
	index++;
	for(uint16_t i = count;i>0;i--)
	{
		Arr[index] = aux;
		index++;
		aux = Arr[index];
	}
}

void DSP_convolution(void)
{
	uint16_t res = 0u;
	uint8_t * Ptr = get_ImpulsePtr(g_IR_select);

	for(uint32_t i=0; i<(SAMPLES_PER_SEC+kDSP_IR_Metallic_Len - 1u);i++)
	{
		ArrayShift(past_auxArr, Read_samples[i],i);
		for(uint16_t j=i ; j>0 ;j--)
		{
			res += *(Ptr+i) * past_auxArr[j];
		}
		Play_samples[i] = res;
	}
}

void DSP_setIR(DSP_IR_t impulseResponse)
{
	switch(impulseResponse)
	{
	case kDSP_IR_NoEffect:
		g_IR_select = kDSP_IR_NoEffect;
	break;
	case kDSP_IR_Hall:
		g_IR_select = kDSP_IR_Hall;
	break;
	case kDSP_IR_Metallic:
		g_IR_select = kDSP_IR_Metallic;
	break;
	case kDSP_IR_Box:
		g_IR_select = kDSP_IR_Box;
	break;
	case kDSP_IR_Reverb:
		g_IR_select = kDSP_IR_Reverb;
	break;
	case kDSP_IR_Cricket:
		g_IR_select = kDSP_IR_Cricket;
	break;
	}
}


void DSP_setDMA(void)
{
	DMA_ADC_MEM_DAC(Read_samples, Play_samples);
}

