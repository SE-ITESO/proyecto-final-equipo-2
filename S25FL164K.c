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

#define SECOND_BYTE (1U)

/*!
 * MEMORY_Read
 * Function to read the spi memory one byte at a time
 *
 * @param *dataAddrs Pointer to dhe address whe data will be stored
 * @param readAddrs Value of the address to be read in the memory
 * @param dataLen Length of the read data, each 16 bits equals 1 in length
 * */
void MEMORY_Read(uint16_t* dataArr, uint32_t readAddrs,uint32_t dataLen)
{
	uint8_t addrsArr[4];
	uint32_t index = 0u;
	uint8_t readByte;
	uint8_t auxArr[2];
	uint8_t count = 0u;
	uint16_t data;
	addrsArr[0] = 0x03;	//Read command for the memory

	dspi_half_duplex_transfer_t xfer;
	xfer.configFlags = kDSPI_MasterPcsContinuous | kDSPI_MasterCtar1 | kDSPI_MasterPcs1;
	xfer.isPcsAssertInTransfer = true;
	xfer.rxData = &readByte;
	xfer.rxDataSize = 1u;
	xfer.txData = addrsArr;
	xfer.txDataSize = 4u;
	xfer.isTransmitFirst = true;

	for(uint32_t i=dataLen; i>0; i--)
	{
		addrsArr[1] = (readAddrs >> 16u) & 0xFF;
		addrsArr[2] = (readAddrs >> 8u) & 0xFF;
		addrsArr[3] = readAddrs & 0xFF;
		DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);

		if(SECOND_BYTE == count)
		{
			auxArr[1] = readByte;
			count = 0;
			data = auxArr[0];
			data |= (auxArr[1] << 8u);
			dataArr[index] = data;
			index++;
		}
		else
		{
			auxArr[0] = readByte;
			count++;
		}
		readAddrs++;
	}
}

void MEMORY_Write(uint16_t* dataArr,uint32_t writeAddrs, uint32_t dataLen)
{
	uint8_t addrsArr[4];
	addrsArr[0]= 0x02;			//Page program command for the memory
	uint8_t write_En = 0x06;	//Write enable command for the memory
	uint8_t data = 0;
	uint8_t auxarr[256];

	dspi_half_duplex_transfer_t xfer;
	xfer.configFlags = kDSPI_MasterPcsContinuous | kDSPI_MasterCtar1 | kDSPI_MasterPcs1;
	xfer.isTransmitFirst = true;


	/*****************Sending the Write enable command prior to writing to the memory********************/
	xfer.rxData = &data;
	xfer.rxDataSize = 0u;
	xfer.txData = &write_En;
	xfer.txDataSize = 1u;
	xfer.isPcsAssertInTransfer = false;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);
	/****************************************************************************************************/
	xfer.rxData = &data;
	xfer.rxDataSize = 0u;
	xfer.txData = &write_En;
	xfer.txDataSize = 1u;
	xfer.isPcsAssertInTransfer = true;
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


/*!
 * MEMORY_checkBusy
 *
 * Performs a reading of the Status Register 1 of the memory
 * and returns a 1 if the status busy is active, meaning that the memory is busy
 *
 * @retval status of the busy bit in the Status register 1
 *
 * */
uint8_t MEMORY_checkBusy(void)
{
	uint8_t readSR1 = 0x05;
	uint8_t data = 0u;
	uint8_t checkMask = 0x01;
	uint8_t Mask = 0u;
	uint8_t retval = 0u;

	xfer.rxData = &data;
	xfer.rxDataSize = 1u;
	xfer.txData = &readSR1;
	xfer.txDataSize = 1u;
	xfer.isPcsAssertInTransfer = true;
	DSPI_MasterHalfDuplexTransferBlocking(SPI0, &xfer);

	Mask = data && checkMask;

	if(Mask)
	{
		retval = 1u;
	}

	return retval;
}



void MEMORY_ERASE_Block(uint32_t memAddrs)
{

}
