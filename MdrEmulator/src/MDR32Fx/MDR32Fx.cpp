/*
 * MDR32Fx.c
 *
 *  Created on: 12 окт. 2020 г.
 *      Author: borzenkov
 */
#include <iostream>
#include "MDR32Fx.h"

using namespace std;

MDR_RST_CLK_TypeDef *MdrRstSlk;

MDR_PORT_TypeDef *MdrPortA;
MDR_PORT_TypeDef *MdrPortB;
MDR_PORT_TypeDef *MdrPortC;
MDR_PORT_TypeDef *MdrPortD;
MDR_PORT_TypeDef *MdrPortE;
MDR_PORT_TypeDef *MdrPortF;

MDR_TIMER_TypeDef *MdrPortTimer1;
MDR_TIMER_TypeDef *MdrPortTimer2;
MDR_TIMER_TypeDef *MdrPortTimer3;

MDR_CAN_TypeDef *MdrCan1;
MDR_CAN_TypeDef *MdrCan2;

void MDR_INIT()
{
	string str = "";

	MdrRstSlk = new MDR_RST_CLK_TypeDef();

	str = "A";
	MdrPortA = new MDR_PORT_TypeDef(str);
	str = "B";
	MdrPortB = new MDR_PORT_TypeDef(str);
	str = "C";
	MdrPortC = new MDR_PORT_TypeDef(str);
	str = "D";
	MdrPortD = new MDR_PORT_TypeDef(str);
	str = "E";
	MdrPortE = new MDR_PORT_TypeDef(str);
	str = "F";
	MdrPortF = new MDR_PORT_TypeDef(str);

	str = "1";
	MdrPortTimer1 = new MDR_TIMER_TypeDef(str);
	str = "2";
	MdrPortTimer2 = new MDR_TIMER_TypeDef(str);
	str = "3";
	MdrPortTimer3 = new MDR_TIMER_TypeDef(str);

	str = "1";
	MdrCan1 = new MDR_CAN_TypeDef(str);
	str = "2";
	MdrCan2 = new MDR_CAN_TypeDef(str);
}
