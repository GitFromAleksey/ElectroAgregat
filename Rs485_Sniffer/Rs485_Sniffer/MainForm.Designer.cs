/*
 * Created by SharpDevelop.
 * User: Admin
 * Date: 27.11.2019
 * Time: 14:54
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace Rs485_Sniffer
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.comboBoxPorts = new System.Windows.Forms.ComboBox();
			this.buttonTest = new System.Windows.Forms.Button();
			this.groupBoxKDG = new System.Windows.Forms.GroupBox();
			this.richTextBoxKDG = new System.Windows.Forms.RichTextBox();
			this.groupBoxKRP = new System.Windows.Forms.GroupBox();
			this.richTextBoxKRP = new System.Windows.Forms.RichTextBox();
			this.groupBoxKOM = new System.Windows.Forms.GroupBox();
			this.richTextBoxKOM = new System.Windows.Forms.RichTextBox();
			this.groupBoxPDU = new System.Windows.Forms.GroupBox();
			this.richTextBoxKSHR = new System.Windows.Forms.RichTextBox();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openLogFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.convertLogToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toXlsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toTxtToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.richTextBoxKSHSN5 = new System.Windows.Forms.RichTextBox();
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.richTextBoxKSHSN6 = new System.Windows.Forms.RichTextBox();
			this.textBoxIncommingData = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.groupBoxKDG.SuspendLayout();
			this.groupBoxKRP.SuspendLayout();
			this.groupBoxKOM.SuspendLayout();
			this.groupBoxPDU.SuspendLayout();
			this.menuStrip1.SuspendLayout();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// comboBoxPorts
			// 
			this.comboBoxPorts.FormattingEnabled = true;
			this.comboBoxPorts.Location = new System.Drawing.Point(12, 48);
			this.comboBoxPorts.Name = "comboBoxPorts";
			this.comboBoxPorts.Size = new System.Drawing.Size(121, 21);
			this.comboBoxPorts.TabIndex = 0;
			this.comboBoxPorts.DropDown += new System.EventHandler(this.ComboBoxPortsDropDown);
			this.comboBoxPorts.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ComboBoxPortsKeyDown);
			// 
			// buttonTest
			// 
			this.buttonTest.Location = new System.Drawing.Point(136, 48);
			this.buttonTest.Name = "buttonTest";
			this.buttonTest.Size = new System.Drawing.Size(93, 23);
			this.buttonTest.TabIndex = 1;
			this.buttonTest.Text = "Открыть порт";
			this.buttonTest.UseVisualStyleBackColor = true;
			this.buttonTest.Click += new System.EventHandler(this.ButtonTestClick);
			// 
			// groupBoxKDG
			// 
			this.groupBoxKDG.Controls.Add(this.richTextBoxKDG);
			this.groupBoxKDG.Location = new System.Drawing.Point(223, 172);
			this.groupBoxKDG.Name = "groupBoxKDG";
			this.groupBoxKDG.Size = new System.Drawing.Size(205, 357);
			this.groupBoxKDG.TabIndex = 2;
			this.groupBoxKDG.TabStop = false;
			this.groupBoxKDG.Text = "БУД";
			// 
			// richTextBoxKDG
			// 
			this.richTextBoxKDG.Location = new System.Drawing.Point(6, 19);
			this.richTextBoxKDG.Name = "richTextBoxKDG";
			this.richTextBoxKDG.Size = new System.Drawing.Size(193, 332);
			this.richTextBoxKDG.TabIndex = 0;
			this.richTextBoxKDG.Text = "";
			// 
			// groupBoxKRP
			// 
			this.groupBoxKRP.Controls.Add(this.richTextBoxKRP);
			this.groupBoxKRP.Location = new System.Drawing.Point(435, 172);
			this.groupBoxKRP.Name = "groupBoxKRP";
			this.groupBoxKRP.Size = new System.Drawing.Size(205, 357);
			this.groupBoxKRP.TabIndex = 3;
			this.groupBoxKRP.TabStop = false;
			this.groupBoxKRP.Text = "КШУ";
			// 
			// richTextBoxKRP
			// 
			this.richTextBoxKRP.Location = new System.Drawing.Point(6, 19);
			this.richTextBoxKRP.Name = "richTextBoxKRP";
			this.richTextBoxKRP.Size = new System.Drawing.Size(193, 332);
			this.richTextBoxKRP.TabIndex = 1;
			this.richTextBoxKRP.Text = "";
			// 
			// groupBoxKOM
			// 
			this.groupBoxKOM.Controls.Add(this.richTextBoxKOM);
			this.groupBoxKOM.Location = new System.Drawing.Point(646, 172);
			this.groupBoxKOM.Name = "groupBoxKOM";
			this.groupBoxKOM.Size = new System.Drawing.Size(205, 357);
			this.groupBoxKOM.TabIndex = 3;
			this.groupBoxKOM.TabStop = false;
			this.groupBoxKOM.Text = "КОМ";
			// 
			// richTextBoxKOM
			// 
			this.richTextBoxKOM.Location = new System.Drawing.Point(6, 19);
			this.richTextBoxKOM.Name = "richTextBoxKOM";
			this.richTextBoxKOM.Size = new System.Drawing.Size(193, 332);
			this.richTextBoxKOM.TabIndex = 1;
			this.richTextBoxKOM.Text = "";
			// 
			// groupBoxPDU
			// 
			this.groupBoxPDU.Controls.Add(this.richTextBoxKSHR);
			this.groupBoxPDU.Location = new System.Drawing.Point(857, 172);
			this.groupBoxPDU.Name = "groupBoxPDU";
			this.groupBoxPDU.Size = new System.Drawing.Size(205, 357);
			this.groupBoxPDU.TabIndex = 3;
			this.groupBoxPDU.TabStop = false;
			this.groupBoxPDU.Text = "КШР";
			// 
			// richTextBoxKSHR
			// 
			this.richTextBoxKSHR.Location = new System.Drawing.Point(6, 19);
			this.richTextBoxKSHR.Name = "richTextBoxKSHR";
			this.richTextBoxKSHR.Size = new System.Drawing.Size(193, 332);
			this.richTextBoxKSHR.TabIndex = 1;
			this.richTextBoxKSHR.Text = "";
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.fileToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(1276, 24);
			this.menuStrip1.TabIndex = 4;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.openToolStripMenuItem,
									this.openLogFolderToolStripMenuItem,
									this.convertLogToolStripMenuItem,
									this.exitToolStripMenuItem});
			this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
			this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
			this.fileToolStripMenuItem.Text = "File";
			// 
			// openToolStripMenuItem
			// 
			this.openToolStripMenuItem.Name = "openToolStripMenuItem";
			this.openToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
			this.openToolStripMenuItem.Text = "Open";
			this.openToolStripMenuItem.Click += new System.EventHandler(this.OpenToolStripMenuItemClick);
			// 
			// openLogFolderToolStripMenuItem
			// 
			this.openLogFolderToolStripMenuItem.Name = "openLogFolderToolStripMenuItem";
			this.openLogFolderToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
			this.openLogFolderToolStripMenuItem.Text = "Open Log Folder";
			this.openLogFolderToolStripMenuItem.Click += new System.EventHandler(this.OpenLogFolderToolStripMenuItemClick);
			// 
			// convertLogToolStripMenuItem
			// 
			this.convertLogToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.toXlsToolStripMenuItem,
									this.toTxtToolStripMenuItem});
			this.convertLogToolStripMenuItem.Name = "convertLogToolStripMenuItem";
			this.convertLogToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
			this.convertLogToolStripMenuItem.Text = "Convert Log";
			// 
			// toXlsToolStripMenuItem
			// 
			this.toXlsToolStripMenuItem.Name = "toXlsToolStripMenuItem";
			this.toXlsToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
			this.toXlsToolStripMenuItem.Text = "To Xls";
			this.toXlsToolStripMenuItem.Click += new System.EventHandler(this.ToXlsToolStripMenuItemClick);
			// 
			// toTxtToolStripMenuItem
			// 
			this.toTxtToolStripMenuItem.Name = "toTxtToolStripMenuItem";
			this.toTxtToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
			this.toTxtToolStripMenuItem.Text = "To Txt";
			// 
			// exitToolStripMenuItem
			// 
			this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
			this.exitToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
			this.exitToolStripMenuItem.Text = "Exit";
			this.exitToolStripMenuItem.Click += new System.EventHandler(this.ExitToolStripMenuItemClick);
			// 
			// openFileDialog1
			// 
			this.openFileDialog1.FileName = "openFileDialog1";
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.richTextBoxKSHSN5);
			this.groupBox1.Location = new System.Drawing.Point(12, 172);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(205, 357);
			this.groupBox1.TabIndex = 5;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "КШСН5";
			// 
			// richTextBoxKSHSN5
			// 
			this.richTextBoxKSHSN5.Location = new System.Drawing.Point(6, 19);
			this.richTextBoxKSHSN5.Name = "richTextBoxKSHSN5";
			this.richTextBoxKSHSN5.Size = new System.Drawing.Size(193, 332);
			this.richTextBoxKSHSN5.TabIndex = 1;
			this.richTextBoxKSHSN5.Text = "";
			// 
			// timer1
			// 
			this.timer1.Enabled = true;
			this.timer1.Interval = 50;
			this.timer1.Tick += new System.EventHandler(this.Timer1Tick);
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.richTextBoxKSHSN6);
			this.groupBox2.Location = new System.Drawing.Point(1068, 172);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(205, 357);
			this.groupBox2.TabIndex = 6;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "КШСН6";
			// 
			// richTextBoxKSHSN6
			// 
			this.richTextBoxKSHSN6.Location = new System.Drawing.Point(6, 19);
			this.richTextBoxKSHSN6.Name = "richTextBoxKSHSN6";
			this.richTextBoxKSHSN6.Size = new System.Drawing.Size(193, 332);
			this.richTextBoxKSHSN6.TabIndex = 1;
			this.richTextBoxKSHSN6.Text = "";
			// 
			// textBoxIncommingData
			// 
			this.textBoxIncommingData.Enabled = false;
			this.textBoxIncommingData.Location = new System.Drawing.Point(12, 552);
			this.textBoxIncommingData.MaxLength = 200;
			this.textBoxIncommingData.Name = "textBoxIncommingData";
			this.textBoxIncommingData.Size = new System.Drawing.Size(1246, 20);
			this.textBoxIncommingData.TabIndex = 7;
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(12, 532);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(121, 17);
			this.label1.TabIndex = 8;
			this.label1.Text = "Поток сырых данных:";
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1276, 584);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.textBoxIncommingData);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.groupBoxKOM);
			this.Controls.Add(this.groupBoxPDU);
			this.Controls.Add(this.groupBoxKRP);
			this.Controls.Add(this.groupBoxKDG);
			this.Controls.Add(this.buttonTest);
			this.Controls.Add(this.comboBoxPorts);
			this.Controls.Add(this.menuStrip1);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "MainForm";
			this.Text = "Rs485_Sniffer ED(150+100)-T400-3RA_DIAF.565612.002";
			this.Load += new System.EventHandler(this.MainFormLoad);
			this.groupBoxKDG.ResumeLayout(false);
			this.groupBoxKRP.ResumeLayout(false);
			this.groupBoxKOM.ResumeLayout(false);
			this.groupBoxPDU.ResumeLayout(false);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.groupBox1.ResumeLayout(false);
			this.groupBox2.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textBoxIncommingData;
		private System.Windows.Forms.RichTextBox richTextBoxKSHSN6;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.RichTextBox richTextBoxKSHSN5;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.ToolStripMenuItem openLogFolderToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem toTxtToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem toXlsToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem convertLogToolStripMenuItem;
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.RichTextBox richTextBoxKSHR;
		private System.Windows.Forms.RichTextBox richTextBoxKOM;
		private System.Windows.Forms.RichTextBox richTextBoxKRP;
		private System.Windows.Forms.RichTextBox richTextBoxKDG;
		private System.Windows.Forms.GroupBox groupBoxPDU;
		private System.Windows.Forms.GroupBox groupBoxKOM;
		private System.Windows.Forms.GroupBox groupBoxKRP;
		private System.Windows.Forms.GroupBox groupBoxKDG;
		private System.Windows.Forms.Button buttonTest;
		private System.Windows.Forms.ComboBox comboBoxPorts;
	}
}
