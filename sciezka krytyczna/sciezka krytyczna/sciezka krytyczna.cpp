// sciezka krytyczna.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include<fstream>
#include<iostream>
#include <list>


using namespace std;


class zadanie
{
public:
	int ID;
	int waga;
	int ES,EF,LS,LF;
	list<zadanie*>  next;
	list<zadanie*> before;
	zadanie();
};

	zadanie::zadanie()
	{
		ID=0;
		waga=0;
		ES,EF,LS,LF=0;		
	}

	
struct relacja
{
	short poczatek;
	short koniec;
};


int _tmain(int argc, _TCHAR* argv[])
{
	list<zadanie> lista_zadan;
	list<zadanie> lista_zadan2;
	list<zadanie>::iterator it=lista_zadan.begin();
	list<zadanie>::iterator it3=lista_zadan.begin();
	list<relacja> lista_relacji;
	list<relacja>::iterator it2=lista_relacji.begin();
	int a,b;
	int flaga=0;
	fstream plik;
	plik.open("datasort10.txt", std::ios::in );
	plik >> a;
	
	for(int i=0; i < a; i++)
	{
		zadanie *nowa = new zadanie();
		nowa->ID=i+1;
		plik >> nowa->waga;
		lista_zadan.push_back(*nowa);		
	}
	plik >> b;

	for(int i=0; i<b; i++)
	{
		relacja *rel = new relacja();
		plik >> rel->poczatek;
		plik >> rel->koniec;
		lista_relacji.push_back(*rel);
		for(it=lista_zadan.begin(); it!=lista_zadan.end(); it++)
		{
			if(rel->poczatek == it->ID)
			{
				for(it3=lista_zadan.begin(); it3!=lista_zadan.end(); it3++)
				{
					if(rel->koniec == it3->ID)
					{
						zadanie *x = new zadanie();
							x->ID= it3->ID;
							x->waga= it3->waga;
							x->ES= it3->ES; x->EF= it3->EF; x->LS= it3->LS; x->LF= it3->LF;
							x->next = it3->next;
							x->before = it3->before;
							it->next.push_back(x);

						zadanie *y = new zadanie();
							y->ID= it->ID;
							y->waga= it->waga;
							y->ES= it->ES; y->EF= it->EF; y->LS= it->LS; y->LF= it->LF;
							y->next = it->next;
							y->before = it->before;
							it3->before.push_back(y);
					}
				}
			}
		}

	}



///////////////////// 
	// Algorym
////////////////////

//while(a>8)
//{
for(list<zadanie>::iterator obiekt_it=lista_zadan.begin(); obiekt_it!=lista_zadan.end();obiekt_it++)
{

	if(flaga==1)
	{obiekt_it--;flaga=0;}



	if( obiekt_it->before.empty())
	{//cout<<obiekt_it->ID<<endl;
		obiekt_it->ES=0;
		obiekt_it->EF=obiekt_it->ES+obiekt_it->waga;
		//cout << obiekt_it-> ID<<"   " <<obiekt_it->ES<<" "<<obiekt_it->EF<<endl;
		
		for(list<zadanie*>::iterator next_it=obiekt_it->next.begin(); next_it != obiekt_it->next.end(); next_it++)
		{//cout<<obiekt_it->ID<<endl;
			if((*next_it)->ES < obiekt_it->EF)
			 (*next_it)->ES = obiekt_it->EF;	
			 (*next_it)->EF = (*next_it)->ES + (*next_it)->waga;
			 //cout << (**next_it).ID<<"   " <<(**next_it).ES<<" "<<(**next_it).EF<<endl;	
			// cout<<obiekt_it->ID<<endl; //////   ||||
			 //cout << (*next_it)->ID << endl;

			
			 for(list<zadanie*>::iterator before_it=(*next_it)->before.begin(); before_it != (*next_it)->before.end(); before_it++)
			 {	cout<<obiekt_it->ID<<endl<<"jestem";																	///// cuda wianki
				
				if(obiekt_it->ID==(*before_it)->ID)
				{
					before_it=(*before_it)->before.erase(before_it);
					//cout<<obiekt_it->ID<<" " <<(*before_it)->ID<<endl;
				}
			 }
			 
		} 


		obiekt_it=lista_zadan.erase(obiekt_it);
		 flaga=1;

		 for(list<zadanie>::iterator it6=lista_zadan.begin(); it6!=lista_zadan.end();it6++)											//wyswietlanie beforow
		{//cout<<endl<<"jestem numer " <<it6->ID<<" wyprzedza mnie: ";
			for(list<zadanie*>::iterator before_it=(*it6).before.begin(); before_it != (*it6).before.end(); before_it++)
			{
			//cout<<(**before_it).ID<<" ";
			}
		}
		
	}
//}
//a--;
}


	system("PAUSE");
	return 0;
}

