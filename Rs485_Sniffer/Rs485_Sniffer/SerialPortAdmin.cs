/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 27.11.2019
 * Time: 14:20
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO.Ports;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of Class1.
	/// </summary>
	public class SerialPortAdmin
	{	
		private Dictionary<string, sPort> m_SerialPorts;
		
		public SerialPortAdmin()
		{
			string[] portNames = SerialPort.GetPortNames();
			
			m_SerialPorts = new Dictionary<string, sPort>();
			
			foreach(string portName in portNames)
			{
				m_SerialPorts.Add(portName, new sPort(portName));
			}
		}
		
		public List<string> GetAvailabelPortNames()
		{
			List<string> res = new List<string>();
			
			foreach(KeyValuePair<string, sPort> kv in m_SerialPorts)
			{
				if(kv.Value._IsAvailabel)
				{
					res.Add(kv.Key);
				}
			}
			
			return res;
		}
		
		public sPort GetPortInstance(string portName)
		{
			if(m_SerialPorts.ContainsKey(portName))
			{
				return (m_SerialPorts[portName]);
			}
			else
			{
				return null;
			}
		}

		public bool IsPortOpen(sPort port)
		{
			return port.IsPortOpen();
		}
	}
}
