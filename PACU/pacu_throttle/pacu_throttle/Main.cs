using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;

namespace pacu_throttle
{
    public partial class Main : Form
    {
        bool port_is_open = false;

        public Main()
        {
            InitializeComponent();
            port_is_open = sp1.IsOpen;
            refreshPorts();
        }

        private void refreshPorts()
        {
            portsCombo.Items.Clear();
            portsCombo.Items.AddRange(SerialPort.GetPortNames());
        }

        private void spdBar_ValueChanged(object sender, EventArgs e)
        {
            int val = spdBar.Value * 10;

            percTxb.Text = val.ToString();

            if (port_is_open)
            {
                sp1.WriteLine(val.ToString()+"#");
            }
        }



        private void WriteLog(string text)
        {
            logTxb.Text += text + Environment.NewLine;
        }

        private void Main_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (port_is_open)
            {
                //Close port
                sp1.Close();
            }
        }

        private void Main_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void refreshBtn_Click(object sender, EventArgs e)
        {
            refreshPorts();
        }

        private void connectBtn_Click(object sender, EventArgs e)
        {
            if (port_is_open)
            {
                try
                {
                    sp1.Close();
                    connectBtn.Text = "Connect";
                }
                catch (IOException er)
                {
                    MessageBox.Show(er.Message, "Error closing port", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                if(portsCombo.Text != "")
                {
                    sp1.PortName = portsCombo.Text;

                    try
                    {
                        sp1.Open();
                        port_is_open = sp1.IsOpen;
                        connectBtn.Text = "Disconnect";
                    }
                    catch(IOException er)
                    {
                        MessageBox.Show(er.Message, "Error opening port", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("Please select a COM Port", "Error no COM Port");
                }
            }
        }

        private void sp1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            WriteLog(sp1.ReadLine());
        }
    }
}
