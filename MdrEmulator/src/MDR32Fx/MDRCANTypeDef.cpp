/*
 * MDRCANTypeDef.cpp
 *
 *  Created on: 13 янв. 2021 г.
 *      Author: borzenkov
 */

#include "MDRCANTypeDef.h"

MDR_CAN_TypeDef::MDR_CAN_TypeDef():
Name("")
{
	Init("");
}

MDR_CAN_TypeDef::MDR_CAN_TypeDef(string& name)
{
	Init(name);
}

MDR_CAN_TypeDef::~MDR_CAN_TypeDef()
{

}

void MDR_CAN_TypeDef::Init(string name)
{
	this->Name = name;

	CONTROL.Init("MDR_CAN" + name + "->CONTROL",0);
	STATUS.Init("MDR_CAN" + name + "->STATUS",0);
	BITTMNG.Init("MDR_CAN" + name + "->BITTMNG",0);
	RESERVED0.Init("MDR_CAN" + name + "->RESERVED0",0);
	INT_EN.Init("MDR_CAN" + name + "->INT_EN",0);
	RESERVED1[2].Init("MDR_CAN" + name + "->RESERVED1",0);
	OVER.Init("MDR_CAN" + name + "->OVER",0);
	RXID.Init("MDR_CAN" + name + "->RXID",0);
	RXDLC.Init("MDR_CAN" + name + "->RXDLC",0);
	RXDATAL.Init("MDR_CAN" + name + "->RXDATAL",0);
	RXDATAH.Init("MDR_CAN" + name + "->RXDATAH",0);
	TXID.Init("MDR_CAN" + name + "->TXID",0);
	TXDLC.Init("MDR_CAN" + name + "->TXDLC",0);
	DATAL.Init("MDR_CAN" + name + "->DATAL",0);
	DATAH.Init("MDR_CAN" + name + "->DATAH",0);
	for(int i = 0; i < 32; i++)
		BUF_CON[i].Init("MDR_CAN" + name + "->BUF_CON[" + std::to_string(i) + "]",0); // TODO нужно инициализировать массив
	INT_RX.Init("MDR_CAN" + name + "->INT_RX",0);
	RX.Init("MDR_CAN" + name + "->RX",0);
	INT_TX.Init("MDR_CAN" + name + "->INT_TX",0);
	TX.Init("MDR_CAN" + name + "->TX",0);
	for(int i = 0; i < 76; i++)
		RESERVED2[i].Init("MDR_CAN" + name + "->RESERVED2[" + std::to_string(i) +  "]",0);
	//		MDR_CAN_BUF_TypeDef CAN_BUF[32]; // TODO реализовать класс MDR_CAN_BUF_TypeDef
	for(int i = 0; i < 64; i++)
		RESERVED3[i].Init("MDR_CAN" + name + "->RESERVED3[" + std::to_string(i) +  "]",0);
//		MDR_CAN_BUF_FILTER_TypeDef CAN_BUF_FILTER[32]; // TODO реализовать класс MDR_CAN_BUF_FILTER_TypeDef
}
