// SPD3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <time.h>

using namespace std;

struct zadania
{
	int zadanie;
	int ID;
};

bool compare (zadania first, zadania secound)
{
	return (first.zadanie > secound.zadanie);
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


	/*for(int i = 0; i<n; i++)
	{
		for(int j = 0; j<m; j++)
			cout << tablica[i][j] << " ";
	cout << endl;
	}*/

	list<zadania> * szereg = new list<zadania>;
	
	for(unsigned int k=0; k<n; k++)
		{
		int suma=0;
		for(unsigned int q=0; q<m; q++)
			suma+=tablica[k][q];
		zadania * nowy=new zadania;
		nowy->ID=k+1;
		nowy->zadanie=suma;
		szereg->push_back(*nowy);	 	
		}
	szereg->sort(compare);


	
	//for(list<zadania>::iterator it = szereg->begin(); it!=szereg->end(); it++)
		//cout << it->ID << " ";
	//cout << endl;
	for(list<zadania>::iterator it = szereg->begin(); it!=szereg->end(); it++)
		cout << it->zadanie << " ";
	cout << endl;

	fstream data_out ("out.txt", ios::out|ios::app);
	data_out << nazwa << endl;
	for(list<zadania>::iterator it = szereg->begin(); it!=szereg->end(); it++)
		data_out << it->ID << " ";
	data_out<< endl;

	delete szereg;
	delete [] tablica;
	}
	stop=clock();
	czas= stop-start;
	cout << czas << " ms" << endl;
	data_in.close();
			
	system("PAUSE");
}

