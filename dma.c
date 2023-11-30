/*
 * dma.c
 *
 *  Created on: 15 nov 2023
 *      Author: MIKE
 */


#include "dma.h"
#include "fsl_dac.h"
#include "adc.h"

#define TCD_QUEUE_SIZE      1U
#define DMA_ALWAYS_EN_SOURCE (58u)
#define DAC0ADDRS DAC0
#define ADC0ADDRS (0x4003B010U)

static void (*DMA_callback)(void) = 0u;

volatile bool g_Transfer_Done = false;


AT_QUICKACCESS_SECTION_DATA_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE + 1], sizeof(edma_tcd_t));

edma_handle_t g_EDMA_Handle;
static edma_transfer_config_t transferConfig1;
static edma_transfer_config_t transferConfig2;

static void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        DMA_callback();
    }
}

void DMA_init(void)
{
	edma_config_t userConfig;

	DMAMUX_Init(DMAMUX0);
	DMAMUX_EnablePeriodTrigger(DMAMUX0, 0u);
	DMAMUX_SetSource(DMAMUX0, 0u, DMA_ALWAYS_EN_SOURCE);
	DMAMUX_EnableChannel(DMAMUX0, 0u);
	EDMA_GetDefaultConfig(&userConfig);
	EDMA_Init(DMA0, &userConfig);
	EDMA_CreateHandle(&g_EDMA_Handle, DMA0, 0);
	EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
	EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);
}

void DMA_callbackInit(void (*dma_Handler)(void))
{
	DMA_callback = dma_Handler;
}

static void DMA_xfer2DAC(uint8_t* dataAddrs, uint16_t dataLen)
{
	EDMA_PrepareTransferConfig(&transferConfig1,
			   dataAddrs,
			   2,
			   2, /* source offset */
			   DAC0ADDRS,
			   2,
			   0,               /* dest offset */
			   2u,   		/* minor loop bytes: 8*/
			   dataLen); /* major loop counts : 4 */
   EDMA_TcdSetMajorOffsetConfig(
					   tcdMemoryPoolPtr, //param tcd A point to the TCD structure.
					   -dataLen, //* param sourceOffset source address offset.
					   0);//destOffset destination address offset.

   EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig1, NULL);

   EDMA_TcdEnableInterrupts(&tcdMemoryPoolPtr[0], kEDMA_MajorInterruptEnable);
   EDMA_TcdEnableAutoStopRequest(&tcdMemoryPoolPtr[0], false);
   EDMA_InstallTCD(DMA0, 0, &tcdMemoryPoolPtr[0]);
   EDMA_EnableChannelRequest(DMA0, 0);
}

void DMA_ADC_MEM_DAC(uint16_t * receiveDataAddrs,uint16_t * sendDataAddrs)
{
	edma_config_t userConfig;

	DMAMUX_Init(DMAMUX0);
	DMAMUX_EnablePeriodTrigger(DMAMUX0, 0u);
	DMAMUX_EnablePeriodTrigger(DMAMUX0, 1u);

	DMAMUX_SetSource(DMAMUX0, 0u, DMA_ALWAYS_EN_SOURCE);
	DMAMUX_EnableChannel(DMAMUX0, 0u);
	EDMA_GetDefaultConfig(&userConfig);
	EDMA_Init(DMA0, &userConfig);
	EDMA_CreateHandle(&g_EDMA_Handle, DMA0, 0);
	EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
	EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);

	EDMA_PrepareTransferConfig(&transferConfig1,
			   sendDataAddrs,
			   2,
			   2, /* source offset */
			   DAC0ADDRS,
			   2,
			   0,               /* dest offset */
			   2u,   		/* minor loop bytes: 8*/
			   24000); /* major loop counts : 24kBytes = 1 second*/
   EDMA_TcdSetMajorOffsetConfig(
					   tcdMemoryPoolPtr, //param tcd A point to the TCD structure.
					   0, //* param sourceOffset source address offset.
					   0);//destOffset destination address offset.

   EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig1, NULL);

   EDMA_TcdEnableInterrupts(&tcdMemoryPoolPtr[0], kEDMA_MajorInterruptEnable);
   EDMA_TcdEnableAutoStopRequest(&tcdMemoryPoolPtr[0], false);
   EDMA_InstallTCD(DMA0, 0, &tcdMemoryPoolPtr[0]);
   EDMA_EnableChannelRequest(DMA0, 0);



	DMAMUX_SetSource(DMAMUX0, 1u, 40u);
	DMAMUX_EnableChannel(DMAMUX0, 1u);
	EDMA_GetDefaultConfig(&userConfig);
	EDMA_Init(DMA0, &userConfig);
	EDMA_CreateHandle(&g_EDMA_Handle, DMA0, 1);
	EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
	EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);

	EDMA_PrepareTransferConfig(&transferConfig2,
			   receiveDataAddrs,
			   2,
			   2, /* source offset */
			   sendDataAddrs,
			   2,
			   2,               /* dest offset */
			   2u,   		/* minor loop bytes: 8*/
			   24000); /* major loop counts : 24kBytes = 1 second*/
  EDMA_TcdSetMajorOffsetConfig(
					   tcdMemoryPoolPtr, //param tcd A point to the TCD structure.
					   -24000, //* param sourceOffset source address offset.
					   0);//destOffset destination address offset.

  EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig2, NULL);

  EDMA_TcdEnableInterrupts(&tcdMemoryPoolPtr[0], kEDMA_MajorInterruptEnable);
  EDMA_TcdEnableAutoStopRequest(&tcdMemoryPoolPtr[0], false);
  EDMA_InstallTCD(DMA0, 1u, &tcdMemoryPoolPtr[0]);
  EDMA_EnableChannelRequest(DMA0, 1u);
}

void DMA_config(DMA_Config_t config)
{
	switch(config)
	{
	case kDMA_DMA2DAC:

	break;
	case kDMA_DMA2MEM:

	break;
	case kDMA_DMA2MEMSPI:

	break;
	}
}
