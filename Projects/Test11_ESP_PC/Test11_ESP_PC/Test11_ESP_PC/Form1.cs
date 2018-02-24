using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;

namespace Test11_ESP_PC
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        /*
        struct OData
        {
            public int AcX = 0;
            public int AcY = 0;
            public int AcZ = 0;
            public int Tmp = 0;
            public int GyX = 0;
            public int GyY = 0;
            public int GyZ = 0;
        }
        OData DData = new OData();*/
        //WebClient wc = new WebClient();

        double[] MData = new double[7];
        long Time = 0;
        private void Form1_Load(object sender, EventArgs e)
        {
            
            //wb.Url = new System.Uri("http://192.168.1.100:12345/mpuData");
        }

        private void btn_req_Click(object sender, EventArgs e)
        {
            wb.Url = new Uri(txt_req.Text);
            //wb.Url = new System.Uri(txt_req.Text);
            timer1.Enabled = true;
        }

        private void wb_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {

            textBox1.Text = wb.DocumentText;   
            /*
            string[] Result = wb.DocumentText.Split('|');
            for (int q = 0; q < 7; q++)
            {
                MData[q] += Convert.ToDouble(Result[q]);
            }
            string u = MData[0].ToString() + "|" + MData[1].ToString() + "|" + MData[2].ToString() + "|" + MData[3].ToString() + "|" + MData[4].ToString() + "|" + MData[5].ToString() + "|" + MData[6].ToString();
            this.Text = u;
            Clipboard.SetText(u);
            */
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            wb.Refresh(WebBrowserRefreshOption.Completely);
        }
    }
}
