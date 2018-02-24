using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace Navigator
{
    public partial class Form1 : Form
    {
        string IPADDress = "";
        string IPADDPORT = "";
        long CalibDirectIndex = 0, OffsettX = 0, OffsettY = 0, OffsettZ = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btn_COM_Connect_Click(object sender, EventArgs e)
        {
            if (btn_COM_Connect.Text == "Connect")
            {
                IPADDress = txt_COM_Target_IP.Text; IPADDPORT = txt_COM_Target_PORT.Text;
                WB1.Url = new Uri("http://" + IPADDress + ":" + IPADDPORT + "/ping");
                MessageBox.Show("Loading PING request\nPlz w8...", "Plz w8...", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else if (btn_COM_Connect.Text == "Disconnect")
            {
                btn_COM_Connect.Text = "Connect";
                txt_COM_Target_IP.Enabled = true; txt_COM_Target_PORT.Enabled = true;
                lbl_COM_Status.Text = "Status: Disconnected";
                CHK_1_COM.BackColor = Color.Red;
            }
        }

        private void WB1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            if (WB1.DocumentText.Equals("R"))
            {
                btn_COM_Connect.Text = "Disconnect";
                txt_COM_Target_IP.Enabled = false; txt_COM_Target_PORT.Enabled = false;
                WB1.Url = new Uri("http://" + IPADDress + ":" + IPADDPORT + "/mpuStatus");
                lbl_COM_Status.Text = "Status: " + " /// " + "Positive reply from ESP";
                CHK_1_COM.BackColor = Color.Green;
            }
            else if (WB1.DocumentText.Contains("MPU Device Founded"))
            {
                lbl_COM_Status.Text = "Status: " + WB1.DocumentText + " /// " + "Positive reply from ESP";
                if (WB1.DocumentText == " Positive MPU Device Founded")
                {
                    CHK_2_MPU.BackColor = Color.Green;
                }
                else if (WB1.DocumentText == " Negative MPU Device Founded")
                {
                    CHK_2_MPU.BackColor = Color.Red;
                }
            }
            else
            {
                lbl_COM_Status.Text = "Status: NO REPLY CONFIRMED...";
                if (!tmr_COM_TogglePING.Enabled)
                {
                    Clipboard.SetText(WB1.DocumentText);
                    MessageBox.Show(WB1.DocumentText, "Error on PING Device", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                CHK_1_COM.BackColor = Color.Red;
            }
        }

        private void btn_COM_TogglePING_Click(object sender, EventArgs e)
        {
            if (btn_COM_TogglePING.Text == "Toggle Ping")
            {
                tmr_COM_TogglePING.Enabled = true;
            }
            else if (btn_COM_TogglePING.Text == "Pinging")
            {
                tmr_COM_TogglePING.Enabled = false;
                btn_COM_TogglePING.Text = "Toggle Ping";
            }
        }

        private void tmr_COM_TogglePING_Tick(object sender, EventArgs e)
        {
            try
            {
                btn_COM_TogglePING.Text = "Pinging";
                WB1.Url = new Uri("http://" + IPADDress + ":" + IPADDPORT + "/ping");
            }
            catch (Exception Ert) { tmr_COM_TogglePING.Enabled = false; btn_COM_TogglePING.Text = "Toggle Ping"; MessageBox.Show(Ert.Message, "TogglePING Error:::Seting up URI", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }

        private void CHK_1_COM_BackColorChanged(object sender, EventArgs e)
        {
            if (CHK_1_COM.BackColor == Color.Red)
            {
                CHK_2_MPU.BackColor = Color.Red;
            }
        }

        private void btn_MPU_CalibDir_Click(object sender, EventArgs e)
        {
            CalibDirectIndex = 0;
            WB2.Url = new Uri("http://" + IPADDress + ":" + IPADDPORT + "/mpuData");
        }

        private long GetGyro(int Index//0X | 1Y | 2Z
            , string Data)
        {
            long Rt = 0;
            try
            {
                string[] YYY = Data.Split('|');
                Rt = Convert.ToInt64(YYY[Index]);
                return Rt;
            }
            catch (Exception Ert) { MessageBox.Show(Ert.Message); return 0; }
        }

        private void WB2_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            if (CalibDirectIndex < 50)
            {
                string DDd = WB2.DocumentText;
                if (!DDd.StartsWith("<!DOCTYPE"))
                {
                    OffsettX += GetGyro(0, DDd);
                    OffsettY += GetGyro(1, DDd);
                    OffsettZ += GetGyro(2, DDd);
                    CalibDirectIndex++;
                }
                btn_MPU_CalibDir.Text = "CalibDirect:::" + CalibDirectIndex.ToString();
                WB2.Url = new Uri("http://" + IPADDress + ":" + IPADDPORT + "/mpuData");
            }
            else
            {
                OffsettX = OffsettX / 50;
                OffsettY = OffsettY / 50;
                OffsettZ = OffsettZ / 50;
                btn_MPU_CalibDir.Text = "CalibDirect";
            }
        }

        private void btn_MPU_GetData_Click(object sender, EventArgs e)
        {
            if (btn_MPU_GetData.Text == "Get Data")
            {
                btn_MPU_GetData.Text = "Getting Data";
                WB3.Url = new Uri("http://" + IPADDress + ":" + IPADDPORT + "/mpuData");
            }
            else if(btn_MPU_GetData.Text=="Getting Data")
            {
                btn_MPU_GetData.Text = "Get Data";
            }
        }

        private void WB3_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            if (btn_MPU_GetData.Text == "Getting Data")
            {
                string TTTT = WB3.DocumentText;
                if (!TTTT.StartsWith("<!DOCTYPE"))
                {
                    lbl_MPU_Data_X.Text = (GetGyro(0, TTTT) - OffsettX).ToString();
                    lbl_MPU_Data_Y.Text = (GetGyro(1, TTTT) - OffsettY).ToString();
                    lbl_MPU_Data_Z.Text = (GetGyro(2, TTTT) - OffsettZ).ToString();
                }
                Thread.Sleep(500);
                WB3.Url = new Uri("http://" + IPADDress + ":" + IPADDPORT + "/mpuData");
            }
        }
    }
}
