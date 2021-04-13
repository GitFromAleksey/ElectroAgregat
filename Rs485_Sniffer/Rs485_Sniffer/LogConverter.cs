/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 09.12.2019
 * Time: 12:47
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Collections.Generic;
using Newtonsoft.Json;
using Excel = Microsoft.Office.Interop.Excel;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of LogConverter.
	/// </summary>
	public class LogConverter
	{
		private FileInfo m_LogFile;
		private Excel.ApplicationClass m_ExcelApp;
		private Excel.Worksheet m_WorkSheet;
		private int m_Row;

		public LogConverter()
		{
		}
		
		public LogConverter(string logFileFullName)
		{
			SetFile(logFileFullName);
		}
		
		private void XlsInit()
		{
			m_Row = 1;
			m_ExcelApp = (Excel.ApplicationClass)new Excel.Application();
			m_ExcelApp.Visible = false;
			m_ExcelApp.Workbooks.Add();
			m_WorkSheet = (Excel.Worksheet)m_ExcelApp.ActiveSheet;
		}
		
		public bool SetFile(string logFileFullName)
		{
			bool res = false;

			if((logFileFullName == null) || (logFileFullName == ""))
				return res;	
			
			if(null != m_LogFile)
			{
				if( logFileFullName.Equals(m_LogFile.FullName) )
					return res;
			}
				
			m_LogFile = new FileInfo(logFileFullName);

			res = m_LogFile.Exists;
			
			return res;
		}
		
		public void ConvertLogToXls()
		{
			if(m_LogFile == null)return;
			if(!m_LogFile.Exists)return;
			string jsonStrSerialized;
			Dictionary<string,string> jsonStrDeSerialized;
			StreamReader sr = new StreamReader(m_LogFile.FullName);
			List<List<Dictionary<string,string>>> devices = new List<List<Dictionary<string, string>>>();

			while(!sr.EndOfStream)
			{
				jsonStrSerialized = sr.ReadLine();
				jsonStrDeSerialized = JsonConvert.DeserializeObject<Dictionary<string,string>>(jsonStrSerialized);
				
				if(devices.Count == 0)
				{
					// добавляем логи первого устройства в список
					List<Dictionary<string,string>> dev = new List<Dictionary<string,string>>();
					dev.Add(jsonStrDeSerialized);
					devices.Add(dev);
				}
				else
				{
					// ищем есть ли логи устройства в списке
					bool logContain = false;
					foreach(List<Dictionary<string,string>> dev in devices)
					{
						// идем по списку устройств и смотрим первый элемент каждого списка 
						if(dev[0].ContainsKey("NumberBlock"))
						{
							// если есть логи устройства
							if(dev[0]["NumberBlock"] == jsonStrDeSerialized["NumberBlock"])
							{
								logContain = true;
								// добавляем элемент логов для соответствующего устройства
								dev.Add(jsonStrDeSerialized);
								break;
							}
						}
					}
					// если нет логов устройства, то добавляем список логов для него
					if(!logContain)
					{
						List<Dictionary<string,string>> dev = new List<Dictionary<string,string>>();
						dev.Add(jsonStrDeSerialized);
						devices.Add(dev);
					}
				}
			}
			
			sr.Close();

			XlsInit();
			
			// добавляем листы если не хватает
			while(m_ExcelApp.Worksheets.Count < devices.Count)
				m_ExcelApp.Worksheets.Add();

			// переименовываем листы в соответствии с номерами устройств
//			for(int devNum = 1; devNum <= m_ExcelApp.Worksheets.Count; ++devNum)
//			{
//				Excel.Worksheet wsh = (Excel.Worksheet)m_ExcelApp.Worksheets[devNum];
//				Dictionary<string,string> dict = devices[devNum-1][0];
//				wsh.Name = dict["NumberBlock"];
//			}
			for(int devNum = 0; devNum < devices.Count; ++devNum)
			{
				Excel.Worksheet wsh = (Excel.Worksheet)m_ExcelApp.Worksheets[devNum+1];
				Dictionary<string,string> dict = devices[devNum][0];
				wsh.Name = dict["NumberBlock"];
			}			
			
			// начинаем заполнять таблицу
			foreach(List<Dictionary<string,string>> dev in devices)
			{
				Excel.Worksheet _workSheet = null;
				int cell = 1;
				int row = 1;
				
				// делаем активным тот лист в который пишем
				for(int devNum = 1; devNum <= m_ExcelApp.Worksheets.Count; ++devNum)
				{
					Excel.Worksheet wsh = (Excel.Worksheet)m_ExcelApp.Worksheets[devNum];
					if(wsh.Name == dev[0]["NumberBlock"])
					{
						_workSheet = wsh;
						break;
					}
				}
				
				// заполняем заголовок
				List<string> keys = new List<string>(dev[0].Keys);
				foreach(string key in keys)
				{
					_workSheet.Cells[row, cell++] = key;
				}
				row++;
				// выводим значения под заголовками
				foreach(Dictionary<string,string> entrie in dev)
				{
					cell = 1;
					foreach(KeyValuePair<string,string> keyVal in entrie)
					{
						_workSheet.Cells[row, cell++] = keyVal.Value;
					}
					++row;
				}
			}
			m_ExcelApp.Visible = true;
		}
	}
}
