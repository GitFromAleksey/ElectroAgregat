#ifndef __ETHCONFIG_H_
#define __ETHCONFIG_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	uint16_t MAC_Address[3];
	bool (*OSI_Handler)(uint32_t *_pTxData, uint16_t *_TxLenBytes, uint32_t *_pRxData, uint16_t lenBytes);
	void (*OSI_GetBroadcast)(uint32_t *_pTxData, uint16_t *_TxLenBytes);
} t_Eth_init;

// ����������� �������� Ethernrt-����������� 5600��1�
typedef struct
{
	unsigned int MAC_CTRL;
    unsigned int MinFrame;
    unsigned int MaxFrame;
    unsigned int CollConfig;
    unsigned int IPGTx;
    unsigned int MAC_ADDR_T;
    unsigned int MAC_ADDR_M;
    unsigned int MAC_ADDR_H;
    unsigned int HASH0;
    unsigned int HASH1;
    unsigned int HASH2;
    unsigned int HASH3;
    unsigned int INT_MSK;
    unsigned int INT_SRC;
    unsigned int PHY_CTRL;
    unsigned int PHY_STAT;
    unsigned int RXBF_HEAD;
    unsigned int RXBF_TAIL;
    unsigned int dammy0;
    unsigned int dammy1;
    unsigned int STAT_RX_ALL;
    unsigned int STAT_RX_OK;
    unsigned int STAT_RX_OVF;
    unsigned int STAT_RX_LOST;
    unsigned int STAT_TX_ALL;
    unsigned int STAT_TX_OK;
    unsigned int base_RxBF;
    unsigned int base_TxBF;
    unsigned int base_RxBD;
    unsigned int base_TxBD;
    unsigned int base_RG;
    unsigned int GCTRL;
} _ethernet;

//��������� ��� ����������� ����������� �������
typedef struct
{
	unsigned int	StartAddress;			//��������� ����� ����������� � ������ ����������� 1986��91�1
	unsigned short	Status;					//����� �����������
	unsigned short	PacketLength;			//����� ��������� ������
	unsigned short	PacketStartAddressH;	//����� � ������, ��� ���������� ������ ���� ������ (������� �����, ������ 0�0000)
	unsigned short	PacketStartAddressL;	//����� � ������, ��� ���������� ������ ���� ������ (������� �����)
	unsigned short	LastDesc;				//������� ���������� ����������� (1 - ��������� ����������, 0 - �� ��������� ����������)
} _rx_descriptor;

//��������� ��� ������ � ������� ������������ ����������� �������
typedef struct
{
	_rx_descriptor* RxCurrentDescriptor;	//��������� �� ������� ���������� ����������� �������
	unsigned short Number;					//����� �������� ����������� (��������� �������� �� 0 �� NUMRXDESCRIPTOR-1)
} _rx_current_descriptor;

//��������� ��� ����������� ������������ �������
typedef struct
{
	unsigned int	StartAddress;			//��������� ����� ����������� � ������ ����������� 1986��91�1
	unsigned short	Status;					//����� �����������
	unsigned short	PacketLength;			//����� ��������� ������
	unsigned short	PacketStartAddressH;	//����� � ������, ��� ���������� ������ ���� ������ (������� �����, ������ 0�0000)
	unsigned short	PacketStartAddressL;	//����� � ������, ��� ���������� ������ ���� ������ (������� �����)
	unsigned short	LastDesc;				//������� ���������� ����������� (1 - ��������� ����������, 0 - �� ��������� ����������)
} _tx_descriptor;

//��������� ��� ������ � ������� ������������ ������������ �������
typedef struct
{
	_tx_descriptor* TxCurrentDescriptor;	//��������� �� ������� ���������� ������������ �������
	unsigned short Number;					//����� �������� ����������� (��������� �������� �� 0 �� NUMTXDESCRIPTOR-1)
	unsigned int FirstEmptyWord;			//����� ������� ���������� ����� � ������ �����������
} _tx_current_descriptor;


// ���� �������� ���������� _ethernet.MAC_CTRL
typedef struct
{
	unsigned LB_EN					: 1;
	unsigned BIG_ENDIAN			: 1;
	unsigned HALFD_EN				: 1;
	unsigned BCKOF_DIS			: 1;
	unsigned ERR_FRAME_EN		: 1;
	unsigned SHRT_FRAME_EN	: 1;
	unsigned LONG_FRAME_EN	: 1;
	unsigned CTRL_FRAME_EN	: 1;
	unsigned MCA_EN					: 1;
	unsigned BCA_EN					: 1;
	unsigned PRO_EN					: 1;
	unsigned PAUSE_EN				: 1;
	unsigned DSCR_SCAN_EN		: 1;
	unsigned RX_RST					: 1;	
	unsigned TX_RST					: 1;
} t_mac_ctrl;

// ������� ���������� _ethernet.MAC_CTRL
typedef union
{
	t_mac_ctrl sMAC_CTRL;
	uint16_t MAC_CTRL;
} u_mac_ctrl;


//��������� ����� ������ ���������
#define BASE_ETH_RXBuffer		0x60000000  //Absolut ADDRESS = 0x0000

//��������� ����� ������ ������������ ����������� �������
#define BASE_ETH_RXDescBuffer	0x60002000  //Absolut ADDRESS = 0x0800

//��������� ����� �����������
#define BASE_ETH_TXBuffer		0x60004000  //Absolut ADDRESS = 0x1000

//��������� ����� ������ ������������ ������������ �������
#define BASE_ETH_TXDescBuffer	0x60006000  //Absolut ADDRESS = 0x1800

//��������� ����� ����������� ��������� Ethernrt-����������� 5600��1�
#define BASE_ETHERNET			0x60007F00  //Absolut ADDRESS = 0x1FC0

#define Ethernet              ((_ethernet *)BASE_ETHERNET)

#define RxBuffer              ((unsigned int *)BASE_ETH_RXBuffer)
#define RxDescriptor          ((unsigned int *)BASE_ETH_RXDescBuffer)

#define TxBuffer              ((unsigned int *)BASE_ETH_TXBuffer)
#define TxDescriptor          ((unsigned int *)BASE_ETH_TXDescBuffer)

//��������� ����� ������ ���������
#define BASE_ETH_RXBuffer		0x60000000  //Absolut ADDRESS = 0x0000

//��������� ����� ������ ������������ ����������� �������
#define BASE_ETH_RXDescBuffer	0x60002000  //Absolut ADDRESS = 0x0800

//��������� ����� �����������
#define BASE_ETH_TXBuffer		0x60004000  //Absolut ADDRESS = 0x1000

//��������� ����� ������ ������������ ������������ �������
#define BASE_ETH_TXDescBuffer	0x60006000  //Absolut ADDRESS = 0x1800

////��������� ����� ����������� ��������� Ethernrt-����������� 5600��1�
//#define BASE_ETHERNET			0x60007F00  //Absolut ADDRESS = 0x1FC0

//#define Ethernet              ((_ethernet *)BASE_ETHERNET)

//#define RxBuffer              ((unsigned int *)BASE_ETH_RXBuffer)
//#define RxDescriptor          ((unsigned int *)BASE_ETH_RXDescBuffer)

//#define TxBuffer              ((unsigned int *)BASE_ETH_TXBuffer)
//#define TxDescriptor          ((unsigned int *)BASE_ETH_TXDescBuffer)

#define NUMRXDESCRIPTOR	16	//���������� ������������ ����������� ������� (������� 1, �������� 32)
#define NUMTXDESCRIPTOR	16	//���������� ������������ ������������ ������� (������� 1, �������� 32)

#define PRINTSTATUSON	1	//����������� ��������� � ������������ ���������� ����������� (1 - ��������, 0 - ���������)

//������� ���������������� ����������� 5600��1�
void EthCfg(t_Eth_init *pEthInit);
// ���������� �� ��������� ������
void EthernetRun(void);
// ��� �������� ������������������ ������ UDP
void EthernetSendBroadcast(void);


#endif /*__CONFIG_H_*/

