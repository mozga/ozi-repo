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
    

    public partial class Lista_Kontaktów : Form
    {
        
        public Lista_Kontaktów()
        {
            InitializeComponent();
        }
        
        
        [Serializable]
        struct Osoba
        {
            public string Imie { get; set; }
            public string Nazwisko { get; set; }
            public string data_urodzenia { get; set; }
            public string Ulica { get; set; }
            public string Nr_ulicy { get; set; }
            public string kod { get; set; }
            public string Miasto { get; set; }
            public string Panstwo { get; set; }
            public string email { get; set; }
            public string www { get; set; }
            public List<string> telefony { get; set; }
        }

        List<Osoba> Lista = new List<Osoba>();
        List<string> tel = new List<string>();

        public void przypisz()
        {
            listView1.Items.Clear();
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

        private void button1_Click(object sender, EventArgs e)
        {
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
            nowy.telefony = tel;
            tel.Clear();



            if (wiek(nowy.data_urodzenia) != 0)
            {
                Lista.Add(nowy);
                przypisz();

                /*               Imie.Text = "";
                               Nazwisko.Text = "";
                               Data_urodzenia.Text = "";
                               Ulica.Text = "";
                               Nr.Text = "";
                               kod.Text = "";
                               Miasto.Text = "";
                               Panstwo.Text = "";
                               email.Text = "";
                               www.Text = "";
                               telefon.Text="";*/
                telefon_box.Items.Clear();
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
            if (listView1.SelectedItems.Count != 0)
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

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

            if (Lista.Count() != 0)
            {

                listView1.Items.Clear();
                foreach (Osoba item in Lista)
                {
                    string tmp = item.Imie + " " + item.Nazwisko + " " + wiek(item.data_urodzenia).ToString() + " " + item.Ulica + " " + item.Nr_ulicy + " " +
                        item.kod + " " + item.Miasto + " " + item.Panstwo + " " + item.email + " " + item.www;
                    if (tmp.Contains(textBox1.Text))
                    {
                        ListViewItem nowy = new ListViewItem(item.Imie);
                        nowy.SubItems.Add(item.Nazwisko);
                        nowy.SubItems.Add(wiek(item.data_urodzenia).ToString());
                        nowy.SubItems.Add(item.Ulica + " " + item.Nr_ulicy);
                        nowy.SubItems.Add(item.kod);
                        nowy.SubItems.Add(item.Miasto);
                        nowy.SubItems.Add(item.Panstwo);
                        nowy.SubItems.Add(item.email);
                        nowy.SubItems.Add(item.www);
                        listView1.Items.Add(nowy);

                    }
                }
            }
            if (textBox1.Text.Length == 0)
                przypisz();
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
            nowy.telefony = tel;

            if (wiek(nowy.data_urodzenia) != 0)
            {
                Lista.Add(nowy);
                przypisz();

                /*Imie.Text = "";
                Nazwisko.Text = "";
                Data_urodzenia.Text = "";
                Ulica.Text = "";
                Nr.Text = "";
                kod.Text = "";
                Miasto.Text = "";
                Panstwo.Text = "";
                email.Text = "";
                www.Text = "";*/
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
                                            linkLabelwww.Text = Lista[i].www;
                                            //tel = Lista[i].telefony;
                                            // telefon_box.Items.Clear();
                                            telefon_box.DataSource = Lista[i].telefony;
                                            for (int j = 0; j < tel.Capacity; j++)
                                                telefon_box.Items.Add("aaaa");
                                        }

            }
        }

        private void telefon_button_Click(object sender, EventArgs e)
        {
            tel.Add(telefon.Text);
            telefon_box.Items.Clear();
            for (int j = 0; j < tel.Capacity; j++)
                telefon_box.Items.Add(tel[j]);

        }


        /// <summary>
        /// ///////////////////////////////////////////////////SERIALIZACJA///////////////////////////////////////
        /// //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// </summary>
        /// <param name="file"></param>
        public void DataSerialization(string file)
        {
            FileStream stream = new FileStream(file, FileMode.Create); //tworze strumien
            BinaryFormatter formatter = new BinaryFormatter(); //formater
            formatter.Serialize(stream, this.Lista); //serializuje
            stream.Close();
        }

        public void DataDeserialization(string file)
        {
            FileStream stream = new FileStream(file, FileMode.Open); //tworze strumien
            BinaryFormatter formatter = new BinaryFormatter(); //formater
            this.Lista = (List<Osoba>)formatter.Deserialize(stream); //deserializuje
            stream.Close();

        }

        private void buttonSerialBin_Click(object sender, EventArgs e)
        {
            saveFileDialog1.Filter = "Plik binarny (*.bin)|*.bin"; //otwiram okno dialogowe
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                DataSerialization(saveFileDialog1.FileName); //serializuje
                MessageBox.Show("Zapisano listę do pliku: " + saveFileDialog1.FileName, "Informacja");

            }

        }

        private void buttonDeserialBin_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Plik binarny (*.bin)|*.bin";
            openFileDialog1.Multiselect = false;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                DataDeserialization(openFileDialog1.FileName); //deserializuje
                MessageBox.Show("Wczytano listę z pliku: " + openFileDialog1.FileName, "Informacja");
                przypisz();
                
                
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////
         

        }
      

        private void linkLabelwww_MouseDoubleClick(object sender, MouseEventArgs e)
        {
           
        }

    }
}