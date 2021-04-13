#ifndef RCFILTR_H
#define RCFILTR_H

#include "stdint.h"

#define FILTR_FIX_POINT_POS		(uint8_t)16
#define FILTR_SPS							(uint32_t)(30) // кол-во измерений в сек
#define FILTR_T_SEC						0.1f

typedef struct
{
	int32_t K;						// коэффициент фильтра
	int32_t Dacc;					// аккумулятор данных
	int32_t Dout;					// значение после фильтрации
	uint8_t fixPointPos;	// положение фиксированной точки
} t_RcFiltr;

void RcFiltrInit(t_RcFiltr *rcValue, float t_sec, uint32_t sps_hz, uint8_t fixPointPos);
void RcFiltrCalc(t_RcFiltr *rcValue, uint32_t dataIn);

#endif /* RCFILTR_H */
