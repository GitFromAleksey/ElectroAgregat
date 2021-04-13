#ifndef AGREGATUDP_H
#define AGREGATUDP_H

#include <stdint.h>
#include <stdbool.h>

typedef union
{
	uint16_t DgStatusWord;
	struct
	{
		unsigned 								: 1;
		unsigned DgUError				: 1;
		unsigned DgLevelFuel		: 1;
		unsigned DgLevelOil			: 1;
		unsigned DgLevelOg			: 1;
		unsigned DgTempOg				: 1;
		unsigned DgOilPress			: 1;
		unsigned DgNotSync			: 1;
		unsigned DgLoIzol				: 1;
		unsigned DgQfPeregruz		: 1;
		unsigned DgQf						: 1;
		unsigned DgRaznos				: 1;
		unsigned DgNotOborotov	: 1;
		unsigned DgNotVozb			: 1;
		unsigned DgNotStop			: 1;		
		unsigned DgNotStart			: 1;
	} DgStatusBits;
} u_word_2_agregat_codogramm;

typedef union
{
	uint16_t DgLukesStatusWord;
	struct
	{
		unsigned 												: 14;
		unsigned DgLukePritochniyError	: 1;
		unsigned DgLukeRadiatorError		: 1;
	} DgLukesStatusBits;
} u_word_3_agregat_codogramm;


typedef union
{
	uint16_t GomStatusWord;
	struct
	{
		unsigned 								: 7;
		unsigned GomNotSync			: 1;
		unsigned GomLoIzol			: 1;
		unsigned GomQfPeregruz	: 1;
		unsigned GomQf					: 1;
		unsigned GomNotRaznos		: 1;
		unsigned GomNotOborotov	: 1;	
		unsigned GomNotVozb			: 1;
		unsigned 								: 2;
	} GomStatusBits;
} u_word_4_agregat_codogramm;

typedef union
{
	uint16_t KRP_StatusWord;
	struct
	{
		unsigned 								: 6;
		unsigned CheredFaz			: 1;
		unsigned Pogar					: 1;
		unsigned NetRBP					: 1;
		unsigned NetQfPeregruz	: 1;
		unsigned NetQf					: 1;
		unsigned 								: 2;		
		unsigned DgStatus				: 3;
	} KRP_StatusBits;
} u_word_5_agregat_codogramm;


typedef union
{
	uint16_t IndicatorWord;
	struct
	{
		unsigned 									: 1;
		unsigned PumpFuelFillIsOn	: 1;
		unsigned PumpOilFillIsOn	: 1;
		unsigned PPZ_Norma				: 1;
		unsigned RezervNumber			: 2;
		unsigned NetRezerv				: 1;
		unsigned EthernetControl	: 1;
		unsigned NetIsConnected		: 1;
		unsigned AutoFuelFill			: 1;
		unsigned AutoOilFill			: 1;
		unsigned PGD							: 1;
		unsigned EPG							: 1;
		unsigned NetOnLine				: 1;		
		unsigned GomOnLine				: 1;		
		unsigned DgOnLine					: 1;
	} IndicatorBits;
} u_word_6_agregat_codogramm;

typedef struct
{
	unsigned UBattery	: 13;
	unsigned SyncNET	: 1;
	unsigned SyncGOM	: 1;
	unsigned SyncKDG	: 1;
} t_bf_word_16_agregat_codogramm;

typedef struct
{
	unsigned DG_FuelLevel	: 8;
	unsigned Ibattery	: 8;
	unsigned : 16;
} t_bf_word_17_agregat_codogramm;

typedef struct
{
	unsigned messageType : 8;
	unsigned source : 8;
	u_word_2_agregat_codogramm uDG_State;
	u_word_3_agregat_codogramm uDG_LukeState;
	u_word_4_agregat_codogramm uGOM_Status;
	u_word_5_agregat_codogramm uKRP_Status;
	u_word_6_agregat_codogramm uIndicator;
	uint32_t Word7_Ulin;
	uint32_t Word8_Udg;
	uint32_t Word9_Ugom;
	uint32_t Word10_Unet;
	uint32_t Word11_Inet;
	uint32_t Tog_bf;//t_bf_word_12_agregat_codogramm Tog_bf;
	uint32_t Word13_OilPressure;
	uint32_t Word14_RizolDG;
	uint32_t Word15_RizolGOM;
	t_bf_word_16_agregat_codogramm SyncStatusAndUbat_bf;
	t_bf_word_17_agregat_codogramm FuelLevelAndIbattery_bf;
	uint32_t Word18_Flin;
	uint32_t Word19_Rezerv_DG_Oboroti;
	uint32_t Word20_Rezerv_GOM_Oboroti;
} t_agregat_codogramm;

#define AGREGAT_CODOGRAMM_FULL_LEN_BYTES			(uint16_t)(sizeof(t_agregat_codogramm))
#define AGREGAT_CODOGRAMM_LEN_BYTES						(uint16_t)(AGREGAT_CODOGRAMM_FULL_LEN_BYTES>>1)

void StartDg(uint32_t *pTxArray, uint16_t *pTxLen);
void StopDg(uint32_t *pTxArray, uint16_t *pTxLen);
void AutoRefuil(uint32_t *pTxArray, uint16_t *pTxLen);
void ArmRefuil(uint32_t *pTxArray, uint16_t *pTxLen);
void ResetSiren(uint32_t *pTxArray, uint16_t *pTxLen);
void SwitchNetOnLine(uint32_t *pTxArray, uint16_t *pTxLen);
void PgdOnOff(uint32_t *pTxArray, uint16_t *pTxLen);
void EpgOnOff(uint32_t *pTxArray, uint16_t *pTxLen);
void NetRezerv(uint32_t *pTxArray, uint16_t *pTxLen);
void Gom1600(uint32_t *pTxArray, uint16_t *pTxLen);
void ChangeFnomGom(uint32_t *pTxArray, uint16_t *pTxLen, bool up_down);
void ChangeUnomGom(uint32_t *pTxArray, uint16_t *pTxLen, bool up_down);
void ChangeFnomDg(uint32_t *pTxArray, uint16_t *pTxLen, bool up_down);
void ChangeUnomDg(uint32_t *pTxArray, uint16_t *pTxLen, bool up_down);
void GetStatus(uint32_t *pTxArray, uint16_t *pTxLen);


#endif /* AGREGATUDP_H */
