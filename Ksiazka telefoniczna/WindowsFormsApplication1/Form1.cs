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

        public void przypisz()
        {
           
            for (int i = 0; i < Lista.Count(); i++)
            {
                ListViewItem nowy = new ListViewItem(Lista[i].Imie);
                nowy.SubItems.Add(Lista[i].Nazwisko);
                nowy.SubItems.Add(wiek(Lista[i].data_urodzenia).ToString());
                nowy.SubItems.Add(Lista[i].Ulica + " " + Lista[i].Nr_ulicy);
                nowy.SubItems.Add(Lista[i].kod);
                nowy.SubItems.Add(Lista[i].Miasto);
                nowy.SubItems.Add(Lista[i].Panstwo);
                nowy.SubItems.Add(Lista[i].email);
                nowy.SubItems.Add(Lista[i].www);
                //telefon
                listView1.Items.Add(nowy);
               
            }
           
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



            if (wiek(nowy.data_urodzenia) != 0)
            {
                Lista.Add(nowy);
                for (int i = 1; i < Lista.Count(); i++)
                {
                    listView1.Items[0].Remove();
                }
                przypisz();

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
            for (int i = 0; i < Lista.Count(); i++)
            {
                
                if (Lista[i].Imie.Equals(listView1.SelectedItems[0].SubItems[0].Text))
                 if (Lista[i].Nazwisko.Equals(listView1.SelectedItems[0].SubItems[1].Text))
                  if ((wiek(Lista[i].data_urodzenia).ToString()).Equals(listView1.SelectedItems[0].SubItems[2].Text))
                   if ((Lista[i].Ulica+" "+Lista[i].Nr_ulicy).Equals(listView1.SelectedItems[0].SubItems[3].Text))
                    if (Lista[i].kod.Equals(listView1.SelectedItems[0].SubItems[4].Text))
                     if (Lista[i].Miasto.Equals(listView1.SelectedItems[0].SubItems[5].Text))
                      if (Lista[i].Panstwo.Equals(listView1.SelectedItems[0].SubItems[6].Text))
                                 Lista.Remove(Lista[i]);
                            
                                    
            }
            for (int i = Lista.Count()+1; i > 0; i--)
                listView1.Items[i-1].Remove();
           
            przypisz();
            
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
            for (int i = 0; i < Lista.Count(); i++)
            {

                if (Lista[i].Imie.Equals(listView1.SelectedItems[0].SubItems[0].Text))
                    if (Lista[i].Nazwisko.Equals(listView1.SelectedItems[0].SubItems[1].Text))
                        if ((wiek(Lista[i].data_urodzenia).ToString()).Equals(listView1.SelectedItems[0].SubItems[2].Text))
                            if ((Lista[i].Ulica + " " + Lista[i].Nr_ulicy).Equals(listView1.SelectedItems[0].SubItems[3].Text))
                                if (Lista[i].kod.Equals(listView1.SelectedItems[0].SubItems[4].Text))
                                    if (Lista[i].Miasto.Equals(listView1.SelectedItems[0].SubItems[5].Text))
                                        if (Lista[i].Panstwo.Equals(listView1.SelectedItems[0].SubItems[6].Text))
                                            Lista.Remove(Lista[i]);
            }
                Osoba nowy = new Osoba();

                nowy.Imie = Imie.Text;
                nowy.Nazwisko = Nazwisko.Text;
                nowy.data_urodzenia = Data_urodzenia.Text;
                nowy.Ulica = Ulica.Text;
                nowy.Nr_ulicy = Nr.Text;
                nowy.kod = kod.Text;
                nowy.Miasto = Miasto.Text;
                nowy.Panstwo = Panstwo.Text;
                nowy.email = email.Text;
                nowy.www = www.Text;
                //nowy.telefony;



                if (wiek(nowy.data_urodzenia) != 0)
                {
                    Lista.Add(nowy);
                    for (int i = 0; i < Lista.Count(); i++)
                    {
                        listView1.Items[0].Remove();
                    }
                    przypisz();

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

        private void listView1_DoubleClick(object sender, EventArgs e)
        {
            for (int i = 0; i < Lista.Count(); i++)
            {

                if (Lista[i].Imie.Equals(listView1.SelectedItems[0].SubItems[0].Text))
                    if (Lista[i].Nazwisko.Equals(listView1.SelectedItems[0].SubItems[1].Text))
                        if ((wiek(Lista[i].data_urodzenia).ToString()).Equals(listView1.SelectedItems[0].SubItems[2].Text))
                            if ((Lista[i].Ulica + " " + Lista[i].Nr_ulicy).Equals(listView1.SelectedItems[0].SubItems[3].Text))
                                if (Lista[i].kod.Equals(listView1.SelectedItems[0].SubItems[4].Text))
                                    if (Lista[i].Miasto.Equals(listView1.SelectedItems[0].SubItems[5].Text))
                                        if (Lista[i].Panstwo.Equals(listView1.SelectedItems[0].SubItems[6].Text))
                                        {
                                            Imie.Text = Lista[i].Imie;
                                            Nazwisko.Text = Lista[i].Nazwisko;
                                            Data_urodzenia.Text = Lista[i].data_urodzenia;
                                            Ulica.Text = Lista[i].Ulica;
                                            Nr.Text = Lista[i].Nr_ulicy;
                                            kod.Text = Lista[i].kod;
                                            Miasto.Text = Lista[i].Miasto;
                                            Panstwo.Text = Lista[i].Panstwo;
                                            email.Text = Lista[i].email;
                                            www.Text = Lista[i].www;
                                        }
                                            
            }
        }

   

    }
    

}