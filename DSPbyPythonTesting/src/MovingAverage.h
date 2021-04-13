/*
 * MovingAverage.h
 *
 *  Created on: 6 нояб. 2020 г.
 *      Author: borzenkov
 */

#ifndef SRC_MOVINGAVERAGE_H_
#define SRC_MOVINGAVERAGE_H_

#include <stdint.h>

typedef struct
{
	int32_t accumulator;	// аккумулятор для данных
	uint8_t div;			// делитель
	int32_t avgValue;		// скользящее среднее
} t_MoveAvg;

void MoveAvgInit(t_MoveAvg *avg, uint8_t div);
int32_t MoveAvgCalc(t_MoveAvg *avg, uint32_t inputData);

#endif /* SRC_MOVINGAVERAGE_H_ */
