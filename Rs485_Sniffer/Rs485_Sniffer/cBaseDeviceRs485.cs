/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 03.12.2019
 * Time: 12:34
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Drawing;
using System.Runtime.Remoting.Messaging;
using System.Windows.Forms;
using System.Collections.Generic;

namespace Rs485_Sniffer
{

	public class ProtocolParam
	{
		public enum eParamType
		{
			TypeDecimal,
			TypeHex,
			TypeBinary
		}

		public int HiByteNumber;
		public int LoByteNumber;
		public string Describtion;
		public int Value;
		public eParamType ParamType;

		
		public ProtocolParam(int loByteNum, string desc)
		{
			HiByteNumber = -1;
			LoByteNumber = loByteNum;
			Describtion = desc;
			Value = -1;
			ParamType = eParamType.TypeDecimal;
		}		
		
		public ProtocolParam(int hiByteNum, int loByteNum, string desc)
		{
			HiByteNumber = hiByteNum;
			LoByteNumber = loByteNum;
			Describtion = desc;
			Value = -1;
			ParamType = eParamType.TypeDecimal;
		}
		
		public ProtocolParam(int loByteNum, string desc, eParamType paramType)
		{
			HiByteNumber = -1;
			LoByteNumber = loByteNum;
			Describtion = desc;
			Value = -1;
			ParamType = paramType;
		}
		
		public ProtocolParam(int hiByteNum, int loByteNum, string desc, eParamType paramType)
		{
			HiByteNumber = hiByteNum;
			LoByteNumber = loByteNum;
			Describtion = desc;
			Value = -1;
			ParamType = paramType;
		}
		
		public string GetDescribtion() { return Describtion; }
		public string GetValue() { return Value.ToString(); }
		
		public string Print()
		{
			string res = Describtion + " [" + HiByteNumber + "," + LoByteNumber + "] = ";
			
			switch(ParamType)
			{
				case eParamType.TypeDecimal:
					res += Value + "\r\n";
					break;
				case eParamType.TypeHex:
					res += "0x" + Value.ToString("X2") + "\r\n";
					break;
				case eParamType.TypeBinary:
					res += "0b" + Convert.ToString(Value, 2) + "\r\n";
					break;
				default:
					res += Value + "\r\n";
					break;					
			}
			return res;
		}
	}
	/// <summary>
	/// базовый класс для всех устройств шины Rs485
	/// </summary>
	public class cBaseDeviceRs485 : IObserver<byte[]>, IObservable<Dictionary<string,string>>
	{
		protected int DeviceNumber;
		protected string DeviceName;
		protected List<ProtocolParam> paramList;
		protected cBinaryDecoder m_BinaryDecoder;
		private RichTextBox m_Rtb;
		private List<IObserver<Dictionary<string,string>>> observers;
		 

		internal class Unsubscriber<list> : IDisposable
		{
		   private List<IObserver<list>> _observers;
		   private IObserver<list> _observer;
		
		   internal Unsubscriber(List<IObserver<list>> observers, IObserver<list> observer)
		   {
		      this._observers = observers;
		      this._observer = observer;
		   }
		
		   public void Dispose() 
		   {
		      if (_observers.Contains(_observer))
		         _observers.Remove(_observer);
		   }
		}
		
		public cBaseDeviceRs485()
		{
			paramList = new List<ProtocolParam>();
			observers = new List<IObserver<Dictionary<string,string>>>();
		}
		
		public void ParseParamsFromRowData(byte[] data)
		{
//			byte[] _data = new byte[data.Length];
//			for(int i = 0; i < data.Length; ++i)
//				_data[i] = data[data.Length - (i+1)];
//
//			foreach(ProtocolParam pm in paramList)
//			{
//				// TODO обязанность по вытаскиванию параметров из сырых данных лучше отдать классу ProtocolParam
//				if(pm.HiByteNumber == -1)
//				{
//					pm.Value = _data[pm.LoByteNumber+1];
//				}
//				else
//				{
//					pm.Value = (_data[pm.HiByteNumber+1]<<8) | _data[pm.LoByteNumber+1];
//				}
//			}
			int dataBytesLen = 40; // это количество принятых байт должно быть равно MAX_BYTES_COUNT из PacketDetector
			foreach(ProtocolParam pm in paramList)
			{
				// TODO обязанность по вытаскиванию параметров из сырых данных лучше отдать классу ProtocolParam
				if(pm.HiByteNumber == -1)
				{
					pm.Value = data[dataBytesLen-pm.LoByteNumber];// TODO массив данных лучше бы развернуть перед расшифровкой
				}
				else
				{
					pm.Value = (data[dataBytesLen-pm.HiByteNumber]<<8) | data[dataBytesLen-pm.LoByteNumber];
				}
			}
		}
		
		public void AddProtocolParam(ProtocolParam pp)
		{
			if(paramList == null) return;
			if(pp == null) return;
			paramList.Add(pp);
		}
		
		public void AddRichTexBox(RichTextBox rtb)
		{
			this.m_Rtb = rtb;
		}
		
		public void PrintText(string text)
		{
			string res = "";

			if(this.m_Rtb == null)
				return;

			foreach(ProtocolParam pm in paramList)
			{
				res += pm.Print();
				
			}

//			if(m_BinaryDecoder != null)
//				res += m_BinaryDecoder.PrintAll((UInt32)11);
			
			if(m_Rtb.InvokeRequired)
			{
				m_Rtb.BeginInvoke(new Action(() => m_Rtb.Text = DeviceName + ":\r\n" + res));
			}
		}
		
		public virtual void OnNext(byte[] b)
		{
			if(b[2] == DeviceNumber)
			{
				ParseParamsFromRowData(b);
				PrintText("data");
				SendToObservers();
			}
		}
		
		private void SendToObservers()
		{
			Dictionary<string,string> _params = new Dictionary<string, string>();
			
			_params.Add("DeviceName", DeviceName);
			
			foreach(ProtocolParam par in paramList)
			{
				_params.Add(par.GetDescribtion(),par.GetValue());
			}
			
			foreach(IObserver<Dictionary<string,string>> obs in observers)
			{
				obs.OnNext(_params);
			}			
		}
		
		public virtual void OnCompleted(){}
		
		public virtual void OnError(Exception ex){}
		
		public IDisposable Subscribe(IObserver<Dictionary<string,string>> observer)
		{
			if(!observers.Contains(observer))
			{
				observers.Add(observer);
			}
			
			return new Unsubscriber<Dictionary<string,string>>(observers, observer);
		}
	}
}
