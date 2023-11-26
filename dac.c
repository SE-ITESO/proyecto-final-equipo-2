/*
 * dac.c
 *
 *  Created on: 30 sep 2023
 *      Author: MIKE
 */

#include <stdint.h>
#include "dac.h"
#include "fsl_dac.h"

//DAC configuration data types
static  dac_config_t DacConfig;
static  dac_buffer_config_t DacBuffConf;

#define BUFF_MAX_INDEX 15u

/*!
 * DAC_setup configures and initializes the DAC
 * in its circular buffer working mode
 * and enables the DAC's buffer
 */
void DAC_setup(void)
{
	DAC_GetDefaultConfig(&DacConfig);
	DAC_Init(DAC0, &DacConfig);
	DAC_Enable(DAC0, true);
	DAC_EnableBuffer(DAC0, true);
	DAC_GetDefaultBufferConfig(&DacBuffConf);
	DacBuffConf.triggerMode = kDAC_BufferTriggerBySoftwareMode;
	DacBuffConf.watermark = kDAC_BufferWatermark1Word;
	DacBuffConf.workMode = kDAC_BufferWorkAsNormalMode;
	DacBuffConf.upperLimit = BUFF_MAX_INDEX;
	DAC_SetBufferConfig(DAC0, &DacBuffConf);
	DAC_SetBufferReadPointer(DAC0, 0u);
	DAC_SetBufferValue(DAC0, 0u, 0u);
}
