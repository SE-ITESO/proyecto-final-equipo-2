#include <stdint.h>
#include "SPI.h"
#include "S25FL164K.h"
#include "system_clock.h"
#include "fsl_clock.h"

#define DATA_SIZE 90000u
#define MAX_16_BIT 0xFFFF

uint16_t Arr[DATA_SIZE];

int main(void)
{
	SYSTEM_CLOCK_setup();
	CLOCK_SetSimSafeDivs();


	uint16_t count = 0u;

	for(uint32_t i=0;i<DATA_SIZE;i++)
	{
		Arr[i] = count;
		count++;

		if(count>MAX_16_BIT)
		{
			count = 0u;
		}
	}
	SPI_config();

	MEMORY_ReadSR();

	MEMORY_Write(Arr, 0x000000, DATA_SIZE);
	MEMORY_Read(Arr, 0x000000, DATA_SIZE);

	while(1)
	{

	}
	return 0;
}
