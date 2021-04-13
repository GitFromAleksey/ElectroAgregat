/*
 * Created by SharpDevelop.
 * User: borzenkov
 * Date: 03.07.2020
 * Time: 14:53
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Windows.Forms;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of PDU.
	/// </summary>
	public class PDU : cBaseDeviceRs485
	{
		private const int DEVICE_NUMBER = 1;
		private const string DEVICE_NAME = "ПДУ";
		
		public PDU()
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
		}
		
		public PDU(RichTextBox rtb)
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
			AddRichTexBox(rtb);
		}
		
		private void ProtocolInit()
		{
			AddProtocolParam(new ProtocolParam(38,		"NumberBlock"));

		}
	}
}
