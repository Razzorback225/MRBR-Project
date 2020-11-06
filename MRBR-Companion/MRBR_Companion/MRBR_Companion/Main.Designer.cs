namespace MRBR_Companion
{
    partial class Main
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.SerialPortCB = new System.Windows.Forms.ComboBox();
            this.SerialGB = new System.Windows.Forms.GroupBox();
            this.connectBtn = new System.Windows.Forms.Button();
            this.RefreshBtn = new System.Windows.Forms.Button();
            this.SerialPort = new System.IO.Ports.SerialPort(this.components);
            this.TabControl = new System.Windows.Forms.TabControl();
            this.ControlsTab = new System.Windows.Forms.TabPage();
            this.TrainControlsGB = new System.Windows.Forms.GroupBox();
            this.EmBreakBtn = new System.Windows.Forms.PictureBox();
            this.TrackCB = new System.Windows.Forms.ComboBox();
            this.ReverseDirBtn = new System.Windows.Forms.PictureBox();
            this.FwdInd = new System.Windows.Forms.PictureBox();
            this.BcwdInd = new System.Windows.Forms.PictureBox();
            this.SpeedIndicGB = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.SpeedLabel = new System.Windows.Forms.Label();
            this.SpeedControl = new System.Windows.Forms.TrackBar();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.TrLgtCB = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            this.SwCtrlGB = new System.Windows.Forms.GroupBox();
            this.SwNameCB = new System.Windows.Forms.ComboBox();
            this.GoStrBtn = new System.Windows.Forms.Button();
            this.ConsoleTab = new System.Windows.Forms.TabPage();
            this.SendCmdBtn = new System.Windows.Forms.Button();
            this.CommandInputBox = new System.Windows.Forms.TextBox();
            this.Shell = new System.Windows.Forms.TextBox();
            this.LayoutTab = new System.Windows.Forms.TabPage();
            this.LayoutMapBox = new System.Windows.Forms.PictureBox();
            this.SettingsTab = new System.Windows.Forms.TabPage();
            this.SerialGB.SuspendLayout();
            this.TabControl.SuspendLayout();
            this.ControlsTab.SuspendLayout();
            this.TrainControlsGB.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.EmBreakBtn)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ReverseDirBtn)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.FwdInd)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BcwdInd)).BeginInit();
            this.SpeedIndicGB.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SpeedControl)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SwCtrlGB.SuspendLayout();
            this.ConsoleTab.SuspendLayout();
            this.LayoutTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LayoutMapBox)).BeginInit();
            this.SuspendLayout();
            // 
            // SerialPortCB
            // 
            this.SerialPortCB.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SerialPortCB.FormattingEnabled = true;
            this.SerialPortCB.Location = new System.Drawing.Point(6, 19);
            this.SerialPortCB.Name = "SerialPortCB";
            this.SerialPortCB.Size = new System.Drawing.Size(245, 32);
            this.SerialPortCB.TabIndex = 0;
            // 
            // SerialGB
            // 
            this.SerialGB.BackColor = System.Drawing.Color.White;
            this.SerialGB.Controls.Add(this.connectBtn);
            this.SerialGB.Controls.Add(this.RefreshBtn);
            this.SerialGB.Controls.Add(this.SerialPortCB);
            this.SerialGB.Dock = System.Windows.Forms.DockStyle.Top;
            this.SerialGB.Location = new System.Drawing.Point(0, 0);
            this.SerialGB.Name = "SerialGB";
            this.SerialGB.Size = new System.Drawing.Size(824, 64);
            this.SerialGB.TabIndex = 1;
            this.SerialGB.TabStop = false;
            this.SerialGB.Text = "Serial ports";
            // 
            // connectBtn
            // 
            this.connectBtn.BackColor = System.Drawing.Color.White;
            this.connectBtn.FlatAppearance.BorderColor = System.Drawing.Color.White;
            this.connectBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.connectBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.connectBtn.Location = new System.Drawing.Point(373, 17);
            this.connectBtn.Name = "connectBtn";
            this.connectBtn.Size = new System.Drawing.Size(120, 34);
            this.connectBtn.TabIndex = 2;
            this.connectBtn.Text = "CONNECT";
            this.connectBtn.UseVisualStyleBackColor = false;
            this.connectBtn.Click += new System.EventHandler(this.connectBtn_Click);
            // 
            // RefreshBtn
            // 
            this.RefreshBtn.BackColor = System.Drawing.Color.White;
            this.RefreshBtn.FlatAppearance.BorderColor = System.Drawing.Color.White;
            this.RefreshBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.RefreshBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RefreshBtn.Location = new System.Drawing.Point(257, 17);
            this.RefreshBtn.Name = "RefreshBtn";
            this.RefreshBtn.Size = new System.Drawing.Size(110, 34);
            this.RefreshBtn.TabIndex = 1;
            this.RefreshBtn.Text = "REFRESH";
            this.RefreshBtn.UseVisualStyleBackColor = false;
            this.RefreshBtn.Click += new System.EventHandler(this.RefreshBtn_Click);
            // 
            // SerialPort
            // 
            this.SerialPort.BaudRate = 115200;
            this.SerialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort_DataReceived);
            // 
            // TabControl
            // 
            this.TabControl.Controls.Add(this.ControlsTab);
            this.TabControl.Controls.Add(this.ConsoleTab);
            this.TabControl.Controls.Add(this.LayoutTab);
            this.TabControl.Controls.Add(this.SettingsTab);
            this.TabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TabControl.Location = new System.Drawing.Point(0, 64);
            this.TabControl.Name = "TabControl";
            this.TabControl.SelectedIndex = 0;
            this.TabControl.Size = new System.Drawing.Size(824, 377);
            this.TabControl.TabIndex = 2;
            this.TabControl.Selected += new System.Windows.Forms.TabControlEventHandler(this.tabControl_Selected);
            // 
            // ControlsTab
            // 
            this.ControlsTab.Controls.Add(this.TrainControlsGB);
            this.ControlsTab.Controls.Add(this.groupBox1);
            this.ControlsTab.Controls.Add(this.SwCtrlGB);
            this.ControlsTab.Location = new System.Drawing.Point(4, 22);
            this.ControlsTab.Name = "ControlsTab";
            this.ControlsTab.Padding = new System.Windows.Forms.Padding(3);
            this.ControlsTab.Size = new System.Drawing.Size(816, 351);
            this.ControlsTab.TabIndex = 0;
            this.ControlsTab.Text = "Controls";
            this.ControlsTab.UseVisualStyleBackColor = true;
            // 
            // TrainControlsGB
            // 
            this.TrainControlsGB.Controls.Add(this.EmBreakBtn);
            this.TrainControlsGB.Controls.Add(this.TrackCB);
            this.TrainControlsGB.Controls.Add(this.ReverseDirBtn);
            this.TrainControlsGB.Controls.Add(this.FwdInd);
            this.TrainControlsGB.Controls.Add(this.BcwdInd);
            this.TrainControlsGB.Controls.Add(this.SpeedIndicGB);
            this.TrainControlsGB.Controls.Add(this.SpeedControl);
            this.TrainControlsGB.Dock = System.Windows.Forms.DockStyle.Right;
            this.TrainControlsGB.Location = new System.Drawing.Point(579, 3);
            this.TrainControlsGB.Name = "TrainControlsGB";
            this.TrainControlsGB.Size = new System.Drawing.Size(234, 345);
            this.TrainControlsGB.TabIndex = 3;
            this.TrainControlsGB.TabStop = false;
            this.TrainControlsGB.Text = "Train controls";
            // 
            // EmBreakBtn
            // 
            this.EmBreakBtn.Image = ((System.Drawing.Image)(resources.GetObject("EmBreakBtn.Image")));
            this.EmBreakBtn.Location = new System.Drawing.Point(19, 130);
            this.EmBreakBtn.Name = "EmBreakBtn";
            this.EmBreakBtn.Size = new System.Drawing.Size(128, 128);
            this.EmBreakBtn.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.EmBreakBtn.TabIndex = 6;
            this.EmBreakBtn.TabStop = false;
            this.EmBreakBtn.Click += new System.EventHandler(this.EmBreakBtn_Click);
            // 
            // TrackCB
            // 
            this.TrackCB.FormattingEnabled = true;
            this.TrackCB.Location = new System.Drawing.Point(6, 19);
            this.TrackCB.Name = "TrackCB";
            this.TrackCB.Size = new System.Drawing.Size(221, 21);
            this.TrackCB.TabIndex = 2;
            // 
            // ReverseDirBtn
            // 
            this.ReverseDirBtn.Image = ((System.Drawing.Image)(resources.GetObject("ReverseDirBtn.Image")));
            this.ReverseDirBtn.Location = new System.Drawing.Point(60, 294);
            this.ReverseDirBtn.Name = "ReverseDirBtn";
            this.ReverseDirBtn.Size = new System.Drawing.Size(113, 48);
            this.ReverseDirBtn.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.ReverseDirBtn.TabIndex = 5;
            this.ReverseDirBtn.TabStop = false;
            this.ReverseDirBtn.Click += new System.EventHandler(this.EmBreakBtn_Click);
            // 
            // FwdInd
            // 
            this.FwdInd.Image = ((System.Drawing.Image)(resources.GetObject("FwdInd.Image")));
            this.FwdInd.Location = new System.Drawing.Point(179, 294);
            this.FwdInd.Name = "FwdInd";
            this.FwdInd.Size = new System.Drawing.Size(48, 48);
            this.FwdInd.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.FwdInd.TabIndex = 4;
            this.FwdInd.TabStop = false;
            // 
            // BcwdInd
            // 
            this.BcwdInd.Image = ((System.Drawing.Image)(resources.GetObject("BcwdInd.Image")));
            this.BcwdInd.Location = new System.Drawing.Point(6, 294);
            this.BcwdInd.Name = "BcwdInd";
            this.BcwdInd.Size = new System.Drawing.Size(48, 48);
            this.BcwdInd.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.BcwdInd.TabIndex = 3;
            this.BcwdInd.TabStop = false;
            // 
            // SpeedIndicGB
            // 
            this.SpeedIndicGB.Controls.Add(this.label2);
            this.SpeedIndicGB.Controls.Add(this.SpeedLabel);
            this.SpeedIndicGB.Location = new System.Drawing.Point(6, 49);
            this.SpeedIndicGB.Name = "SpeedIndicGB";
            this.SpeedIndicGB.Size = new System.Drawing.Size(170, 75);
            this.SpeedIndicGB.TabIndex = 2;
            this.SpeedIndicGB.TabStop = false;
            this.SpeedIndicGB.Text = "Current Speed";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(97, 16);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 55);
            this.label2.TabIndex = 2;
            this.label2.Text = "%";
            // 
            // SpeedLabel
            // 
            this.SpeedLabel.AutoSize = true;
            this.SpeedLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SpeedLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SpeedLabel.Location = new System.Drawing.Point(3, 16);
            this.SpeedLabel.Name = "SpeedLabel";
            this.SpeedLabel.Size = new System.Drawing.Size(51, 55);
            this.SpeedLabel.TabIndex = 1;
            this.SpeedLabel.Text = "0";
            // 
            // SpeedControl
            // 
            this.SpeedControl.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.SpeedControl.Location = new System.Drawing.Point(182, 49);
            this.SpeedControl.Name = "SpeedControl";
            this.SpeedControl.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.SpeedControl.Size = new System.Drawing.Size(45, 236);
            this.SpeedControl.TabIndex = 0;
            this.SpeedControl.ValueChanged += new System.EventHandler(this.SpeedControl_ValueChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.TrLgtCB);
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Location = new System.Drawing.Point(159, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(147, 117);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Traffic Lights Control";
            // 
            // TrLgtCB
            // 
            this.TrLgtCB.FormattingEnabled = true;
            this.TrLgtCB.Location = new System.Drawing.Point(6, 19);
            this.TrLgtCB.Name = "TrLgtCB";
            this.TrLgtCB.Size = new System.Drawing.Size(134, 21);
            this.TrLgtCB.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(6, 46);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(134, 64);
            this.button1.TabIndex = 1;
            this.button1.Text = "Toggle Traffic Light";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // SwCtrlGB
            // 
            this.SwCtrlGB.Controls.Add(this.SwNameCB);
            this.SwCtrlGB.Controls.Add(this.GoStrBtn);
            this.SwCtrlGB.Location = new System.Drawing.Point(6, 6);
            this.SwCtrlGB.Name = "SwCtrlGB";
            this.SwCtrlGB.Size = new System.Drawing.Size(147, 117);
            this.SwCtrlGB.TabIndex = 0;
            this.SwCtrlGB.TabStop = false;
            this.SwCtrlGB.Text = "Switches Control";
            // 
            // SwNameCB
            // 
            this.SwNameCB.FormattingEnabled = true;
            this.SwNameCB.Location = new System.Drawing.Point(6, 19);
            this.SwNameCB.Name = "SwNameCB";
            this.SwNameCB.Size = new System.Drawing.Size(134, 21);
            this.SwNameCB.TabIndex = 0;
            // 
            // GoStrBtn
            // 
            this.GoStrBtn.Location = new System.Drawing.Point(6, 46);
            this.GoStrBtn.Name = "GoStrBtn";
            this.GoStrBtn.Size = new System.Drawing.Size(134, 64);
            this.GoStrBtn.TabIndex = 1;
            this.GoStrBtn.Text = "Toggle Switch";
            this.GoStrBtn.UseVisualStyleBackColor = true;
            // 
            // ConsoleTab
            // 
            this.ConsoleTab.Controls.Add(this.SendCmdBtn);
            this.ConsoleTab.Controls.Add(this.CommandInputBox);
            this.ConsoleTab.Controls.Add(this.Shell);
            this.ConsoleTab.Location = new System.Drawing.Point(4, 22);
            this.ConsoleTab.Name = "ConsoleTab";
            this.ConsoleTab.Padding = new System.Windows.Forms.Padding(3);
            this.ConsoleTab.Size = new System.Drawing.Size(816, 351);
            this.ConsoleTab.TabIndex = 1;
            this.ConsoleTab.Text = "Console";
            this.ConsoleTab.UseVisualStyleBackColor = true;
            // 
            // SendCmdBtn
            // 
            this.SendCmdBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SendCmdBtn.Location = new System.Drawing.Point(737, 317);
            this.SendCmdBtn.Name = "SendCmdBtn";
            this.SendCmdBtn.Size = new System.Drawing.Size(76, 27);
            this.SendCmdBtn.TabIndex = 2;
            this.SendCmdBtn.Text = "Send";
            this.SendCmdBtn.UseVisualStyleBackColor = true;
            this.SendCmdBtn.Click += new System.EventHandler(this.SendCmdBtn_Click);
            // 
            // CommandInputBox
            // 
            this.CommandInputBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.CommandInputBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.CommandInputBox.Font = new System.Drawing.Font("Lucida Console", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CommandInputBox.Location = new System.Drawing.Point(8, 318);
            this.CommandInputBox.Name = "CommandInputBox";
            this.CommandInputBox.Size = new System.Drawing.Size(728, 27);
            this.CommandInputBox.TabIndex = 1;
            this.CommandInputBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.CommandInputBox_KeyPress);
            // 
            // Shell
            // 
            this.Shell.BackColor = System.Drawing.Color.Black;
            this.Shell.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Shell.ForeColor = System.Drawing.Color.Green;
            this.Shell.Location = new System.Drawing.Point(2, 7);
            this.Shell.Multiline = true;
            this.Shell.Name = "Shell";
            this.Shell.ReadOnly = true;
            this.Shell.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.Shell.Size = new System.Drawing.Size(811, 304);
            this.Shell.TabIndex = 0;
            // 
            // LayoutTab
            // 
            this.LayoutTab.Controls.Add(this.LayoutMapBox);
            this.LayoutTab.Location = new System.Drawing.Point(4, 22);
            this.LayoutTab.Name = "LayoutTab";
            this.LayoutTab.Padding = new System.Windows.Forms.Padding(3);
            this.LayoutTab.Size = new System.Drawing.Size(816, 351);
            this.LayoutTab.TabIndex = 3;
            this.LayoutTab.Text = "Layout Map";
            this.LayoutTab.UseVisualStyleBackColor = true;
            // 
            // LayoutMapBox
            // 
            this.LayoutMapBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LayoutMapBox.Image = global::MRBR_Companion.Properties.Resources.init_img;
            this.LayoutMapBox.InitialImage = null;
            this.LayoutMapBox.Location = new System.Drawing.Point(3, 3);
            this.LayoutMapBox.Name = "LayoutMapBox";
            this.LayoutMapBox.Size = new System.Drawing.Size(810, 345);
            this.LayoutMapBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.LayoutMapBox.TabIndex = 0;
            this.LayoutMapBox.TabStop = false;
            this.LayoutMapBox.Click += new System.EventHandler(this.LayoutMapBox_Click);
            // 
            // SettingsTab
            // 
            this.SettingsTab.Location = new System.Drawing.Point(4, 22);
            this.SettingsTab.Name = "SettingsTab";
            this.SettingsTab.Padding = new System.Windows.Forms.Padding(3);
            this.SettingsTab.Size = new System.Drawing.Size(816, 351);
            this.SettingsTab.TabIndex = 2;
            this.SettingsTab.Text = "Settings";
            this.SettingsTab.UseVisualStyleBackColor = true;
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(824, 441);
            this.Controls.Add(this.TabControl);
            this.Controls.Add(this.SerialGB);
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "MRBR Companion";
            this.SerialGB.ResumeLayout(false);
            this.TabControl.ResumeLayout(false);
            this.ControlsTab.ResumeLayout(false);
            this.TrainControlsGB.ResumeLayout(false);
            this.TrainControlsGB.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.EmBreakBtn)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ReverseDirBtn)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.FwdInd)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BcwdInd)).EndInit();
            this.SpeedIndicGB.ResumeLayout(false);
            this.SpeedIndicGB.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SpeedControl)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.SwCtrlGB.ResumeLayout(false);
            this.ConsoleTab.ResumeLayout(false);
            this.ConsoleTab.PerformLayout();
            this.LayoutTab.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.LayoutMapBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox SerialPortCB;
        private System.Windows.Forms.GroupBox SerialGB;
        private System.Windows.Forms.Button RefreshBtn;
        private System.IO.Ports.SerialPort SerialPort;
        private System.Windows.Forms.Button connectBtn;
        private System.Windows.Forms.TabControl TabControl;
        private System.Windows.Forms.TabPage ControlsTab;
        private System.Windows.Forms.TabPage ConsoleTab;
        private System.Windows.Forms.Button SendCmdBtn;
        private System.Windows.Forms.TextBox CommandInputBox;
        private System.Windows.Forms.TextBox Shell;
        private System.Windows.Forms.TabPage SettingsTab;
        private System.Windows.Forms.TabPage LayoutTab;
        private System.Windows.Forms.PictureBox LayoutMapBox;
        private System.Windows.Forms.GroupBox SwCtrlGB;
        private System.Windows.Forms.ComboBox SwNameCB;
        private System.Windows.Forms.Button GoStrBtn;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox TrLgtCB;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox TrainControlsGB;
        private System.Windows.Forms.GroupBox SpeedIndicGB;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label SpeedLabel;
        private System.Windows.Forms.TrackBar SpeedControl;
        private System.Windows.Forms.PictureBox ReverseDirBtn;
        private System.Windows.Forms.PictureBox FwdInd;
        private System.Windows.Forms.PictureBox BcwdInd;
        private System.Windows.Forms.ComboBox TrackCB;
        private System.Windows.Forms.PictureBox EmBreakBtn;
    }
}

