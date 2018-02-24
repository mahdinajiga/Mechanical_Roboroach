namespace WindowsFormsApplication1
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
            this.a0 = new System.Windows.Forms.Label();
            this.a1 = new System.Windows.Forms.Label();
            this.a2 = new System.Windows.Forms.Label();
            this.a3 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // a0
            // 
            this.a0.AutoSize = true;
            this.a0.BackColor = System.Drawing.Color.Black;
            this.a0.Location = new System.Drawing.Point(55, 9);
            this.a0.Name = "a0";
            this.a0.Size = new System.Drawing.Size(9, 13);
            this.a0.TabIndex = 0;
            this.a0.Text = "l";
            // 
            // a1
            // 
            this.a1.AutoSize = true;
            this.a1.BackColor = System.Drawing.Color.Black;
            this.a1.Location = new System.Drawing.Point(70, 9);
            this.a1.Name = "a1";
            this.a1.Size = new System.Drawing.Size(9, 13);
            this.a1.TabIndex = 1;
            this.a1.Text = "l";
            // 
            // a2
            // 
            this.a2.AutoSize = true;
            this.a2.BackColor = System.Drawing.Color.Black;
            this.a2.Location = new System.Drawing.Point(85, 9);
            this.a2.Name = "a2";
            this.a2.Size = new System.Drawing.Size(9, 13);
            this.a2.TabIndex = 2;
            this.a2.Text = "l";
            // 
            // a3
            // 
            this.a3.AutoSize = true;
            this.a3.BackColor = System.Drawing.Color.Black;
            this.a3.Location = new System.Drawing.Point(100, 9);
            this.a3.Name = "a3";
            this.a3.Size = new System.Drawing.Size(9, 13);
            this.a3.TabIndex = 3;
            this.a3.Text = "l";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1400;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(166, 29);
            this.Controls.Add(this.a3);
            this.Controls.Add(this.a2);
            this.Controls.Add(this.a1);
            this.Controls.Add(this.a0);
            this.Name = "Form1";
            this.ShowIcon = false;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label a0;
        private System.Windows.Forms.Label a1;
        private System.Windows.Forms.Label a2;
        private System.Windows.Forms.Label a3;
        private System.Windows.Forms.Timer timer1;
    }
}

