/*
 * port.c
 *
 *  Created on: 15 oct. 2023
 *      Author: diego
 */

#include "port.h"
#include "fsl_clock.h"
#include "fsl_port.h"


#define IC20_SCL_pin 2u
#define IC20_SDA_pin 3u
#define UART0_RX_pin 16u
#define UART0_TX_pin 17u
#define UART4_RX_pin 14u
#define UART4_TX_pin 15u
#define Stop 6u			/*SW2 pin*/

static const port_pin_config_t portSWConf = {
		kPORT_PullUp,
		kPORT_FastSlewRate,
		kPORT_PassiveFilterEnable,
		kPORT_OpenDrainDisable,
		kPORT_HighDriveStrength,
		kPORT_MuxAsGpio,
		kPORT_UnlockRegister
};

void PORT_init(void)
{
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortC);

    PORT_SetPinConfig(PORTC, Stop, &portSWConf);

    PORT_SetPinMux(PORTB, IC20_SCL_pin, kPORT_MuxAlt2);
    PORT_SetPinMux(PORTB, IC20_SDA_pin, kPORT_MuxAlt2);

    PORT_SetPinMux(PORTB, UART0_RX_pin, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTB, UART0_TX_pin, kPORT_MuxAlt3);

    PORT_SetPinMux(PORTC, UART4_RX_pin, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTC, UART4_TX_pin, kPORT_MuxAlt3);
}

