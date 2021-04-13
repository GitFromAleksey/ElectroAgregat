/*
 * Created by SharpDevelop.
 * User: borzenkov
 * Date: 05.06.2020
 * Time: 15:19
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Windows.Forms;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of KSHSN5.
	/// </summary>
	public class KSHSN5 : cBaseDeviceRs485
	{
		private const int DEVICE_NUMBER = 1;
		private const string DEVICE_NAME = "КШСН5";
		
		public KSHSN5()
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
		}

		public KSHSN5(RichTextBox rtb)
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
			AddRichTexBox(rtb);
		}
		
		private void ProtocolInit()
		{
			AddProtocolParam(new ProtocolParam(38,		"NumberBlock"));
			AddProtocolParam(new ProtocolParam(36, 37,	"RegimWorkDU",			ProtocolParam.eParamType.TypeHex));
			AddProtocolParam(new ProtocolParam(34,35,	"RegimWork",			ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(33,		"RegS_SN5",				ProtocolParam.eParamType.TypeHex));
			AddProtocolParam(new ProtocolParam(31,32,	"UNom1",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(29,30,	"R1 = 0",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(27,28,	"UNom2",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(25,26,	"UGenInd",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(23,24,	"ULineInd",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(22,		"IGenInd",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(21,		"Power",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(19,20,	"_UGenInd",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(17,18,	"FGenInd",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(15,16,	"FLineInd",				ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(14,		"_FLineInd",			ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(12,13,	"ErrorWork_LO",			ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(11,		"ErrorWork_HI",			ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(9,10,	"UBat",					ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(8,		"RegSSN6",				ProtocolParam.eParamType.TypeHex));
			AddProtocolParam(new ProtocolParam(6,7,		"ErrorSn4Shu",			ProtocolParam.eParamType.TypeHex));
			AddProtocolParam(new ProtocolParam(5,		"IS_FVU_ON()",			ProtocolParam.eParamType.TypeDecimal));
			AddProtocolParam(new ProtocolParam(1,		"RegS(lo)_from_PDU",	ProtocolParam.eParamType.TypeHex));
		}
	}
}
