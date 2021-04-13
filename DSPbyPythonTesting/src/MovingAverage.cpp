/*
 * MovingAverage.c
 *
 *  Created on: 6 нояб. 2020 г.
 *      Author: borzenkov
 */

#include "MovingAverage.h"

// ----------------------------------------------------------------------------
void MoveAvgInit(t_MoveAvg *avg, uint8_t div)
{
	avg->accumulator = 0;
	avg->avgValue = 0;
	avg->div = div;
}
// ----------------------------------------------------------------------------
int32_t MoveAvgCalc(t_MoveAvg *avg, uint32_t inputData)
{
	avg->accumulator -= (avg->accumulator >> avg->div);
	avg->accumulator += inputData;
	avg->avgValue = (avg->accumulator >> avg->div);

	return avg->avgValue;
}
// ----------------------------------------------------------------------------
