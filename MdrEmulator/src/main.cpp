//============================================================================
// Name        : MdrEmulator.cpp
// Author      : Aleksey
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "MDR32Fx/MDR32Fx.h"
using namespace std;

// ----------------------------------------------------------------------------
void InitPORTA(void)
{
	MDR_PORTA->OE=0x10;

	MDR_PORTA->FUNC =0;

	MDR_PORTA->ANALOG =0xff; //PA-digital
	MDR_PORTA->PULL=0xff0000; //PA-R+=on
	MDR_PORTA->PWR=0x5555;
	MDR_PORTA->PD=0xef;////Trigger Shmitta=on
}
// ----------------------------------------------------------------------------
void InitPORTB(void)
{
	MDR_RST_CLK->PER_CLOCK |= 0x400000; // PORTB
	MDR_PORTB->ANALOG = 0x7F8; // 0x7ff; // 0111 1111 1111
	MDR_PORTB->OE = 0x7e0; // 0111 1110 0000
	MDR_PORTB->PULL = 0;
	MDR_PORTB->FUNC = 0; //capture TMR3_CH4 PB7,PB2,PB3-Can1
	MDR_PORTB->PWR = 0x55555555;
	MDR_PORTB->PD = 0;//Trigger Shmitta=on
}
// ----------------------------------------------------------------------------
void InitPORTC(void)
{
	MDR_RST_CLK->PER_CLOCK |= 0x800000;
	MDR_PORTC->RXTX = 0x1;
	MDR_PORTC->OE = 0x1;
	MDR_PORTC->FUNC = 0;
	MDR_PORTC->ANALOG = 0xff; // PC0-digital
	MDR_PORTC->PULL = 0x50002; // PC0-R+=on
	MDR_PORTC->PWR = 0x5555;
	MDR_PORTC->PD = 0; // Trigger Shmitta=on
}
// ----------------------------------------------------------------------------
void InitPORTD(void)
{
	MDR_PORTD->ANALOG=0xe3; //analog
	MDR_PORTD->PULL=0x630000;//R +=on
	MDR_PORTD->PWR=0x5555; //
	MDR_PORTD->OE =0x80; //PD7=out
	MDR_PORTD->FUNC =0;
	MDR_PORTD->PD=0;//Trigger Shmitta=on
}
// ----------------------------------------------------------------------------
void InitPORTE(void)
{
	MDR_RST_CLK->PER_CLOCK |=0x2000000; //PORTE

	MDR_PORTE->OE=0xcc;
	//  PORTE->FUNC=0x2f;//TIM2_CH3,TIM2_CH1
	MDR_PORTE->ANALOG =0xff; //PE-digital
	MDR_PORTE->PULL=0xcc; //PE-R-=on
	MDR_PORTE->PD=3;//Open stok
	MDR_PORTE->PWR=0x5555;//slow front
}
// ----------------------------------------------------------------------------
void InitPORTF(void)
{
	MDR_PORTF->OE=0xfe;//f; //PF0,PF1=out
	MDR_PORTF->FUNC=0;//xA;//PF0,PF1=SSP,PF2,PF3=CAN1
	MDR_PORTF->ANALOG |=0xff; //PF-digital
	MDR_PORTF->PULL=0; //PF2,PF3-R-=on
	MDR_PORTF->PWR=0x5555; //Slow front
	MDR_PORTF->PD=0; //driver
}
// ----------------------------------------------------------------------------
void InitTimer1(void)
{
	MDR_RST_CLK->PER_CLOCK |=0x4000; //Timer1
	MDR_TIMER1->CNTRL = 0;
	MDR_TIMER1->CNT = 0x00000007; //CT
	MDR_TIMER1->ARR =0xffff;//CT from 0 to ARR
	MDR_TIMER1->PSG =0x1;//FTim2=clk/2
	MDR_TIMER1->CNTRL = 0x1;//Enable Timer1

	MDR_TIMER1->IE = 0x2;//CNT=ARR,CH1  prov

//	NVIC->ISER[0] |= 0x4000; // Timer1 Reset irq
}
// ----------------------------------------------------------------------------
void InitTimer2(void)
{
	MDR_RST_CLK->PER_CLOCK |= 0x8000; //Timer2

	MDR_TIMER2->CNTRL = 0;
	MDR_TIMER2->CNT = 0x00000007; // CT
	MDR_TIMER2->ARR = 0xffff; // CT from 0 to ARR
	MDR_TIMER2->PSG = 0xf; // FTim2 = clk / 2
	MDR_TIMER2->CNTRL = 0x1; // Enable Timer2

	MDR_TIMER2->IE = 0x2; // CNT = ARR
//	NVIC->ISER[0] |= 0x8000; // SYS->ISER00 |= 0x8000; // Timer2
}
// ----------------------------------------------------------------------------
void InitTimer3(void)
{
	MDR_RST_CLK->PER_CLOCK |= 0x8000; //Timer2

	MDR_TIMER3->CNTRL = 0;
	MDR_TIMER3->CNT = 0x00000007; // CT
	MDR_TIMER3->ARR = 0xffff; // CT from 0 to ARR
	MDR_TIMER3->PSG = 0xf; // FTim2 = clk / 2
	MDR_TIMER3->CNTRL = 0x1; // Enable Timer2

	MDR_TIMER3->IE = 0x2; // CNT = ARR
//	NVIC->ISER[0] |= 0x8000; // SYS->ISER00 |= 0x8000; // Timer2
}
// ----------------------------------------------------------------------------
void InitCAN1(void)
{
	MDR_RST_CLK->PER_CLOCK |=1;
	MDR_RST_CLK->CAN_CLOCK =0x1000003; //enable F
	// CAN->CAN1_BITTMNG=0;
	// MDR_CAN1->CAN1_BITTMNG=0;
	MDR_CAN1->BITTMNG=0;
	MDR_CAN1->CONTROL=0;
	MDR_CAN1->INT_EN=0x3;
	MDR_CAN1->INT_RX=0xf0;
	MDR_CAN1->INT_TX=0;

	MDR_CAN1->BUF_CON[0]=0x5;
	MDR_CAN1->BUF_CON[1]=0x5;
	MDR_CAN1->BUF_CON[2]=0x5;
	MDR_CAN1->BUF_CON[3]=0x5;//transmit

	MDR_CAN1->BUF_CON[4]=0x3;//7;
	MDR_CAN1->BUF_CON[5] =0x3;
	MDR_CAN1->BUF_CON[6]=0x3;
	MDR_CAN1->BUF_CON[7] =0x3;//receive

// TODO реализовать CAN_BUF_FILTER и потом раскомментировать
//	MDR_CAN1->CAN_BUF_FILTER[4].MASK =0;//0x800000;
//	MDR_CAN1->CAN_BUF_FILTER[5].MASK =0;//0x400000;
//	MDR_CAN1->CAN_BUF_FILTER[6].MASK =0;//0x800000;
//	MDR_CAN1->CAN_BUF_FILTER[7].MASK =0;//0x400000;
//
//
//	MDR_CAN1->CAN_BUF_FILTER[4].FILTER =0;//0x800000;
//	MDR_CAN1->CAN_BUF_FILTER[5].FILTER =0;//0x400000;
//	MDR_CAN1->CAN_BUF_FILTER[6].FILTER =0;//0x800000;
//	MDR_CAN1->CAN_BUF_FILTER[7].FILTER =0;//0x400000;
//
//	MDR_CAN1->CAN_BUF[4].ID =0x800000;
//	MDR_CAN1->CAN_BUF[5].ID =0x400000;
//	MDR_CAN1->CAN_BUF[6].ID =0x800000;
//	MDR_CAN1->CAN_BUF[7].ID =0x400000;
//
//	MDR_CAN1->CAN_BUF[0].DLC =0x8;//8 byte
//	MDR_CAN1->CAN_BUF[1].DLC =0x8;
//	MDR_CAN1->CAN_BUF[2].DLC =0x8;
//	MDR_CAN1->CAN_BUF[3].DLC =0x8;//8 byte
//	MDR_CAN1->CAN_BUF[4].DLC =0x8;
//	MDR_CAN1->CAN_BUF[5].DLC =0x8;
//	MDR_CAN1->CAN_BUF[6].DLC =0x8;
//	MDR_CAN1->CAN_BUF[7].DLC =0x8;
	MDR_CAN1->CONTROL =0x1;//0x1b;//0x19;
}
// ----------------------------------------------------------------------------

int main()
{
	cout << "\n!!! MDR Emulator start !!!\n" << endl; // prints !!!Hello World!!!

	MDR_INIT();

	MDR_RST_CLK->PER_CLOCK |= 0x10; // RST_CLK
	MDR_RST_CLK->HS_CONTROL = 0x1; // osc_E = on
	if(!(MDR_RST_CLK->CLOCK_STATUS & 4))
		MDR_RST_CLK->CPU_CLOCK = 0x102; // CLOCK_CPU = osc_E

	InitPORTA();
	InitPORTB();
	InitPORTC();
	InitPORTD();
	InitPORTE();
	InitPORTF();

	InitTimer1();
	InitTimer2();
	InitTimer3();

	InitCAN1();

	return 0;
}
