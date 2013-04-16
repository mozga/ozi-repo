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
	int early_waga;
	int cena_j;
	int ES,EF,LS,LF;
	list<zadanie*>  next;
	list<zadanie*> before;
	zadanie();
};

	zadanie::zadanie()
	{
		ID=0;
		waga=0;
		cena_j=0;
		ES,EF,LS,LF=0;		
	}

bool compare(zadanie pierwszy, zadanie drugi) 
{
	return (pierwszy.ES < drugi.ES);
}

bool comp_alg(zadanie pierwszy, zadanie drugi)
{
	return (pierwszy.cena_j < drugi.cena_j);
}



	
struct relacja
{
	short poczatek;
	short koniec;
};

int algorytm_skracania (list<zadanie> &lista_zadan,list<zadanie> &lista_zadan3,int budzet,int rozmiar,int &dlugosc)
{
	int budzet_tmp=budzet;
	int ilosc2=0;
	int ilosc3=0;

	lista_zadan.sort(comp_alg);			// sortowanie od najtanszych do najdro¿szych 

	cout<<"redukcja "<<endl;
	for(list<zadanie>::iterator obiekt_it=lista_zadan.begin(); obiekt_it!=lista_zadan.end();obiekt_it++)	
		{
			if((obiekt_it->EF==obiekt_it->LF) && (obiekt_it->ES==obiekt_it->LS))
			{
				int ilosc = obiekt_it->waga - obiekt_it->early_waga;
				ilosc2=ilosc;
				ilosc3=ilosc;
				for(ilosc; ilosc!=0 && budzet_tmp>0; ilosc--)
					if(budzet_tmp > obiekt_it->cena_j)
						{budzet_tmp-=obiekt_it->cena_j; ilosc3--;}
				
				for(list<zadanie>::iterator obiekt_it2=lista_zadan3.begin(); obiekt_it2!=lista_zadan3.end();obiekt_it2++)
					if(obiekt_it->ID==obiekt_it2->ID)
						obiekt_it2->waga=obiekt_it->waga-ilosc2+ilosc3;
			
			}

			cout<<obiekt_it->ID<<" "<<ilosc2-ilosc3<<endl;
			ilosc2=0;
			ilosc3=0;
	}
			cout<<"wydane srodki: "<<budzet-budzet_tmp<<endl;
			
			dlugosc=algorytm(lista_zadan3,lista_zadan3,rozmiar,dlugosc);
			return dlugosc;
}



int algorytm(list<zadanie> &lista_zadan, list<zadanie> lista_zadan2,int rozmiar,int &dlugosc)
{
	int rozmiar2=rozmiar; 
	for(list<zadanie>::iterator obiekt_it=lista_zadan.begin(); obiekt_it!=lista_zadan.end();obiekt_it++)
		obiekt_it->ES=0;
while(rozmiar)
{
	for(list<zadanie>::iterator obiekt_it=lista_zadan.begin(); obiekt_it!=lista_zadan.end();obiekt_it++)
		if(obiekt_it->before.empty())
		{
			obiekt_it->EF=obiekt_it->ES+obiekt_it->waga;
			for(list<zadanie*>::iterator next_it=obiekt_it->next.begin(); next_it != obiekt_it->next.end(); next_it++)
				for(list<zadanie>::iterator obiekt2_it=lista_zadan.begin(); obiekt2_it!=lista_zadan.end();obiekt2_it++)
					if(obiekt2_it->ID==(*next_it)->ID)
					{
						if(obiekt2_it->ES < obiekt_it->EF)
						obiekt2_it->ES = obiekt_it->EF;	
						obiekt2_it->EF = obiekt2_it->ES + obiekt2_it->waga;

						if(dlugosc < obiekt2_it->EF)
							dlugosc= obiekt2_it->EF;

						for(list<zadanie*>::iterator before_it = obiekt2_it->before.begin(); before_it != obiekt2_it->before.end();)
							if((*before_it)->ID==obiekt_it->ID)
							{
								 if(obiekt2_it->before.size()>1)
								{
									before_it=obiekt2_it->before.erase(before_it);
									break;
								}
								if(obiekt2_it->before.size()==1)
								{
									obiekt2_it->before.clear();
									break;
								}
							}
							else
								before_it++;
					}
		}
rozmiar--;
}
//////////////////////
//		W tyl		//
//////////////////////
for(list<zadanie>::iterator obiekt_it2=lista_zadan.begin(); obiekt_it2!=lista_zadan.end();obiekt_it2++)
{
	for(list<zadanie>::iterator obiekt_it=lista_zadan2.begin(); obiekt_it!=lista_zadan2.end();obiekt_it++)
	{
		obiekt_it->LF=obiekt_it2->EF;
		obiekt_it->LF=dlugosc;
	}
}

while(rozmiar2)
{
	for(list<zadanie>::iterator obiekt_it=lista_zadan2.begin(); obiekt_it!=lista_zadan2.end();obiekt_it++)
	{
		if(obiekt_it->next.empty())
		{
			obiekt_it->LS=obiekt_it->LF-obiekt_it->waga;
			for(list<zadanie*>::iterator before_it=obiekt_it->before.begin(); before_it != obiekt_it->before.end(); before_it++)
			{
				for(list<zadanie>::iterator obiekt2_it=lista_zadan2.begin(); obiekt2_it!=lista_zadan2.end();obiekt2_it++)
				{
					if(obiekt2_it->ID==(*before_it)->ID)
					{
						if(obiekt2_it->LF > obiekt_it->LS)
						obiekt2_it->LF = obiekt_it->LS;	
						obiekt2_it->LS = obiekt2_it->LF - obiekt2_it->waga;
						for(list<zadanie*>::iterator next_it = obiekt2_it->next.begin(); next_it != obiekt2_it->next.end();)
						{
							if((*next_it)->ID==obiekt_it->ID)
							{
								 if(obiekt2_it->next.size()>1)
								{
									next_it=obiekt2_it->next.erase(next_it);
									break;
								}
								if(obiekt2_it->next.size()==1)
								{
									obiekt2_it->next.clear();
									break;
								}
							}
							else
								next_it++;
						} 
					}
				} 
			}
		}
	}
	rozmiar2--;
}

	for(list<zadanie>::iterator obiekt_it=lista_zadan.begin(); obiekt_it!=lista_zadan.end();obiekt_it++)
{
	for(list<zadanie>::iterator obiekt_it2=lista_zadan2.begin(); obiekt_it2!=lista_zadan2.end();obiekt_it2++)
	{
		if(obiekt_it->ID==obiekt_it2->ID)
		{obiekt_it->LS=obiekt_it2->LS;
		 obiekt_it->LF=obiekt_it2->LF;}
	}
}

return dlugosc;
}

void wyswietlanie(list<zadanie> &lista_zadan, int dlugosc)
{


 cout<<"ES EF LS LF :"<<endl;
for(list<zadanie>::iterator obiekt_it=lista_zadan.begin(); obiekt_it!=lista_zadan.end();obiekt_it++)
		cout<< obiekt_it->ES << " " << obiekt_it->EF << " " << obiekt_it->LS<<" "<< obiekt_it->LF << endl;
cout<<endl;
cout<<"dlugosc :"<<dlugosc<<endl<<endl;

lista_zadan.sort(compare);

cout<<"sciezka krytyczna: " <<endl;
for(list<zadanie>::iterator obiekt_it=lista_zadan.begin(); obiekt_it!=lista_zadan.end();obiekt_it++)	
		if((obiekt_it->EF==obiekt_it->LF) && (obiekt_it->ES==obiekt_it->LS))
			cout<< obiekt_it->ID<<" "<<obiekt_it->ES<<" "<<obiekt_it->EF<<endl;
}

	


int _tmain(int argc, _TCHAR* argv[])
{
	list<zadanie> lista_zadan;
	list<zadanie> lista_zadan3;

	list<relacja> lista_relacji;
	int rozmiar,ilosc_relacji,budzet;
	int dlugosc=0;
	fstream plik;
	plik.open("data10.txt", std::ios::in );
	plik >> rozmiar;
	plik >> ilosc_relacji;
	plik >> budzet;
	
	for(int i=0; i <rozmiar; i++)
	{
		zadanie *nowa = new zadanie();
		nowa->ID=i+1;
		plik >> nowa->waga;
		plik >> nowa->early_waga;
		plik >> nowa->cena_j;
		lista_zadan.push_back(*nowa);		
	}
	

	for(int i=0; i<ilosc_relacji; i++)
	{
		relacja *rel = new relacja();
		plik >> rel->poczatek;
		plik >> rel->koniec;
		lista_relacji.push_back(*rel);
		for(list<zadanie>::iterator it=lista_zadan.begin(); it!=lista_zadan.end(); it++)
		{
			if(rel->poczatek == it->ID)
			{
				for(list<zadanie>::iterator it3=lista_zadan.begin(); it3!=lista_zadan.end(); it3++)
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

	lista_zadan3=lista_zadan;

	algorytm(lista_zadan,lista_zadan,rozmiar,dlugosc);						// wyliczenie œciezki krytycznej dla bazowej wartosci czasu trwania zadania
	//wyswietlanie(lista_zadan,dlugosc);
	algorytm_skracania(lista_zadan,lista_zadan3,budzet,rozmiar,dlugosc);					// algorytm skracania sciezki krytycznej

	//dlugosc=0;
	cout<<endl;
	dlugosc=algorytm(lista_zadan3,lista_zadan3,rozmiar,dlugosc);			// ponowne wyliczenie sciezki krytycznej
	wyswietlanie(lista_zadan3,dlugosc);

	



	system("PAUSE");
}


	



////////////////////////////// WYSWIETLANIE CALEJ LISTY ////////////////////////////////////////////
/*
	for(list<zadanie>::iterator obiekt_it=lista_zadan3.begin(); obiekt_it!=lista_zadan3.end();obiekt_it++)
	{
		cout<<"ID "<<obiekt_it->ID<<" waga "<<obiekt_it->waga<<" wczesna waga "<<obiekt_it->early_waga<<" cena " << obiekt_it->cena_j<<endl;
		cout<<"po mnie jest ";
		for(list<zadanie*>::iterator next_it=obiekt_it->next.begin(); next_it != obiekt_it->next.end(); next_it++)
			cout << (*next_it)->ID<<" "; 
		cout<<endl;
		cout<<"przedemna sa ";
		for(list<zadanie*>::iterator before_it=obiekt_it->before.begin(); before_it != obiekt_it->before.end(); before_it++)
			cout<< (*before_it)->ID<<" ";
		cout <<endl<<endl;

	}
*/