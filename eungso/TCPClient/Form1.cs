using System;
using System.Drawing;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;
using System.Diagnostics;

namespace TCPClient
{
    public partial class Client_Form : Form
    {
        TcpClient client;

        StreamReader reader;
        StreamWriter writer;
        NetworkStream network;
        Thread receiveThread;
        bool connected;

        // listView에서 선택된 icon의 이름을 get
        string selectedIcon = "";

        // 다운로드 할 파일의 경로
        string full_path;

        // 서버에서 얻어온 경로
        string get_path;

        public Client_Form()
        {
            InitializeComponent();
        }

        // 서버와의 연결
        private void connect_btn_Click(object sender, EventArgs e)
        {
            if (path_txtBox.Text == "")
            {
                MessageBox.Show("경로가 설정되어있지 않습니다.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else if (ip_txtBox.Text == "" || port_txtBox.Text == "")
            {
                MessageBox.Show("IP 또는 Port번호를 입력해 주세요", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else if (connect_btn.Text == "서버연결" && ip_txtBox.Text != "" && port_txtBox.Text != "")
            {
                Connect();
            }
            else if(connect_btn.Text == "서버 끊기" && ip_txtBox.Text != "" && port_txtBox.Text != "")
            {
                Disconnect();
                connect_btn.Text = "서버연결";
                connect_btn.ForeColor = Color.Black;
            }         
        }

        public void Disconnect()
        {
            if (!connected)
                return;
            connected = false;
            reader.Close();
            writer.Close();
            network.Close();
            client.Close();
            receiveThread.Abort();
        }

        public void Connect()
        {
            client = new TcpClient();
            if (!client.Connected)
            {
                try
                {
                    client.Connect(ip_txtBox.Text, Int32.Parse(port_txtBox.Text));
                }
                catch
                {
                    connected = false;
                    MessageBox.Show("서버를 확인해 주세요", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                connected = true;
                connect_btn.Text = "서버 끊기";
                connect_btn.ForeColor = Color.Red;

                network = client.GetStream();
                reader = new StreamReader(network);
                writer = new StreamWriter(network);
                ReceivePathData();
            }
            receiveThread = new Thread(new ThreadStart(Receive));
            receiveThread.Start();
        }

        public void ReceivePathData()
        {
            get_path = reader.ReadLine();
            if (get_path != null)
                show_directory();
        }

        public void Receive()
        {
            try
            {
                while (connected)
                {
                    if(get_path != null)
                        get_path = reader.ReadLine();
                }
            }
            catch
            {
                //MessageBox.Show("Receive Error");
            }
            Disconnect();
        }

        private void Send(int num)
        {
            try
            {
                if (num == 1) {
                    writer.WriteLine("Before Expand 데이터 요청...");
                    writer.Flush();
                }
                else if(num == 2)
                {
                    writer.WriteLine("Before Select 데이터 요청...");
                    writer.Flush();
                }
                else if(num == 3)
                {
                    writer.WriteLine(full_path + " 데이터 다운로드 완료...");
                    writer.Flush();
                }
            }
            catch
            {
                //MessageBox.Show("데이터 전송 실패");
            }
        }
        private void Client_Form_FormClosing(object sender, FormClosingEventArgs e)
        {
            Disconnect();
        }

        // 다운로드 경로 설정
        private void path_btn_Click(object sender, EventArgs e)
        {
            if(folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                get_path = folderBrowserDialog1.SelectedPath;
                path_txtBox.Text = get_path;
            }
        }


        /* Tree View */
        // TreeView에 디렉토리 목록 생성
        private void show_directory()
        {
            // treeView 초기화
            treeView1.Nodes.Clear();

            DirectoryInfo di = new DirectoryInfo(get_path);
            TreeNode root = treeView1.Nodes.Add(di.FullName);
            root.Tag = "D";

            treeView1.SelectedNode = root;
            root.Nodes.Add("");
        }

        // 디렉토리 내의 파일들을 load
        private void LoadFiles(string path, TreeNode root)
        {
            string[] files = Directory.GetFiles(path, "*.*");

            foreach(string file in files)
            {
                FileInfo fi = new FileInfo(file);
                TreeNode tmp = root.Nodes.Add(fi.Name);
                if (fi.Extension == ".jpg" || fi.Extension == ".png")
                    tmp.ImageIndex = 2;
                else if (fi.Extension == ".avi" || fi.Extension == ".mp4" || fi.Extension == ".wmv")
                    tmp.ImageIndex = 1;
                else if (fi.Extension == ".mp3")
                    tmp.ImageIndex = 3;
                else if (fi.Extension == ".txt")
                    tmp.ImageIndex = 4;
                else
                    tmp.ImageIndex = 5;
                tmp.SelectedImageIndex = tmp.ImageIndex;
                tmp.Tag = "F";
            }
        }

        // 현재 디렉토리의 하위 디렉토리들 load
        private void LoadSubDirectory(string path, TreeNode root)
        {
            string[] dir_list = Directory.GetDirectories(path);
            root.Nodes.Clear();
            foreach (string sub in dir_list)
            {
                DirectoryInfo di = new DirectoryInfo(sub);
                TreeNode tmp = root.Nodes.Add(di.Name);
                tmp.Tag = "D";
                tmp.Nodes.Add("");
                tmp.ImageIndex = 0;
            }
        }

        // e : 트리노드 확장시 하위 디렉토리와 파일들을 트리노드에 추가
        private void treeView1_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            Send(1);
            string path;
            path = e.Node.FullPath;
            full_path = e.Node.FullPath;
            // e에 대한 디렉토리 추가
            LoadSubDirectory(path, e.Node);

            // e에 속하는 파일들을 추가
            LoadFiles(path, e.Node);
        }

        // treeview에서 특정 항목을 선택하면 listView에 해당 폴더의 파일 및 하위 디렉토리를 보여줌
        private void treeView1_BeforeSelect(object sender, TreeViewCancelEventArgs e)
        {
            Send(2);
            if (e.Node.Tag.ToString() != "D")  
                return;

            DirectoryInfo di;
            DirectoryInfo[] sub_dir;
            ListViewItem item;

            string path = e.Node.FullPath;
            full_path = e.Node.FullPath;
            string[] files = Directory.GetFiles(path, "*.*");

            try
            {
                listView1.Items.Clear();
                di = new DirectoryInfo(path);
                sub_dir = di.GetDirectories();
                foreach(DirectoryInfo sub in sub_dir)
                {
                    item = listView1.Items.Add(sub.Name);
                    item.SubItems.Add("");
                    item.SubItems.Add(sub.LastWriteTime.ToString());
                    item.ImageIndex = 0;
                    item.Tag = "D";
                }

                // 상세 정보 출력을 위해 파일의 특징들을 subItem으로 저장
                foreach(string file in files)
                {
                    FileInfo fi = new FileInfo(file);
                    item = listView1.Items.Add(fi.Name);    // [0]
                    item.SubItems.Add(fi.Length.ToString()); // [1]
                    item.SubItems.Add(fi.LastWriteTime.ToString()); //[2]

                    item.SubItems.Add(fi.CreationTime.ToString()); //[3]
                    item.SubItems.Add(fi.LastAccessTime.ToString()); // [4]
                    item.SubItems.Add(fi.Extension);    //[5]
                    item.SubItems.Add(fi.FullName); // [6]

                    // 파일의 확장자에 따라 Tag를 설정하여 분류
                    if (fi.Extension == ".jpg" || fi.Extension == ".png" || fi.Extension == ".jpeg")
                    {
                        item.ImageIndex = 2;
                        item.Tag = "I";
                    }
                    else if (fi.Extension == ".avi" || fi.Extension == ".mp4" || fi.Extension == ".wmv")
                    {
                        item.ImageIndex = 1;
                        item.Tag = "V";
                    }
                    else if (fi.Extension == ".mp3")
                    {
                        item.ImageIndex = 3;
                        item.Tag = "M";
                    }
                    else if (fi.Extension == ".txt")
                    {
                        item.ImageIndex = 4;
                        item.Tag = "T";
                    }
                    else
                    {
                        item.ImageIndex = 5;
                        item.Tag = "X";
                    }
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /* ListView */
        // 마우스 우클릭시 출력되는 menu strip
        private void menu_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem item = (ToolStripMenuItem)sender;
            menu_detail.Checked = false;
            menu_big.Checked = false;
            menu_simple.Checked = false;
            menu_small.Checked = false;

            switch(item.Text)
            {
                case "자세히":
                    menu_detail.Checked = true;
                    listView1.View = View.Details;
                    break;
                case "간단히":
                    menu_simple.Checked = true;
                    listView1.View = View.List;
                    break;
                case "작은아이콘":
                    menu_small.Checked = true;
                    listView1.View = View.SmallIcon;
                    break;
                case "큰아이콘":
                    menu_big.Checked = true;
                    listView1.View = View.LargeIcon;
                    break;
            }
        }

        // 상세정보 출력
        private void menu_Info_Click(object sender, EventArgs e)
        {
            if (selectedIcon != "")
            {
                // 선택된 item의 정보를 get
                ListViewItem item = listView1.Items[listView1.FocusedItem.Index];
                string image_tag = item.Tag.ToString();

                // 디렉토리의 경우 처리
                if (image_tag == "D")
                {
                    MessageBox.Show("디렉토리는 상세정보를 지원하지 않습니다", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    selectedIcon = "";
                    return;
                }

                // 선택된 item의 정보를 set
                string file_name = item.SubItems[0].Text;
                string file_size = item.SubItems[1].Text;
                string write_time = item.SubItems[2].Text;
                string create_time = item.SubItems[3].Text;
                string access_time = item.SubItems[4].Text;
                string extension = item.SubItems[5].Text.Substring(1);
                string location = item.SubItems[6].Text;

                // 자식폼을 modal로 출력
                Form2 form2 = new Form2(image_tag, file_name, file_size, write_time, create_time, access_time, extension, location);
                form2.ShowDialog();

                // Listview의 비어있는 공간에서 상세정보를 클릭하는 경우 아무것도 띄우지 않는다.
                selectedIcon = "";
            }

            // selected가 없는 경우에는 빈 공간에서 클릭한 경우이므로 단순히 return
            else
                return;
        }

        // listView의 특정 item 우클릭시 해당 파일 또는 디렉토리의 이름 get
        private void listView1_MouseClick(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Right)
            {
                selectedIcon = listView1.GetItemAt(e.X, e.Y).Text;
            }
        }

        //  디렉토리 더블클릭시 해당 디렉토리로 이동 & 하위 디렉토리 출력
        //  파일 더블클릭시 해당 파일의 상세정보 출력
        private void listView1_DoubleClick(object sender, EventArgs e)
        {
            ListViewItem item = listView1.Items[listView1.FocusedItem.Index];
            string image_tag = item.Tag.ToString();
            if (image_tag == "D")
            {
                ListView.SelectedListViewItemCollection item_list;
                item_list = listView1.SelectedItems;

                foreach(ListViewItem i in item_list)
                    OpenItem(i);
                return;
            }

            string file_name = item.SubItems[0].Text;
            string file_size = item.SubItems[1].Text;
            string write_time = item.SubItems[2].Text;
            string create_time = item.SubItems[3].Text;
            string access_time = item.SubItems[4].Text;
            string extension = item.SubItems[5].Text.Substring(1);
            string location = item.SubItems[6].Text;

            Form2 form2 = new Form2(image_tag, file_name, file_size, write_time, create_time, access_time, extension, location);
            form2.ShowDialog();
        }

        // ListView에서 폴더 더블클릭 시 하위 디렉토리 및 파일들을 출력
        private void OpenItem(ListViewItem item)
        {
            TreeNode node;
            TreeNode child;

            if (item.Tag.ToString() == "D")
            {
                node = treeView1.SelectedNode;
                node.Expand();

                child = node.FirstNode;
                while (child != null)
                {
                    if (child.Text == item.Text)
                    {
                        treeView1.SelectedNode = child;
                        treeView1.Focus();
                        break;
                    }
                    child = child.NextNode;
                }
            }
        }

        // 다운로드 항목 클릭
        private void menu_download_Click(object sender, EventArgs e)
        {
            if (selectedIcon != "")
            {
                ListViewItem item = listView1.Items[listView1.FocusedItem.Index];
                string image_tag = item.Tag.ToString();
                
                // 디렉토리의 경우 다운로드 X
                if (image_tag == "D")
                    MessageBox.Show("폴더는 다운로드를 지원하지 않습니다.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                else
                {
                    // 파일이 다운로드될 위치
                    string download_path = path_txtBox.Text;

                    // 현재 경로를 저장하기 위한 변수
                    string tmp_path = full_path;

                    full_path = Path.GetFullPath(tmp_path + "\\" + selectedIcon);

                    FileStream sourceFileStream = File.OpenRead(full_path);
                    byte[] fileBuffer = new byte[sourceFileStream.Length];
                    sourceFileStream.Read(fileBuffer, 0, (int)sourceFileStream.Length);

                    FileStream destFileStream;

                    // 이미 존재하는 파일의 경우 다운로드 여부 선택
                    if(File.Exists(download_path + "\\" + selectedIcon))
                    {
                        if (MessageBox.Show("이미 존재하는 파일입니다. 다운로드 하시겠습니까?", "Warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
                        {     
                            destFileStream = new FileStream(download_path + "\\" + selectedIcon, FileMode.Create);
                            destFileStream.Write(fileBuffer, 0, fileBuffer.Length);
                            destFileStream.Flush();
                            destFileStream.Close();
                            Send(3);
                        }
                    }
                    else
                    {
                        destFileStream = new FileStream(download_path + "\\" + selectedIcon, FileMode.Create);
                        destFileStream.Write(fileBuffer, 0, fileBuffer.Length);
                        destFileStream.Flush();
                        destFileStream.Close();
                        Send(3);
                    }
                    sourceFileStream.Close();
                    full_path = tmp_path;
                }
                selectedIcon = "";
            }

            // selected가 없는 경우에는 빈 공간에서 클릭한 경우이므로 단순히 return
            else
                return;
        }

        private void open_btn_Click(object sender, EventArgs e)
        {
            if(path_txtBox.Text != "")
                Process.Start(path_txtBox.Text);
        }
    }
}
