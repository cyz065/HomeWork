using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TCPClient
{
    public partial class Form2 : Form
    {
        public Form2(string image_tag, string file_name, string file_size, string write_time, string create_time, string access_time, string extension, string location)
        {
            InitializeComponent();
            if (image_tag == "I")
                file_icon.Image = Properties.Resources.image;
            else if (image_tag == "V")
                file_icon.Image = Properties.Resources.avi;
            else if (image_tag == "M")
                file_icon.Image = Properties.Resources.music;
            else if (image_tag == "T")
                file_icon.Image = Properties.Resources.text;
            else if (image_tag == "X")
                file_icon.Image = Properties.Resources.temp;

            this.file_name.Text = file_name;
            this.file_size.Text = file_size;
            this.location.Text = location;
            file_type.Text = extension;
            make_day.Text = create_time;
            modify.Text = write_time;
            access.Text = access_time;
        }

        private void close_btn_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
