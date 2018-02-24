using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        int t = 100;

        private void Form1_Load(object sender, EventArgs e)
        {
            a0.BackColor = Color.FromArgb(0, 0, 0);
            a1.BackColor = Color.FromArgb(0, 0, 0);
            a2.BackColor = Color.FromArgb(0, 0, 0);
            a3.BackColor = Color.FromArgb(0, 0, 0);
            Thread.Sleep(100);
        }

        private void SetCol(int NUM, bool State)
        {
            switch (NUM)
            {
                case 0:
                    if (State)
                    { a0.BackColor = Color.Green; }
                    else { a0.BackColor = Color.White; }
                    break;
                case 1:
                    if (State)
                    { a1.BackColor = Color.Yellow; }
                    else { a1.BackColor = Color.White; }
                    break;
                case 2:
                    if (State)
                    { a2.BackColor = Color.Blue; }
                    else { a2.BackColor = Color.White; }
                    break;
                case 3:
                    if (State)
                    { a3.BackColor = Color.Red; }
                    else { a3.BackColor = Color.White; }
                    break;
            }
        }
        private void Cycle()
        {
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 255, 0);
            a1.BackColor = Color.FromArgb(0, 0, 0);
            a2.BackColor = Color.FromArgb(0, 0, 0);
            a3.BackColor = Color.FromArgb(0, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 192, 0);
            a1.BackColor = Color.FromArgb(255, 255, 0);
            a2.BackColor = Color.FromArgb(0, 0, 0);
            a3.BackColor = Color.FromArgb(0, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 128, 0);
            a1.BackColor = Color.FromArgb(192, 192, 0);
            a2.BackColor = Color.FromArgb(0, 0, 255);
            a3.BackColor = Color.FromArgb(0, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 0, 0);
            a1.BackColor = Color.FromArgb(128, 128, 0);
            a2.BackColor = Color.FromArgb(0, 0, 192);
            a3.BackColor = Color.FromArgb(255, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 0, 0);
            a1.BackColor = Color.FromArgb(0, 0, 0);
            a2.BackColor = Color.FromArgb(0, 0, 128);
            a3.BackColor = Color.FromArgb(192, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 0, 0);
            a1.BackColor = Color.FromArgb(0, 0, 0);
            a2.BackColor = Color.FromArgb(0, 0, 0);
            a3.BackColor = Color.FromArgb(128, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 0, 0);
            a1.BackColor = Color.FromArgb(0, 0, 0);
            a2.BackColor = Color.FromArgb(0, 0, 0);
            a3.BackColor = Color.FromArgb(0, 0, 0);
            Thread.Sleep(150);
            this.Refresh();
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            a0.BackColor = Color.FromArgb(0, 0, 0);
            a1.BackColor = Color.FromArgb(0, 0, 0);
            a2.BackColor = Color.FromArgb(0, 0, 0);
            a3.BackColor = Color.FromArgb(255, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 0, 0);
            a1.BackColor = Color.FromArgb(0, 0, 0);
            a2.BackColor = Color.FromArgb(0, 0, 255);
            a3.BackColor = Color.FromArgb(192, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 0, 0);
            a1.BackColor = Color.FromArgb(255, 255, 0);
            a2.BackColor = Color.FromArgb(0, 0, 192);
            a3.BackColor = Color.FromArgb(128, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 255, 0);
            a1.BackColor = Color.FromArgb(192, 192, 0);
            a2.BackColor = Color.FromArgb(0, 0, 128);
            a3.BackColor = Color.FromArgb(0, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 192, 0);
            a1.BackColor = Color.FromArgb(128, 128, 0);
            a2.BackColor = Color.FromArgb(0, 0, 0);
            a3.BackColor = Color.FromArgb(0, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 128, 0);
            a1.BackColor = Color.FromArgb(0, 0, 0);
            a2.BackColor = Color.FromArgb(0, 0, 0);
            a3.BackColor = Color.FromArgb(0, 0, 0);
            Thread.Sleep(t);
            this.Refresh();
            a0.BackColor = Color.FromArgb(0, 0, 0);
            a1.BackColor = Color.FromArgb(0, 0, 0);
            a2.BackColor = Color.FromArgb(0, 0, 0);
            a3.BackColor = Color.FromArgb(0, 0, 0);
            Thread.Sleep(150);
            this.Refresh();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Interval = 15 * t;
            Cycle();
        }
    }
}
