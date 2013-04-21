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
	bool koniec = false;
	 
	ifstream data_in ("FSTA.txt");
	clock_t start, stop;

	start=clock();

	for(unsigned l=0;l<4;l++)		// liczba instancji
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

	for(list<zadanie>::iterator it=szereg->begin(); it !=szereg->end();it++)
		cout << it->ID << " ";

	list<unsigned int> * kolejnosc = new list<unsigned int>;

	list<zadanie>::iterator it_main=szereg->begin();

	kolejnosc->push_front(it_main->ID);
	it_main++;

	unsigned int * sumy = new unsigned int[m];

//*************************************************************************************\\

	for(; it_main!=szereg->end(); it_main++)
	{
		unsigned int suma_ID;
		for(unsigned int i=0; i<m; i++)
			sumy[i]=0;

		list<unsigned int>::iterator ID = kolejnosc->begin();

		for(list<unsigned int>::iterator it = kolejnosc->begin(); it!=kolejnosc->end(); it++)
		{
			sumy[0]+=tablica[*it-1][0];
			for(unsigned int j=1; j<m; j++)
				sumy[j]=max(sumy[j-1], sumy[j])+tablica[*it-1][j];
		}

		sumy[0]+=tablica[it_main->ID-1][0];
		for(unsigned int j=1; j<m; j++)
			sumy[j]=max(sumy[j-1], sumy[j])+tablica[it_main->ID-1][j];

		suma_ID=sumy[m-1];
		koniec=true;

		for(list<unsigned int>::iterator it = kolejnosc->begin(); it!=kolejnosc->end(); it++)
		{
			list<unsigned int>::iterator sum = kolejnosc->begin();
			for(unsigned int i=0; i<m; i++)
				sumy[i]=0;
			while(sum!=kolejnosc->end())
			{
				if(sum==it)
				{
					sumy[0]+=tablica[it_main->ID-1][0];
					for(unsigned int j=1; j<m; j++)
						sumy[j]=max(sumy[j-1], sumy[j])+tablica[it_main->ID-1][j];
				}
				sumy[0]+=tablica[*sum-1][0];
				for(unsigned int j=1; j<m; j++)
					sumy[j]=max(sumy[j-1], sumy[j])+tablica[*sum-1][j];
				sum++;
			}

			if(suma_ID > sumy[m-1])					// roznica
			{
				suma_ID=sumy[m-1];
				ID=it;
				koniec=false;
			}
		}

		if(koniec)
			kolejnosc->push_back(it_main->ID);
		else
			kolejnosc->insert(ID, it_main->ID);

	}

	for(list<unsigned int>::iterator it = kolejnosc->begin(); it!=kolejnosc->end(); it++)
		cout << *it << " ";
	cout << endl;

	cout << sumy[m-1] << endl << endl;

	fstream data_out ("out.txt", ios::out|ios::app);
	data_out << nazwa << endl;
	for(list<unsigned int>::iterator it = kolejnosc->begin(); it!=kolejnosc->end(); it++)
		data_out << *it << " ";
	data_out << endl;

	for(unsigned int i=0; i<n; i++)
		delete tablica[i];

	delete [] tablica;
	}

	stop=clock();
	czas= stop-start;
	cout << czas << " ms" << endl;
	data_in.close();
			
	system("PAUSE");
}