/*
 * LowPassFilter.cpp
 *
 *  Created on: 1 дек. 2020 г.
 *      Author: borzenkov
 */
#include "LowPassFilter.h"

bool LowPassFilterInit(t_low_pass_filter *filtr, float k, uint8_t fixPointPos)
{
	if(k > 1)
		k = 1;

	if( (k * (1<<fixPointPos)) < 1 )
	{
		filtr->isInit = false;// k_fix_point == 0
		return filtr->isInit;
	}

	float tmp = (1<<fixPointPos) * k;
	filtr->k_fix_point = (int32_t)tmp;
	filtr->data_out = 0;
	filtr->fixPointPos = fixPointPos;

	filtr->isInit = true;

	return filtr->isInit;
}

//	pot = (1-K)*pot + K*pot_raw
int32_t LowPassFilterCalc(t_low_pass_filter *filtr, uint32_t data_in)
{
	int32_t tmp1 = 0;
	int32_t tmp2 = 0;

	if(!filtr->isInit)
	{
		filtr->data_out = data_in;
		return data_in;
	}

	tmp1 = ((1<<filtr->fixPointPos) - filtr->k_fix_point);
	tmp1 = (tmp1 * filtr->data_out)>>filtr->fixPointPos;

	tmp2 = (filtr->k_fix_point * data_in)>>filtr->fixPointPos;

	filtr->data_out = tmp1 + tmp2;

	return filtr->data_out;
}
