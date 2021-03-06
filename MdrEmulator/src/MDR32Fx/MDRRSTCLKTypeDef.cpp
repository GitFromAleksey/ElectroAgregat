/*
 * MDRRSTCLKTypeDef.cpp
 *
 *  Created on: 24 ????. 2020 ?.
 *      Author: borzenkov
 */

#include "MDRRSTCLKTypeDef.h"

MDR_RST_CLK_TypeDef::MDR_RST_CLK_TypeDef()
{
	PER_CLOCK.Init("MDR_RST_CLK->PER_CLOCK",0);
	CLOCK_STATUS.Init("MDR_RST_CLK->CLOCK_STATUS",0);
	PLL_CONTROL.Init("MDR_RST_CLK->PLL_CONTROL",0);
	HS_CONTROL.Init("MDR_RST_CLK->HS_CONTROL",0);
	CPU_CLOCK.Init("MDR_RST_CLK->CPU_CLOCK",0);
	USB_CLOCK.Init("MDR_RST_CLK->USB_CLOCK",0);
	ADC_MCO_CLOCK.Init("MDR_RST_CLK->ADC_MCO_CLOCK",0);
	RTC_CLOCK.Init("MDR_RST_CLK->RTC_CLOCK",0);
	CAN_CLOCK.Init("MDR_RST_CLK->CAN_CLOCK",0);
	TIM_CLOCK.Init("MDR_RST_CLK->TIM_CLOCK",0);
	UART_CLOCK.Init("MDR_RST_CLK->UART_CLOCK",0);
	SSP_CLOCK.Init("MDR_RST_CLK->SSP_CLOCK",0);
}

MDR_RST_CLK_TypeDef::~MDR_RST_CLK_TypeDef() {
	// TODO Auto-generated destructor stub
}

