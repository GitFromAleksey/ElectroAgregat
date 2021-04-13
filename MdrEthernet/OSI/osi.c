#include <string.h>
#include "osi.h"
#include <stdlib.h>

t_ip_address _My_IP;
t_mac_address _My_MAC;
t_mac_address _Broadcast_MAC;
uint16_t UdpPortSrc = 0;
uint16_t UdpPortDst = 0;
uint16_t UdpPortBroadcast = 0xFFFF;
void (*UdpParser)(uint32_t *txArray, uint16_t *txLen, uint32_t *rxArray, uint16_t rxLen);

void OSI_Init(t_osi_init *pSetup)
{
	_My_MAC.MAC2 = pSetup->MAC_Address[2];
	_My_MAC.MAC1 = pSetup->MAC_Address[1];
	_My_MAC.MAC0 = pSetup->MAC_Address[0];

	_My_IP.SPA1 = pSetup->IP_Address[1];
	_My_IP.SPA0 = pSetup->IP_Address[0];

	UdpPortSrc = pSetup->UDP_SrcPort;
	UdpPortDst = pSetup->UDP_DstPort;
	
	UdpParser = pSetup->UdpParser;
	
	_Broadcast_MAC.MAC0 = 0xFFFF;
	_Broadcast_MAC.MAC1 = 0xFFFF;
	_Broadcast_MAC.MAC2 = 0xFFFF;
}

//--------------------------------------------------------------------------------------
bool CompareArrays(uint8_t *arr1, uint8_t *arr2, uint8_t size)
{
	while(size-- > 0)
	{
		if(*arr1 != *arr2)
			return false;
		++arr1;
		++arr2;
	}
	return true;
}
//--------------------------------------------------------------------------------------
bool CompareIP(t_ip_address *pIP1, t_ip_address *pIP2)
{
	return CompareArrays((uint8_t*)pIP1, (uint8_t*)pIP2, sizeof(t_ip_address));
}
//--------------------------------------------------------------------------------------
unsigned short CalcChecksumm(uint32_t* dataPtr, uint8_t dataLenWords, uint32_t *skipWordPtr)
{
	uint32_t Check = 0;
	uint32_t d = 0;

	while(dataLenWords-- > 0)
	{
		d = *dataPtr;
		if(dataPtr++ == skipWordPtr)
			continue;
		Check += d;
	}
	Check = (Check >> 16) + (Check & 0xFFFF);

	return (uint16_t)(~Check);
}
// очень хитрый алгоритм рассчета контрольной суммы UDP
uint16_t CheckSumUDP(t_ipv4_header_format* _pRxIPv4, uint16_t udpLenBytes)
{
	t_ipv4_header_format *pRxIPv4 = (t_ipv4_header_format *)_pRxIPv4;
	t_udp_packet *pUDP = (t_udp_packet *)&pRxIPv4->firstDataWord;
	
	uint16_t udpCheckSumm;
	uint16_t tmp = pUDP->CheckSumm;

	// копируем сюда, чтобы использовать алгоритм CalcChecksumm без изменения
	pUDP->CheckSumm = udpLenBytes + TRANSPORT_PROTOCOL_UDP;	// тоже учавствуют в рассчёте
	
	udpCheckSumm = CalcChecksumm((uint32_t*) &pRxIPv4->SrcIP, /* сдвигаем указатель на SrcIP структуры t_ipv4_header_format */
						 (udpLenBytes+8)>>1,	/* длина в словах */
							0);	// адрес слова, которое не учавствует в рассчёте
	
	pUDP->CheckSumm = tmp;
	
	return udpCheckSumm;
}
//--------------------------------------------------------------------------------------
bool ARP_Handler( uint32_t *_pTxArp, uint16_t *pTxDataLen, uint32_t *_pRxArp)
{
	bool res = false;
	t_arp_packet *pTxArp;
	t_arp_packet *pRxArp;

	pRxArp = (t_arp_packet *)_pRxArp;
	if(pRxArp->HTYPE != ETHER_HARDWARE_TYPE_PROTOCOL) return res;
	if(pRxArp->OPER != ETHER_ARP_OPERATION_REQUEST_CODE) return res;

	if( !CompareIP(&pRxArp->TPA, &_My_IP) ) return res;

	// получаем указатель в области памяти TX буфера 5600VG1U
	// и сразу туда пишем ответ
	pTxArp = (t_arp_packet*)_pTxArp;
	memcpy((void*)pTxArp, (void*)pRxArp, sizeof(t_arp_packet));
	// обмен MAC адреса
	memcpy(&pTxArp->THA, &pRxArp->SHA, sizeof(t_mac_address));
	memcpy(&pTxArp->SHA, &_My_MAC, sizeof(t_mac_address));
	// обмен IP адреса
	memcpy(&pTxArp->TPA, &pRxArp->SPA, sizeof(t_ip_address));
	memcpy(&pTxArp->SPA, &_My_IP, sizeof(t_ip_address));
	
	// операция ответа
	pTxArp->OPER = ETHER_ARP_OPERATION_ANSWER_CODE;

	*pTxDataLen += sizeof(t_arp_packet);

	res = true;

	return res;
}
//--------------------------------------------------------------------------------------
bool UDP_Handling(uint32_t *_pTxIPv4, uint16_t *pTxDataLen, uint32_t *_pRxIPv4, uint16_t rxUdpLenBytes)
{
	bool res = false;
	uint16_t txUdpLen = 0;
	
	t_ipv4_header_format *pRxIPv4 = (t_ipv4_header_format *)_pRxIPv4;
	t_ipv4_header_format *pTxIPv4 = (t_ipv4_header_format *)_pTxIPv4;
	
	t_udp_packet *pRxUDP = (t_udp_packet *)&pRxIPv4->firstDataWord;
	t_udp_packet *pTxUDP = (t_udp_packet *)&pTxIPv4->firstDataWord;
	
	if(CheckSumUDP(pRxIPv4, rxUdpLenBytes) != pRxUDP->CheckSumm)
		return false;
	
//	if(pRxUDP->SourcePort != UdpPortSrc) // не удалил, возможно пригодится
//		return res;
	
	if(pRxUDP->DestinationPort != UdpPortDst)
		return res;
	
	memcpy( ((void*)pTxUDP), ((void*)pRxUDP), rxUdpLenBytes*2);
	// callback обработчика UDP данных
	UdpParser((uint32_t*) &pTxUDP->Data, &txUdpLen, (uint32_t*) &pRxUDP->Data, rxUdpLenBytes - UDP_HDR_LEN_BYTES);

	pTxUDP->SourcePort = UdpPortDst;
	pTxUDP->DestinationPort = UdpPortSrc;
	pTxUDP->DatagrammLenght = txUdpLen + UDP_HDR_LEN_BYTES;

	memcpy( &pTxIPv4->DstIP, &pRxIPv4->SrcIP, sizeof(t_ip_address) );
	memcpy( &pTxIPv4->SrcIP, &_My_IP, sizeof(t_ip_address) );
	pTxUDP->CheckSumm = CheckSumUDP(pTxIPv4, pTxUDP->DatagrammLenght);
	
	*pTxDataLen += pTxUDP->DatagrammLenght;
	
	res = true;
	
	return res;
}
//--------------------------------------------------------------------------------------
bool ICMP_Handling(uint32_t *_pTxICMP, uint16_t *pTxDataLen, uint32_t *_pRxICMP, uint16_t rxIcmpLenBytes)
{
	bool res = false;	
	t_icmp_protocol *pRxICMP;
	t_icmp_protocol *pTxICMP;

	pRxICMP = (t_icmp_protocol *)_pRxICMP;
	pTxICMP = (t_icmp_protocol *)_pTxICMP;

	if(CalcChecksumm((uint32_t*) pRxICMP, 
               rxIcmpLenBytes>>1, 
               (uint32_t*)&pRxICMP->CRC16) != pRxICMP->CRC16)
							    return res;
	
	if(ICMP_TYPE_ECHO_REQUEST != pRxICMP->Type)
		return res;
	if(ICMP_CODE_ECHO_REQUEST != pRxICMP->Code)
		return res;

	memcpy( ((uint8_t*)pTxICMP), ((uint8_t*)pRxICMP), rxIcmpLenBytes*2);
	pTxICMP->Type = ICMP_TYPE_ECHO_REPLY;
	pTxICMP->Code = ICMP_CODE_ECHO_REPLY;
	pTxICMP->CRC16 = 0;
	
	pTxICMP->CRC16 = CalcChecksumm((uint32_t*) pTxICMP, 
               rxIcmpLenBytes>>1, 
               (uint32_t*)&pTxICMP->CRC16);

	*pTxDataLen += rxIcmpLenBytes;
	res = true;
							 
	return res;
}
//--------------------------------------------------------------------------------------
bool IPv4Handler( uint32_t *_pTxIPv4, uint16_t *pTxDataLen, uint32_t *_pRxIPv4, uint16_t rxLenBytes)
{
	bool res = false;
	t_ipv4_header_format *pRxIPv4;
	t_ipv4_header_format *pTxIPv4;
	
	pRxIPv4 = (t_ipv4_header_format *)_pRxIPv4;
	pTxIPv4 = (t_ipv4_header_format *)_pTxIPv4;
	
	if(CalcChecksumm((uint32_t*) pRxIPv4, 
							IP_V4_LEN_WORDS,
							(uint32_t*)&pRxIPv4->CRC16) != pRxIPv4->CRC16 )
									return res;
	
	if( !CompareIP(&pRxIPv4->DstIP, &_My_IP) )
	return res;
	
	if(TRANSPORT_PROTOCOL_ICMP == pRxIPv4->Protocol)
		res = ICMP_Handling(&pTxIPv4->firstDataWord, pTxDataLen, &pRxIPv4->firstDataWord, rxLenBytes - IP_V4_LEN_BYTES);
	if(TRANSPORT_PROTOCOL_UDP == pRxIPv4->Protocol)
		res = UDP_Handling((uint32_t*)pTxIPv4, pTxDataLen, (uint32_t*)pRxIPv4, rxLenBytes - IP_V4_LEN_BYTES);
	
	if(!res) return res;
	
	*pTxDataLen += IP_V4_LEN_BYTES;
	
	memcpy( pTxIPv4, pRxIPv4, IP_V4_FULL_LEN_BYTES );
	memcpy( &pTxIPv4->DstIP, &pRxIPv4->SrcIP, sizeof(t_ip_address) );
	memcpy( &pTxIPv4->SrcIP, &_My_IP, sizeof(t_ip_address) );
	pTxIPv4->PacketSize = *pTxDataLen;//
	pTxIPv4->CRC16 = 0;
	pTxIPv4->CRC16 = CalcChecksumm((uint32_t*) pTxIPv4, 
              IP_V4_LEN_WORDS, 
							(uint32_t*)&pTxIPv4->CRC16);
							
	return res;
}
//--------------------------------------------------------------------------------------
bool EthernetHandler(uint32_t *_pTxData, uint16_t *_TxLenBytes, uint32_t *_pRxData, uint16_t rxDataLenBytes)
{
	bool res = false;
	uint16_t txDataLen = 0;
	t_ETH_Packet_hdr *pFirstTxBuf = (t_ETH_Packet_hdr *)_pTxData;
	t_ETH_Packet_hdr *pEthHdr = (t_ETH_Packet_hdr *)_pRxData;

	// сразу отнимаем длину CRC32 Ethernet пакета, чтобы потом каждый раз не забывать
	rxDataLenBytes = rxDataLenBytes - ETHERNET_PACKET_CRC32_BYTES_LEN;	
	
	switch(pEthHdr->EtherType)
	{
		case ETHER_PROTOCOL_TYPE_IP_V4:
			res = IPv4Handler( &pFirstTxBuf->dataFirstWord, &txDataLen, &pEthHdr->dataFirstWord, rxDataLenBytes - ETHERNET_PACKET_HDR_BYTES_LEN);
			break;
		case ETHER_PROTOCOL_TYPE_ARP:
			res = ARP_Handler( &pFirstTxBuf->dataFirstWord, &txDataLen, &pEthHdr->dataFirstWord);
			break;
		default:
			break;
	}
	if(res)
	{
		txDataLen += ETHERNET_PACKET_HDR_BYTES_LEN;

		memcpy((t_ETH_Packet_hdr*)pFirstTxBuf, pEthHdr, sizeof(t_ETH_Packet_hdr));
		memcpy(&((t_ETH_Packet_hdr*)pFirstTxBuf)->destMac, &pEthHdr->srcMac, sizeof(t_mac_address));
		memcpy(&((t_ETH_Packet_hdr*)pFirstTxBuf)->srcMac, &_My_MAC, sizeof(t_mac_address));
		
		*_TxLenBytes = txDataLen;
	}
	
	return res;
}
// TODO доделать. Нужно сделать без выделения памяти malloc каждый вызов. Сделать выделение при инциализации модуля.
void vUDP_Broadcast(uint32_t *_pTxData, uint16_t *_TxLenBytes)
{
	uint16_t txLenBytes = 0;
	t_ETH_Packet_hdr *tmpPtr;

	t_ETH_Packet_hdr *deceptionEthHdrPtr;
	t_ipv4_header_format *deceptionIPv4HdrPtr;
	t_udp_packet *deceptionUdpPacketPtr;
	
	deceptionEthHdrPtr = (t_ETH_Packet_hdr*)malloc(ETHERNET_PACKET_HDR_BYTES_LEN + IP_V4_FULL_LEN_BYTES + ICMP_FULL_LEN_BYTES + UDP_HDR_FULL_LEN_BYTES);
	tmpPtr = (t_ETH_Packet_hdr *)_pTxData;
	
	if(deceptionEthHdrPtr == 0)
		return;
	
	memcpy(&deceptionEthHdrPtr->srcMac, &_Broadcast_MAC, sizeof(t_mac_address));
	memcpy(&deceptionEthHdrPtr->destMac, &_Broadcast_MAC, sizeof(t_mac_address));
	deceptionEthHdrPtr->EtherType = ETHER_PROTOCOL_TYPE_IP_V4;

	deceptionIPv4HdrPtr = (t_ipv4_header_format*)&deceptionEthHdrPtr->dataFirstWord;
	deceptionIPv4HdrPtr->ECN = 0;
	deceptionIPv4HdrPtr->DSCP = 0;
	deceptionIPv4HdrPtr->IHL = 5;
	deceptionIPv4HdrPtr->Version = 4;
	deceptionIPv4HdrPtr->PacketSize = IP_V4_LEN_BYTES + UDP_HDR_LEN_BYTES; //?
	deceptionIPv4HdrPtr->Identificator = 0; // ?
	deceptionIPv4HdrPtr->FragmentShift = 0;
	deceptionIPv4HdrPtr->Flags = 2;
	deceptionIPv4HdrPtr->Protocol = TRANSPORT_PROTOCOL_UDP;
	deceptionIPv4HdrPtr->TTL = 64;
	deceptionIPv4HdrPtr->CRC16 = 0; // ?
	
	deceptionIPv4HdrPtr->SrcIP.SPA0 = 0xFFFF;
	deceptionIPv4HdrPtr->SrcIP.SPA1 = 0xFFFF;
	memcpy(&deceptionIPv4HdrPtr->DstIP, &_My_IP, sizeof(t_ip_address));
	
	deceptionUdpPacketPtr = (t_udp_packet *)&deceptionIPv4HdrPtr->firstDataWord;
	deceptionUdpPacketPtr->CheckSumm = 0;
	deceptionUdpPacketPtr->Data = 0;
	deceptionUdpPacketPtr->DatagrammLenght = UDP_HDR_LEN_BYTES + sizeof(deceptionUdpPacketPtr->Data);
	deceptionUdpPacketPtr->DestinationPort = UdpPortDst;
	deceptionUdpPacketPtr->SourcePort = UdpPortBroadcast;
	
	deceptionUdpPacketPtr->CheckSumm = CheckSumUDP(deceptionIPv4HdrPtr, deceptionUdpPacketPtr->DatagrammLenght);
	
	deceptionIPv4HdrPtr->CRC16 = CalcChecksumm((uint32_t*) deceptionIPv4HdrPtr, IP_V4_LEN_WORDS, (uint32_t*)&deceptionIPv4HdrPtr->CRC16);
							
	EthernetHandler((uint32_t*)tmpPtr, &txLenBytes, (uint32_t*)deceptionEthHdrPtr, ETHERNET_PACKET_HDR_BYTES_LEN + IP_V4_LEN_BYTES + UDP_HDR_LEN_BYTES + sizeof(deceptionUdpPacketPtr->Data) + ETHERNET_PACKET_CRC32_BYTES_LEN);
	
	free(deceptionEthHdrPtr);
	
	*_TxLenBytes = txLenBytes;

}
