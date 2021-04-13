/*
 * LowPassFilter.h
 *
 *  Created on: 1 дек. 2020 г.
 *      Author: borzenkov
 */

#ifndef LOWPASSFILTER_H_
#define LOWPASSFILTER_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	int32_t k_fix_point;	// коэф. фильтра с фиксированной точкой
	uint8_t fixPointPos;	// положение фиксированной точки
	int32_t data_out;		// отфильтрованные данные
	bool isInit;
} t_low_pass_filter;

// k - коэф. фильтра (0 - 1)
// fixPointPos - положение фиксированной точки для рассчёта
bool LowPassFilterInit(t_low_pass_filter *filtr, float k, uint8_t fixPointPos);

int32_t LowPassFilterCalc(t_low_pass_filter *filtr, uint32_t data_in);

#endif /* LOWPASSFILTER_H_ */
