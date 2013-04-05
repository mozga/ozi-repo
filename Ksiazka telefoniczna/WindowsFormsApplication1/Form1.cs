using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml;

namespace Lista_Kontaktow
{
    [Serializable()]
    public partial class Lista_Kontaktów : Form
    {

        public Lista_Kontaktów()
        {
            InitializeComponent();
        }

        struct Osoba
        {
            public string Imie;
            public string Nazwisko;
            public string data_urodzenia;
            public string Ulica;
            public string Nr_ulicy;
            public string kod;
            public string Miasto;
            public string Panstwo;
            public string email;
            public string www;
            public List<Telefon> telefony;
         }

        List<Osoba> Lista = new List<Osoba>();

        struct Telefon
        {
            public string numer;
            public string typ;
        }

        public int wiek(string Data_urodzenia)
        {
            try
            {
                DateTime Bday = new DateTime();
                Bday = DateTime.ParseExact(Data_urodzenia, "dd.MM.yyyy", null);
                DateTime now = DateTime.Today;
                int age = now.Year - Bday.Year;
                if (now < Bday.AddYears(age)) age--;
                    return age;
            }
            catch (Exception E)
            {
                MessageBox.Show("Błąd: " + E.Message, "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return 0;
            }

        }

        BinaryFormatter f = new BinaryFormatter();

        private void button1_Click(object sender, EventArgs e)
        {
            Osoba nowy = new Osoba();

            nowy.Imie = Imie.Text;
            nowy.Nazwisko = Nazwisko.Text;
            nowy.data_urodzenia = Data_urodzenia.Text;
            nowy.Ulica = Ulica.Text;
            nowy.Nr_ulicy= Nr.Text;
            nowy.kod = kod.Text;
            nowy.Miasto = Miasto.Text;
            nowy.Panstwo = Panstwo.Text;
            nowy.email = email.Text;
            nowy.www = www.Text;
            //nowy.telefony;

            

            ListViewItem nowy1 = new ListViewItem(nowy.Imie);
            nowy1.SubItems.Add(nowy.Nazwisko);
            nowy1.SubItems.Add(wiek(nowy.data_urodzenia).ToString());
            nowy1.SubItems.Add(nowy.Ulica+" "+nowy.Nr_ulicy);
            nowy1.SubItems.Add(nowy.kod);
            nowy1.SubItems.Add(nowy.Miasto);
            nowy1.SubItems.Add(nowy.Panstwo);
            nowy1.SubItems.Add(nowy.email);
            nowy1.SubItems.Add(nowy.www);
                  //telefon

            if (wiek(nowy.data_urodzenia) != 0)
            {
                listView1.Items.Add(nowy1);
                Lista.Add(nowy);

                Imie.Text = "";
                Nazwisko.Text = "";
                Data_urodzenia.Text = "";
                Ulica.Text = "";
                Nr.Text = "";
                kod.Text = "";
                Miasto.Text = "";
                Panstwo.Text = "";
                email.Text = "";
                www.Text = "";
                pictureBox1.Image = WindowsFormsApplication1.Properties.Resources.indeks;
            }

        }
        
       private void d_zdjecie_Click_1(object sender, EventArgs e)
        {

            OpenFileDialog openfile1 = new OpenFileDialog();
            openfile1.ShowDialog();
            pictureBox1.ImageLocation = openfile1.FileName;
            this.Text = openfile1.FileName;
            
        }
        
        private void button2_Click(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count == 0) return;
            listView1.SelectedItems[0].Remove();
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {
            try
            {
                //Stream file = File.Open("data.bin", FileMode.Open);
                //listView1 = (ListView)f.Deserialize(file); nie dziala... TEZ! :D
                //file.Close();
            }
            catch (Exception E)
            {
                MessageBox.Show("Błąd: " + E.Message, "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Form1_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Stream file = File.Open("data.bin", FileMode.Create);
            f.Serialize(file, listView1);  // nie zapisuje :(
            file.Close();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            //UpdateListView
        }

        private void edytuj_button_Click(object sender, EventArgs e)
        {
            int Data = wiek(Data_urodzenia.Text);

            listView1.SelectedItems[0].SubItems[0].Text = Imie.Text;
            listView1.SelectedItems[0].SubItems[1].Text=Nazwisko.Text;
            listView1.SelectedItems[0].SubItems[2].Text=Data.ToString();
            listView1.SelectedItems[0].SubItems[3].Text=Ulica.Text + " " + Nr.Text;
            listView1.SelectedItems[0].SubItems[4].Text=kod.Text;
            listView1.SelectedItems[0].SubItems[5].Text=Miasto.Text;
            listView1.SelectedItems[0].SubItems[6].Text=Panstwo.Text;
            listView1.SelectedItems[0].SubItems[7].Text=email.Text;
            listView1.SelectedItems[0].SubItems[8].Text=www.Text;
            listView1.SelectedItems[0].SubItems[9].Text=Ulica.Text;
            listView1.SelectedItems[0].SubItems[10].Text=Nr.Text;
            listView1.SelectedItems[0].SubItems[11].Text=Data_urodzenia.Text;
        }

        private void listView1_DoubleClick(object sender, EventArgs e)
        {
            Imie.Text = listView1.SelectedItems[0].SubItems[0].Text;
            Nazwisko.Text = listView1.SelectedItems[0].SubItems[1].Text;
            Data_urodzenia.Text = listView1.SelectedItems[0].SubItems[11].Text;
            Ulica.Text = listView1.SelectedItems[0].SubItems[9].Text;
            Nr.Text = listView1.SelectedItems[0].SubItems[10].Text;
            kod.Text = listView1.SelectedItems[0].SubItems[4].Text;
            Miasto.Text = listView1.SelectedItems[0].SubItems[5].Text;
            Panstwo.Text = listView1.SelectedItems[0].SubItems[6].Text;
            email.Text = listView1.SelectedItems[0].SubItems[7].Text;
            www.Text = listView1.SelectedItems[0].SubItems[8].Text;
        }

   

    }
    

}