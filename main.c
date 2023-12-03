#include <stdint.h>
#include "SPI.h"
#include "S25FL164K.h"
#include "system_clock.h"
#include "recorder.h"

int main(void)
{
	SYSTEM_CLOCK_setup();
	CLOCK_SetSimSafeDivs();


}
