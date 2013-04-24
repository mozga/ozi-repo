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
};

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
	list<proces> r, q;

	for(short i=0; i<n; i++)
	{
		proces *nowy= new proces();
		plik >> nowy->r >> nowy->p >> nowy->q;
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
			it->p--;
			if(it->p==0)
				q.pop_front();
		}
		k++;	//+q (wszystkich)
	}

	plik.open("out.txt", ios::out|ios::app);
	plik << name << endl;
	cout << endl << k << endl;
	plik << endl << "Dlugosc: " << k << endl << endl;

	plik.close();
}



int _tmain(int argc, _TCHAR* argv[])
{
	algorytm("data01.txt");
/*	algorytm("data02.txt");
	algorytm("data03.txt");
	algorytm("data04.txt");
	algorytm("data05.txt");
	algorytm("data06.txt");
	algorytm("data07.txt");
	algorytm("data08.txt");
	algorytm("data09.txt");
	algorytm("data10.txt");*/
	system("PAUSE");
}