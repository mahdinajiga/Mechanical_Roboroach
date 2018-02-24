namespace Navigator
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
            this.grp_COM = new System.Windows.Forms.GroupBox();
            this.WB2 = new System.Windows.Forms.WebBrowser();
            this.WB1 = new System.Windows.Forms.WebBrowser();
            this.btn_COM_TogglePING = new System.Windows.Forms.Button();
            this.CHK_1_COM = new System.Windows.Forms.Label();
            this.lbl_COM_Status = new System.Windows.Forms.Label();
            this.btn_COM_Connect = new System.Windows.Forms.Button();
            this.txt_COM_Target_PORT = new System.Windows.Forms.TextBox();
            this.lbl_Show_2 = new System.Windows.Forms.Label();
            this.txt_COM_Target_IP = new System.Windows.Forms.TextBox();
            this.lbl_Show_1 = new System.Windows.Forms.Label();
            this.tmr_COM_TogglePING = new System.Windows.Forms.Timer(this.components);
            this.grp_MPU = new System.Windows.Forms.GroupBox();
            this.btn_MPU_CalibDir = new System.Windows.Forms.Button();
            this.CHK_2_MPU = new System.Windows.Forms.Label();
            this.tmr_MPU_GetData = new System.Windows.Forms.Timer(this.components);
            this.WB3 = new System.Windows.Forms.WebBrowser();
            this.btn_MPU_GetData = new System.Windows.Forms.Button();
            this.lbl_MPU_Data_X = new System.Windows.Forms.Label();
            this.lbl_MPU_Data_Y = new System.Windows.Forms.Label();
            this.lbl_MPU_Data_Z = new System.Windows.Forms.Label();
            this.grp_COM.SuspendLayout();
            this.grp_MPU.SuspendLayout();
            this.SuspendLayout();
            // 
            // grp_COM
            // 
            this.grp_COM.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.grp_COM.Controls.Add(this.WB2);
            this.grp_COM.Controls.Add(this.WB1);
            this.grp_COM.Controls.Add(this.btn_COM_TogglePING);
            this.grp_COM.Controls.Add(this.CHK_1_COM);
            this.grp_COM.Controls.Add(this.lbl_COM_Status);
            this.grp_COM.Controls.Add(this.btn_COM_Connect);
            this.grp_COM.Controls.Add(this.txt_COM_Target_PORT);
            this.grp_COM.Controls.Add(this.lbl_Show_2);
            this.grp_COM.Controls.Add(this.txt_COM_Target_IP);
            this.grp_COM.Controls.Add(this.lbl_Show_1);
            this.grp_COM.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.grp_COM.Location = new System.Drawing.Point(12, 12);
            this.grp_COM.Name = "grp_COM";
            this.grp_COM.Size = new System.Drawing.Size(1258, 40);
            this.grp_COM.TabIndex = 0;
            this.grp_COM.TabStop = false;
            this.grp_COM.Text = "Communications";
            // 
            // WB2
            // 
            this.WB2.Location = new System.Drawing.Point(65, 11);
            this.WB2.MinimumSize = new System.Drawing.Size(20, 20);
            this.WB2.Name = "WB2";
            this.WB2.Size = new System.Drawing.Size(55, 20);
            this.WB2.TabIndex = 3;
            this.WB2.Visible = false;
            this.WB2.DocumentCompleted += new System.Windows.Forms.WebBrowserDocumentCompletedEventHandler(this.WB2_DocumentCompleted);
            // 
            // WB1
            // 
            this.WB1.Location = new System.Drawing.Point(6, 11);
            this.WB1.MinimumSize = new System.Drawing.Size(20, 20);
            this.WB1.Name = "WB1";
            this.WB1.Size = new System.Drawing.Size(53, 20);
            this.WB1.TabIndex = 3;
            this.WB1.Visible = false;
            this.WB1.DocumentCompleted += new System.Windows.Forms.WebBrowserDocumentCompletedEventHandler(this.WB1_DocumentCompleted);
            // 
            // btn_COM_TogglePING
            // 
            this.btn_COM_TogglePING.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_COM_TogglePING.Location = new System.Drawing.Point(348, 11);
            this.btn_COM_TogglePING.Name = "btn_COM_TogglePING";
            this.btn_COM_TogglePING.Size = new System.Drawing.Size(73, 23);
            this.btn_COM_TogglePING.TabIndex = 6;
            this.btn_COM_TogglePING.Text = "Toggle Ping";
            this.btn_COM_TogglePING.UseVisualStyleBackColor = true;
            this.btn_COM_TogglePING.Click += new System.EventHandler(this.btn_COM_TogglePING_Click);
            // 
            // CHK_1_COM
            // 
            this.CHK_1_COM.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.CHK_1_COM.BackColor = System.Drawing.Color.Red;
            this.CHK_1_COM.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.CHK_1_COM.Location = new System.Drawing.Point(1152, 11);
            this.CHK_1_COM.Name = "CHK_1_COM";
            this.CHK_1_COM.Size = new System.Drawing.Size(100, 23);
            this.CHK_1_COM.TabIndex = 5;
            this.CHK_1_COM.Text = "Communication";
            this.CHK_1_COM.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.CHK_1_COM.BackColorChanged += new System.EventHandler(this.CHK_1_COM_BackColorChanged);
            // 
            // lbl_COM_Status
            // 
            this.lbl_COM_Status.AutoSize = true;
            this.lbl_COM_Status.Location = new System.Drawing.Point(427, 16);
            this.lbl_COM_Status.Name = "lbl_COM_Status";
            this.lbl_COM_Status.Size = new System.Drawing.Size(43, 13);
            this.lbl_COM_Status.TabIndex = 4;
            this.lbl_COM_Status.Text = "Status: ";
            // 
            // btn_COM_Connect
            // 
            this.btn_COM_Connect.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_COM_Connect.Location = new System.Drawing.Point(272, 11);
            this.btn_COM_Connect.Name = "btn_COM_Connect";
            this.btn_COM_Connect.Size = new System.Drawing.Size(70, 23);
            this.btn_COM_Connect.TabIndex = 1;
            this.btn_COM_Connect.Text = "Connect";
            this.btn_COM_Connect.UseVisualStyleBackColor = true;
            this.btn_COM_Connect.Click += new System.EventHandler(this.btn_COM_Connect_Click);
            // 
            // txt_COM_Target_PORT
            // 
            this.txt_COM_Target_PORT.Location = new System.Drawing.Point(223, 13);
            this.txt_COM_Target_PORT.Name = "txt_COM_Target_PORT";
            this.txt_COM_Target_PORT.Size = new System.Drawing.Size(43, 20);
            this.txt_COM_Target_PORT.TabIndex = 3;
            this.txt_COM_Target_PORT.Text = "12345";
            this.txt_COM_Target_PORT.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lbl_Show_2
            // 
            this.lbl_Show_2.AutoSize = true;
            this.lbl_Show_2.Location = new System.Drawing.Point(207, 16);
            this.lbl_Show_2.Name = "lbl_Show_2";
            this.lbl_Show_2.Size = new System.Drawing.Size(10, 13);
            this.lbl_Show_2.TabIndex = 2;
            this.lbl_Show_2.Text = ":";
            // 
            // txt_COM_Target_IP
            // 
            this.txt_COM_Target_IP.Location = new System.Drawing.Point(107, 13);
            this.txt_COM_Target_IP.Name = "txt_COM_Target_IP";
            this.txt_COM_Target_IP.Size = new System.Drawing.Size(94, 20);
            this.txt_COM_Target_IP.TabIndex = 1;
            this.txt_COM_Target_IP.Text = "192.168.43.159";
            this.txt_COM_Target_IP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lbl_Show_1
            // 
            this.lbl_Show_1.AutoSize = true;
            this.lbl_Show_1.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.lbl_Show_1.Location = new System.Drawing.Point(6, 16);
            this.lbl_Show_1.Name = "lbl_Show_1";
            this.lbl_Show_1.Size = new System.Drawing.Size(95, 13);
            this.lbl_Show_1.TabIndex = 0;
            this.lbl_Show_1.Text = "Target IP Address:";
            // 
            // tmr_COM_TogglePING
            // 
            this.tmr_COM_TogglePING.Interval = 5000;
            this.tmr_COM_TogglePING.Tick += new System.EventHandler(this.tmr_COM_TogglePING_Tick);
            // 
            // grp_MPU
            // 
            this.grp_MPU.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.grp_MPU.Controls.Add(this.lbl_MPU_Data_Z);
            this.grp_MPU.Controls.Add(this.lbl_MPU_Data_Y);
            this.grp_MPU.Controls.Add(this.lbl_MPU_Data_X);
            this.grp_MPU.Controls.Add(this.btn_MPU_GetData);
            this.grp_MPU.Controls.Add(this.btn_MPU_CalibDir);
            this.grp_MPU.Controls.Add(this.CHK_2_MPU);
            this.grp_MPU.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.grp_MPU.Location = new System.Drawing.Point(12, 70);
            this.grp_MPU.Name = "grp_MPU";
            this.grp_MPU.Size = new System.Drawing.Size(1258, 46);
            this.grp_MPU.TabIndex = 2;
            this.grp_MPU.TabStop = false;
            this.grp_MPU.Text = "MPU-6050   GY-521";
            // 
            // btn_MPU_CalibDir
            // 
            this.btn_MPU_CalibDir.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_MPU_CalibDir.Location = new System.Drawing.Point(6, 17);
            this.btn_MPU_CalibDir.Name = "btn_MPU_CalibDir";
            this.btn_MPU_CalibDir.Size = new System.Drawing.Size(95, 23);
            this.btn_MPU_CalibDir.TabIndex = 7;
            this.btn_MPU_CalibDir.Text = "CalibDirect";
            this.btn_MPU_CalibDir.UseVisualStyleBackColor = true;
            this.btn_MPU_CalibDir.Click += new System.EventHandler(this.btn_MPU_CalibDir_Click);
            // 
            // CHK_2_MPU
            // 
            this.CHK_2_MPU.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.CHK_2_MPU.BackColor = System.Drawing.Color.Red;
            this.CHK_2_MPU.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.CHK_2_MPU.Location = new System.Drawing.Point(1152, 16);
            this.CHK_2_MPU.Name = "CHK_2_MPU";
            this.CHK_2_MPU.Size = new System.Drawing.Size(100, 23);
            this.CHK_2_MPU.TabIndex = 6;
            this.CHK_2_MPU.Text = "MPU-6050";
            this.CHK_2_MPU.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // WB3
            // 
            this.WB3.Location = new System.Drawing.Point(138, 23);
            this.WB3.MinimumSize = new System.Drawing.Size(20, 20);
            this.WB3.Name = "WB3";
            this.WB3.Size = new System.Drawing.Size(67, 20);
            this.WB3.TabIndex = 3;
            this.WB3.Visible = false;
            this.WB3.DocumentCompleted += new System.Windows.Forms.WebBrowserDocumentCompletedEventHandler(this.WB3_DocumentCompleted);
            // 
            // btn_MPU_GetData
            // 
            this.btn_MPU_GetData.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.btn_MPU_GetData.Location = new System.Drawing.Point(106, 17);
            this.btn_MPU_GetData.Name = "btn_MPU_GetData";
            this.btn_MPU_GetData.Size = new System.Drawing.Size(95, 23);
            this.btn_MPU_GetData.TabIndex = 8;
            this.btn_MPU_GetData.Text = "Get Data";
            this.btn_MPU_GetData.UseVisualStyleBackColor = true;
            this.btn_MPU_GetData.Click += new System.EventHandler(this.btn_MPU_GetData_Click);
            // 
            // lbl_MPU_Data_X
            // 
            this.lbl_MPU_Data_X.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lbl_MPU_Data_X.Location = new System.Drawing.Point(207, 16);
            this.lbl_MPU_Data_X.Name = "lbl_MPU_Data_X";
            this.lbl_MPU_Data_X.Size = new System.Drawing.Size(175, 23);
            this.lbl_MPU_Data_X.TabIndex = 9;
            this.lbl_MPU_Data_X.Text = "X";
            this.lbl_MPU_Data_X.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lbl_MPU_Data_Y
            // 
            this.lbl_MPU_Data_Y.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lbl_MPU_Data_Y.Location = new System.Drawing.Point(388, 16);
            this.lbl_MPU_Data_Y.Name = "lbl_MPU_Data_Y";
            this.lbl_MPU_Data_Y.Size = new System.Drawing.Size(175, 23);
            this.lbl_MPU_Data_Y.TabIndex = 10;
            this.lbl_MPU_Data_Y.Text = "Y";
            this.lbl_MPU_Data_Y.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lbl_MPU_Data_Z
            // 
            this.lbl_MPU_Data_Z.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lbl_MPU_Data_Z.Location = new System.Drawing.Point(569, 16);
            this.lbl_MPU_Data_Z.Name = "lbl_MPU_Data_Z";
            this.lbl_MPU_Data_Z.Size = new System.Drawing.Size(175, 23);
            this.lbl_MPU_Data_Z.TabIndex = 11;
            this.lbl_MPU_Data_Z.Text = "Z";
            this.lbl_MPU_Data_Z.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(1282, 571);
            this.Controls.Add(this.WB3);
            this.Controls.Add(this.grp_MPU);
            this.Controls.Add(this.grp_COM);
            this.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Navigator";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.grp_COM.ResumeLayout(false);
            this.grp_COM.PerformLayout();
            this.grp_MPU.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grp_COM;
        private System.Windows.Forms.Button btn_COM_Connect;
        private System.Windows.Forms.TextBox txt_COM_Target_PORT;
        private System.Windows.Forms.Label lbl_Show_2;
        private System.Windows.Forms.TextBox txt_COM_Target_IP;
        private System.Windows.Forms.Label lbl_Show_1;
        private System.Windows.Forms.Label lbl_COM_Status;
        private System.Windows.Forms.Label CHK_1_COM;
        private System.Windows.Forms.Button btn_COM_TogglePING;
        private System.Windows.Forms.Timer tmr_COM_TogglePING;
        private System.Windows.Forms.GroupBox grp_MPU;
        private System.Windows.Forms.Label CHK_2_MPU;
        private System.Windows.Forms.WebBrowser WB1;
        private System.Windows.Forms.Button btn_MPU_CalibDir;
        private System.Windows.Forms.WebBrowser WB2;
        private System.Windows.Forms.Button btn_MPU_GetData;
        private System.Windows.Forms.Timer tmr_MPU_GetData;
        private System.Windows.Forms.WebBrowser WB3;
        private System.Windows.Forms.Label lbl_MPU_Data_Z;
        private System.Windows.Forms.Label lbl_MPU_Data_Y;
        private System.Windows.Forms.Label lbl_MPU_Data_X;
    }
}

