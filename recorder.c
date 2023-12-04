/*
 * recorder.c
 *
 *  Created on: 1 dic. 2023
 *      Author: diego
 */

#include "pit.h"
#include "recorder.h"
#include "S25FL164K.h"

#define RECORDED_SAMPLES (90000u)

typedef enum{
	False = 0u,
	True = 1u
}Bool_t;

static uint8_t flag1 = False;
static uint8_t flag2 = False;

static uint8_t g_sample_count_adc = 0;
static uint8_t g_sample_count_dac = 0;

static uint16_t msg [RECORDED_SAMPLES];
static Recorder_msg_t g_msg_sel = kRECORDER_Msg1;

void RECORDER_RecordAudio(void)
{
	DMA_ADC_MEM(msg, (RECORDED_SAMPLES*2));
	PIT_startxTimer(kPit_1, 100);
}

void RECORDER_PlayMsg(Recorder_msg_t sel)
{
	DMA_MEM_DAC(msg, (RECORDED_SAMPLES*2));
	switch (sel)
	{
	case kRECORDER_Msg1:
		if (flag1)
		{
			PIT_startxTimer(kPit_1, Delay100Us);
		}
		else
		{
			MEMORY_Read(msg, MSG1_ADDRS, MSG_LENG);
			PIT_startxTimer(kPit_1, Delay100Us);
			flag1 = True;
			flag2 = False;
		}
	break;
	case kRECORDER_Msg2:
		if (flag2)
		{
			PIT_startxTimer(kPit_1, Delay100Us);
		}
		else
		{
			MEMORY_Read(msg, MSG2_ADDRS,MSG_LENG);
			PIT_startxTimer(kPit_1, Delay100Us);
			flag2 = True;
			flag1 = False;
		}
	break;
	}
}

void RECORDER_SaveAudio(void)
{
	switch(g_msg_sel)
	{
	case kRECORDER_Msg1:
		MEMORY_Write(msg, kRECORDER_Msg1_Addrs, RECORDED_SAMPLES);
	break;
	case kRECORDER_Msg2:
		MEMORY_Write(msg, kRECORDER_Msg2_Addrs, RECORDED_SAMPLES);
	break;
	}
}
