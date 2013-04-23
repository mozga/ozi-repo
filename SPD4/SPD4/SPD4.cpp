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


int _tmain(int argc, _TCHAR* argv[])
{
	unsigned short n, k=0;
	fstream plik;
	plik.open("data01.txt", std::ios::in );
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
		list<proces>::iterator it=r.begin();
		for( unsigned int i=0; i < r.size(); i++, it++)
		{
			if(it->r<=k)
			{
				q.push_back(*it);
				if(i<r.size()-1)
					it=r.erase(it);
				else
					r.pop_back();
				if(r.empty() || i==r.size())
					break;
			}
		}
		q.sort(comp_q);
		cout << k << endl;
		for (list<proces>::iterator it=q.begin(); it!=q.end(); it++)
			cout << it->r << " " << it->p << " " << it->q << " " << it->ID << endl; //asdasdasdasdasdas
		if(!q.empty())
		{
			it=q.begin();
			procesy.push_back(*it);
			k+=it->p;
			q.pop_front();
		}
		else
			k++;
	}

	list<proces>::iterator it=procesy.begin();

	for(it=procesy.begin(); it!=procesy.end();it++)
		cout << it->ID  << " "; //<< it->r << " " << it->p << " " << it->q << endl;

	plik.open("out01.txt", std::ios::out );
	plik << n << endl;
	for(it=procesy.begin(); it!=procesy.end();it++)
		plik << it->ID << " ";
	plik << endl << sumowanie(procesy) << endl;
	cout << endl << sumowanie(procesy) << endl;

	plik.close();
	system("PAUSE");
}