/*
 * Antidrebezg.h
 *
 *  Created on: 9 окт. 2020 г.
 *      Author: borzenkov
 */

#ifndef ANTIDREBEZG_H_
#define ANTIDREBEZG_H_

#include <stdint.h>

void AntidrebezgAllCntInit(uint8_t cntValue);
void AntidrebezgOneCntInit(uint8_t cntValue, uint8_t bitNumber);
void AntidrebezgMaskCntInit(uint8_t cntValue, uint32_t bitMask);
void Antidrebezg(uint32_t *pRegS, uint32_t *pRegKn);

#endif /* ANTIDREBEZG_H_ */
