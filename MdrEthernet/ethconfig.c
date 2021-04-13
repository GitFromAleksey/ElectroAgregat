
/*
Конфигурирование контроллера Ethernet и функции для обмена данными по параллельному интерфейсу.
*/
#include <string.h>
#include "MDR32Fx.h"
#include "ethconfig.h"
#include "stdbool.h"


/*
MAC адрес
3E-2C-49-74-9B-52*
F1-18-C8-98-D8-45
D9-9A-88-4B-43-78
54-69-B3-D9-B2-24
74-9A-89-2C-B4-03
87-F3-30-D1-67-CB
24-59-E4-ED-F1-BC
33-CA-57-BC-16-9A
34-6B-03-E7-44-B6
0C-B8-51-95-E5-05
99-6D-F8-C9-3F-60
94-64-B9-78-51-AB
*/

#define MAX_RX_BUFFER_WORDS_SIZE    100u // максимальный размер приемного буфера в словах
#define MAX_TX_BUFFER_WORDS_SIZE    100u // максимальный размер приемного буфера в словах

uint32_t EthRxBuffer[MAX_RX_BUFFER_WORDS_SIZE];
uint32_t EthTxBuffer[MAX_RX_BUFFER_WORDS_SIZE];

_tx_current_descriptor TxCurrentDesc;	//экземпляр структуры _tx_current_descriptor
_rx_current_descriptor RxCurrentDesc;	//экземпляр структуры _rx_current_descriptor


//массив дескрипторов отправляемых пакетов
_tx_descriptor ATxDescriptor[32] =  {{0x60006000,0x0000,0,0,0,0},{0x60006010,0x0000,0,0,0,0},{0x60006020,0x0000,0,0,0,0},{0x60006030,0x0000,0,0,0,0},
{0x60006040,0x0000,0,0,0,0},{0x60006050,0x0000,0,0,0,0},{0x60006060,0x0000,0,0,0,0},{0x60006070,0x0000,0,0,0,0},
{0x60006080,0x0000,0,0,0,0},{0x60006090,0x0000,0,0,0,0},{0x600060A0,0x0000,0,0,0,0},{0x600060B0,0x0000,0,0,0,0},
{0x600060C0,0x0000,0,0,0,0},{0x600060D0,0x0000,0,0,0,0},{0x600060E0,0x0000,0,0,0,0},{0x600060F0,0x0000,0,0,0,0},
{0x60006100,0x0000,0,0,0,0},{0x60006110,0x0000,0,0,0,0},{0x60006120,0x0000,0,0,0,0},{0x60006130,0x0000,0,0,0,0},
{0x60006140,0x0000,0,0,0,0},{0x60006150,0x0000,0,0,0,0},{0x60006160,0x0000,0,0,0,0},{0x60006170,0x0000,0,0,0,0},
{0x60006180,0x0000,0,0,0,0},{0x60006190,0x0000,0,0,0,0},{0x600061A0,0x0000,0,0,0,0},{0x600061B0,0x0000,0,0,0,0},
{0x600061C0,0x0000,0,0,0,0},{0x600061D0,0x0000,0,0,0,0},{0x600061E0,0x0000,0,0,0,0},{0x600061F0,0x4000,0,0,0,1}};

_rx_descriptor	ARxDescriptor[32] = {{0x60002000,0x8000,0,0,0,0},{0x60002010,0x8000,0,0,0,0},{0x60002020,0x8000,0,0,0,0},{0x60002030,0x8000,0,0,0,0},
{0x60002040,0x8000,0,0,0,0},{0x60002050,0x8000,0,0,0,0},{0x60002060,0x8000,0,0,0,0},{0x60002070,0x8000,0,0,0,0},
{0x60002080,0x8000,0,0,0,0},{0x60002090,0x8000,0,0,0,0},{0x600020A0,0x8000,0,0,0,0},{0x600020B0,0x8000,0,0,0,0},
{0x600020C0,0x8000,0,0,0,0},{0x600020D0,0x8000,0,0,0,0},{0x600020E0,0x8000,0,0,0,0},{0x600020F0,0x8000,0,0,0,0},
{0x60002100,0x8000,0,0,0,0},{0x60002110,0x8000,0,0,0,0},{0x60002120,0x8000,0,0,0,0},{0x60002130,0x8000,0,0,0,0},
{0x60002140,0x8000,0,0,0,0},{0x60002150,0x8000,0,0,0,0},{0x60002160,0x8000,0,0,0,0},{0x60002170,0x8000,0,0,0,0},
{0x60002180,0x8000,0,0,0,0},{0x60002190,0x8000,0,0,0,0},{0x600021A0,0x8000,0,0,0,0},{0x600021B0,0x8000,0,0,0,0},
{0x600021C0,0x8000,0,0,0,0},{0x600021D0,0x8000,0,0,0,0},{0x600021E0,0x8000,0,0,0,0},{0x600021F0,0xC000,0,0,0,1}};

void ClkCfg(void);
bool EthernetReadIncomingPacket(uint32_t **pData, uint16_t *pLength);
void ExtBusCfg(void);
uint32_t *FindFirstTXEmptyWord(void);
void InitRxDescriptor(void);
void InitTxDescriptor(void);
void PortConfig(void);
unsigned short Read_Packet_Length(_rx_descriptor* RxDesc);
unsigned short Read_Packet_Start_Address(_rx_descriptor* RxDesc);
unsigned short Read_Rx_Descriptor(_rx_descriptor* RxDesc);
unsigned short Read_Tx_Descriptor(_tx_descriptor* TxDesc);
int Ready_Rx_Descriptor(_rx_descriptor* RxDesc);
void SendPacket(uint32_t *pData, uint16_t *pLength);
void SetNextTxDesc(unsigned short PacketLen);
int Write_Tx_Descriptor(unsigned short PacketLen, _tx_current_descriptor* TxCurrentDesc);

void EthCfg(t_Eth_init *pEthInit);
// вызывается из основного потока
void EthernetRun(void);

// указатель на обработчик OSI стека протоколов. Вызывается из EthernetRun()
bool (*OSI_Handler)(uint32_t *_pTxData, uint16_t *_TxLenBytes, uint32_t *_pRxData, uint16_t lenBytes);
void (*OSI_GetBroadcast)(uint32_t *_pTxData, uint16_t *_TxLenBytes);
	
//--------------------------------------------------------------------------------------
//Функция для настройки внешней системной шины
//Параметр:	нет
//Возвращаемых знаений нет
//--------------------------------------------------------------------------------------
void ExtBusCfg(void)
{
//	EXT_BUS_CNTRL->EXT_BUS_CONTROL = 0x2002;  //wait state=0 (3 HCLK), RAM mode
}

//--------------------------------------------------------------------------------------
//Функция для настройки портов контроллера 1986ВЕ91Т1
//Параметр:	нет
//Возвращаемых знаений нет
//-------------------------------------------------------------------------------------- 
void PortConfig(void)
{
//Data Bus[0:15]
// 		MDR_PORTA->ANALOG = 0xFFFF;
// 		MDR_PORTA->PWR = 0xAAAAAAAA;
// 		MDR_PORTA->FUNC = 0x55555555;

// //OE-WE & Buttons
// 		MDR_PORTC->ANALOG = 0xFFFF; // OE-WE
// 		MDR_PORTC->PWR = 0xAAAAAAAA; // OE-WE
// 		MDR_PORTC->FUNC = 0x00000014; // OE-WE
// //		PORTC->PD   = 0x00000000; // OE-WE//Светодиоды
// //		PORTC->RXTX = 0x0000;
// //		PORTC->OE = 0x0080;
// //LED

//         PORTD->RXTX = 0;
//         PORTD->OE = 0x7C00; //PORTD10 - PORTD14 - outputs
//         PORTD->FUNC = 0x00000000; //PORTD - ports
//         PORTD->ANALOG = 0xFF00; //PORTD - digital
//         PORTD->PWR = 0xAAAA0000; //PORTD8 - PORTD15 - fast edge

// //Address Bus[0:12]
// 		PORTE->ANALOG = 0xFFFF; // CS
// 		PORTE->PWR = 0xAAAAAAAA; // CS
// 		PORTE->RXTX = 0x0000;
// 		PORTE->OE = 0x0030;
// 		PORTE->FUNC = 0x01000000; // CS

// 		PORTF->ANALOG = 0xFFFF;
// 		PORTF->PWR = 0xFFFFFFFF;
// 		PORTF->FUNC = 0x55555555;

// 		PORTB->RXTX = 0;
//         PORTB->OE = 0x8000; //PORTD10 - PORTD14 - outputs
//         PORTB->FUNC = 0x00000000; //PORTD - ports
//         PORTB->ANALOG = 0xC000; //PORTD - digital
//         PORTB->PWR = 0xC0000000; //PORTD8 - PORTD15 - fast edge
}

//--------------------------------------------------------------------------------------
//Функция для настройки тактовых сигналов контроллера 1986ВЕ91Т1
//Параметр:	нет
//Возвращаемых знаений нет
//-------------------------------------------------------------------------------------- 
void ClkCfg(void)
{
//         RST_CLK -> HS_CONTROL = 0x00000001;
// 	
//         while((RST_CLK -> CLOCK_STATUS & 0x00000004) != 0x00000004)
// 			{}
// 			
// 		RST_CLK -> CPU_CLOCK = 0x00000102;
// 		//RST_CLK->PER_CLOCK = 0x63E00018;
// 		RST_CLK -> PER_CLOCK = 0xffffffff;
}
//--------------------------------------------------------------------------------------
//Функция для инициализации Ethernet-контроллера 5600ВГ1У
//Параметр:	нет
//Возвращаемых значений нет
//--------------------------------------------------------------------------------------
void EthCfg(t_Eth_init *pEthInit)
{
	int i;
	
	u_mac_ctrl macCtrl;

	OSI_Handler = pEthInit->OSI_Handler;
	OSI_GetBroadcast = pEthInit->OSI_GetBroadcast;
	
	macCtrl.MAC_CTRL = 0;
	macCtrl.sMAC_CTRL.BCA_EN = 1;
	macCtrl.sMAC_CTRL.BIG_ENDIAN = 1;

	InitTxDescriptor();	
	InitRxDescriptor();
	
	Ethernet->GCTRL = 0x8000;	// Reset 5600VG1U

	for(i=0;i<1000;i++){}		  // Little delay

	Ethernet->GCTRL = 0x4382;
	Ethernet->MinFrame = 0x0040;
	Ethernet->CollConfig = 0;
	Ethernet->IPGTx = 0x000A;

	Ethernet->MAC_ADDR_H = pEthInit->MAC_Address[2];
	Ethernet->MAC_ADDR_M = pEthInit->MAC_Address[1];
	Ethernet->MAC_ADDR_T = pEthInit->MAC_Address[0];

	Ethernet->PHY_CTRL = 0x31D0;
	Ethernet->MAC_CTRL = macCtrl.MAC_CTRL;// 0x0200;  //Receive broadcast packet and packet with my MAC-address, littel endian ON
}
//--------------------------------------------------------------------------------------
//Функция для подготовки дескрипторов передатчика к отправке пакетов
//Параметр:	PacketLen - размер пакета в байтах,
//			TxCurrentDesc - указатель на текущий дескриптор отправляемых пакетов
//Возвращаемых значений нет
//--------------------------------------------------------------------------------------
int Write_Tx_Descriptor(unsigned short PacketLen, _tx_current_descriptor* TxCurrentDesc)
{
	unsigned int* MyDesc;

	MyDesc = (unsigned int*)(TxCurrentDesc->TxCurrentDescriptor->StartAddress);

	*(MyDesc+1) = PacketLen;
	*(MyDesc+3) = (TxCurrentDesc->FirstEmptyWord>>2)&0x0000FFFF;

	if(TxCurrentDesc->TxCurrentDescriptor->LastDesc == 1) 
		*MyDesc = 0xC000;
	else 
		*MyDesc = 0x8000;

	TxCurrentDesc->FirstEmptyWord += (PacketLen/2)<<2;	//адрес первого свободного 16-разрядного слова в буфере
												//сдвг PacketLen на 1 разряд, так как в передаваемом пакете
												//необходимо указывать размер в байтах, а в буфере - 16-разрядные слова!
	if(TxCurrentDesc->FirstEmptyWord > 0x60005FFC)
	{
		TxCurrentDesc->FirstEmptyWord -= 0x00006000;
		TxCurrentDesc->FirstEmptyWord |= 0x60004000;
	}

	return 0;
}

//--------------------------------------------------------------------------------------
//Функция для определения статуса отправляемого пакета
//Параметр:	TxDesc - указатель на дескриптор отправляемых пакетов
//Возвращает:	1 - пакет не отправлен
//				0 - пакет отправлен 
//--------------------------------------------------------------------------------------
unsigned short Read_Tx_Descriptor(_tx_descriptor* TxDesc)
{
	unsigned int* MyDesc;

	MyDesc = (unsigned int*)(TxDesc->StartAddress);

	if((*MyDesc & 0x8000) == 0x8000) 
		return 1;            //пакет не отправлен
	else 
		return 0;                                              //пакет отправлен
}
//--------------------------------------------------------------------------------------
//Функция для установки признака готовности к приему пакета дескриптором принимаемых пакетв
//Параметр:	RxDesc - указатель на дескриптор принимаемых пакетов
//Возвращает:	0
//--------------------------------------------------------------------------------------
int Ready_Rx_Descriptor(_rx_descriptor* RxDesc)
{
	unsigned int* MyDesc;

	MyDesc = (unsigned int*)(RxDesc->StartAddress);

	if(RxDesc->LastDesc == 1) 
		*MyDesc = 0xC000;	//установка готовности дескриптора к приему пакета
	else 
		*MyDesc = 0x8000;						//установка готовности дескриптора к приему пакета

	return 0;
}

//--------------------------------------------------------------------------------------
//Функция для определения наличия принятого пакета
//Параметр:	RxDesc - указатель на дескриптор принимаемых пакетов
//Возвращает:	1 - пакет не принят
//				0 - пакет принят
//--------------------------------------------------------------------------------------
unsigned short Read_Rx_Descriptor(_rx_descriptor* RxDesc)
{
	unsigned int* RDescPointer;

	RDescPointer = (unsigned int*)RxDesc->StartAddress;

	if( (*RDescPointer & 0x8000) == 0x8000) 
		return 1;	
	else
		return 0;
}
//--------------------------------------------------------------------------------------
//Функция для получения размера приянтого пакета
//Параметр:	RxDesc - указатель на дескриптор принимаемых пакетов
//Возвращает:	размер пакета в байтах
//--------------------------------------------------------------------------------------
unsigned short Read_Packet_Length(_rx_descriptor* RxDesc)
{
		unsigned int* RDescPointer;
		RDescPointer = (unsigned int*)(RxDesc->StartAddress + 4);		//получим адрес длины пакета
        return (unsigned short)(*RDescPointer);       //Temp;
}
//--------------------------------------------------------------------------------------
//Функция для получения адреса, по которому расположен пакета в буфере приемника
//Параметр:	RxDesc - указатель на дескриптор принимаемых пакетов
//Возвращает:	адрес пакета в буфере
//--------------------------------------------------------------------------------------
unsigned short Read_Packet_Start_Address(_rx_descriptor* RxDesc)
{
	unsigned int* RDescPointer;
	RDescPointer = (unsigned int*)(RxDesc->StartAddress + 12);	//получим адрес стартового адреса пакета
		return (unsigned short)(*RDescPointer);
}
//--------------------------------------------------------------------------------------
//Функция для инициализации дескрипторов передаваемых пакетов
////Параметр:	нет
////Возвращаемых значений нет
//--------------------------------------------------------------------------------------
void InitTxDescriptor(void)
{
	uint16_t Temp;
	unsigned int* TDescPointer;

	TxCurrentDesc.TxCurrentDescriptor = ATxDescriptor;
	TxCurrentDesc.FirstEmptyWord = 0x60004000;

	for(Temp=0;Temp<NUMTXDESCRIPTOR;Temp++)
	{
		TDescPointer = (unsigned int*)(TxCurrentDesc.TxCurrentDescriptor->StartAddress);
		*TDescPointer = TxCurrentDesc.TxCurrentDescriptor->Status;
		TxCurrentDesc.TxCurrentDescriptor++;
	}

	TxCurrentDesc.TxCurrentDescriptor--;
	TxCurrentDesc.TxCurrentDescriptor->LastDesc = 1;	//????????? ???????? ?????????? ???????????
	TDescPointer = (unsigned int*)(TxCurrentDesc.TxCurrentDescriptor->StartAddress);
	*TDescPointer = 0x4000;								//????????? ?????????????? ??????????

	TxCurrentDesc.Number = 0;
	TxCurrentDesc.TxCurrentDescriptor = ATxDescriptor;
}
//--------------------------------------------------------------------------------------
//Функция для инициализации дескрипторов принимаемых пакетов
//Параметр:	нет
//Возвращаемых значений нет
//--------------------------------------------------------------------------------------
void InitRxDescriptor(void)
{
	uint16_t Temp;
	unsigned int* RDescPointer;

	RxCurrentDesc.RxCurrentDescriptor = ARxDescriptor;

	for(Temp=0;Temp<NUMRXDESCRIPTOR;Temp++)
	{
		RDescPointer = (unsigned int*)(RxCurrentDesc.RxCurrentDescriptor->StartAddress);
		*RDescPointer = RxCurrentDesc.RxCurrentDescriptor->Status;
		RxCurrentDesc.RxCurrentDescriptor++;
	}

	RxCurrentDesc.RxCurrentDescriptor--;
	RxCurrentDesc.RxCurrentDescriptor->LastDesc = 1;	//установка признака последнего дескриптора
	RDescPointer = (unsigned int*)(RxCurrentDesc.RxCurrentDescriptor->StartAddress);
	*RDescPointer = 0xC000;								//последний обрабатываемый дескриптор

	RxCurrentDesc.Number = 0;
	RxCurrentDesc.RxCurrentDescriptor = ARxDescriptor;
}
//--------------------------------------------------------------------------------------
uint32_t *FindFirstTXEmptyWord(void)
{
	while(Read_Tx_Descriptor(TxCurrentDesc.TxCurrentDescriptor) != 0)
	{
		TxCurrentDesc.TxCurrentDescriptor++;
		TxCurrentDesc.Number++;
		if(TxCurrentDesc.Number == NUMTXDESCRIPTOR)
		{
			TxCurrentDesc.Number = 0;
			TxCurrentDesc.TxCurrentDescriptor = ATxDescriptor;
		}	
	}

	return (uint32_t*)TxCurrentDesc.FirstEmptyWord;
}
//--------------------------------------------------------------------------------------
void SetNextTxDesc(unsigned short PacketLen)
{
	//Write_Tx_Descriptor((sizeof(t_ETH_Packet_hdr) + sizeof(t_arp_packet) - 4)/2, &TxCurrentDesc);     // packet len 42 bytes
	Write_Tx_Descriptor(PacketLen, &TxCurrentDesc);     // packet len 42 bytes
	
	TxCurrentDesc.TxCurrentDescriptor++;
	TxCurrentDesc.Number++;
	if(TxCurrentDesc.Number == NUMTXDESCRIPTOR)
	{
		TxCurrentDesc.Number = 0;
		TxCurrentDesc.TxCurrentDescriptor = ATxDescriptor;
	}
}
//--------------------------------------------------------------------------------------
bool EthernetReadIncomingPacket(uint32_t **pData, uint16_t *pLength)
{
	bool res = false;
	uint16_t	Address;

	if(Read_Rx_Descriptor(RxCurrentDesc.RxCurrentDescriptor) == 0)
	{
		*pLength = Read_Packet_Length(RxCurrentDesc.RxCurrentDescriptor);
		Address = Read_Packet_Start_Address(RxCurrentDesc.RxCurrentDescriptor);

		*pData = (uint32_t*)((uint32_t)RxBuffer + ((uint32_t)Address<<2));
		
		res = true;
	}
	else
	{
		pData = 0;
		*pLength = 0;
		res = false;
	}
	return res;
}
//--------------------------------------------------------------------------------------
void SendPacket(uint32_t *pData, uint16_t *pLength)
{
	
}
//--------------------------------------------------------------------------------------
// TODO доработать эту функцию, чтобы она читала из циклического буфера микросхемы
void RxBufferFill(uint32_t* pRxData, uint16_t RxLength)
{
	uint32_t *pEthRxBuffer = &EthRxBuffer[0];

	if(RxLength > MAX_RX_BUFFER_WORDS_SIZE)
		RxLength = MAX_RX_BUFFER_WORDS_SIZE;
	
	while(RxLength-- > 0)
	{
		*pEthRxBuffer++ = *pRxData++;
//		if(pRxData > 0x600021F0)
//			pRxData = 0x60002000;
	}
}
//--------------------------------------------------------------------------------------
void EthernetRun(void)
{
	uint16_t RxLength;          //Размер принятого пакета
	uint32_t* pRxData;
	uint16_t TxLength;
	uint32_t* pTxData;
	
	if(EthernetReadIncomingPacket(&pRxData, &RxLength))
	{
		RxBufferFill(pRxData, RxLength);
		pTxData = (uint32_t *)FindFirstTXEmptyWord();
		// TODO здесь на обработку отправляется указатедь pTxData в микросхеме 5600ВГ1 и это неправильно
		// потому что это указатель на цилклический буфер и может теряться часть данных при максимальных
		// значениях индекса буфера. Нужно сделать промежуточных буфер, копировать туда данные, а потом
		// передавать его указатель на обработку. Также нужно сделать и с исходящим буфером.
		//if(OSI_Handler(pTxData, &TxLength, pRxData, RxLength))
		if(OSI_Handler(pTxData, &TxLength, &EthRxBuffer[0], RxLength))
		{
			if((pTxData + TxLength) > (uint32_t*)0x60005FFC)
			{
				TxCurrentDesc.FirstEmptyWord = 0x60004000;
				return;
			}
			
			SetNextTxDesc(TxLength);
		}
		
		Ready_Rx_Descriptor(RxCurrentDesc.RxCurrentDescriptor);
		
		Ethernet->RXBF_HEAD = (Ethernet->RXBF_TAIL - 1) & 0x07FF; // 0000 0111 1111 1111
					
		RxCurrentDesc.RxCurrentDescriptor++;
		RxCurrentDesc.Number++;
		if(RxCurrentDesc.Number == NUMRXDESCRIPTOR)
		{
			RxCurrentDesc.RxCurrentDescriptor = ARxDescriptor;
			RxCurrentDesc.Number = 0;	
		}
	}

}

void EthernetSendBroadcast(void)
{
	uint32_t* pTxData;
	uint16_t TxLength;
	
	pTxData = (uint32_t *)FindFirstTXEmptyWord();
	
	// broadcast UDP
	OSI_GetBroadcast(pTxData, &TxLength);
	
	if((pTxData + TxLength) > (uint32_t*)0x60005FFC)
	{
		TxCurrentDesc.FirstEmptyWord = 0x60004000;
		return;
	}
	
	SetNextTxDesc(TxLength);

}
