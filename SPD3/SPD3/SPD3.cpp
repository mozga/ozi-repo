// SPD3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <time.h>
#include <algorithm>

using namespace std;

struct zadanie
{
	unsigned int suma;
	unsigned int ID;
};

bool compare (zadanie first, zadanie secound)
{
	return (first.suma > secound.suma);
}


int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int n, m, czas;

	ifstream data_in ("FSTA.txt");
	clock_t start, stop;

	start=clock();

	for(unsigned l=0;l<1;l++)
	{
	string nazwa, numer;
	data_in >> nazwa;
	data_in >> n >> m;
	unsigned int ** tablica = new unsigned int * [n];
	for(unsigned int i=0; i<n; i++)
		tablica[i]= new unsigned int[m];


	for(unsigned int i = 0; i<n; i++)
		for(unsigned int j = 0; j<m; j++)
		{ data_in >> numer; data_in >> tablica[i][j];}

	list<zadanie> * szereg = new list<zadanie>;
	
	for(unsigned int k=0; k<n; k++)
		{
		int suma=0;
		for(unsigned int q=0; q<m; q++)
			suma+=tablica[k][q];
		zadanie * nowy=new zadanie;
		nowy->ID=k+1;
		nowy->suma=suma;
		szereg->push_back(*nowy);	 	
		}
	szereg->sort(compare);

	list<zadanie> * kolejnosc = new list<zadanie>;
	zadanie pierwszy;
	list<zadanie>::iterator it1=szereg->begin();
	
	unsigned int * dlugosci_const = new unsigned int[m];	
	for(unsigned int j=0; j<m; j++)
		dlugosci_const[j]=tablica[it1->ID][j];

	pierwszy.ID=it1->ID;
	pierwszy.suma=it1->suma;
	kolejnosc->push_front(pierwszy);
	it1++;
	for(unsigned int kurwa=0; kurwa<3;/*it1!=szereg->end();*/kurwa++, it1++)
	{
	unsigned int * dlugosci_tmp = new unsigned int[m];	
	for(unsigned int i=0; i<m; i++)
		dlugosci_tmp[i]=dlugosci_const[i];
	unsigned int * dlugosci = new unsigned int[m];	
		//cout << it1->ID << endl;
		//for(int k=0;k<m;k++)
			//cout << dlugosci[k] << " ";
		//cout << endl;
		zadanie nast;
		nast.suma=0xFFFFFFFF;
		list<zadanie>::iterator it =kolejnosc->begin();
		for(; it!=kolejnosc->end(); it++)
			for(unsigned int j=0; j<m; j++)
			{		cout << tablica[it->ID-1][j] << " ";
					cout << dlugosci_tmp[j-1]<< " ";
					cout << dlugosci_tmp[j]<< endl;
				if(j==0)
					dlugosci_tmp[j]+=tablica[it->ID-1][j];
				else
					dlugosci_tmp[j]=max(dlugosci_tmp[j-1], dlugosci_tmp[j])+tablica[it->ID][j];}
			if(nast.suma > dlugosci_tmp[m])
			{
				nast.suma=dlugosci_tmp[m];
				nast.ID=it1->ID;
				for(unsigned int i=0; i<m; i++)
					dlugosci[i]=dlugosci_tmp[i];
			}
			for(unsigned int i=0;i<m;i++)
				dlugosci_const[i]=dlugosci[i];
		for(list<zadanie>::iterator it = szereg->begin(); it!=szereg->end(); it++)
			cout << it->ID << " ";
		cout << endl;
		for(list<zadanie>::iterator it = kolejnosc->begin(); it!=kolejnosc->end(); it++)
			cout << it->ID << " ";
		cout << endl;
		//cout << it1->ID << endl;
		kolejnosc->insert(it, nast);
	
	}
	for(list<zadanie>::iterator it = szereg->begin(); it!=szereg->end(); it++)
		cout << it->ID << " ";
	cout << endl;
	for(list<zadanie>::iterator it = kolejnosc->begin(); it!=kolejnosc->end(); it++)
		cout << it->ID << " ";
	cout << endl;
	for(list<zadanie>::iterator it = kolejnosc->begin(); it!=kolejnosc->end(); it++)
		cout << it->suma << " ";
	cout << endl;

	fstream data_out ("out.txt", ios::out|ios::app);
	data_out << nazwa << endl;
	for(list<zadanie>::iterator it = szereg->begin(); it!=szereg->end(); it++)
		data_out << it->ID << " ";
	data_out<< endl;

	delete szereg;
	delete [] dlugosci_const;
	delete [] tablica;
	}
	stop=clock();
	czas= stop-start;
	cout << czas << " ms" << endl;
	data_in.close();
			
	system("PAUSE");
}

