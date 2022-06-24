
namespace TCPClient
{
    partial class Form2
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
            this.file_icon = new System.Windows.Forms.PictureBox();
            this.file_name = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.file_type_label = new System.Windows.Forms.Label();
            this.file_type = new System.Windows.Forms.Label();
            this.location_label = new System.Windows.Forms.Label();
            this.location = new System.Windows.Forms.Label();
            this.file_size_label = new System.Windows.Forms.Label();
            this.file_size = new System.Windows.Forms.Label();
            this.make_day_label = new System.Windows.Forms.Label();
            this.make_day = new System.Windows.Forms.Label();
            this.modify_label = new System.Windows.Forms.Label();
            this.modify = new System.Windows.Forms.Label();
            this.access_label = new System.Windows.Forms.Label();
            this.access = new System.Windows.Forms.Label();
            this.close_btn = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.file_icon)).BeginInit();
            this.SuspendLayout();
            // 
            // file_icon
            // 
            this.file_icon.Image = global::TCPClient.Properties.Resources.text;
            this.file_icon.Location = new System.Drawing.Point(27, 12);
            this.file_icon.Name = "file_icon";
            this.file_icon.Size = new System.Drawing.Size(129, 182);
            this.file_icon.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.file_icon.TabIndex = 0;
            this.file_icon.TabStop = false;
            // 
            // file_name
            // 
            this.file_name.Location = new System.Drawing.Point(251, 94);
            this.file_name.Name = "file_name";
            this.file_name.Size = new System.Drawing.Size(356, 21);
            this.file_name.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label1.Location = new System.Drawing.Point(10, 208);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(635, 2);
            this.label1.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label2.Location = new System.Drawing.Point(10, 327);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(635, 2);
            this.label2.TabIndex = 3;
            // 
            // file_type_label
            // 
            this.file_type_label.AutoSize = true;
            this.file_type_label.Location = new System.Drawing.Point(32, 230);
            this.file_type_label.Name = "file_type_label";
            this.file_type_label.Size = new System.Drawing.Size(61, 12);
            this.file_type_label.TabIndex = 4;
            this.file_type_label.Text = "파일 형식:";
            // 
            // file_type
            // 
            this.file_type.AutoSize = true;
            this.file_type.Location = new System.Drawing.Point(156, 230);
            this.file_type.Name = "file_type";
            this.file_type.Size = new System.Drawing.Size(0, 12);
            this.file_type.TabIndex = 5;
            // 
            // location_label
            // 
            this.location_label.AutoSize = true;
            this.location_label.Location = new System.Drawing.Point(32, 265);
            this.location_label.Name = "location_label";
            this.location_label.Size = new System.Drawing.Size(33, 12);
            this.location_label.TabIndex = 6;
            this.location_label.Text = "위치:";
            // 
            // location
            // 
            this.location.AutoSize = true;
            this.location.Location = new System.Drawing.Point(156, 265);
            this.location.Name = "location";
            this.location.Size = new System.Drawing.Size(0, 12);
            this.location.TabIndex = 7;
            // 
            // file_size_label
            // 
            this.file_size_label.AutoSize = true;
            this.file_size_label.Location = new System.Drawing.Point(32, 299);
            this.file_size_label.Name = "file_size_label";
            this.file_size_label.Size = new System.Drawing.Size(33, 12);
            this.file_size_label.TabIndex = 8;
            this.file_size_label.Text = "크기:";
            // 
            // file_size
            // 
            this.file_size.AutoSize = true;
            this.file_size.Location = new System.Drawing.Point(156, 299);
            this.file_size.Name = "file_size";
            this.file_size.Size = new System.Drawing.Size(0, 12);
            this.file_size.TabIndex = 9;
            // 
            // make_day_label
            // 
            this.make_day_label.AutoSize = true;
            this.make_day_label.Location = new System.Drawing.Point(32, 343);
            this.make_day_label.Name = "make_day_label";
            this.make_day_label.Size = new System.Drawing.Size(61, 12);
            this.make_day_label.TabIndex = 10;
            this.make_day_label.Text = "만든 날짜:";
            // 
            // make_day
            // 
            this.make_day.AutoSize = true;
            this.make_day.Location = new System.Drawing.Point(156, 343);
            this.make_day.Name = "make_day";
            this.make_day.Size = new System.Drawing.Size(0, 12);
            this.make_day.TabIndex = 11;
            // 
            // modify_label
            // 
            this.modify_label.AutoSize = true;
            this.modify_label.Location = new System.Drawing.Point(32, 379);
            this.modify_label.Name = "modify_label";
            this.modify_label.Size = new System.Drawing.Size(73, 12);
            this.modify_label.TabIndex = 12;
            this.modify_label.Text = "수정한 날짜:";
            // 
            // modify
            // 
            this.modify.AutoSize = true;
            this.modify.Location = new System.Drawing.Point(156, 379);
            this.modify.Name = "modify";
            this.modify.Size = new System.Drawing.Size(0, 12);
            this.modify.TabIndex = 13;
            // 
            // access_label
            // 
            this.access_label.AutoSize = true;
            this.access_label.Location = new System.Drawing.Point(32, 416);
            this.access_label.Name = "access_label";
            this.access_label.Size = new System.Drawing.Size(81, 12);
            this.access_label.TabIndex = 14;
            this.access_label.Text = "엑세스한 날짜";
            // 
            // access
            // 
            this.access.AutoSize = true;
            this.access.Location = new System.Drawing.Point(156, 416);
            this.access.Name = "access";
            this.access.Size = new System.Drawing.Size(0, 12);
            this.access.TabIndex = 15;
            // 
            // close_btn
            // 
            this.close_btn.Location = new System.Drawing.Point(525, 442);
            this.close_btn.Name = "close_btn";
            this.close_btn.Size = new System.Drawing.Size(82, 30);
            this.close_btn.TabIndex = 16;
            this.close_btn.Text = "확인";
            this.close_btn.UseVisualStyleBackColor = true;
            this.close_btn.Click += new System.EventHandler(this.close_btn_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(655, 484);
            this.Controls.Add(this.close_btn);
            this.Controls.Add(this.access);
            this.Controls.Add(this.access_label);
            this.Controls.Add(this.modify);
            this.Controls.Add(this.modify_label);
            this.Controls.Add(this.make_day);
            this.Controls.Add(this.make_day_label);
            this.Controls.Add(this.file_size);
            this.Controls.Add(this.file_size_label);
            this.Controls.Add(this.location);
            this.Controls.Add(this.location_label);
            this.Controls.Add(this.file_type);
            this.Controls.Add(this.file_type_label);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.file_name);
            this.Controls.Add(this.file_icon);
            this.Name = "Form2";
            this.Text = "상세정보";
            ((System.ComponentModel.ISupportInitialize)(this.file_icon)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox file_icon;
        private System.Windows.Forms.TextBox file_name;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label file_type_label;
        private System.Windows.Forms.Label file_type;
        private System.Windows.Forms.Label location_label;
        private System.Windows.Forms.Label location;
        private System.Windows.Forms.Label file_size_label;
        private System.Windows.Forms.Label file_size;
        private System.Windows.Forms.Label make_day_label;
        private System.Windows.Forms.Label make_day;
        private System.Windows.Forms.Label modify_label;
        private System.Windows.Forms.Label modify;
        private System.Windows.Forms.Label access_label;
        private System.Windows.Forms.Label access;
        private System.Windows.Forms.Button close_btn;
    }
}