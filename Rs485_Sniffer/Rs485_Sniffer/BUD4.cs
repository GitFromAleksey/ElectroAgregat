/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 03.12.2019
 * Time: 11:29
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Windows.Forms;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of KDG.
	/// </summary>
	public class BUD4 : cBaseDeviceRs485
	{
		private const int DEVICE_NUMBER = 2;
		private const string DEVICE_NAME = "БУД4";
		
		public BUD4()
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
		}
		
		public BUD4(RichTextBox rtb)
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

			AddProtocolParam(new ProtocolParam(33,		"RegTransmitCAN[1]"));
			AddProtocolParam(new ProtocolParam(32,		"55"));
			AddProtocolParam(new ProtocolParam(30, 31,	"NDiz"));
			AddProtocolParam(new ProtocolParam(29,		"PM"));
			
			AddProtocolParam(new ProtocolParam(28,		"TOG"));
			AddProtocolParam(new ProtocolParam(26,		"UT"));
			AddProtocolParam(new ProtocolParam(24, 25,	"ErrorWork_LO", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(22, 23,	"ErrorWork_HI", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(21,		"StatusPud"));
			AddProtocolParam(new ProtocolParam(19, 20,	"UBat"));
		}
	}
}
