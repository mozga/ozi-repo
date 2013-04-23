using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace przegladarka
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void explorer_view_SelectedIndexChanged(object sender, EventArgs e)
        {
           string[] nazwy;
            nazwy= Directory.GetLogicalDrives();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] nazwy;
            nazwy = Directory.GetLogicalDrives();
            foreach (string dysk in nazwy)
            {
                Dysk1.Items.Add(dysk);
            }
            Dysk1.SelectedIndex = Dysk1.Items.IndexOf("C:\\");
        }

    }
}
