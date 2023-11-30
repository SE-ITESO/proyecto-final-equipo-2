/*
 * S25FL164K.c
 *
 *  Created on: 12 nov 2023
 *      Author: MIKE
 */

#include "S25FL164K.h"
#include "SPI.h"
#include "stdint.h"
#include "fsl_dspi.h"

/*!
 * MEMORY_Read
 * Function to read the spi memory one byte at a time
 *
 * @param *dataAddrs Pointer to dhe address whe data will be stored
 * @param readAddrs Value of the address to be read in the memory
 * */
void MEMORY_Read(uint8_t* dataArr, uint32_t readAddrs)
{
	uint8_t readArr[4];
	readArr[0] = 0x03;
	readArr[1] = (readAddrs >> 16u) & 0xFF;
	readArr[2] = (readAddrs >> 8u) & 0xFF;
	readArr[3] = readAddrs & 0xFF;
	dspi_half_duplex_transfer_t xfer;
	xfer.configFlags = kDSPI_MasterPcsContinuous | kDSPI_MasterCtar1 | kDSPI_MasterPcs1;
	xfer.isPcsAssertInTransfer = true;
	xfer.rxData = dataArr;
	xfer.rxDataSize = 1u;
	xfer.txData = readArr;
	xfer.txDataSize = 4u;
	xfer.isTransmitFirst = true;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
}


/*!
 * MEMORY_ReadSR
 * This function is used to write the Status Registers of the memory
 * */
void MEMORY_ReadSR(void)
{
	uint8_t readSR1 = 0x05;
	uint8_t readSR2 = 0x35;
	uint8_t readSR3 = 0x33;
	uint8_t data = 0u;
	uint8_t WE_VSR = 0x50;
	//uint8_t WSR [1] = {0x01};
	uint8_t WSR_arr [4] = {0x01,0x00,0x00,0x10};

	dspi_half_duplex_transfer_t xfer;
	xfer.configFlags = kDSPI_MasterPcsContinuous | kDSPI_MasterCtar1 | kDSPI_MasterPcs1;
	xfer.isTransmitFirst = true;
	xfer.isPcsAssertInTransfer = true;
#if 0
	/*Read Status register SR1, SR2 and SR3*/
	xfer.rxData = &data;
	xfer.rxDataSize = 1u;
	xfer.txData = &readSR1;
	xfer.txDataSize = 1u;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
	xfer.rxData = &data;
	xfer.rxDataSize = 1u;
	xfer.txData = &readSR2;
	xfer.txDataSize = 1u;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
	xfer.rxData = &data;
	xfer.rxDataSize = 1u;
	xfer.txData = &readSR3;
	xfer.txDataSize = 1u;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
#endif
	/***********************************************************************/
	xfer.rxData = &data;
	xfer.rxDataSize = 0u;
	xfer.txData = &WE_VSR;
	xfer.txDataSize = 1u;
	xfer.isPcsAssertInTransfer = false;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
#if 0
	xfer.rxData = &data;
	xfer.rxDataSize = 0u;
	xfer.txData = WSR;
	xfer.txDataSize = 1u;
	xfer.isPcsAssertInTransfer = true;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
#endif
	xfer.rxData = &data;
	xfer.rxDataSize = 0u;
	xfer.txData = WSR_arr;
	xfer.txDataSize = 4u;
	xfer.isPcsAssertInTransfer = false;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
	/************************************************************************/

	/*Read Status register SR1, SR2 and SR3*/
	xfer.rxData = &data;
	xfer.rxDataSize = 1u;
	xfer.txData = &readSR1;
	xfer.txDataSize = 1u;
	xfer.isPcsAssertInTransfer = true;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
	xfer.rxData = &data;
	xfer.rxDataSize = 1u;
	xfer.txData = &readSR2;
	xfer.txDataSize = 1u;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
	xfer.rxData = &data;
	xfer.rxDataSize = 1u;
	xfer.txData = &readSR3;
	xfer.txDataSize = 1u;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
}


void MEMORY_ERASE_Block(uint32_t memAddrs)
{

}
