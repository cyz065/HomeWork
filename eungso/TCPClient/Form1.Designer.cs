
namespace TCPClient
{
    partial class Client_Form
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Client_Form));
            this.ip_label = new System.Windows.Forms.Label();
            this.path_label = new System.Windows.Forms.Label();
            this.ip_txtBox = new System.Windows.Forms.TextBox();
            this.path_txtBox = new System.Windows.Forms.TextBox();
            this.port_label = new System.Windows.Forms.Label();
            this.port_txtBox = new System.Windows.Forms.TextBox();
            this.connect_btn = new System.Windows.Forms.Button();
            this.path_btn = new System.Windows.Forms.Button();
            this.open_btn = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.listView1 = new System.Windows.Forms.ListView();
            this.file_name = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.file_size = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.date = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.menu_Info = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_download = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.menu_detail = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_simple = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_small = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_big = new System.Windows.Forms.ToolStripMenuItem();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.groupBox1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ip_label
            // 
            this.ip_label.AutoSize = true;
            this.ip_label.Location = new System.Drawing.Point(19, 20);
            this.ip_label.Name = "ip_label";
            this.ip_label.Size = new System.Drawing.Size(20, 12);
            this.ip_label.TabIndex = 0;
            this.ip_label.Text = "IP:";
            // 
            // path_label
            // 
            this.path_label.AutoSize = true;
            this.path_label.Location = new System.Drawing.Point(19, 52);
            this.path_label.Name = "path_label";
            this.path_label.Size = new System.Drawing.Size(85, 12);
            this.path_label.TabIndex = 1;
            this.path_label.Text = "다운로드 경로:";
            // 
            // ip_txtBox
            // 
            this.ip_txtBox.Location = new System.Drawing.Point(45, 15);
            this.ip_txtBox.Name = "ip_txtBox";
            this.ip_txtBox.Size = new System.Drawing.Size(561, 21);
            this.ip_txtBox.TabIndex = 2;
            // 
            // path_txtBox
            // 
            this.path_txtBox.Location = new System.Drawing.Point(110, 48);
            this.path_txtBox.Name = "path_txtBox";
            this.path_txtBox.ReadOnly = true;
            this.path_txtBox.Size = new System.Drawing.Size(647, 21);
            this.path_txtBox.TabIndex = 3;
            // 
            // port_label
            // 
            this.port_label.AutoSize = true;
            this.port_label.Location = new System.Drawing.Point(611, 20);
            this.port_label.Name = "port_label";
            this.port_label.Size = new System.Drawing.Size(42, 12);
            this.port_label.TabIndex = 4;
            this.port_label.Text = "PORT:";
            // 
            // port_txtBox
            // 
            this.port_txtBox.Location = new System.Drawing.Point(659, 15);
            this.port_txtBox.Name = "port_txtBox";
            this.port_txtBox.Size = new System.Drawing.Size(98, 21);
            this.port_txtBox.TabIndex = 5;
            // 
            // connect_btn
            // 
            this.connect_btn.Location = new System.Drawing.Point(156, 88);
            this.connect_btn.Name = "connect_btn";
            this.connect_btn.Size = new System.Drawing.Size(75, 23);
            this.connect_btn.TabIndex = 6;
            this.connect_btn.Text = "서버연결";
            this.connect_btn.UseVisualStyleBackColor = true;
            this.connect_btn.Click += new System.EventHandler(this.connect_btn_Click);
            // 
            // path_btn
            // 
            this.path_btn.Location = new System.Drawing.Point(355, 88);
            this.path_btn.Name = "path_btn";
            this.path_btn.Size = new System.Drawing.Size(75, 23);
            this.path_btn.TabIndex = 7;
            this.path_btn.Text = "경로설정";
            this.path_btn.UseVisualStyleBackColor = true;
            this.path_btn.Click += new System.EventHandler(this.path_btn_Click);
            // 
            // open_btn
            // 
            this.open_btn.Location = new System.Drawing.Point(557, 88);
            this.open_btn.Name = "open_btn";
            this.open_btn.Size = new System.Drawing.Size(75, 23);
            this.open_btn.TabIndex = 8;
            this.open_btn.Text = "폴더열기";
            this.open_btn.UseVisualStyleBackColor = true;
            this.open_btn.Click += new System.EventHandler(this.open_btn_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.panel1);
            this.groupBox1.Location = new System.Drawing.Point(12, 117);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(785, 486);
            this.groupBox1.TabIndex = 9;
            this.groupBox1.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.listView1);
            this.panel1.Controls.Add(this.splitter1);
            this.panel1.Controls.Add(this.treeView1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 17);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(779, 466);
            this.panel1.TabIndex = 0;
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.file_name,
            this.file_size,
            this.date});
            this.listView1.ContextMenuStrip = this.contextMenuStrip1;
            this.listView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView1.HideSelection = false;
            this.listView1.LargeImageList = this.imageList1;
            this.listView1.Location = new System.Drawing.Point(187, 0);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(592, 466);
            this.listView1.SmallImageList = this.imageList1;
            this.listView1.TabIndex = 2;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.DoubleClick += new System.EventHandler(this.listView1_DoubleClick);
            this.listView1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listView1_MouseClick);
            // 
            // file_name
            // 
            this.file_name.Text = "파일이름";
            // 
            // file_size
            // 
            this.file_size.Text = "파일크기";
            // 
            // date
            // 
            this.date.Text = "수정한날짜";
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_Info,
            this.menu_download,
            this.toolStripMenuItem1,
            this.menu_detail,
            this.menu_simple,
            this.menu_small,
            this.menu_big});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(135, 142);
            // 
            // menu_Info
            // 
            this.menu_Info.Name = "menu_Info";
            this.menu_Info.Size = new System.Drawing.Size(134, 22);
            this.menu_Info.Text = "상세정보";
            this.menu_Info.Click += new System.EventHandler(this.menu_Info_Click);
            // 
            // menu_download
            // 
            this.menu_download.Name = "menu_download";
            this.menu_download.Size = new System.Drawing.Size(134, 22);
            this.menu_download.Text = "다운로드";
            this.menu_download.Click += new System.EventHandler(this.menu_download_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(131, 6);
            // 
            // menu_detail
            // 
            this.menu_detail.Name = "menu_detail";
            this.menu_detail.Size = new System.Drawing.Size(134, 22);
            this.menu_detail.Text = "자세히";
            this.menu_detail.Click += new System.EventHandler(this.menu_Click);
            // 
            // menu_simple
            // 
            this.menu_simple.Name = "menu_simple";
            this.menu_simple.Size = new System.Drawing.Size(134, 22);
            this.menu_simple.Text = "간단히";
            this.menu_simple.Click += new System.EventHandler(this.menu_Click);
            // 
            // menu_small
            // 
            this.menu_small.Name = "menu_small";
            this.menu_small.Size = new System.Drawing.Size(134, 22);
            this.menu_small.Text = "작은아이콘";
            this.menu_small.Click += new System.EventHandler(this.menu_Click);
            // 
            // menu_big
            // 
            this.menu_big.Name = "menu_big";
            this.menu_big.Size = new System.Drawing.Size(134, 22);
            this.menu_big.Text = "큰아이콘";
            this.menu_big.Click += new System.EventHandler(this.menu_Click);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "folder.png");
            this.imageList1.Images.SetKeyName(1, "avi.png");
            this.imageList1.Images.SetKeyName(2, "image.png");
            this.imageList1.Images.SetKeyName(3, "music.png");
            this.imageList1.Images.SetKeyName(4, "text.png");
            this.imageList1.Images.SetKeyName(5, "temp.png");
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(184, 0);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 466);
            this.splitter1.TabIndex = 1;
            this.splitter1.TabStop = false;
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Left;
            this.treeView1.ImageIndex = 0;
            this.treeView1.ImageList = this.imageList1;
            this.treeView1.Location = new System.Drawing.Point(0, 0);
            this.treeView1.Name = "treeView1";
            this.treeView1.SelectedImageIndex = 0;
            this.treeView1.Size = new System.Drawing.Size(184, 466);
            this.treeView1.TabIndex = 0;
            this.treeView1.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler(this.treeView1_BeforeExpand);
            this.treeView1.BeforeSelect += new System.Windows.Forms.TreeViewCancelEventHandler(this.treeView1_BeforeSelect);
            // 
            // Client_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(809, 616);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.open_btn);
            this.Controls.Add(this.path_btn);
            this.Controls.Add(this.connect_btn);
            this.Controls.Add(this.port_txtBox);
            this.Controls.Add(this.port_label);
            this.Controls.Add(this.path_txtBox);
            this.Controls.Add(this.ip_txtBox);
            this.Controls.Add(this.path_label);
            this.Controls.Add(this.ip_label);
            this.Name = "Client_Form";
            this.Text = "FileManager - Client";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Client_Form_FormClosing);
            this.groupBox1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label ip_label;
        private System.Windows.Forms.Label path_label;
        private System.Windows.Forms.TextBox ip_txtBox;
        private System.Windows.Forms.TextBox path_txtBox;
        private System.Windows.Forms.Label port_label;
        private System.Windows.Forms.TextBox port_txtBox;
        private System.Windows.Forms.Button connect_btn;
        private System.Windows.Forms.Button path_btn;
        private System.Windows.Forms.Button open_btn;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem menu_Info;
        private System.Windows.Forms.ToolStripMenuItem menu_download;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem menu_detail;
        private System.Windows.Forms.ToolStripMenuItem menu_simple;
        private System.Windows.Forms.ToolStripMenuItem menu_small;
        private System.Windows.Forms.ToolStripMenuItem menu_big;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.ColumnHeader file_name;
        private System.Windows.Forms.ColumnHeader file_size;
        private System.Windows.Forms.ColumnHeader date;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
    }
}

