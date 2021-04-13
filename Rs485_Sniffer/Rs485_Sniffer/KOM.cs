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
	/// Description of KOM.
	/// </summary>
	public class KOM : cBaseDeviceRs485
	{
		private const int DEVICE_NUMBER = 5;
		private const string DEVICE_NAME = "KOM";
		
		public KOM()
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
		}
		
		public KOM(RichTextBox rtb)
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
			AddProtocolParam(new ProtocolParam(34, 35,	"RegimWork"));
			AddProtocolParam(new ProtocolParam(32, 33,	"ErrorWork_HI", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(30, 31,	"ErrorWork_LO", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(29,		"RegTransmitRS1Temp"));
			
			AddProtocolParam(new ProtocolParam(27, 28,	"UNom"));
			AddProtocolParam(new ProtocolParam(25, 26,	"ParamEnd[0]"));
			AddProtocolParam(new ProtocolParam(23, 24,	"ParamEnd[2]"));
			AddProtocolParam(new ProtocolParam(21, 22,	"ParamEnd[1]"));
			AddProtocolParam(new ProtocolParam(19, 20,	"ParamEnd[3]"));
			
			AddProtocolParam(new ProtocolParam(18,		"FGen"));
			AddProtocolParam(new ProtocolParam(16, 17,	"StatusGen"));
			AddProtocolParam(new ProtocolParam(14, 15,	"NNom"));
			AddProtocolParam(new ProtocolParam(12, 13,	"RIzol"));
			
			AddProtocolParam(new ProtocolParam(7, 8,	"RegSCAN", ProtocolParam.eParamType.TypeBinary));
			
			AddProtocolParam(new ProtocolParam(6,		"BitResetError"));
			AddProtocolParam(new ProtocolParam(5,		"RegS_", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(4,		"RegimWork_"));
			AddProtocolParam(new ProtocolParam(3,		"NumberRegim"));
			AddProtocolParam(new ProtocolParam(1, 2,	"NDiz"));
		}
	}
}
