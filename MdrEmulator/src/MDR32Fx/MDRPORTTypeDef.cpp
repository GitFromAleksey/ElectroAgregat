/*
 * MDRPORTTypeDef.cpp
 *
 *  Created on: 25 но€б. 2020 г.
 *      Author: borzenkov
 */

#include "MDRPORTTypeDef.h"

MDR_PORT_TypeDef::MDR_PORT_TypeDef():
Name("")
{
	Init("");
}

MDR_PORT_TypeDef::MDR_PORT_TypeDef(string& name)
{
	Init(name);
	//	 RXTX.Init("MDR_PORT->RXTX",0);
//	 OE.Init("MDR_PORT->OE",0);
//	 FUNC.Init("MDR_PORT->FUNC",0);
//	 ANALOG.Init("MDR_PORT->ANALOG",0);
//	 PULL.Init("MDR_PORT->PULL",0);
//	 PD.Init("MDR_PORT->PD",0);
//	 PWR.Init("MDR_PORT->PWR",0);
//	 GFEN.Init("MDR_PORT->GFEN",0);
}

MDR_PORT_TypeDef::~MDR_PORT_TypeDef() {
	// TODO Auto-generated destructor stub
}

void MDR_PORT_TypeDef::Init(string name)
{
	this->Name = name;

	RXTX.Init("MDR_PORT" + name + "->RXTX",0);
	OE.Init("MDR_PORT" + name + "->OE",0);
	FUNC.Init("MDR_PORT" + name + "->FUNC",0);
	ANALOG.Init("MDR_PORT" + name + "->ANALOG",0);
	PULL.Init("MDR_PORT" + name + "->PULL",0);
	PD.Init("MDR_PORT" + name + "->PD",0);
	PWR.Init("MDR_PORT" + name + "->PWR",0);
	GFEN.Init("MDR_PORT" + name + "->GFEN",0);
}
