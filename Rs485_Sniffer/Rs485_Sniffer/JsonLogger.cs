/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 06.12.2019
 * Time: 16:28
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.Remoting.Messaging;
using System.Text;
using Microsoft.Office.Interop.Excel;
using Newtonsoft.Json;
using Excel = Microsoft.Office.Interop.Excel;

//using System.Runtime.Serialization.Json;




namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of XlsLogger.
	/// </summary>
	public class JsonLogger : IObserver<Dictionary<string,string>>
	{
		private Excel.ApplicationClass m_ExcelApp;
		private Excel.Worksheet m_WorkSheet;
		//private int m_Row;

		private FileInfo m_LogfileInfo;
		
		public JsonLogger()
		{
			m_LogfileInfo = GetLogFileInfo();
				
//			m_Row = 1;
//			m_ExcelApp = (Excel.ApplicationClass)new Excel.Application();
//			m_ExcelApp.Visible = true;
//			m_ExcelApp.Workbooks.Add();
//			m_WorkSheet = (Excel.Worksheet)m_ExcelApp.ActiveSheet;
		}
		
		private FileInfo GetLogFileInfo()
		{
			string logFilePath;
			string logFileName;
			FileInfo logfileInfo = null;
			DateTime dt = DateTime.Now;
			
			logFilePath = Environment.CurrentDirectory;
			logFileName = "log_" + dt.Hour + "_" + dt.Day + "."  + dt.Month + "."  + dt.Year + ".json";
			logFilePath += "\\" + logFileName;
			logfileInfo = new FileInfo(logFilePath);
			
			return logfileInfo;
		}
		
		public string GetLogDirectory()
		{
			return Environment.CurrentDirectory;
		}
		
		public virtual void OnNext(Dictionary<string,string> data)
		{
//			int cell = 1;
//			foreach(KeyValuePair<string, string> kv in data)
//			{
//				m_WorkSheet.Cells[m_Row, cell++] = kv.Key;
//				m_WorkSheet.Cells[m_Row, cell++] = kv.Value;
//			}
//			++m_Row;

			data.Add("DateTime",DateTime.Now.ToString("yyyy-MM-ddTHH:mm:ss.fff"));
			
			string jsonStrSerialized = JsonConvert.SerializeObject(data);

			FileInfo fi = GetLogFileInfo();
			
			if(!fi.Exists)
			{
				fi.Create().Close();
			}			
			
			StreamWriter sw = new StreamWriter(fi.FullName, true);
			sw.WriteLine(jsonStrSerialized);
			sw.Close();
			//Dictionary<string,string> jsonStrDeSerialized = JsonConvert.DeserializeObject<Dictionary<string,string>>(jsonStrSerialized);
		}
		
		public virtual void OnCompleted(){}
		
		public virtual void OnError(Exception ex){}
	}
}

