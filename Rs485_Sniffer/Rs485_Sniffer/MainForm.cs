/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 27.11.2019
 * Time: 14:54
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;
using Microsoft.Office.Interop.Excel;
using Excel = Microsoft.Office.Interop.Excel;

namespace Rs485_Sniffer
{
	/// <summary>
	/// Description of MainForm.
	/// </summary>
	public partial class MainForm : Form
	{
		SerialPortAdmin spe;
		sPort port;
		PacketDetector packetDetector;
		List<cBaseDeviceRs485> devices_rs485;
		JsonLogger json_logger;
		cBytesLogger byteLogger;
		private LogConverter m_LogConverter;
		
//		Device kdg;
//		Device krp;
//		Device kom;
//		Device pdu;
		
		
		public MainForm()
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			
			//
			//comboBoxPorts.Items.AddRange(SerialPortExchange.GetPortNames());
			spe = new SerialPortAdmin();
			
			
			packetDetector = new PacketDetector();
			devices_rs485 = new List<cBaseDeviceRs485>();
			
			json_logger = new JsonLogger();
			byteLogger = new cBytesLogger();
			
			this.richTextBoxKDG.TextChanged += new System.EventHandler(this.RichTextBoxTextChanged);
			this.richTextBoxKRP.TextChanged += new System.EventHandler(this.RichTextBoxTextChanged);
			this.richTextBoxKOM.TextChanged += new System.EventHandler(this.RichTextBoxTextChanged);
			this.richTextBoxKSHR.TextChanged += new System.EventHandler(this.RichTextBoxTextChanged);
			this.richTextBoxKSHSN5.TextChanged += new System.EventHandler(this.RichTextBoxTextChanged);
			this.richTextBoxKSHSN6.TextChanged += new System.EventHandler(this.RichTextBoxTextChanged);
			
			devices_rs485.Add(new BUD4(richTextBoxKDG));
			devices_rs485.Add(new KSHU(richTextBoxKRP));
			devices_rs485.Add(new KOM(richTextBoxKOM));
			devices_rs485.Add(new KSHR(richTextBoxKSHR));
			devices_rs485.Add(new KSHSN5(richTextBoxKSHSN5));
			// devices.Add(new KSHSN6(richTextBoxKSHSN6)); // TODO (ПО вылетает с ошибкой т.к. длина пакета 80 байт)раскомментировать когда включен в сеть КШСН6 - ПДУ
			
			foreach(cBaseDeviceRs485 dev in devices_rs485)
			{
				packetDetector.Subscribe(dev);
				dev.Subscribe(json_logger);
			}
			
//			packetDetector.Subscribe(new KDG(richTextBoxKDG));
//			packetDetector.Subscribe(new KDG(richTextBoxKRP));
//			packetDetector.Subscribe(new KDG(richTextBoxKOM));
//			packetDetector.Subscribe(new KDG(richTextBoxPDU));
		}
		
		void MainFormLoad(object sender, EventArgs e)
		{
			
		}
		
		void ComboBoxPortsKeyDown(object sender, KeyEventArgs e)
		{
//			sPort port = null;
			
			if(e.KeyData == Keys.Enter)
			{
//				port = spe.GetPortInstance(comboBoxPorts.Text);
//				port.Subscribe(packetDetector);
//				port.Subscribe(byteLogger);
//				port.OpenPort();
//				comboBoxPorts.Enabled = false;
				
				buttonTest.PerformClick();
			}
		}
		void ComboBoxPortsDropDown(object sender, EventArgs e)
		{
			comboBoxPorts.Items.Clear();
			comboBoxPorts.Items.AddRange(spe.GetAvailabelPortNames().ToArray());
		}

		void OpenToolStripMenuItemClick(object sender, EventArgs e)
		{
			openFileDialog1.InitialDirectory = json_logger.GetLogDirectory();

			if(openFileDialog1.ShowDialog() == DialogResult.OK)
			{
				if(m_LogConverter == null)
					m_LogConverter = new LogConverter(openFileDialog1.FileName);
				else
					m_LogConverter.SetFile(openFileDialog1.FileName);
			}
		}

		void ToXlsToolStripMenuItemClick(object sender, EventArgs e)
		{
			if(m_LogConverter == null) return;
			
			m_LogConverter.ConvertLogToXls();
		}
		
		void ButtonTestClick(object sender, EventArgs e)
		{
			sPort port = null;
			
			port = spe.GetPortInstance(comboBoxPorts.Text);
			if(port == null)return;
			
			if(!port._IsAvailabel) return;
			
			if(!port.IsPortOpen())
			{
				port.Subscribe(packetDetector);
				port.Subscribe(byteLogger);
				port.OpenPort();
				comboBoxPorts.Enabled = false;
				buttonTest.Text = "Закрыть порт";
			}
			else
			{
				port.ClosePort();
				comboBoxPorts.Enabled = true;
				buttonTest.Text = "Открыть порт";
			}
		}

		void OpenLogFolderToolStripMenuItemClick(object sender, EventArgs e)
		{
			System.Diagnostics.Process.Start("explorer.exe", json_logger.GetLogDirectory());
		}
		
		void ExitToolStripMenuItemClick(object sender, EventArgs e)
		{
			Close();
		}

		
		void RichTextBoxTextChanged(object sender, EventArgs e)
		{
			timer1.Stop();
			((RichTextBox)sender).BackColor = Color.White;
			timer1.Start();
		}
		
		void Timer1Tick(object sender, EventArgs e)
		{
			richTextBoxKDG.BackColor = Color.LightGray;
			richTextBoxKOM.BackColor = Color.LightGray;
			richTextBoxKRP.BackColor = Color.LightGray;
			richTextBoxKSHR.BackColor = Color.LightGray;
			richTextBoxKSHSN5.BackColor = Color.LightGray;
			richTextBoxKSHSN6.BackColor = Color.LightGray;
			
			// добавление данных в строку вывода сырых данных, а затем удаление лишних первых символов
			textBoxIncommingData.Text += byteLogger.GetIncommingDataInString();;
			int syting_len_to_delete = textBoxIncommingData.Text.Length - textBoxIncommingData.MaxLength;
			if(syting_len_to_delete > 0)
				textBoxIncommingData.Text = textBoxIncommingData.Text.Remove(0,syting_len_to_delete);
			else if(textBoxIncommingData.Text.Length > 0)
				textBoxIncommingData.Text = textBoxIncommingData.Text.Remove(0,2);
			
		}
		

	}
}
