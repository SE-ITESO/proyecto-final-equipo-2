/*
 * recorder.h
 *
 *  Created on: 1 dic. 2023
 *      Author: diego
 */

#ifndef RECORDER_H_
#define RECORDER_H_

#define Delay100Us 100u
#define MSG1_ADDRS 0x000000u
#define MSG2_ADDRS 0x003000u
#define MSG_LENG 90000u

typedef enum{
	kRECORDER_Msg1_Addrs = 0x000000u,
	kRECORDER_Msg2_Addrs = 0x030000u
};

typedef enum {
	kRECORDER_Msg1 = 0u,
	kRECORDER_Msg2 = 1u
}Recorder_msg_t;

typedef enum {
	kRECORDER_Adc = 0u,
	kRECORDER_Dac = 1u
}Recorder_transfer_t;



void RECORDER_RecordAudio(void);
void RECORDER_PlayMsg(Recorder_msg_t sel);
void RECORDER_CheckSamples(Recorder_transfer_t sel);

#endif /* RECORDER_H_ */
