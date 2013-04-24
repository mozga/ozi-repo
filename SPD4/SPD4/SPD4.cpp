// SPD4.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct proces
{
	unsigned short r;		//wyprzedzanie
	unsigned short p;		//zadanie
	unsigned short q;		//opoznienie
	unsigned short ID;		//identyfikator
};

int sumowanie(list<proces> lista)
{
	unsigned int suma=0, suma_tmp=0;
	for(list<proces>::iterator it=lista.begin();it!=lista.end();it++)
	{
		if(it->r>=suma)
			suma=it->r;
		suma+=it->p;
	}
	for(list<proces>::reverse_iterator it=lista.rbegin();it!=lista.rend();it++)
	{
		if(it->q>=suma_tmp)
			suma_tmp=it->q;
		suma_tmp+=it->p;
	}
	suma+=suma_tmp;
	for(list<proces>::iterator it=lista.begin();it!=lista.end();it++)
		suma-=it->p;
	return suma;
}

bool comp_r(proces p1, proces p2)
{
	return (p1.r<p2.r);
}

bool comp_q(proces p1, proces p2)
{
	return (p1.q>p2.q);
}

void algorytm(char * name)
{
	unsigned short n, k=0;
	fstream plik;
	plik.open(name, std::ios::in );
	plik >> n;
	list<proces> r, q, procesy;

	for(short i=0; i<n; i++)
	{
		proces *nowy= new proces();
		plik >> nowy->r >> nowy->p >> nowy->q;
		nowy->ID=i+1;
		r.push_front(*nowy);
		delete nowy;
	}
	plik.close();

	r.sort(comp_r);

	while(!r.empty() || !q.empty())
	{
		for(list<proces>::iterator it=r.begin(); it!=r.end();)
			if(it->r<=k)
			{
				q.push_back(*it);
				it=r.erase(it);
			}
			else
				break;
		q.sort(comp_q);

		if(!q.empty())
		{
			list<proces>::iterator it=q.begin();
			procesy.push_back(*it);
			k+=it->p;
			q.pop_front();
		}
		else
			k++;
	}

	list<proces>::iterator it=procesy.begin();

	for(it=procesy.begin(); it!=procesy.end();it++)
		cout << it->ID  << " ";

	plik.open("out.txt", ios::out|ios::app);
	plik << name << endl;
	plik << n << endl;
	for(it=procesy.begin(); it!=procesy.end();it++)
		plik << it->ID << " ";
	cout << endl << sumowanie(procesy) << endl;
	plik << endl << "Dlugosc: " << sumowanie(procesy) << endl << endl;

	plik.close();
}



int _tmain(int argc, _TCHAR* argv[])
{
	algorytm("data01.txt");
	algorytm("data02.txt");
	algorytm("data03.txt");
	algorytm("data04.txt");
	algorytm("data05.txt");
	algorytm("data06.txt");
	algorytm("data07.txt");
	algorytm("data08.txt");
	algorytm("data09.txt");
	algorytm("data10.txt");
	system("PAUSE");
}