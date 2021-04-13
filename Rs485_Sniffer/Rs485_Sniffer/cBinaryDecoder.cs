/*
 * Created by SharpDevelop.
 * User: borzenkov
 * Date: 26.09.2020
 * Time: 10:22
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using System.Security.Cryptography.X509Certificates;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of cBinaryDecoder.
	/// </summary>
	public class cBinaryDecoder
	{
		public string m_Name;
		private Dictionary<int, string> m_BitsDictonary;
		
		public cBinaryDecoder(string name)
		{
			m_Name = name;
			m_BitsDictonary = new Dictionary<int, string>();
		}
		
		public bool AddNewBitDescribtion(int bitNumber, string describtion)
		{
			if(m_BitsDictonary.ContainsKey(bitNumber))
				return false;
			
			m_BitsDictonary.Add(bitNumber, describtion);
			
			return true;
		}
		
		public string PrinOneBit(int bitNumber, UInt32 word)
		{
			string res = "bit:" + bitNumber + ", ";
			string val = "null";
			
			if(m_BitsDictonary.TryGetValue(bitNumber, out val))
				res += val + ":" + (word & (1<<bitNumber));
			
			return val;
		}
		
		public string PrintAll(UInt32 word)
		{
			string res = "";
			
			for(int i = 0; i < (sizeof(UInt32)*8); ++i)
			{
				res += PrinOneBit(i, word);
			}
			
			return res;
		}
	}
}
