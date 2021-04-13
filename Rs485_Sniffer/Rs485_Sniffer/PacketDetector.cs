/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 03.12.2019
 * Time: 8:53
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of PacketDetector.
	/// </summary>
	public class PacketDetector : IObserver<byte>, IObservable<byte[]>
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
		
		private List<IObserver<byte[]>> observers;
		private int m_bytesCounter;
		private const int MAX_BYTES_COUNT = 42;
		private byte[] m_rxBytesBuf;
		
		public PacketDetector()
		{
			m_bytesCounter = 0;
			
			m_rxBytesBuf = new byte[MAX_BYTES_COUNT];
			observers = new List<IObserver<byte[]>>();
		}
		
		bool rx = false;
		private void func(byte b)
		{
			if(!rx)
			{
				if( (b == 0xFF) && (m_rxBytesBuf[0] != 0xFF) )
				{
					m_rxBytesBuf[0] = 0xFF;
				}
				else if( (b == 0xFF) && (m_rxBytesBuf[0] == 0xFF) )
				{
					m_rxBytesBuf[1] = 0xFF;
					m_bytesCounter = 2;
					rx = true;
				}
				return;
			}
			
			m_rxBytesBuf[m_bytesCounter++] = b;
			
			if(m_bytesCounter >= MAX_BYTES_COUNT)
			{
				foreach(IObserver<byte[]> obs in observers)
				{
					obs.OnNext(m_rxBytesBuf);
				}

				for(int i = 0; i < m_rxBytesBuf.Length; ++i)
					m_rxBytesBuf[i] = 0;

				m_bytesCounter = 0;
				rx = false;
			}
		}
		
		
		public virtual void OnNext(byte b)
		{
			func(b);
//			m_rxBytesBuf[m_bytesCounter] = b;
//			++m_bytesCounter;
//			
//			if(m_bytesCounter >= MAX_BYTES_COUNT)
//			{
////				m_bytesCounter = 0;
//
//				// TODO нужно добавить проверку CRC. И вообще нужно переписать, так как алгоритм выделения пакета хреновенько работает.
//				
//				if( ((m_rxBytesBuf[0]<<8)|(m_rxBytesBuf[1])) != 0xFFFF)
//				{
//					m_bytesCounter = 0;
//					return;
//				}
//				
//				foreach(IObserver<byte[]> obs in observers)
//				{
//					obs.OnNext(m_rxBytesBuf);
//				}
//
//				for(int i = 0; i < m_rxBytesBuf.Length; ++i)
//					m_rxBytesBuf[i] = 0;
//
//				m_bytesCounter = 0;
//			}
//			
//			if(m_bytesCounter > 1)
//			{
//				int first = m_rxBytesBuf[m_bytesCounter-2];
//				int second = m_rxBytesBuf[m_bytesCounter-1];
//				
//				if(first == 255)
//				{
//					if(second == 255)
//					{
//						for(int i = 0; i < m_rxBytesBuf.Length; ++i)
//							m_rxBytesBuf[i] = 0;
//						
//						m_rxBytesBuf[0] = m_rxBytesBuf[1] = 0xFF;
//						m_bytesCounter = 2;
//					}
//				}
//			}
		}
		
		public IDisposable Subscribe(IObserver<byte[]> observer)
		{
			if(!observers.Contains(observer))
			{
				observers.Add(observer);
			}
			
			return new Unsubscriber<byte[]>(observers, observer);
		}
		
		public virtual void OnCompleted()
		{
			
		}
		
		public virtual void OnError(Exception ex)
		{
			
		}
		
	}
}
