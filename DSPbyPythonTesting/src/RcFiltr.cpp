#include "RcFiltr.h"

void RcFiltrInit(t_RcFiltr *rcValue, float t_sec, uint32_t sps_hz, uint8_t fixPointPos)
{
	float tmp = t_sec * sps_hz;
	tmp = (1<<16)*(1/tmp);
	rcValue->K = (int32_t)tmp;
	rcValue->Dacc = 0;
	rcValue->Dout = 0;
	rcValue->fixPointPos = fixPointPos;
}

void RcFiltrCalc(t_RcFiltr *rcValue, uint32_t dataIn)
{
	rcValue->Dacc = rcValue->Dacc + dataIn - rcValue->Dout;
	rcValue->Dout = (rcValue->Dacc * rcValue->K)>>rcValue->fixPointPos;
}
