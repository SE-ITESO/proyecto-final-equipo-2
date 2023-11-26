/*
 * dma.c
 *
 *  Created on: 15 nov 2023
 *      Author: MIKE
 */


#include "dma.h"
#include "fsl_dac.h"

#define TCD_QUEUE_SIZE      1U
#define DMA_ALWAYS_EN_SOURCE (58u)
#define DAC0ADDRS DAC0

static void (*DMA_callback)(void) = 0u;

volatile bool g_Transfer_Done = false;

AT_QUICKACCESS_SECTION_DATA_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE + 1], sizeof(edma_tcd_t));

edma_handle_t g_EDMA_Handle;
static edma_transfer_config_t transferConfig;

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

void DMA_xfer2DAC(uint8_t* dataAddrs, uint16_t dataLen)
{
	EDMA_PrepareTransferConfig(&transferConfig,
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

   EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL);

   EDMA_TcdEnableInterrupts(&tcdMemoryPoolPtr[0], kEDMA_MajorInterruptEnable);
   EDMA_TcdEnableAutoStopRequest(&tcdMemoryPoolPtr[0], false);
   EDMA_InstallTCD(DMA0, 0, &tcdMemoryPoolPtr[0]);
   EDMA_EnableChannelRequest(DMA0, 0);
}
