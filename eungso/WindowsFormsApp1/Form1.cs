using System;
using System.Drawing;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;

namespace WindowsFormsApp1
{
    public partial class Server_Form : Form
    {
        TcpListener server = null;
        TcpClient client = null;

        NetworkStream network;
        StreamReader reader;
        StreamWriter writer;

        Thread receiveThread;
        Thread listenThread;

        bool connected;
        bool started = false;
        string ip; int port; string path;
        string[] download_arr = null;

        public void Message(string msg)
        {
            this.Invoke(new MethodInvoker(delegate ()
            {
                log_txt.AppendText(msg + "\r\n");
                log_txt.Focus();
                log_txt.ScrollToCaret();
                log_txt.Focus();
            }));
        }

        public void Listen()
        {
            IPAddress addr = IPAddress.Parse(ip);
            server = new TcpListener(addr, port);
            try
            {
                server.Start();
                started = true;
                Message("클라이언트 접속 대기중...");

                while (started)
                {
                    client = server.AcceptTcpClient();

                    if (client.Connected)
                    {
                        connected = true;
                        Message("클라이언트 접속");

                        network = client.GetStream();
                        reader = new StreamReader(network);
                        writer = new StreamWriter(network);
                        Send();
                        receiveThread = new Thread(new ThreadStart(Receive));
                        receiveThread.Start();
                        if(download_arr != null)
                        {
                            Message(download_arr[0]);
                            Message(download_arr[1]);
                        }
                    }
                }
            }
            catch
            {
                Message("오류 발생");
                return;
            }
        }

        public Server_Form()
        {
            InitializeComponent();
        }

        // 경로를 선택
        private void path_btn_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
            {
                path = folderBrowserDialog.SelectedPath;
                path_txtBox.Text = path;
                Message(path + "로 경로가 수정되었습니다.");
            }
        }

        private void On_Off_Btn_Click(object sender, EventArgs e)
        {
            if (path == null)
            {
                MessageBox.Show("경로를 선택해주세요", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            else if (ip_txtBox.Text == "" || port_txtBox.Text == "")
            {
                MessageBox.Show("ip 또는 port번호를 입력해주세요", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            else if (On_Off_Btn.Text == "서버끊기")
            {
                On_Off_Btn.Text = "서버켜기";
                On_Off_Btn.ForeColor = Color.Black;
                ServerStop();
            }
            else if (On_Off_Btn.Text == "서버켜기")
            {
                ip = ip_txtBox.Text;
                port = Int32.Parse(port_txtBox.Text);
                listenThread = new Thread(new ThreadStart(Listen));
                listenThread.Start();

                On_Off_Btn.Text = "서버끊기";
                On_Off_Btn.ForeColor = Color.Red;
            }
        }

        public void ServerStop()
        {
            if (!started)
                return;

            if (server != null)
                server.Stop();

            if (reader != null)
                reader.Close();

            if (writer != null)
                writer.Close();

            if (receiveThread != null)
                receiveThread.Abort();

            if (listenThread != null)
                listenThread.Abort();

            Message("서비스 종료");
        }

        private void Disconnect()
        {
            if (!connected)
                return;
            connected = false;

            reader.Close();
            writer.Close();
            network.Close();
            receiveThread.Abort();
            //listenThread.Abort();
        }

        public void Receive()
        {
            try
            {
                while (client.Connected)
                {
                    string msg = reader.ReadLine();
                    if (msg != null)
                        Message(msg);
                }
            }

            catch
            {
                Message("Receive에러");
            }
            Disconnect();
        }

        public void Send()
        {
            try
            {
                writer.WriteLine(path);
                writer.Flush();

                Message("초기화 데이터 요청...");
            }
            catch
            {
                Message("데이터 전송 실패");
            }
        }

        private void Server_Form_FormClosing(object sender, FormClosingEventArgs e)
        {
            ServerStop();
        }
    }
}
