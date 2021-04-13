#include "Antidrebezg.h"

#define REGS_SIZE	(sizeof(uint32_t) * 8)
uint8_t antidrebezgCnt[REGS_SIZE] = {0};
uint8_t atidrebezgCntVal[REGS_SIZE] = {0};

// инициализирует максимальные значения всех счётчиков массива atidrebezgCntVal[]
void AntidrebezgAllCntInit(uint8_t cntValue)
{
	uint8_t i;
	for(i = 0; i < REGS_SIZE; ++i)
		atidrebezgCntVal[i] = cntValue;
}

// инициализирует счётчик только для одного бита
void AntidrebezgOneCntInit(uint8_t cntValue, uint8_t bitNumber)
{
	if(bitNumber >= REGS_SIZE)
		return;
	atidrebezgCntVal[bitNumber] = cntValue;
}

// инициализирует одним значением отдельные счётчики по бит маске
void AntidrebezgMaskCntInit(uint8_t cntValue, uint32_t bitMask)
{
	uint8_t i;
	for(i = 0; i < REGS_SIZE; ++i)
	{
		if((bitMask & (1<<i)) == (uint32_t)(1<<i))
		{
			atidrebezgCntVal[i] = cntValue;
		}
	}
}

// обработчик антидребезга. Должен вызываться в ReadKn()
void Antidrebezg(uint32_t *pRegS, uint32_t *pRegKn)
{
	uint8_t bitCnt = 0;
	uint32_t regS = *pRegS;
	uint32_t regKn = *pRegKn;

	for(bitCnt = 0; bitCnt < REGS_SIZE; ++bitCnt)
	{
		// выставлен бит?
		if( (regKn & (1<<bitCnt)) != (regS & (1<<bitCnt)) )
		{
			// считаем счетчик для бита
			if(antidrebezgCnt[bitCnt] == atidrebezgCntVal[bitCnt])
			{
				// если досчитали до нуля, то ставим бит
				if( (regKn & (1<<bitCnt)) == (uint32_t)(1<<bitCnt) )
					regS |= (1<<bitCnt);
				else
					regS &= ~(1<<bitCnt);
				antidrebezgCnt[bitCnt] = 0;
			}
			else
			{
				++antidrebezgCnt[bitCnt];
			}
		}
	}
	*pRegS = regS;
}
