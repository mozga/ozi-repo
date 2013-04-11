using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{ 
    public partial class Przeglad : Form
    {
        public string ja
        {
            get;
            set
           ;
        }
        public void SetWeb(string web)
        {
                            // ja = "http://" + ja;
                textBox1.Text = "http://" + web;
            ja = web;
                webBrowser1.Navigate(ja);


        }
        public Przeglad()
        {
            InitializeComponent();

        }

        private void Przeglad_Load(object sender, EventArgs e)
        {

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            
        }

        
        
 }
}
