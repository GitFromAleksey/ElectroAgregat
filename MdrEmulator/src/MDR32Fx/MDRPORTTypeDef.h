/*
 * MDRPORTTypeDef.h
 *
 *  Created on: 25 но€б. 2020 г.
 *      Author: borzenkov
 */

#ifndef MDR32FX_MDRPORTTYPEDEF_H_
#define MDR32FX_MDRPORTTYPEDEF_H_

#include <iostream>
#include "../cMyUint32t.h"

using namespace std;

class MDR_PORT_TypeDef
{
	public:
		string Name;

		cMyUint32_t  RXTX;
		cMyUint32_t  OE;
		cMyUint32_t  FUNC;
		cMyUint32_t  ANALOG;
		cMyUint32_t  PULL;
		cMyUint32_t  PD;
		cMyUint32_t  PWR;
		cMyUint32_t  GFEN;

		MDR_PORT_TypeDef();
		MDR_PORT_TypeDef(string& name);
		virtual ~MDR_PORT_TypeDef();

		void Init(string name);

};

#endif /* MDR32FX_MDRPORTTYPEDEF_H_ */
