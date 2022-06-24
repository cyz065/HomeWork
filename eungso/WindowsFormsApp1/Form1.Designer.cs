
using System;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    partial class Server_Form
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.ip_label = new System.Windows.Forms.Label();
            this.port_label = new System.Windows.Forms.Label();
            this.path_label = new System.Windows.Forms.Label();
            this.ip_txtBox = new System.Windows.Forms.TextBox();
            this.port_txtBox = new System.Windows.Forms.TextBox();
            this.path_txtBox = new System.Windows.Forms.TextBox();
            this.On_Off_Btn = new System.Windows.Forms.Button();
            this.path_btn = new System.Windows.Forms.Button();
            this.logBox = new System.Windows.Forms.GroupBox();
            this.log_txt = new System.Windows.Forms.TextBox();
            this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.logBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // ip_label
            // 
            this.ip_label.AutoSize = true;
            this.ip_label.Location = new System.Drawing.Point(40, 38);
            this.ip_label.Name = "ip_label";
            this.ip_label.Size = new System.Drawing.Size(16, 12);
            this.ip_label.TabIndex = 0;
            this.ip_label.Text = "IP";
            // 
            // port_label
            // 
            this.port_label.AutoSize = true;
            this.port_label.Location = new System.Drawing.Point(40, 77);
            this.port_label.Name = "port_label";
            this.port_label.Size = new System.Drawing.Size(38, 12);
            this.port_label.TabIndex = 1;
            this.port_label.Text = "PORT";
            // 
            // path_label
            // 
            this.path_label.AutoSize = true;
            this.path_label.Location = new System.Drawing.Point(40, 112);
            this.path_label.Name = "path_label";
            this.path_label.Size = new System.Drawing.Size(37, 12);
            this.path_label.TabIndex = 2;
            this.path_label.Text = "PATH";
            // 
            // ip_txtBox
            // 
            this.ip_txtBox.Location = new System.Drawing.Point(109, 34);
            this.ip_txtBox.Name = "ip_txtBox";
            this.ip_txtBox.Size = new System.Drawing.Size(299, 21);
            this.ip_txtBox.TabIndex = 3;
            // 
            // port_txtBox
            // 
            this.port_txtBox.Location = new System.Drawing.Point(109, 72);
            this.port_txtBox.Name = "port_txtBox";
            this.port_txtBox.Size = new System.Drawing.Size(299, 21);
            this.port_txtBox.TabIndex = 4;
            // 
            // path_txtBox
            // 
            this.path_txtBox.Location = new System.Drawing.Point(109, 109);
            this.path_txtBox.Name = "path_txtBox";
            this.path_txtBox.ReadOnly = true;
            this.path_txtBox.Size = new System.Drawing.Size(299, 21);
            this.path_txtBox.TabIndex = 5;
            // 
            // On_Off_Btn
            // 
            this.On_Off_Btn.Location = new System.Drawing.Point(480, 50);
            this.On_Off_Btn.Name = "On_Off_Btn";
            this.On_Off_Btn.Size = new System.Drawing.Size(120, 39);
            this.On_Off_Btn.TabIndex = 6;
            this.On_Off_Btn.Text = "서버켜기";
            this.On_Off_Btn.UseVisualStyleBackColor = true;
            this.On_Off_Btn.Click += new System.EventHandler(this.On_Off_Btn_Click);
            // 
            // path_btn
            // 
            this.path_btn.Location = new System.Drawing.Point(480, 101);
            this.path_btn.Name = "path_btn";
            this.path_btn.Size = new System.Drawing.Size(120, 29);
            this.path_btn.TabIndex = 7;
            this.path_btn.Text = "경로선택";
            this.path_btn.UseVisualStyleBackColor = true;
            this.path_btn.Click += new System.EventHandler(this.path_btn_Click);
            // 
            // logBox
            // 
            this.logBox.Controls.Add(this.log_txt);
            this.logBox.Location = new System.Drawing.Point(42, 174);
            this.logBox.Name = "logBox";
            this.logBox.Size = new System.Drawing.Size(558, 264);
            this.logBox.TabIndex = 8;
            this.logBox.TabStop = false;
            this.logBox.Text = "log";
            // 
            // log_txt
            // 
            this.log_txt.Dock = System.Windows.Forms.DockStyle.Fill;
            this.log_txt.Location = new System.Drawing.Point(3, 17);
            this.log_txt.Multiline = true;
            this.log_txt.Name = "log_txt";
            this.log_txt.Size = new System.Drawing.Size(552, 244);
            this.log_txt.TabIndex = 0;
            // 
            // Server_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(628, 450);
            this.Controls.Add(this.logBox);
            this.Controls.Add(this.path_btn);
            this.Controls.Add(this.On_Off_Btn);
            this.Controls.Add(this.path_txtBox);
            this.Controls.Add(this.port_txtBox);
            this.Controls.Add(this.ip_txtBox);
            this.Controls.Add(this.path_label);
            this.Controls.Add(this.port_label);
            this.Controls.Add(this.ip_label);
            this.Name = "Server_Form";
            this.Text = "File Manager - Server";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Server_Form_FormClosing);
            this.logBox.ResumeLayout(false);
            this.logBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label ip_label;
        private System.Windows.Forms.Label port_label;
        private System.Windows.Forms.Label path_label;
        private System.Windows.Forms.TextBox ip_txtBox;
        private System.Windows.Forms.TextBox port_txtBox;
        private System.Windows.Forms.TextBox path_txtBox;
        private System.Windows.Forms.Button On_Off_Btn;
        private System.Windows.Forms.Button path_btn;
        private System.Windows.Forms.GroupBox logBox;
        private System.Windows.Forms.TextBox log_txt;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
    }
}

