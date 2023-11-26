/*
 * Wdog.c
 *
 *  Created on: 1 oct. 2023
 *      Author: diego
 */

#include <stdint.h>
#include "fsl_wdog.h"
#include "wdog.h"
#include "fsl_rcm.h"

#define WDOGTiemout 0xBB8u  // 3s WDOG timeout

typedef enum{
	FALSE = 0u,
	TRUE = 1u
}bool_t;

//Pointer to the WDOG base register
static WDOG_Type *wdog_base = WDOG;

//Pointer to the RCM base register
static RCM_Type *rcm_base = RCM;

/*!
 * Wdog_init
 * Configures the watchdog in normal mode
 * */
uint16_t Wdog_init(void)
{
	wdog_config_t WdogConf;
	WDOG_GetDefaultConfig(&WdogConf);
	WdogConf.timeoutValue = WDOGTiemout;
	WdogConf.enableWindowMode = FALSE;

	if(!(RCM_GetPreviousResetSources(rcm_base) & kRCM_SourceWdog))
	{
		WDOG_ClearResetCount(wdog_base);
	}
	WDOG_Init(wdog_base, &WdogConf);

	return WDOG_GetResetCount(wdog_base);
}

/*!
 * Wdog_refresh
 * Used to refresh the Wdog
 * */
void Wdog_refresh(void)
{
	WDOG_Refresh(WDOG);
}
