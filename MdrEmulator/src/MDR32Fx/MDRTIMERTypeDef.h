/*
 * MDRTIMERTypeDef.h
 *
 *  Created on: 11 џэт. 2021 у.
 *      Author: borzenkov
 */

#ifndef MDR32FX_MDRTIMERTYPEDEF_H_
#define MDR32FX_MDRTIMERTYPEDEF_H_


#include <iostream>
#include "../cMyUint32t.h"

using namespace std;

class MDR_TIMER_TypeDef
{
	public:
		string Name;

		cMyUint32_t CNT;
		cMyUint32_t PSG;
		cMyUint32_t ARR;
		cMyUint32_t CNTRL;
		cMyUint32_t CCR1;
		cMyUint32_t CCR2;
		cMyUint32_t CCR3;
		cMyUint32_t CCR4;
		cMyUint32_t CH1_CNTRL;
		cMyUint32_t CH2_CNTRL;
		cMyUint32_t CH3_CNTRL;
		cMyUint32_t CH4_CNTRL;
		cMyUint32_t CH1_CNTRL1;
		cMyUint32_t CH2_CNTRL1;
		cMyUint32_t CH3_CNTRL1;
		cMyUint32_t CH4_CNTRL1;
		cMyUint32_t CH1_DTG;
		cMyUint32_t CH2_DTG;
		cMyUint32_t CH3_DTG;
		cMyUint32_t CH4_DTG;
		cMyUint32_t BRKETR_CNTRL;
		cMyUint32_t STATUS;
		cMyUint32_t IE;
		cMyUint32_t DMA_RE;
		cMyUint32_t CH1_CNTRL2;
		cMyUint32_t CH2_CNTRL2;
		cMyUint32_t CH3_CNTRL2;
		cMyUint32_t CH4_CNTRL2;
		cMyUint32_t CCR11;
		cMyUint32_t CCR21;
		cMyUint32_t CCR31;
		cMyUint32_t CCR41;

		MDR_TIMER_TypeDef();
		MDR_TIMER_TypeDef(string& name);
		virtual ~MDR_TIMER_TypeDef();

		void Init(string name);

};


#endif /* MDR32FX_MDRTIMERTYPEDEF_H_ */
