/*
 * Created by SharpDevelop.
 * User: borzenkov
 * Date: 05.06.2020
 * Time: 15:20
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Windows.Forms;

namespace Rs485_Sniffer
{
	/// <summary>
	/// KSHSN6 в одной сети с ПДУ и длина пакета данных 80 байт
	/// </summary>
	public class KSHSN6 : cBaseDeviceRs485
	{
		private const int DEVICE_NUMBER = 1;
		private const string DEVICE_NAME = "КШСН6";
		
		public KSHSN6()
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
		}
		
		public KSHSN6(RichTextBox rtb)
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
			AddRichTexBox(rtb);
		}
		
		private void ProtocolInit()
		{
			AddProtocolParam(new ProtocolParam(78,		"NumberBlock"));
			AddProtocolParam(new ProtocolParam(76,77,	"Uset", ProtocolParam.eParamType.TypeDecimal));

			AddProtocolParam(new ProtocolParam(74,75,	"FSet"));
			AddProtocolParam(new ProtocolParam(72,73,	"FLine"));
			AddProtocolParam(new ProtocolParam(70,71,	"ULine"));
			AddProtocolParam(new ProtocolParam(68,69,	"ISet"));
			AddProtocolParam(new ProtocolParam(66,67,	"PowerSet"));
			AddProtocolParam(new ProtocolParam(64,65,	"UGen1"));
			AddProtocolParam(new ProtocolParam(62,63,	"FGen1"));
			AddProtocolParam(new ProtocolParam(60,61,	"IGen1"));
			AddProtocolParam(new ProtocolParam(58,59,	"PowerGen1"));
			AddProtocolParam(new ProtocolParam(56,		"StatusSn3"));
			AddProtocolParam(new ProtocolParam(54,55,	"UGen2"));
			AddProtocolParam(new ProtocolParam(52,53,	"FGen2"));
			AddProtocolParam(new ProtocolParam(50,51,	"IGen2"));
			AddProtocolParam(new ProtocolParam(48,49,	"PowerGen2"));
			AddProtocolParam(new ProtocolParam(47,		"Dozapravka"));
			AddProtocolParam(new ProtocolParam(46,		"StatusGen1"));
			AddProtocolParam(new ProtocolParam(45,		"StatusGen2"));
			AddProtocolParam(new ProtocolParam(44,		"StatusSet"));
			AddProtocolParam(new ProtocolParam(42,43,	"StatusPud"));
			AddProtocolParam(new ProtocolParam(41,		"RomReceiveCAN[0][13]"));
			AddProtocolParam(new ProtocolParam(38,39,	"Error KP"));
			AddProtocolParam(new ProtocolParam(36,37,	"Uab"));
			AddProtocolParam(new ProtocolParam(34,35,	"NDiz"));
			AddProtocolParam(new ProtocolParam(32,33,	"NDiz2"));
			AddProtocolParam(new ProtocolParam(31,		"TOG1"));
			AddProtocolParam(new ProtocolParam(30,		"PM1"));
			AddProtocolParam(new ProtocolParam(29,		"TOG2"));
			AddProtocolParam(new ProtocolParam(28,		"PM2"));
			AddProtocolParam(new ProtocolParam(27,		"UT1"));
			AddProtocolParam(new ProtocolParam(26,		"TGG1"));
			AddProtocolParam(new ProtocolParam(25,		"UT2"));
			AddProtocolParam(new ProtocolParam(24,		"TGG2"));
			AddProtocolParam(new ProtocolParam(23,		"RegimControl"));
			AddProtocolParam(new ProtocolParam(22,		"ErrorWork"));
			AddProtocolParam(new ProtocolParam(21,		"Temperature2"));
			AddProtocolParam(new ProtocolParam(20,		"Temperature1"));
			AddProtocolParam(new ProtocolParam(18,19,	"ErrorPud1"));
			AddProtocolParam(new ProtocolParam(16,17,	"ErrorPud1_"));
			AddProtocolParam(new ProtocolParam(14,15,	"ErrorPud2"));
			AddProtocolParam(new ProtocolParam(12,13,	"ErrorSN3"));
			AddProtocolParam(new ProtocolParam(10,11,	"ErrorKu1"));
			AddProtocolParam(new ProtocolParam(8,9,		"ErrorKU2"));
			AddProtocolParam(new ProtocolParam(6,7,		"RIzol1"));
			AddProtocolParam(new ProtocolParam(4,5,		"RIzol2"));
			AddProtocolParam(new ProtocolParam(3,		"Sn3"));
			AddProtocolParam(new ProtocolParam(1,2,		"_ErrorWork"));
			
			// TODO дописать остальные параметры
		}
	}
}
