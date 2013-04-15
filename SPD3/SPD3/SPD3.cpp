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
	list<zadanie>::iterator it_main=szereg->begin();

	pierwszy.ID=it_main->ID;
	pierwszy.suma=it_main->suma;
	kolejnosc->push_front(pierwszy);
	it_main++;

	for(unsigned int op=0;/* op<3 &&*/ it_main!=szereg->end(); op++, it_main++)
	{
		unsigned int * sumy = new unsigned int[m];
		for(unsigned int i=0; i<m; i++)
			sumy[i]=0;
		zadanie nast;
		list<zadanie>::iterator it = kolejnosc->begin();
		
		while(it!=kolejnosc->end())
		{
			for(unsigned int j=0; j<m; j++)
				if(it==kolejnosc->begin())
					if(j==0)
						sumy[j]=tablica[it_main->ID-1][j];
					else
						sumy[j]=sumy[j-1]+tablica[it_main->ID-1][j];
				else
					if(j==0)
						sumy[j]+=tablica[it->ID-1][j];
					else
						sumy[j]=max(sumy[j-1], sumy[j])+tablica[it->ID-1][j];
			it++;
		}

		nast.suma=sumy[m-1];
		nast.ID=it_main->ID;
		koniec=true;

		for(it=kolejnosc->begin(); it!=kolejnosc->end(); it++)
		{
			list<zadanie>::iterator sum = kolejnosc->begin();
			for(unsigned int i=0; i<m; i++)
				sumy[i]=0;
			while(sum!=kolejnosc->end())
			{
			list<zadanie>::iterator tmp = sum;
			if(tmp!=kolejnosc->begin())
				tmp--;
				for(unsigned int j=0; j<m; j++)
					if(tmp!=it) // za daleko -1
						if(j==0)
							sumy[j]+=tablica[sum->ID-1][j];
						else
							sumy[j]=max(sumy[j-1], sumy[j])+tablica[sum->ID-1][j];
					else
						if(j==0)
							sumy[j]+=tablica[it_main->ID-1][j];
						else
							sumy[j]=max(sumy[j-1], sumy[j])+tablica[it_main->ID-1][j];
				sum++;
			}
			cout << nast.suma << " " <<sumy[m-1]<< endl;
			if(nast.suma > sumy[m-1])
			{
				nast.suma=sumy[m-1];
				nast.ID=it->ID;
				koniec=false;
			}
		}

		it=kolejnosc->begin();

		if(koniec)
			kolejnosc->push_front(nast);
		else
		{
			while(it->ID!=nast.ID)
				it++;
			nast.ID=it_main->ID;
			kolejnosc->insert(it, nast);
		}
		
		for(list<zadanie>::iterator it = kolejnosc->begin(); it!=kolejnosc->end(); it++)
			cout << it->ID << " ";
		cout << endl;
	}

		for(list<zadanie>::iterator it = szereg->begin(); it!=szereg->end(); it++)
			cout << it->ID << " ";
		cout << endl;

	fstream data_out ("out.txt", ios::out|ios::app);
	data_out << nazwa << endl;
	for(list<zadanie>::iterator it = szereg->begin(); it!=szereg->end(); it++)
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