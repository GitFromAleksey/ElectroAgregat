/*
 * MDRCANTypeDef.h
 *
 *  Created on: 13 янв. 2021 г.
 *      Author: borzenkov
 */

#ifndef MDR32FX_MDRCANTYPEDEF_H_
#define MDR32FX_MDRCANTYPEDEF_H_

#include <iostream>
#include "../cMyUint32t.h"

using namespace std;

class MDR_CAN_TypeDef
{
	public:

	string Name;

		cMyUint32_t CONTROL;
		cMyUint32_t STATUS;
		cMyUint32_t BITTMNG;
		cMyUint32_t RESERVED0;
		cMyUint32_t INT_EN;
		cMyUint32_t RESERVED1[2];
		cMyUint32_t OVER;
		cMyUint32_t RXID;
		cMyUint32_t RXDLC;
		cMyUint32_t RXDATAL;
		cMyUint32_t RXDATAH;
		cMyUint32_t TXID;
		cMyUint32_t TXDLC;
		cMyUint32_t DATAL;
		cMyUint32_t DATAH;
		cMyUint32_t BUF_CON[32];
		cMyUint32_t INT_RX;
		cMyUint32_t RX;
		cMyUint32_t INT_TX;
		cMyUint32_t TX;
		cMyUint32_t RESERVED2[76];
//		MDR_CAN_BUF_TypeDef CAN_BUF[32]; // TODO реализовать класс MDR_CAN_BUF_TypeDef
		cMyUint32_t RESERVED3[64];
//		MDR_CAN_BUF_FILTER_TypeDef CAN_BUF_FILTER[32]; // TODO реализовать класс MDR_CAN_BUF_FILTER_TypeDef


		MDR_CAN_TypeDef();
		MDR_CAN_TypeDef(string& name);
		virtual ~MDR_CAN_TypeDef();

		void Init(string name);
};

#endif /* MDR32FX_MDRCANTYPEDEF_H_ */
