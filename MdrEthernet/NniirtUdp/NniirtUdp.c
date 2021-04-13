#include "NniirtUdp.h"
#include "AgregatUdp.h"
#include "smirnov_task.h"

#define NNIIRT_CODOGRAMM_LEN_BYTES		40u // нихера не 40. Прихожит 20

// описание значений поля messageType
#define MSG_TYPE_STATUS_REQUEST		255u
#define MSG_TYPE_PARAM_SET				1u
#define SOURCE_NUMBER							22u

// описание значений поля param
#define PARAM_START_DG						1u
#define PARAM_STOP_DG							2u
#define PARAM_AUTO_REFUIL					3u
#define PARAM_ARM_REFUIL					4u
#define PARAM_RESET_SIREN					5u

#define PARAM_SWITCH_NET_ON_LINE	51u
#define PARAM_PGD_ON_OFF					52u
#define PARAM_EPG_ON_OFF					53u
#define PARAM_NET_REZERV					54u
#define PARAM_GOM_1600						55u

#define PARAM_CHANGE_F_NOM_GOM		101u
#define PARAM_CHANGE_U_NOM_GOM		102u
#define PARAM_CHANGE_F_NOM_DG			103u
#define PARAM_CHANGE_U_NOM_DG			104u

// описание значений поля value для значений поля param 51-55
#define VALUE_ON									1u
#define VALUE_OFF									0u
// описание значений поля value для значений поля param 101-104
#define VALUE_UP									1u
#define VALUE_DOWN								0u

typedef struct
{
	uint8_t messageType;
	uint8_t source;
	uint32_t param;
	uint32_t value;
} t_nniirt_codogramm;

// ----------------------------------------------------------------------------




void ParamHandler(uint32_t *pTxArray, uint16_t *pTxLen, t_nniirt_codogramm *pCodogramm)
{
	switch(pCodogramm->param)
	{
		// 
		case PARAM_START_DG:
			StartDg(pTxArray, pTxLen);
			break;
		case PARAM_STOP_DG:
			StopDg(pTxArray, pTxLen);
			break;
		case PARAM_AUTO_REFUIL:
			AutoRefuil(pTxArray, pTxLen);
			break;
		case PARAM_ARM_REFUIL:
			ArmRefuil(pTxArray, pTxLen);
			break;
		case PARAM_RESET_SIREN:
			ResetSiren(pTxArray, pTxLen);
			break;
		// 
		case PARAM_SWITCH_NET_ON_LINE:
			SwitchNetOnLine(pTxArray, pTxLen);
			break;
		case PARAM_PGD_ON_OFF:
			PgdOnOff(pTxArray, pTxLen);
			break;
		case PARAM_EPG_ON_OFF:
			EpgOnOff(pTxArray, pTxLen);
			break;
		case PARAM_NET_REZERV:
			NetRezerv(pTxArray, pTxLen);
			break;
		case PARAM_GOM_1600:
			Gom1600(pTxArray, pTxLen);
			break;
		// 
		case PARAM_CHANGE_F_NOM_GOM:
			ChangeFnomGom(pTxArray, pTxLen, pCodogramm->value);
			break;
		case PARAM_CHANGE_U_NOM_GOM:
			ChangeUnomGom(pTxArray, pTxLen, pCodogramm->value);
			break;
		case PARAM_CHANGE_F_NOM_DG:
			ChangeFnomDg(pTxArray, pTxLen, pCodogramm->value);
			break;
		case PARAM_CHANGE_U_NOM_DG:
			ChangeUnomDg(pTxArray, pTxLen, pCodogramm->value);
			break;
		default:
			break;
	}
}
// ----------------------------------------------------------------------------
void NniirtUdpParser(uint32_t *pTxArray, uint16_t *pTxLen, uint32_t *pRxArray, uint16_t rxLen)
{
	t_nniirt_codogramm *pNniirtCodogramm = (t_nniirt_codogramm*)pRxArray;
	
//	if(pNniirtCodogramm->source != SOURCE_NUMBER)  // проверка номера источника, вроде бы не нужна
//		return;
	
	switch(pNniirtCodogramm->messageType)
	{
		case MSG_TYPE_STATUS_REQUEST:
			GetStatus(pTxArray, pTxLen);
			break;
		case MSG_TYPE_PARAM_SET:
			ParamHandler(pTxArray, pTxLen, pNniirtCodogramm);
			break;
		default:
			GetStatus(pTxArray, pTxLen);
			break;
	}
}
// ----------------------------------------------------------------------------
