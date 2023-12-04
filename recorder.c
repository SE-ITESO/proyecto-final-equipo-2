/*
 * recorder.c
 *
 *  Created on: 1 dic. 2023
 *      Author: diego
 */

#include "pit.h"
#include "recorder.h"

typedef enum{
	False = 0u,
	True = 1u
}Bool_t;

typedef enum{
	Microphone_mode = 0u,
	Record_mode = 1u,
	Play_mode =2u
}Mode_t;

static uint8_t flag1 = False;
static uint8_t flag2 = False;

static uint8_t g_sample_count_adc = 0;
static uint8_t g_sample_count_dac = 0;

static Mode_t g_mode = Microphone_mode;		//Mode of operation of the player

static uint16_t msg [100000];
static Recorder_msg_t g_msg_sel = kRECORDER_Msg1;

void RECORDER_RecordAudio()
{
	PIT_startxTimer(kPit_0, Delay100Us);
}

void RECORDER_PlayMsg(Recorder_msg_t sel)
{
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
			MEMORY_Read(msg, MSG2_ADDRS);
			PIT_startxTimer(kPit_1, Delay100Us);
			flag2 = True;
			flag1 = False;
		}
	break;
	}
}



void RECORDER_CheckSamples(Recorder_transfer_t sel)
{
	switch (sel)
	{
	case kRECORDER_Adc:
		g_sample_count_adc ++;
		if(4 < g_sample_count_adc)
		{
			g_sample_count_adc = 0;
			PIT_stopxTimer(kPit_1);
		}
	break;
	case kRECORDER_Dac:
		g_sample_count_dac ++;
		if(4 < g_sample_count_dac)
		{
			g_sample_count_dac = 0;
			PIT_stopxTimer(kPit_0);
		}
	break;
	}

}

void RECORDER_mode(Menu_t Sel)
{
	switch(Sel)
	{
	case kDisplay_M0:
	 PLAYER_init();
	 DISPLAY_MenuSelec(Sel);
	break;
	case kDisplay_MRealT:
	 DISPLAY_MenuSelec(Sel);
	 g_mode = Microphone_mode;
	break;
	case kDisplay_MSetReTime:
	 DISPLAY_MenuSelec(Sel);
	 g_mode = Record_mode;
	break;
	case kDisplay_MPlay:
	 DISPLAY_MenuSelec(Sel);
	 g_mode = Play_mode;
	break;
	}
}
