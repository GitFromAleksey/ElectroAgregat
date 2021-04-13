/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 03.12.2019
 * Time: 8:28
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO.Ports;
using System.Collections.Generic;


namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of sPort.
	/// </summary>
	public class sPort : IObservable<byte>
	{
		internal class Unsubscriber<Byte> : IDisposable
		{
		   private List<IObserver<Byte>> _observers;
		   private IObserver<Byte> _observer;
		
		   internal Unsubscriber(List<IObserver<Byte>> observers, IObserver<Byte> observer)
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
				
		private List<IObserver<byte>> observers;
		
		public SerialPort _SerialPort;
		public string _Describtion;
		public bool _IsAvailabel;
		
		public sPort(string portName)
		{
			observers = new List<IObserver<byte>>();
			
			_Describtion = "";
			_SerialPort = new SerialPort(portName);
			_SerialPort.Parity = Parity.Even;// None;
			_SerialPort.BaudRate = 9600;
			_IsAvailabel = CheckPortAvailabel();
			_SerialPort.DataReceived += new SerialDataReceivedEventHandler(_SerialPort_DataReceived);
		}

		void _SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
		{
			if(!_SerialPort.IsOpen) return;
			
			while(_SerialPort.BytesToRead > 0)
			{
				byte b = (byte)_SerialPort.ReadByte();
				foreach(IObserver<byte> obs in observers)
				{
					obs.OnNext(b);
				}
			}
		}
		
		public IDisposable Subscribe(IObserver<byte> observer)
		{
			if(!observers.Contains(observer))
			{
				observers.Add(observer);
			}
			
			return new Unsubscriber<byte>(observers, observer);
		}

		public void OpenPort()
		{
			if(_IsAvailabel && !_SerialPort.IsOpen)
				_SerialPort.Open();
		}
		
		public void ClosePort()
		{
			observers.Clear();
			if(_IsAvailabel && _SerialPort.IsOpen)
				_SerialPort.Close();
		}
		
		public void Send(byte[] data)
		{
			if(!_IsAvailabel)
				return;
			if(!_SerialPort.IsOpen)
				_SerialPort.Open();
			_SerialPort.Write(data, 0, data.Length);
		}
		
		public bool IsPortOpen()
		{
			return _SerialPort.IsOpen;
		}
		
		bool CheckPortAvailabel()
		{
			bool availabel = true;
			SerialPort _sp = _SerialPort;
			
			try
			{
				_sp.Open();
			}
			catch(Exception ex)
			{
				//MessageBox.Show(ex.Message);
				availabel = false;
			}
			finally
			{
				if(availabel)
					_sp.Close();
			}
			return availabel;
		}

	}
}
