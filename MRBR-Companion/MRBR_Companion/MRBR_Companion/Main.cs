using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;

namespace MRBR_Companion
{
    public partial class Main : Form
    {
        public Main()
        {
            InitializeComponent();
            refreshPortList();
            EnableConsole(false);
            TabControl.SelectedTab.Text = _previousTab = "ControlsTab";
        }

        string _previousTab;  

        bool _reverseDir = false;

        string _serialBuffer;
        OpenFileDialog loadLayoutDg = new OpenFileDialog();
        private void refreshPortList()
        {
            SerialPortCB.Items.Clear();
            SerialPortCB.Items.AddRange(SerialPort.GetPortNames());
        }

        private void RefreshBtn_Click(object sender, EventArgs e)
        {
            refreshPortList();
        }

        private void connectBtn_Click(object sender, EventArgs e)
        {
            try
            {
                if(!SerialPort.IsOpen)
                {
                    if(SerialPortCB.Text != "")
                    {
                        SerialPort.PortName = SerialPortCB.Text;
                        SerialPort.Open();
                        connectBtn.Size = new Size(145, 34);
                        connectBtn.Text = "DISCONNECT";
                        EnableConsole(true);
                    }
                    else
                    {
                        MessageBox.Show("You need to select a serial port first.\nPlease try again", "Serial port error",MessageBoxButtons.OK,MessageBoxIcon.Error);
                    }
                }
                else
                {
                    SerialPort.Close();
                    connectBtn.Size = new Size(120, 34);
                    connectBtn.Text = "CONNECT";
                }
            }
            catch(IOException ex)
            {
                MessageBox.Show(ex.Message, "Serial port error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void SendCmdBtn_Click(object sender, EventArgs e)
        {
            if(CommandInputBox.Text != string.Empty)
            {
                try
                {
                    SerialPort.WriteLine(CommandInputBox.Text + "#");
                    Shell.Text += "user> " + CommandInputBox.Text + Environment.NewLine;
                    CommandInputBox.Clear();
                }
                catch (IOException ex)
                {
                    MessageBox.Show(ex.Message, "Serial port error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void SerialReturnWrite(object sender, EventArgs arg)
        {
            Shell.Text += _serialBuffer + Environment.NewLine;
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            _serialBuffer = SerialPort.ReadExisting();

            Invoke(new EventHandler(SerialReturnWrite));
        }

        private void EnableConsole(bool enable)
        {
            CommandInputBox.Enabled = enable;
            SendCmdBtn.Enabled = enable;
        }

        private void tabControl_Selected(object sender, TabControlEventArgs e)
        {
            if(TabControl.SelectedTab.Text == "Console")
            {
                if(!SerialPort.IsOpen)
                {
                    EnableConsole(false);
                    MessageBox.Show("To use the console, connect to a device first", "No device connected", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    TabControl.SelectTab(_previousTab);
                }
                else
                {
                    EnableConsole(true);
                    _previousTab = TabControl.SelectedTab.Name;
                }
            }
            else if(TabControl.SelectedTab.Text == "Layout Map")
            {
                MessageBox.Show("This tab is not available yet", "Work in progress", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                LayoutMapBox.Enabled = false;
                TabControl.SelectTab(_previousTab);
            }
            else
            {
                _previousTab = TabControl.SelectedTab.Name;
            }
        }

        private void LayoutMapBox_Click(object sender, EventArgs e)
        {
            if(LayoutMapBox.Image == null)
            {
                loadLayoutDg.InitialDirectory = "c:\\";
                loadLayoutDg.Filter = "Image files (*.jpg; *.bmp; *.png; *.tiff; *.gif; *.img)|*.jpg; *.bmp; *.png; *.tiff; *.gif; *.img";
                loadLayoutDg.Title = "Choose your layout file...";

                if(loadLayoutDg.ShowDialog() == DialogResult.OK)
                {
                    LayoutMapBox.SizeMode = PictureBoxSizeMode.StretchImage;
                    LayoutMapBox.Image = new Bitmap(loadLayoutDg.FileName);
                }
            }
        }

        private void SpeedControl_ValueChanged(object sender, EventArgs e)
        {
            SpeedLabel.Text = (SpeedControl.Value * 10).ToString();
        }

        private async void EmBreakBtn_Click(object sender, EventArgs e)
        {
            ((PictureBox)sender).BackColor = Color.LightGray;
            if(((PictureBox)sender).Name == ReverseDirBtn.Name)
            {
                if (!_reverseDir)
                {
                    _reverseDir = true;
                    FwdInd.Image = new Bitmap("Resources/fwd_arr_empty.png");
                    BcwdInd.Image = new Bitmap("Resources/back_arr.png");
                }
                else
                {
                    _reverseDir = false;
                    FwdInd.Image = new Bitmap("Resources/fwd_arr.png");
                    BcwdInd.Image = new Bitmap("Resources/back_arr_empty.png");
                }
            }
            await Task.Delay(100);
            ((PictureBox)sender).BackColor = Color.White;
        }

        private void CommandInputBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if(e.KeyChar == (char)Keys.Enter)
            {
                Invoke(new EventHandler(SendCmdBtn_Click));
            }
        }
    }
}
