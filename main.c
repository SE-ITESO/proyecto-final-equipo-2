/*
 * Final porject
 * Sistemas Embebidos Basados en Microcontroladores
 *
 * Authors:
 * José Miguel Castellanos Padilla
 * Diego Moran Vergara
 *
 * Description:
 *
 * The system consists of an audio recorder that uses the SPI memory S25FL164K to store
 * the audio samples read from the ADC module. The sampling rate is 30kHz.
 *
 * This system is also capable of sending the sampled audio directly to the DAC.
 *
 * The system uses convolution to add different effects to the audio
 *
 * */

#include <stdint.h>
#include "buttons.h"


int main(void) {

	SYSTEM_CLOCK_setup();
	CLOCK_SetSimSafeDivs();


	while(1) {

    }
    return 0 ;
}
