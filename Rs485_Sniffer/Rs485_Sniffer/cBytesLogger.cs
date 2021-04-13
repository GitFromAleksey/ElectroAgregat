/*
 * Created by SharpDevelop.
 * User: borzenkov
 * Date: 01.06.2020
 * Time: 13:48
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Collections.Generic;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of cLogger.
	/// </summary>
	public class cBytesLogger : IObserver<byte>
	{
		private FileInfo m_LogfileInfo;
		private string m_LogFilePath;
		private const uint m_IncommingDataStringMaxLen = 200;
		private Queue<string> m_IncommingDataString; // очередь входящих данных формата ToString("X2")
		
		public cBytesLogger()
		{
			m_LogfileInfo = GetLogFileInfo();
			m_LogFilePath = Environment.CurrentDirectory;
			m_IncommingDataString = new Queue<string>(); // *2 - так как запсь числа текстом занимает 2 символа
		}
		
		private FileInfo GetLogFileInfo()
		{
			string logFilePath;
			string logFileName;
			FileInfo logfileInfo = null;
			DateTime dt = DateTime.Now;
			
			logFilePath = m_LogFilePath;//Environment.CurrentDirectory;
			logFileName = "Byte_log_" + dt.Hour + "_" + dt.Day + "."  + dt.Month + "."  + dt.Year + ".txt";
			logFilePath += "\\" + logFileName;
			logfileInfo = new FileInfo(logFilePath);
			
			return logfileInfo;
		}
		
		public string GetLogPath()
		{
			return m_LogFilePath;
		}
		
		public virtual void OnNext(byte b)
		{
			FileInfo fi = GetLogFileInfo();
			
			if(!fi.Exists)
			{
				fi.Create().Close();
			}			
			
			StreamWriter sw = new StreamWriter(fi.FullName, true);
			string byte_in_string = b.ToString("X2");
			sw.Write(byte_in_string);
//			sw.WriteLine(b.ToString("X2"));
			sw.Close();
			
			if(m_IncommingDataString.Count < m_IncommingDataStringMaxLen) // ограничение по максимальному количеству элементов в очереди
				m_IncommingDataString.Enqueue(byte_in_string);

		}
		
		public virtual void OnCompleted()
		{
			
		}
		
		public virtual void OnError(Exception ex)
		{
			
		}
		
		public string GetIncommingDataInString()
		{
			string str = "";
			
			while(m_IncommingDataString.Count > 0)
			{
				str += m_IncommingDataString.Dequeue();
			}
			
			return str;
		}

	}
}
