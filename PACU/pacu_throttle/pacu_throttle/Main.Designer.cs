namespace pacu_throttle
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
            this.sp1 = new System.IO.Ports.SerialPort(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.connectBtn = new System.Windows.Forms.Button();
            this.portsCombo = new System.Windows.Forms.ComboBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.spdBar = new System.Windows.Forms.TrackBar();
            this.thrLbl = new System.Windows.Forms.Label();
            this.spdInfoGB = new System.Windows.Forms.GroupBox();
            this.percTxb = new System.Windows.Forms.TextBox();
            this.percLbl = new System.Windows.Forms.Label();
            this.refreshBtn = new System.Windows.Forms.Button();
            this.logTxb = new System.Windows.Forms.TextBox();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.spdBar)).BeginInit();
            this.spdInfoGB.SuspendLayout();
            this.SuspendLayout();
            // 
            // sp1
            // 
            this.sp1.BaudRate = 115200;
            this.sp1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.sp1_DataReceived);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.refreshBtn);
            this.panel1.Controls.Add(this.connectBtn);
            this.panel1.Controls.Add(this.portsCombo);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(354, 60);
            this.panel1.TabIndex = 0;
            // 
            // connectBtn
            // 
            this.connectBtn.Dock = System.Windows.Forms.DockStyle.Right;
            this.connectBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.connectBtn.Location = new System.Drawing.Point(81, 21);
            this.connectBtn.Name = "connectBtn";
            this.connectBtn.Size = new System.Drawing.Size(273, 39);
            this.connectBtn.TabIndex = 1;
            this.connectBtn.Text = "Connect";
            this.connectBtn.UseVisualStyleBackColor = true;
            this.connectBtn.Click += new System.EventHandler(this.connectBtn_Click);
            // 
            // portsCombo
            // 
            this.portsCombo.Dock = System.Windows.Forms.DockStyle.Top;
            this.portsCombo.FormattingEnabled = true;
            this.portsCombo.Location = new System.Drawing.Point(0, 0);
            this.portsCombo.Name = "portsCombo";
            this.portsCombo.Size = new System.Drawing.Size(354, 21);
            this.portsCombo.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.logTxb);
            this.panel2.Controls.Add(this.spdInfoGB);
            this.panel2.Controls.Add(this.spdBar);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 60);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(354, 401);
            this.panel2.TabIndex = 1;
            // 
            // spdBar
            // 
            this.spdBar.BackColor = System.Drawing.Color.DimGray;
            this.spdBar.Dock = System.Windows.Forms.DockStyle.Right;
            this.spdBar.Location = new System.Drawing.Point(309, 0);
            this.spdBar.Name = "spdBar";
            this.spdBar.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.spdBar.Size = new System.Drawing.Size(45, 401);
            this.spdBar.TabIndex = 0;
            this.spdBar.ValueChanged += new System.EventHandler(this.spdBar_ValueChanged);
            // 
            // thrLbl
            // 
            this.thrLbl.AutoSize = true;
            this.thrLbl.Location = new System.Drawing.Point(6, 22);
            this.thrLbl.Name = "thrLbl";
            this.thrLbl.Size = new System.Drawing.Size(132, 20);
            this.thrLbl.TabIndex = 1;
            this.thrLbl.Text = "Throttle Value :";
            // 
            // spdInfoGB
            // 
            this.spdInfoGB.Controls.Add(this.percLbl);
            this.spdInfoGB.Controls.Add(this.percTxb);
            this.spdInfoGB.Controls.Add(this.thrLbl);
            this.spdInfoGB.Dock = System.Windows.Forms.DockStyle.Top;
            this.spdInfoGB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.spdInfoGB.Location = new System.Drawing.Point(0, 0);
            this.spdInfoGB.Name = "spdInfoGB";
            this.spdInfoGB.Size = new System.Drawing.Size(309, 58);
            this.spdInfoGB.TabIndex = 3;
            this.spdInfoGB.TabStop = false;
            this.spdInfoGB.Text = "Throttle Infos";
            // 
            // percTxb
            // 
            this.percTxb.Location = new System.Drawing.Point(144, 19);
            this.percTxb.Name = "percTxb";
            this.percTxb.ReadOnly = true;
            this.percTxb.Size = new System.Drawing.Size(102, 26);
            this.percTxb.TabIndex = 2;
            this.percTxb.Text = "0";
            this.percTxb.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // percLbl
            // 
            this.percLbl.AutoSize = true;
            this.percLbl.Location = new System.Drawing.Point(252, 22);
            this.percLbl.Name = "percLbl";
            this.percLbl.Size = new System.Drawing.Size(24, 20);
            this.percLbl.TabIndex = 3;
            this.percLbl.Text = "%";
            // 
            // refreshBtn
            // 
            this.refreshBtn.Dock = System.Windows.Forms.DockStyle.Left;
            this.refreshBtn.Location = new System.Drawing.Point(0, 21);
            this.refreshBtn.Name = "refreshBtn";
            this.refreshBtn.Size = new System.Drawing.Size(75, 39);
            this.refreshBtn.TabIndex = 2;
            this.refreshBtn.Text = "Refresh";
            this.refreshBtn.UseVisualStyleBackColor = true;
            this.refreshBtn.Click += new System.EventHandler(this.refreshBtn_Click);
            // 
            // logTxb
            // 
            this.logTxb.BackColor = System.Drawing.Color.Black;
            this.logTxb.Dock = System.Windows.Forms.DockStyle.Left;
            this.logTxb.Font = new System.Drawing.Font("Lucida Console", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.logTxb.ForeColor = System.Drawing.Color.Green;
            this.logTxb.Location = new System.Drawing.Point(0, 58);
            this.logTxb.Multiline = true;
            this.logTxb.Name = "logTxb";
            this.logTxb.ReadOnly = true;
            this.logTxb.Size = new System.Drawing.Size(309, 343);
            this.logTxb.TabIndex = 4;
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(354, 461);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PACU Throttle";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Main_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Main_FormClosed);
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.spdBar)).EndInit();
            this.spdInfoGB.ResumeLayout(false);
            this.spdInfoGB.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.IO.Ports.SerialPort sp1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ComboBox portsCombo;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button connectBtn;
        private System.Windows.Forms.TrackBar spdBar;
        private System.Windows.Forms.GroupBox spdInfoGB;
        private System.Windows.Forms.Label thrLbl;
        private System.Windows.Forms.Label percLbl;
        private System.Windows.Forms.TextBox percTxb;
        private System.Windows.Forms.Button refreshBtn;
        private System.Windows.Forms.TextBox logTxb;
    }
}

