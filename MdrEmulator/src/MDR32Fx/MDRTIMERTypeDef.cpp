/*
 * MDRTIMERTypeDef.cpp
 *
 *  Created on: 11 џэт. 2021 у.
 *      Author: borzenkov
 */

#include "MDRTIMERTypeDef.h"

MDR_TIMER_TypeDef::MDR_TIMER_TypeDef():
Name("")
{
	Init("");
}

MDR_TIMER_TypeDef::MDR_TIMER_TypeDef(string& name)
{
	Init(name);
	//	 RXTX.Init("MDR_PORT->RXTX",0);
//	 OE.Init("MDR_PORT->OE",0);
//	 FUNC.Init("MDR_PORT->FUNC",0);
//	 ANALOG.Init("MDR_PORT->ANALOG",0);
//	 PULL.Init("MDR_PORT->PULL",0);
//	 PD.Init("MDR_PORT->PD",0);
//	 PWR.Init("MDR_PORT->PWR",0);
//	 GFEN.Init("MDR_PORT->GFEN",0);
}

MDR_TIMER_TypeDef::~MDR_TIMER_TypeDef() {
	// TODO Auto-generated destructor stub
}

void MDR_TIMER_TypeDef::Init(string name)
{
	this->Name = name;

	CNT.Init("MDR_TIMER" + name + "->CNT",0);
	PSG.Init("MDR_TIMER" + name + "->PSG",0);
	ARR.Init("MDR_TIMER" + name + "->ARR",0);
	CNTRL.Init("MDR_TIMER" + name + "->CNTRL",0);
	CCR1.Init("MDR_TIMER" + name + "->CCR1",0);
	CCR2.Init("MDR_TIMER" + name + "->CCR2",0);
	CCR3.Init("MDR_TIMER" + name + "->CCR3",0);
	CCR4.Init("MDR_TIMER" + name + "->CCR4",0);
	CH1_CNTRL.Init("MDR_TIMER" + name + "->CH1_CNTRL",0);
	CH2_CNTRL.Init("MDR_TIMER" + name + "->CH2_CNTRL",0);
	CH3_CNTRL.Init("MDR_TIMER" + name + "->CH3_CNTRL",0);
	CH4_CNTRL.Init("MDR_TIMER" + name + "->CH4_CNTRL",0);
	CH1_CNTRL1.Init("MDR_TIMER" + name + "->CH1_CNTRL1",0);
	CH2_CNTRL1.Init("MDR_TIMER" + name + "->CH2_CNTRL1",0);
	CH3_CNTRL1.Init("MDR_TIMER" + name + "->CH3_CNTRL1",0);
	CH4_CNTRL1.Init("MDR_TIMER" + name + "->CH4_CNTRL1",0);
	CH1_DTG.Init("MDR_TIMER" + name + "->CH1_DTG",0);
	CH2_DTG.Init("MDR_TIMER" + name + "->CH2_DTG",0);
	CH3_DTG.Init("MDR_TIMER" + name + "->CH3_DTG",0);
	CH4_DTG.Init("MDR_TIMER" + name + "->CH4_DTG",0);
	BRKETR_CNTRL.Init("MDR_TIMER" + name + "->BRKETR_CNTRL",0);
	STATUS.Init("MDR_TIMER" + name + "->STATUS",0);
	IE.Init("MDR_TIMER" + name + "->IE",0);
	DMA_RE.Init("MDR_TIMER" + name + "->DMA_RE",0);
	CH1_CNTRL2.Init("MDR_TIMER" + name + "->CH1_CNTRL2",0);
	CH2_CNTRL2.Init("MDR_TIMER" + name + "->CH2_CNTRL2",0);
	CH3_CNTRL2.Init("MDR_TIMER" + name + "->CH3_CNTRL2",0);
	CH4_CNTRL2.Init("MDR_TIMER" + name + "->CH4_CNTRL2",0);
	CCR11.Init("MDR_TIMER" + name + "->CCR11",0);
	CCR21.Init("MDR_TIMER" + name + "->CCR21",0);
	CCR31.Init("MDR_TIMER" + name + "->CCR31",0);
	CCR41.Init("MDR_TIMER" + name + "->CCR41",0);
}

