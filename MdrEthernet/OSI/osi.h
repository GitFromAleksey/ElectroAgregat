#ifndef OSI_H
#define OSI_H

#include "stdbool.h"
#include "stdint.h"

typedef struct
{
	uint16_t MAC_Address[3];
	uint16_t IP_Address[2];
	uint16_t UDP_DstPort;
	uint16_t UDP_SrcPort;
	void (*UdpParser)(uint32_t *txArray, uint16_t *txLen, uint32_t *rxArray, uint16_t rxLen);
} t_osi_init;

typedef struct
{
	uint32_t MAC2;
	uint32_t MAC1;
	uint32_t MAC0;
} t_mac_address;	// Hardware Address MAC

typedef struct
{
	uint32_t SPA1;
	uint32_t SPA0;	
} t_ip_address;	// Protocol Address IP

typedef struct
{
	uint32_t HTYPE;			// Hardware type Ether Type 14-15
	uint32_t PTYPE;			// Protocol type 16-17
	uint8_t PLEN;				// Protocol address lenght(IP address len) 18
	uint8_t HLEN;				// Hardware address lenght(MAC address len) 19
	uint32_t OPER;			// Operation 20-21
	t_mac_address SHA;	// Sender hardware address MAC 22-27
	t_ip_address SPA;		// sender protocol address IP 28-31
	t_mac_address THA;	// Target hardware address MAC 32-37
	t_ip_address TPA;		// Target protocol address IP 38-41
} t_arp_packet;

typedef struct
{
	uint32_t SourcePort;
	uint32_t DestinationPort;
	uint32_t DatagrammLenght;
	uint32_t CheckSumm;
	uint32_t Data;
} t_udp_packet;


#define ICMP_CODE_ECHO_REQUEST		(uint8_t)0x00
#define ICMP_TYPE_ECHO_REQUEST		(uint8_t)0x08

#define ICMP_CODE_ECHO_REPLY			(uint8_t)0x00
#define ICMP_TYPE_ECHO_REPLY			(uint8_t)0x00

typedef struct
{
	uint8_t Code;
	uint8_t Type;
	uint32_t CRC16;
	uint32_t SequenceNumber;
	uint32_t Identifier;	// остальные данные
	uint32_t Payload;	// data
} t_icmp_protocol;

#define TRANSPORT_PROTOCOL_ICMP		0x01	// ICMP (Internet Control Message Protocol)
#define TRANSPORT_PROTOCOL_UDP		0x11	// UDP (User Datagram Protocol)

typedef struct
{
	unsigned ECN : 2;			// Explicit Congestion Notification(указатель перегрузки)
	unsigned DSCP : 6;		// Differentiated Services Code Point, Type of Services (ToS)	
	unsigned IHL : 4;			// Internet header lenght	
	unsigned Version : 4;	// 4 - IPv4

	uint32_t PacketSize;		// Размер пакета полный
	
	uint32_t Identificator;
	
	unsigned FragmentShift : 13;	// смещение врагмента
	unsigned Flags : 3;
	
	unsigned : 16;
	
	unsigned Protocol : 8;	// тип IP протокола (TCP, ICMP)
	unsigned TTL : 8;	// Time to Live
	
	uint32_t CRC16;
	
	t_ip_address SrcIP;
	t_ip_address DstIP;
	uint32_t firstDataWord;
} t_ipv4_header_format;


typedef struct ETH_Packet_hdr
{
	t_mac_address destMac;			// 0-5
	t_mac_address srcMac;				// 6-11
	uint32_t EtherType;					// 12-13
	uint32_t dataFirstWord;			// 14-15
} t_ETH_Packet_hdr;


#define ETHER_HARDWARE_TYPE_PROTOCOL	0x0001	// Hardware type - ethernet protocol
// EtherType
#define ETHER_PROTOCOL_TYPE_IP_V4			0x0800	// Internet protocol (IPv4)
#define ETHER_PROTOCOL_TYPE_ARP				0x0806	// Address resolution protocol

#define ETHER_ARP_OPERATION_REQUEST_CODE	0x0001
#define ETHER_ARP_OPERATION_ANSWER_CODE		0x0002

#define ETHERNET_PACKET_CRC32_BYTES_LEN		(uint16_t)(sizeof(uint32_t))
#define ETHERNET_PACKET_HDR_BYTES_LEN			(uint16_t)((sizeof(t_ETH_Packet_hdr) - sizeof(uint32_t))>>1)
#define ETHERNET_PACKET_HDR_WORDS_LEN			(uint16_t)(ETHERNET_PACKET_HDR_BYTES_LEN>>1)

#define IP_V4_FULL_LEN_BYTES							(uint16_t)(sizeof(t_ipv4_header_format) - sizeof(uint32_t))
#define IP_V4_LEN_BYTES										(uint16_t)(IP_V4_FULL_LEN_BYTES>>1)
#define IP_V4_LEN_WORDS										(uint16_t)(IP_V4_LEN_BYTES>>1)

#define ARP_FULL_LEN_BYTES								(uint16_t)sizeof(t_arp_packet)
#define ARP_LEN_BYTES											(uint16_t)(ARP_FULL_LEN_BYTES>>1)
#define ARP_LEN_WORDS											(uint16_t)(ARP_LEN_BYTES>>1)

#define ICMP_FULL_LEN_BYTES								(uint16_t)sizeof(t_icmp_protocol)
#define ICMP_LEN_BYTES										(uint16_t)(ICMP_FULL_LEN_BYTES>>1)
#define ICMP_LEN_WORDS										(uint16_t)(ICMP_LEN_BYTES>>1)

#define UDP_HDR_FULL_LEN_BYTES						(uint16_t)(sizeof(t_udp_packet) - sizeof(uint32_t))
#define UDP_HDR_LEN_BYTES									(uint16_t)(UDP_HDR_FULL_LEN_BYTES>>1)
#define UDP_HDR_LEN_WORDS									(uint16_t)(UDP_HDR_LEN_BYTES>>1)

#define MAC_ADDRESS_LEN										(uint16_t)(sizeof(t_mac_address))
#define IP_ADDRESS_LEN										(uint16_t)(sizeof(t_ip_address))

void OSI_Init(t_osi_init *setup);
// вызывается при получении пакета Ethernet для обработки
bool EthernetHandler(uint32_t *_pTxData, uint16_t *_TxLenBytes, uint32_t *_pRxData, uint16_t lenBytes);

void vUDP_Broadcast(uint32_t *_pTxData, uint16_t *_TxLenBytes);
//void vUDP_Broadcast(void);

#endif /* OSI_H */
