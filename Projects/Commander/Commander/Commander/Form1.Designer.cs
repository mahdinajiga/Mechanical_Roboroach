namespace Commander
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.btn_fan_r_i = new System.Windows.Forms.Button();
            this.btn_fan_l_i = new System.Windows.Forms.Button();
            this.btn_light_l = new System.Windows.Forms.Button();
            this.btn_light_r = new System.Windows.Forms.Button();
            this.btn_light_m = new System.Windows.Forms.Button();
            this.dec1 = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btn_door_r_l = new System.Windows.Forms.Button();
            this.btn_door_l = new System.Windows.Forms.Button();
            this.btn_door_r = new System.Windows.Forms.Button();
            this.dec3 = new System.Windows.Forms.Button();
            this.btn_drop_l = new System.Windows.Forms.Button();
            this.btn_drop_r = new System.Windows.Forms.Button();
            this.dec4 = new System.Windows.Forms.Button();
            this.btn_fan_l_o = new System.Windows.Forms.Button();
            this.btn_fan_r_o = new System.Windows.Forms.Button();
            this.grp1 = new System.Windows.Forms.GroupBox();
            this.btn_Dis = new System.Windows.Forms.Button();
            this.btn_Con = new System.Windows.Forms.Button();
            this.txt_IP = new System.Windows.Forms.TextBox();
            this.dec5 = new System.Windows.Forms.Button();
            this.btn_spray_l = new System.Windows.Forms.Button();
            this.btn_spray_r = new System.Windows.Forms.Button();
            this.grp2 = new System.Windows.Forms.GroupBox();
            this.txt_MSG = new System.Windows.Forms.TextBox();
            this.btn_sendMess = new System.Windows.Forms.Button();
            this.wbS = new System.Windows.Forms.WebBrowser();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.grp1.SuspendLayout();
            this.grp2.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_fan_r_i
            // 
            this.btn_fan_r_i.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_fan_r_i.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_fan_r_i.Location = new System.Drawing.Point(126, 102);
            this.btn_fan_r_i.Name = "btn_fan_r_i";
            this.btn_fan_r_i.Size = new System.Drawing.Size(107, 29);
            this.btn_fan_r_i.TabIndex = 0;
            this.btn_fan_r_i.Text = "Fan_R_In";
            this.btn_fan_r_i.UseVisualStyleBackColor = false;
            this.btn_fan_r_i.Click += new System.EventHandler(this.btn_fan_r_i_Click);
            // 
            // btn_fan_l_i
            // 
            this.btn_fan_l_i.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_fan_l_i.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_fan_l_i.Location = new System.Drawing.Point(13, 102);
            this.btn_fan_l_i.Name = "btn_fan_l_i";
            this.btn_fan_l_i.Size = new System.Drawing.Size(107, 29);
            this.btn_fan_l_i.TabIndex = 1;
            this.btn_fan_l_i.Text = "Fan_L_In";
            this.btn_fan_l_i.UseVisualStyleBackColor = false;
            this.btn_fan_l_i.Click += new System.EventHandler(this.btn_fan_l_i_Click);
            // 
            // btn_light_l
            // 
            this.btn_light_l.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_light_l.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_light_l.Location = new System.Drawing.Point(465, 137);
            this.btn_light_l.Name = "btn_light_l";
            this.btn_light_l.Size = new System.Drawing.Size(107, 29);
            this.btn_light_l.TabIndex = 3;
            this.btn_light_l.Text = "Light_L";
            this.btn_light_l.UseVisualStyleBackColor = false;
            this.btn_light_l.Click += new System.EventHandler(this.btn_light_l_Click);
            // 
            // btn_light_r
            // 
            this.btn_light_r.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_light_r.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_light_r.Location = new System.Drawing.Point(465, 67);
            this.btn_light_r.Name = "btn_light_r";
            this.btn_light_r.Size = new System.Drawing.Size(107, 29);
            this.btn_light_r.TabIndex = 2;
            this.btn_light_r.Text = "Light_R";
            this.btn_light_r.UseVisualStyleBackColor = false;
            this.btn_light_r.Click += new System.EventHandler(this.btn_light_r_Click);
            // 
            // btn_light_m
            // 
            this.btn_light_m.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_light_m.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_light_m.Location = new System.Drawing.Point(465, 102);
            this.btn_light_m.Name = "btn_light_m";
            this.btn_light_m.Size = new System.Drawing.Size(107, 29);
            this.btn_light_m.TabIndex = 4;
            this.btn_light_m.Text = "Light_M";
            this.btn_light_m.UseVisualStyleBackColor = false;
            this.btn_light_m.Click += new System.EventHandler(this.btn_light_m_Click);
            // 
            // dec1
            // 
            this.dec1.Location = new System.Drawing.Point(13, 137);
            this.dec1.Name = "dec1";
            this.dec1.Size = new System.Drawing.Size(107, 29);
            this.dec1.TabIndex = 5;
            this.dec1.UseVisualStyleBackColor = true;
            this.dec1.Click += new System.EventHandler(this.dec1_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 500;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btn_door_r_l
            // 
            this.btn_door_r_l.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_door_r_l.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_door_r_l.Location = new System.Drawing.Point(239, 137);
            this.btn_door_r_l.Name = "btn_door_r_l";
            this.btn_door_r_l.Size = new System.Drawing.Size(107, 29);
            this.btn_door_r_l.TabIndex = 8;
            this.btn_door_r_l.Text = "Door_R_L";
            this.btn_door_r_l.UseVisualStyleBackColor = false;
            this.btn_door_r_l.Click += new System.EventHandler(this.btn_door_r_l_Click);
            // 
            // btn_door_l
            // 
            this.btn_door_l.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_door_l.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_door_l.Location = new System.Drawing.Point(239, 102);
            this.btn_door_l.Name = "btn_door_l";
            this.btn_door_l.Size = new System.Drawing.Size(107, 29);
            this.btn_door_l.TabIndex = 7;
            this.btn_door_l.Text = "Door_L";
            this.btn_door_l.UseVisualStyleBackColor = false;
            this.btn_door_l.Click += new System.EventHandler(this.btn_door_l_Click);
            // 
            // btn_door_r
            // 
            this.btn_door_r.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_door_r.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_door_r.Location = new System.Drawing.Point(239, 67);
            this.btn_door_r.Name = "btn_door_r";
            this.btn_door_r.Size = new System.Drawing.Size(107, 29);
            this.btn_door_r.TabIndex = 6;
            this.btn_door_r.Text = "Door_R";
            this.btn_door_r.UseVisualStyleBackColor = false;
            this.btn_door_r.Click += new System.EventHandler(this.btn_door_r_Click);
            // 
            // dec3
            // 
            this.dec3.Location = new System.Drawing.Point(352, 137);
            this.dec3.Name = "dec3";
            this.dec3.Size = new System.Drawing.Size(107, 29);
            this.dec3.TabIndex = 11;
            this.dec3.UseVisualStyleBackColor = true;
            // 
            // btn_drop_l
            // 
            this.btn_drop_l.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_drop_l.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_drop_l.Location = new System.Drawing.Point(352, 102);
            this.btn_drop_l.Name = "btn_drop_l";
            this.btn_drop_l.Size = new System.Drawing.Size(107, 29);
            this.btn_drop_l.TabIndex = 10;
            this.btn_drop_l.Text = "Drop_L:::0";
            this.btn_drop_l.UseVisualStyleBackColor = false;
            this.btn_drop_l.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn_drop_l_MouseDown);
            this.btn_drop_l.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn_drop_l_MouseUp);
            // 
            // btn_drop_r
            // 
            this.btn_drop_r.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_drop_r.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_drop_r.Location = new System.Drawing.Point(352, 67);
            this.btn_drop_r.Name = "btn_drop_r";
            this.btn_drop_r.Size = new System.Drawing.Size(107, 29);
            this.btn_drop_r.TabIndex = 9;
            this.btn_drop_r.Text = "Drop_R:::0";
            this.btn_drop_r.UseVisualStyleBackColor = false;
            this.btn_drop_r.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn_drop_r_MouseDown);
            this.btn_drop_r.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn_drop_r_MouseUp);
            // 
            // dec4
            // 
            this.dec4.Location = new System.Drawing.Point(126, 137);
            this.dec4.Name = "dec4";
            this.dec4.Size = new System.Drawing.Size(107, 29);
            this.dec4.TabIndex = 14;
            this.dec4.UseVisualStyleBackColor = true;
            // 
            // btn_fan_l_o
            // 
            this.btn_fan_l_o.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_fan_l_o.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_fan_l_o.Location = new System.Drawing.Point(13, 67);
            this.btn_fan_l_o.Name = "btn_fan_l_o";
            this.btn_fan_l_o.Size = new System.Drawing.Size(107, 29);
            this.btn_fan_l_o.TabIndex = 13;
            this.btn_fan_l_o.Text = "Fan_L_Out";
            this.btn_fan_l_o.UseVisualStyleBackColor = false;
            this.btn_fan_l_o.Click += new System.EventHandler(this.btn_fan_l_o_Click);
            // 
            // btn_fan_r_o
            // 
            this.btn_fan_r_o.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_fan_r_o.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_fan_r_o.Location = new System.Drawing.Point(126, 67);
            this.btn_fan_r_o.Name = "btn_fan_r_o";
            this.btn_fan_r_o.Size = new System.Drawing.Size(107, 29);
            this.btn_fan_r_o.TabIndex = 12;
            this.btn_fan_r_o.Text = "Fan_R_Out";
            this.btn_fan_r_o.UseVisualStyleBackColor = false;
            this.btn_fan_r_o.Click += new System.EventHandler(this.btn_fan_r_o_Click);
            // 
            // grp1
            // 
            this.grp1.Controls.Add(this.btn_Dis);
            this.grp1.Controls.Add(this.btn_Con);
            this.grp1.Controls.Add(this.txt_IP);
            this.grp1.ForeColor = System.Drawing.SystemColors.Control;
            this.grp1.Location = new System.Drawing.Point(12, 12);
            this.grp1.Name = "grp1";
            this.grp1.Size = new System.Drawing.Size(285, 49);
            this.grp1.TabIndex = 15;
            this.grp1.TabStop = false;
            this.grp1.Text = "Connection";
            // 
            // btn_Dis
            // 
            this.btn_Dis.Enabled = false;
            this.btn_Dis.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_Dis.Location = new System.Drawing.Point(193, 17);
            this.btn_Dis.Name = "btn_Dis";
            this.btn_Dis.Size = new System.Drawing.Size(75, 23);
            this.btn_Dis.TabIndex = 2;
            this.btn_Dis.Text = "Disconnect";
            this.btn_Dis.UseVisualStyleBackColor = true;
            this.btn_Dis.Click += new System.EventHandler(this.btn_Dis_Click);
            // 
            // btn_Con
            // 
            this.btn_Con.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_Con.Location = new System.Drawing.Point(112, 17);
            this.btn_Con.Name = "btn_Con";
            this.btn_Con.Size = new System.Drawing.Size(75, 23);
            this.btn_Con.TabIndex = 1;
            this.btn_Con.Text = "Connect";
            this.btn_Con.UseVisualStyleBackColor = true;
            this.btn_Con.Click += new System.EventHandler(this.btn_Con_Click);
            // 
            // txt_IP
            // 
            this.txt_IP.Location = new System.Drawing.Point(6, 19);
            this.txt_IP.Name = "txt_IP";
            this.txt_IP.Size = new System.Drawing.Size(100, 20);
            this.txt_IP.TabIndex = 0;
            this.txt_IP.Text = "192.168.43.159";
            this.txt_IP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // dec5
            // 
            this.dec5.Location = new System.Drawing.Point(578, 137);
            this.dec5.Name = "dec5";
            this.dec5.Size = new System.Drawing.Size(107, 29);
            this.dec5.TabIndex = 18;
            this.dec5.UseVisualStyleBackColor = true;
            this.dec5.Click += new System.EventHandler(this.dec5_Click);
            // 
            // btn_spray_l
            // 
            this.btn_spray_l.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_spray_l.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_spray_l.Location = new System.Drawing.Point(578, 102);
            this.btn_spray_l.Name = "btn_spray_l";
            this.btn_spray_l.Size = new System.Drawing.Size(107, 29);
            this.btn_spray_l.TabIndex = 17;
            this.btn_spray_l.Text = "Spray_L:::0";
            this.btn_spray_l.UseVisualStyleBackColor = false;
            this.btn_spray_l.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn_spray_l_MouseDown);
            this.btn_spray_l.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn_spray_l_MouseUp);
            // 
            // btn_spray_r
            // 
            this.btn_spray_r.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btn_spray_r.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_spray_r.Location = new System.Drawing.Point(578, 67);
            this.btn_spray_r.Name = "btn_spray_r";
            this.btn_spray_r.Size = new System.Drawing.Size(107, 29);
            this.btn_spray_r.TabIndex = 16;
            this.btn_spray_r.Text = "Spray_R:::0";
            this.btn_spray_r.UseVisualStyleBackColor = false;
            this.btn_spray_r.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn_spray_r_MouseDown);
            this.btn_spray_r.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn_spray_r_MouseUp);
            // 
            // grp2
            // 
            this.grp2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.grp2.Controls.Add(this.txt_MSG);
            this.grp2.Controls.Add(this.btn_sendMess);
            this.grp2.ForeColor = System.Drawing.SystemColors.Control;
            this.grp2.Location = new System.Drawing.Point(303, 12);
            this.grp2.Name = "grp2";
            this.grp2.Size = new System.Drawing.Size(381, 49);
            this.grp2.TabIndex = 21;
            this.grp2.TabStop = false;
            this.grp2.Text = "Message:";
            // 
            // txt_MSG
            // 
            this.txt_MSG.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.txt_MSG.Location = new System.Drawing.Point(84, 17);
            this.txt_MSG.Name = "txt_MSG";
            this.txt_MSG.Size = new System.Drawing.Size(291, 20);
            this.txt_MSG.TabIndex = 1;
            // 
            // btn_sendMess
            // 
            this.btn_sendMess.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_sendMess.Location = new System.Drawing.Point(3, 16);
            this.btn_sendMess.Name = "btn_sendMess";
            this.btn_sendMess.Size = new System.Drawing.Size(75, 23);
            this.btn_sendMess.TabIndex = 0;
            this.btn_sendMess.Text = "Send";
            this.btn_sendMess.UseVisualStyleBackColor = true;
            this.btn_sendMess.Click += new System.EventHandler(this.btn_sendMess_Click);
            // 
            // wbS
            // 
            this.wbS.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.wbS.Location = new System.Drawing.Point(12, 172);
            this.wbS.MinimumSize = new System.Drawing.Size(20, 20);
            this.wbS.Name = "wbS";
            this.wbS.Size = new System.Drawing.Size(673, 211);
            this.wbS.TabIndex = 22;
            this.wbS.DocumentCompleted += new System.Windows.Forms.WebBrowserDocumentCompletedEventHandler(this.wbS_DocumentCompleted);
            // 
            // timer2
            // 
            this.timer2.Interval = 5000;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(696, 395);
            this.Controls.Add(this.wbS);
            this.Controls.Add(this.grp2);
            this.Controls.Add(this.dec5);
            this.Controls.Add(this.btn_spray_l);
            this.Controls.Add(this.btn_spray_r);
            this.Controls.Add(this.grp1);
            this.Controls.Add(this.dec4);
            this.Controls.Add(this.btn_fan_l_o);
            this.Controls.Add(this.btn_fan_r_o);
            this.Controls.Add(this.dec3);
            this.Controls.Add(this.btn_drop_l);
            this.Controls.Add(this.btn_drop_r);
            this.Controls.Add(this.btn_door_r_l);
            this.Controls.Add(this.btn_door_l);
            this.Controls.Add(this.btn_door_r);
            this.Controls.Add(this.dec1);
            this.Controls.Add(this.btn_light_m);
            this.Controls.Add(this.btn_light_l);
            this.Controls.Add(this.btn_light_r);
            this.Controls.Add(this.btn_fan_l_i);
            this.Controls.Add(this.btn_fan_r_i);
            this.ForeColor = System.Drawing.SystemColors.Control;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.Text = "Commander";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.grp1.ResumeLayout(false);
            this.grp1.PerformLayout();
            this.grp2.ResumeLayout(false);
            this.grp2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn_fan_r_i;
        private System.Windows.Forms.Button btn_fan_l_i;
        private System.Windows.Forms.Button btn_light_l;
        private System.Windows.Forms.Button btn_light_r;
        private System.Windows.Forms.Button btn_light_m;
        private System.Windows.Forms.Button dec1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button btn_door_r_l;
        private System.Windows.Forms.Button btn_door_l;
        private System.Windows.Forms.Button btn_door_r;
        private System.Windows.Forms.Button dec3;
        private System.Windows.Forms.Button btn_drop_l;
        private System.Windows.Forms.Button btn_drop_r;
        private System.Windows.Forms.Button dec4;
        private System.Windows.Forms.Button btn_fan_l_o;
        private System.Windows.Forms.Button btn_fan_r_o;
        private System.Windows.Forms.GroupBox grp1;
        private System.Windows.Forms.Button btn_Dis;
        private System.Windows.Forms.Button btn_Con;
        private System.Windows.Forms.TextBox txt_IP;
        private System.Windows.Forms.Button dec5;
        private System.Windows.Forms.Button btn_spray_l;
        private System.Windows.Forms.Button btn_spray_r;
        private System.Windows.Forms.GroupBox grp2;
        private System.Windows.Forms.TextBox txt_MSG;
        private System.Windows.Forms.Button btn_sendMess;
        private System.Windows.Forms.WebBrowser wbS;
        private System.Windows.Forms.Timer timer2;
    }
}

