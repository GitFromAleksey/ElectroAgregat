#include <string.h>
#include "AgregatUdp.h"
#include "smirnov_task.h"
#include "keys_pdu.h"
#include "Rs485_Protocol.h"
#include "PduErrors.h"
#include "errors_pkdg.h"
#include "error1_krp.h"
#include "keys_pkdg1.h"
#include "keys_krp.h"

// параметры протокола
#define MESSAGE_TYPE    1u	// тип сообщения
#define SOURCE_NUMBER   22u	// номер источника

void FillDgState(t_agregat_codogramm *cdgm)
{
	cdgm->uDG_State.DgStatusWord = 0x0;
	cdgm->uDG_State.DgStatusBits.DgUError				= (Rs485Kdg.Error1 & ERROR1_U_NO_NORM) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgLevelFuel		= (Rs485Kdg.Error1 & ERROR1_NO_TOPL) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgLevelOil			= (Rs485Kdg.Error2 & ERROR2_NO_MASLA) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgLevelOg			= (Rs485Kdg.Error1 & ERROR1_UROV_OG) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgTempOg				= (Rs485Kdg.Error1 & ERROR1_TOG_DG) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgOilPress			= (Rs485Kdg.Error1 & ERROR1_PM_DG) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgNotSync			= (Rs485Kdg.Error1 & ERROR1_NO_SINHR) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgLoIzol				= (Rs485Kdg.Error1 & ERROR1_RIZOL_DG) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgQfPeregruz		= (Rs485Kdg.Error1 & ERROR1_QF1_DG) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgQf						= (Rs485Kdg.Error1 & ERROR1_QF1_DG) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgRaznos				= (Rs485Kdg.Error1 & ERROR1_RAZNOS) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgNotOborotov	= (Rs485Kdg.Error1 & ERROR1_NO_OBOROT) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgNotVozb			= (Rs485Kdg.Error1 & ERROR1_NO_VOZB) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgNotStop			= (Rs485Kdg.Error2 & ERROR2_NO_STOP) ? (1):(0);
	cdgm->uDG_State.DgStatusBits.DgNotStart			= (Rs485Kdg.Error2 & ERROR2_NO_OBOROT) ? (1):(0);
}

void FillDdLukeState(t_agregat_codogramm *cdgm)
{
	// TODO где-то нет этих аварий нужно поискать
	cdgm->uDG_LukeState.DgLukesStatusWord = 0;
	cdgm->uDG_LukeState.DgLukesStatusBits.DgLukePritochniyError = 0;
	cdgm->uDG_LukeState.DgLukesStatusBits.DgLukeRadiatorError = 0;
}

void FillGomStatus(t_agregat_codogramm *cdgm)
{
	cdgm->uGOM_Status.GomStatusWord = 0;
	cdgm->uGOM_Status.GomStatusBits.GomNotSync			= 0;
	cdgm->uGOM_Status.GomStatusBits.GomLoIzol				= 0;
	cdgm->uGOM_Status.GomStatusBits.GomQfPeregruz		= 0;
	cdgm->uGOM_Status.GomStatusBits.GomQf						= 0;
	cdgm->uGOM_Status.GomStatusBits.GomNotRaznos		= 0;
	cdgm->uGOM_Status.GomStatusBits.GomNotOborotov	= 0;
	cdgm->uGOM_Status.GomStatusBits.GomNotVozb			= 0;
}

void FillKrpStatus(t_agregat_codogramm *cdgm)
{
	cdgm->uKRP_Status.KRP_StatusWord = 0;
	cdgm->uKRP_Status.KRP_StatusBits.CheredFaz			= (Rs485Krp.Error1 & RE1_AD_FAZA) ? (1):(0);//(Avaria & RP_ERROR_CHER_FAZ_BIT) ? (1):(0);
	cdgm->uKRP_Status.KRP_StatusBits.Pogar					= (Rs485Krp.Error1 & RE1_POGAR) ? (1):(0);//(Avaria & RP_AVAR_POGAR_BIT) ? (1):(0);
	cdgm->uKRP_Status.KRP_StatusBits.NetRBP					= (Rs485Krp.Error1 & RE1_RBP) ? (1):(0);//(Avaria & RP_ERROR_RBP_BIT) ? (1):(0);
	cdgm->uKRP_Status.KRP_StatusBits.NetQfPeregruz	= (Rs485Krp.Error1 & RE1_BK_QF1) ? (1):(0);//(Avaria & RP_ERROR_BK_QF1_BIT) ? (1):(0);
	cdgm->uKRP_Status.KRP_StatusBits.NetQf					= (Rs485Krp.Error1 & RE1_BK_QF1) ? (1):(0);//(Avaria & RP_ERROR_BK_QF1_BIT) ? (1):(0);
	cdgm->uKRP_Status.KRP_StatusBits.DgStatus				= 0;//Rs485Kdg.RegimWork & 0x3;
}

void FillIndicator(t_agregat_codogramm *cdgm)
{
	cdgm->uIndicator.IndicatorWord = 0;
	cdgm->uIndicator.IndicatorBits.PumpFuelFillIsOn	= (Rs485Kdg.Transmit_Led_And_CAN & 1) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.PumpOilFillIsOn	= (Rs485Kdg.Transmit_Led_And_CAN & 0x02) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.PPZ_Norma				= (Rs485Krp.Error1 & RE1_POGAR) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.RezervNumber			= 0; // TODO хрен знает где искать
	cdgm->uIndicator.IndicatorBits.NetRezerv				= (RegS & KEY_PKDU_REZERV) ? (1):(0);//(Rs485Krp.RegS & KeyRezervSeti) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.EthernetControl	= 1;
	cdgm->uIndicator.IndicatorBits.NetIsConnected		= (Rs485Krp.RegS & IN_BK_QF1) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.AutoFuelFill			= (Rs485Krp.RegS1 & KeyDozToplAvto) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.AutoOilFill			= (Rs485Krp.RegS & KeyDozMaslAvto) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.PGD							= (RegS & KEY_PKDU_PGD) ? (1):(0);//(Rs485Kdg.RegS & KEY_EPG) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.EPG							= (RegS & KEY_PKDU_EPG) ? (1):(0);//(Rs485Krp.RegS & KEY_EPG) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.NetOnLine				= (Rs485Krp.RegS & IN_BK_K1) ? (1):(0);
	cdgm->uIndicator.IndicatorBits.GomOnLine				= 0;
	cdgm->uIndicator.IndicatorBits.DgOnLine					= (Rs485Kdg.RegS & IN_BK_K1) ? (1):(0);
}

void FillSyncStatusAndUbat(t_agregat_codogramm *cdgm)
{
	cdgm->SyncStatusAndUbat_bf.SyncKDG	= (Rs485Kdg.RegTransmitRS1Temp_32 & (1<<7)) ? (1):(0);
	cdgm->SyncStatusAndUbat_bf.SyncGOM	= 0;// TODO ввести на ЭД2х30
	cdgm->SyncStatusAndUbat_bf.SyncNET	= (Rs485Krp.RegTransmitRS1Temp_32 & (1<<7)) ? (1):(0);
	cdgm->SyncStatusAndUbat_bf.UBattery	= Rs485Krp.UBatInd;//13;
}

void FillFuelLevelAndIbattery(t_agregat_codogramm *cdgm)
{
	cdgm->FuelLevelAndIbattery_bf.DG_FuelLevel	= Rs485Kdg.Ur_Topliva;
	cdgm->FuelLevelAndIbattery_bf.Ibattery			= IBat;
}

void FillOutputData(uint32_t *pCdgm, uint16_t *pDataLen)
{
	t_agregat_codogramm *cdgm = (t_agregat_codogramm *)pCdgm;
	
	cdgm->messageType = MESSAGE_TYPE;
	cdgm->source = SOURCE_NUMBER;

	FillDgState(cdgm);
	FillDdLukeState(cdgm);
	FillGomStatus(cdgm);
	FillKrpStatus(cdgm);
	FillIndicator(cdgm);

	cdgm->Word7_Ulin = Rs485Krp.ULine;
	cdgm->Word8_Udg = Rs485Kdg.UGenInd;
	cdgm->Word9_Ugom = 0;	// TODO отсутствует в smirnov_task. нужно найти
	cdgm->Word10_Unet = Rs485Krp.UGenInd;
	cdgm->Word11_Inet = Rs485Krp.IGenInd;
	cdgm->Tog_bf = TOG;
	cdgm->Word13_OilPressure = Rs485Kdg.PM;
	cdgm->Word14_RizolDG = Rs485Kdg.RIzol;
	cdgm->Word15_RizolGOM = 0;
	FillSyncStatusAndUbat(cdgm);
	FillFuelLevelAndIbattery(cdgm);
	cdgm->Word18_Flin = Rs485Krp.FGenInd;
	cdgm->Word19_Rezerv_DG_Oboroti = 0;
	cdgm->Word20_Rezerv_GOM_Oboroti = 0;
	
	*pDataLen = AGREGAT_CODOGRAMM_LEN_BYTES;
}
// ----------------------------------------------------------------------------
void StartDg(uint32_t *pTxArray, uint16_t *pTxLen)
{
	RegS |= KEY_PKDU_START;
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void StopDg(uint32_t *pTxArray, uint16_t *pTxLen)
{
	RegS |= KEY_PKDU_STOP;
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void AutoRefuil(uint32_t *pTxArray, uint16_t *pTxLen)
{
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void ArmRefuil(uint32_t *pTxArray, uint16_t *pTxLen)
{
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void ResetSiren(uint32_t *pTxArray, uint16_t *pTxLen)
{
	RegS |= KEY_PKDU_RES_ZS;
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void SwitchNetOnLine(uint32_t *pTxArray, uint16_t *pTxLen)
{
	RegS |= KEY_PKDU_SET_TO_LINE;
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void PgdOnOff(uint32_t *pTxArray, uint16_t *pTxLen)
{
	if( (RegS & KEY_PKDU_PGD) == KEY_PKDU_PGD)
		{ RegS &= ~KEY_PKDU_PGD; }
	else
		{ RegS |= KEY_PKDU_PGD; }
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void EpgOnOff(uint32_t *pTxArray, uint16_t *pTxLen)
{
	if( (RegS & KEY_PKDU_EPG) == KEY_PKDU_EPG)
		{ RegS &= ~KEY_PKDU_EPG; }
	else
		{ RegS |= KEY_PKDU_EPG; }
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void NetRezerv(uint32_t *pTxArray, uint16_t *pTxLen)
{
	if( (RegS & KEY_PKDU_REZERV) == KEY_PKDU_REZERV)
		{ RegS &= ~KEY_PKDU_REZERV; }
	else
		{ RegS |= KEY_PKDU_REZERV; }	
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void Gom1600(uint32_t *pTxArray, uint16_t *pTxLen)
{
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void ChangeFnomGom(uint32_t *pTxArray, uint16_t *pTxLen, bool up_down)
{
	if(up_down)	{ RegS |= KEY_PKDU_F_UP; RegS &= ~KEY_PKDU_F_DOWN; }
	else				{ RegS |= KEY_PKDU_F_DOWN; RegS &= ~KEY_PKDU_F_UP; }
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void ChangeUnomGom(uint32_t *pTxArray, uint16_t *pTxLen, bool up_down)
{
	if(up_down)	{ RegS |= KEY_PKDU_U_UP; RegS &= ~KEY_PKDU_U_DWN; }
	else				{ RegS |= KEY_PKDU_U_DWN; RegS &= ~KEY_PKDU_U_UP; }
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void ChangeFnomDg(uint32_t *pTxArray, uint16_t *pTxLen, bool up_down)
{
	if(up_down)	{ RegS |= KEY_PKDU_F_UP; RegS &= ~KEY_PKDU_F_DOWN; }
	else				{ RegS |= KEY_PKDU_F_DOWN; RegS &= ~KEY_PKDU_F_UP; }
	FillOutputData(pTxArray, pTxLen);
}
// ----------------------------------------------------------------------------
void ChangeUnomDg(uint32_t *pTxArray, uint16_t *pTxLen, bool up_down)
{
	if(up_down)	{ RegS |= KEY_PKDU_U_UP; RegS &= ~KEY_PKDU_U_DWN; }
	else				{ RegS |= KEY_PKDU_U_DWN; RegS &= ~KEY_PKDU_U_UP; }
	FillOutputData(pTxArray, pTxLen);
}

void GetStatus(uint32_t *pTxArray, uint16_t *pTxLen)
{
	FillOutputData(pTxArray, pTxLen);
}
