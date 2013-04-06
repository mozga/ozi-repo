// SPD3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int n, m;
	
	ifstream data_in ("data001.txt");
	data_in >> n >> m;

	unsigned int ** tablica = new unsigned int * [n];
	for(int i=0; i<n; i++)
		tablica[i]= new unsigned int[m];


	for(int i = 0; i<n; i++)
		for(int j = 0; j<m; j++)
			data_in >> tablica[i][j];

	data_in.close();

	//for(int i = 0; i<n; i++)
	//{
	//	for(int j = 0; j<m; j++)
	//		cout << tablica[i][j] << " ";
	//cout << endl;
	//}

	list<int> * szereg = new list<int>;
	for(int q=0; q<m; q++)
	{
		int suma=0;
		for(int k=0; k<n; k++)
			suma+=tablica[k][q];
		szereg->push_back(suma);		
	}
	szereg->sort();

	int suma=0;
	for(list<int>::iterator it = szereg->begin(); it!=szereg->end(); it++);
	{
		cout << 
	system("PAUSE");
}

