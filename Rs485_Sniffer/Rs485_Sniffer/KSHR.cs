/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 03.12.2019
 * Time: 11:47
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
	public class KSHR : cBaseDeviceRs485
	{
		private const int DEVICE_NUMBER = 6;
		private const string DEVICE_NAME = "КШР";
		
		public KSHR()
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
		}
		
		public KSHR(RichTextBox rtb)
		{
			DeviceName = DEVICE_NAME;
			DeviceNumber = DEVICE_NUMBER;
			
			ProtocolInit();
			AddRichTexBox(rtb);
		}
		
		private void ProtocolInit()
		{
			m_BinaryDecoder = new cBinaryDecoder("RegS");
			m_BinaryDecoder.AddNewBitDescribtion(0, "REGS_Q2_ON");
			m_BinaryDecoder.AddNewBitDescribtion(1, "REGS_Q1_ON");
			m_BinaryDecoder.AddNewBitDescribtion(2, "REGS_Q4_ON");
			m_BinaryDecoder.AddNewBitDescribtion(3, "REGS_Q3_ON");
			m_BinaryDecoder.AddNewBitDescribtion(4, "REGS_Q5_NU_ON");
			m_BinaryDecoder.AddNewBitDescribtion(5, "REGS_RBP_ON");
			m_BinaryDecoder.AddNewBitDescribtion(6, "REGS_K9_ON");
			m_BinaryDecoder.AddNewBitDescribtion(7, "REGS_K10_ON");
			m_BinaryDecoder.AddNewBitDescribtion(8, "REGS_K11_ON");
			m_BinaryDecoder.AddNewBitDescribtion(9, "REGS_SET_ON_KEY");
			m_BinaryDecoder.AddNewBitDescribtion(10, "REGS_SET_OFF_KEY");
			m_BinaryDecoder.AddNewBitDescribtion(11, "REGS_KS_ON");
			
			AddProtocolParam(new ProtocolParam(38,		"NumberBlock"));
			AddProtocolParam(new ProtocolParam(36,37,	"ErrorWork_LO", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(34,35,	"ErrorWork_HI", ProtocolParam.eParamType.TypeBinary));
			
			AddProtocolParam(new ProtocolParam(32,33,	"FSet"));
			AddProtocolParam(new ProtocolParam(30,31,	"FLine"));
			AddProtocolParam(new ProtocolParam(28,29,	"USet[1]"));
			AddProtocolParam(new ProtocolParam(26,27,	"ULine[1]"));
			AddProtocolParam(new ProtocolParam(24,25,	"ISet[1]"));
			AddProtocolParam(new ProtocolParam(22,23,	"Power"));
			AddProtocolParam(new ProtocolParam(20,21,	"RegS", ProtocolParam.eParamType.TypeBinary));
			AddProtocolParam(new ProtocolParam(18,19,	"DeltaU"));
			AddProtocolParam(new ProtocolParam(16,17,	"StatusSet"));
			AddProtocolParam(new ProtocolParam(15,		"RegimParal"));
			AddProtocolParam(new ProtocolParam(13,14,	"AdFaza"));
			AddProtocolParam(new ProtocolParam(11,12,	"PowerMinus"));
			AddProtocolParam(new ProtocolParam(9,10,	"PowerPlus"));
			AddProtocolParam(new ProtocolParam(6,5,		"RegS_", ProtocolParam.eParamType.TypeBinary));
		}
	}
}
