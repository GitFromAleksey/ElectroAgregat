/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 03.12.2019
 * Time: 11:46
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Windows.Forms;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of KRP.
	/// </summary>
	public class KSHU : cBaseDeviceRs485
	{
		private const int DEVICE_NUMBER = 3;
		private const string DEVICE_NAME = "KШУ";
		
		public KSHU()
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
		}
		
		public KSHU(RichTextBox rtb)
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
			AddRichTexBox(rtb);
		}
		
		private void ProtocolInit()
		{
			AddProtocolParam(new ProtocolParam(38,		"NumberBlock"));
			AddProtocolParam(new ProtocolParam(36, 37,	"RegS", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(34, 35,	"RegimWork", ProtocolParam.eParamType.TypeDecimal));

		
			AddProtocolParam(new ProtocolParam(32, 33,	"ErrorWork_LO", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(30, 31,	"ErrorWork_HI", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(29,		"RegTransmitRS1Temp[29]"));
			AddProtocolParam(new ProtocolParam(27, 28,	"UNom"));
			AddProtocolParam(new ProtocolParam(25, 26,	"UGen[1]"));
			AddProtocolParam(new ProtocolParam(23, 24,	"Fgen"));
			AddProtocolParam(new ProtocolParam(21, 22,	"IGenC[1]"));
			AddProtocolParam(new ProtocolParam(19, 20,	"Power"));
			AddProtocolParam(new ProtocolParam(18,		"FGenInd"));
			AddProtocolParam(new ProtocolParam(16, 17,	"StatusGen"));
			AddProtocolParam(new ProtocolParam(14, 15,	"NNom"));
			AddProtocolParam(new ProtocolParam(11, 12,	"RIzol"));
			AddProtocolParam(new ProtocolParam(7, 8,	"RegS_CAN", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(5,		"RegS_LO", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(4,		"RegimWork_LO", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(3,		"NumberRegim"));
			AddProtocolParam(new ProtocolParam(2,		"StatizmVozbPud"));
			AddProtocolParam(new ProtocolParam(1,		"ErrorSum", ProtocolParam.eParamType.TypeBinary));
			
		}
	}
}
