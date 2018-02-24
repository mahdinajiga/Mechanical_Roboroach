using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Commander
{
    public partial class Form1 : Form
    {

        string IPP = "";
        bool ReqInQue = false;

        int nR = 0, nL = 0, mR = 0, mL = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void btn_fan_l_o_Click(object sender, EventArgs e)
        {
            if (btn_fan_l_o.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/a1");
                timer1.Enabled = true;
                btn_fan_l_o.BackColor = Color.Red;
            }
            else if (btn_fan_l_o.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/a0");
                timer1.Enabled = true;
                btn_fan_l_o.BackColor = Color.Red;
            }
        }

        private void btn_fan_l_i_Click(object sender, EventArgs e)
        {
            if (btn_fan_l_i.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/b1");
                timer1.Enabled = true;
                btn_fan_l_i.BackColor = Color.Red;
            }
            else if (btn_fan_l_i.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/b0");
                timer1.Enabled = true;
                btn_fan_l_i.BackColor = Color.Red;
            }
        }

        private void btn_fan_r_o_Click(object sender, EventArgs e)
        {
            if (btn_fan_r_o.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/c1");
                timer1.Enabled = true;
                btn_fan_r_o.BackColor = Color.Red;
            }
            else if (btn_fan_r_o.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/c0");
                timer1.Enabled = true;
                btn_fan_r_o.BackColor = Color.Red;
            }
        }

        private void btn_fan_r_i_Click(object sender, EventArgs e)
        {
            if (btn_fan_r_i.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/d1");
                timer1.Enabled = true;
                btn_fan_r_i.BackColor = Color.Red;
            }
            else if (btn_fan_r_i.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/d0");
                timer1.Enabled = true;
                btn_fan_r_i.BackColor = Color.Red;
            }
        }

        private void btn_door_r_l_Click(object sender, EventArgs e)
        {
            if (btn_door_r_l.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/e4");
                timer1.Enabled = true;
                btn_door_r_l.BackColor = Color.Red;
            }
            else if (btn_door_r_l.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/e3");
                timer1.Enabled = true;
                btn_door_r_l.BackColor = Color.Red;
            }
        }

        private void btn_door_r_Click(object sender, EventArgs e)
        {
            if (btn_door_r.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/e1");
                timer1.Enabled = true;
                btn_door_r.BackColor = Color.Red;
            }
            else if (btn_door_r.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/e0");
                timer1.Enabled = true;
                btn_door_r.BackColor = Color.Red;
            }
        }

        private void btn_door_l_Click(object sender, EventArgs e)
        {
            if (btn_door_l.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/f1");
                timer1.Enabled = true;
                btn_door_l.BackColor = Color.Red;
            }
            else if (btn_door_l.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/f0");
                timer1.Enabled = true;
                btn_door_l.BackColor = Color.Red;
            }
        }

        private void btn_light_r_Click(object sender, EventArgs e)
        {
            if (btn_light_r.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/i1");
                timer1.Enabled = true;
                btn_light_r.BackColor = Color.Red;
            }
            else if (btn_light_r.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/i0");
                timer1.Enabled = true;
                btn_light_r.BackColor = Color.Red;
            }
        }

        private void btn_light_m_Click(object sender, EventArgs e)
        {
            if (btn_light_m.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/j1");
                timer1.Enabled = true;
                btn_light_m.BackColor = Color.Red;
            }
            else if (btn_light_m.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/j0");
                timer1.Enabled = true;
                btn_light_m.BackColor = Color.Red;
            }
        }

        private void btn_light_l_Click(object sender, EventArgs e)
        {
            if (btn_light_l.BackColor == Color.WhiteSmoke)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/k1");
                timer1.Enabled = true;
                btn_light_l.BackColor = Color.Red;
            }
            else if (btn_light_l.BackColor == Color.Green)
            {
                timer1.Enabled = true;
                wbS.Url = new Uri("http://" + IPP + "/k0");
                timer1.Enabled = true;
                btn_light_l.BackColor = Color.Red;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (btn_Con.Enabled)
                timer1.Enabled = false;
            if (ReqInQue)
            {
                timer1.Enabled = false;
                ReqInQue = false;
                string TT = wbS.DocumentText;
                Recheck(TT);
            }
        }

        private void btn_Con_Click(object sender, EventArgs e)
        {
            IPP = txt_IP.Text;
            txt_IP.Enabled = false;
            btn_Con.Enabled = false;
            timer2.Enabled = true;
            btn_Dis.Enabled = true;
        }

        private void btn_Dis_Click(object sender, EventArgs e)
        {
            txt_IP.Enabled = true;
            btn_Con.Enabled = true;
            btn_Dis.Enabled = false;
        }

        private void btn_sendMess_Click(object sender, EventArgs e)
        {
            //wbR.Url = new Uri("http://" + IPP + "/" + txt_MSG.Text);
        }

        private void btn_spray_r_MouseDown(object sender, MouseEventArgs e)
        {
            btn_spray_r.BackColor = Color.Green;
        }

        private void btn_spray_l_MouseDown(object sender, MouseEventArgs e)
        {
            btn_spray_l.BackColor = Color.Green;
        }

        private void btn_spray_r_MouseUp(object sender, MouseEventArgs e)
        {
            nR++;
            btn_spray_r.Text = "Spray_R:::" + nR;
            btn_spray_r.BackColor = Color.WhiteSmoke;
            wbS.Url = new Uri("http://" + IPP + "/l1");
        }

        private void btn_spray_l_MouseUp(object sender, MouseEventArgs e)
        {
            nL++;
            btn_spray_l.Text = "Spray_L:::" + nL;
            btn_spray_l.BackColor = Color.WhiteSmoke;
            wbS.Url = new Uri("http://" + IPP + "/m1");
        }

        private void Recheck(string TTT)
        {
            switch (TTT[0])
            {
                case 'a':
                    if (TTT[1] == '0')
                    {
                        btn_fan_l_o.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_fan_l_o.BackColor = Color.Green;
                    }
                    break;
                case 'b':
                    if (TTT[1] == '0')
                    {
                        btn_fan_l_i.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_fan_l_i.BackColor = Color.Green;
                    }
                    break;
                case 'c':
                    if (TTT[1] == '0')
                    {
                        btn_fan_r_o.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_fan_r_o.BackColor = Color.Green;
                    }
                    break;
                case 'd':
                    if (TTT[1] == '0')
                    {
                        btn_fan_r_i.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_fan_r_i.BackColor = Color.Green;
                    }
                    break;
                case 'e':
                    if (TTT[1] == '0')
                    {
                        btn_door_r.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_door_r.BackColor = Color.Green;
                    }
                    else if (TTT[1] == '3')
                    {
                        btn_door_r.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '4')
                    {
                        btn_door_r.BackColor = Color.Green;
                    }
                    break;
                case 'f':
                    if (TTT[1] == '0')
                    {
                        btn_door_l.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_door_l.BackColor = Color.Green;
                    }
                    break;
                case 'g':
                    if (TTT[1] == '0')
                    {
                        btn_drop_r.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_drop_r.BackColor = Color.Green;
                    }
                    break;
                case 'h':
                    if (TTT[1] == '0')
                    {
                        btn_drop_l.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_drop_l.BackColor = Color.Green;
                    }
                    break;
                case 'i':
                    if (TTT[1] == '0')
                    {
                        btn_light_r.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_light_r.BackColor = Color.Green;
                    }
                    break;
                case 'j':
                    if (TTT[1] == '0')
                    {
                        btn_light_m.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_light_m.BackColor = Color.Green;
                    }
                    break;
                case 'k':
                    if (TTT[1] == '0')
                    {
                        btn_light_l.BackColor = Color.WhiteSmoke;
                    }
                    else if (TTT[1] == '1')
                    {
                        btn_light_l.BackColor = Color.Green;
                    }
                    break;
                default:
                    if (TTT != "EEE")
                    {
                        timer1.Enabled = false;
                        MessageBox.Show(this, TTT + "\n\n\n\nplz restart the app", "error!!!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        Clipboard.SetText(TTT);
                    }
                    break;
            }
        }

        private void dec5_Click(object sender, EventArgs e)
        {
            btn_door_l.BackColor = Color.WhiteSmoke;
            btn_door_r.BackColor = Color.WhiteSmoke;
            btn_drop_l.BackColor = Color.WhiteSmoke;
            btn_drop_r.BackColor = Color.WhiteSmoke;
            btn_fan_l_i.BackColor = Color.WhiteSmoke;
            btn_fan_l_o.BackColor = Color.WhiteSmoke;
            btn_fan_r_i.BackColor = Color.WhiteSmoke;
            btn_fan_r_o.BackColor = Color.WhiteSmoke;
            btn_light_l.BackColor = Color.WhiteSmoke;
            btn_light_m.BackColor = Color.WhiteSmoke;
            btn_light_r.BackColor = Color.WhiteSmoke;
            btn_spray_r.BackColor = Color.WhiteSmoke;
            btn_spray_l.BackColor = Color.WhiteSmoke;
        }

        private void dec1_Click(object sender, EventArgs e)
        {
            wbS.Url = new Uri("http://" + IPP + "/");
        }

        private void wbS_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            ReqInQue = true;
            timer1.Enabled = true;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            wbS.Url = new Uri("http://" + IPP + "/");
        }

        private void btn_drop_r_MouseDown(object sender, MouseEventArgs e)
        {
            btn_drop_r.BackColor = Color.Green;
        }

        private void btn_drop_l_MouseDown(object sender, MouseEventArgs e)
        {
            btn_drop_l.BackColor = Color.Green;
        }

        private void btn_drop_r_MouseUp(object sender, MouseEventArgs e)
        {
            mR++;
            btn_drop_r.Text = "Drop_R:::" + mR;
            btn_drop_r.BackColor = Color.WhiteSmoke;
            wbS.Url = new Uri("http://" + IPP + "/g1");
        }

        private void btn_drop_l_MouseUp(object sender, MouseEventArgs e)
        {
            mL++;
            btn_drop_l.Text = "Drop_L:::" + mL;
            btn_drop_l.BackColor = Color.WhiteSmoke;
            wbS.Url = new Uri("http://" + IPP + "/h1");
        }

    }
}
