/*
 * MDRRSTCLKTypeDef.h
 *
 *  Created on: 24 нояб. 2020 г.
 *      Author: borzenkov
 */

#ifndef MDR32FX_MDRRSTCLKTYPEDEF_H_
#define MDR32FX_MDRRSTCLKTYPEDEF_H_

//#include <stdint.h>

#include "../cMyUint32t.h"

class MDR_RST_CLK_TypeDef
{
	public:
		cMyUint32_t PER_CLOCK; // Контроллер тактовой частоты
		cMyUint32_t CLOCK_STATUS;
		cMyUint32_t PLL_CONTROL;
		cMyUint32_t HS_CONTROL;
		cMyUint32_t CPU_CLOCK;
		cMyUint32_t USB_CLOCK;
		cMyUint32_t ADC_MCO_CLOCK;
		cMyUint32_t RTC_CLOCK;
		cMyUint32_t CAN_CLOCK;
		cMyUint32_t TIM_CLOCK;
		cMyUint32_t UART_CLOCK;
		cMyUint32_t SSP_CLOCK;

		MDR_RST_CLK_TypeDef();
		virtual ~MDR_RST_CLK_TypeDef();

};

#endif /* MDR32FX_MDRRSTCLKTYPEDEF_H_ */
