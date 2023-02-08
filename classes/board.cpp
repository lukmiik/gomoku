#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include "board.hpp"
using namespace std;

Board::Board()//konstruktor domyślny tworzy tablice reprezentującą plansze
{
	tab = new int* [15];
	for (int i = 0; i < 15; ++i)
	{
		tab[i] = new int[15];
	}
	for (int j = 0; j < 15; ++j)
	{
		for (int k = 0; k < 15; ++k)
		{
			tab[j][k] = { 0 };
		}
	}
}

void Board::print_board(int** tab)//wypisuje plansze na ekran
{
	for (int i = 0; i < 15; ++i)
	{
		cout.width(5);
		cout << left << 15 - i;		
		for (int j = 0; j < 15; ++j)
		{
			if (j == 14)
			{
				if (tab[i][j] == 0)
					cout << " ";
				else if (tab[i][j] == 1)
					cout<<"X";
				else if (tab[i][j] == 2)
					cout<<"O";
			}
			else
			{
				if (tab[i][j] == 0)
					cout<<" ---";
				else if (tab[i][j] == 1)
					cout<<"X---";
				else if (tab[i][j] == 2)
					cout<<"O---";
			}
		}
		cout<<endl;
		if (i != 14)
		{
			cout<<"     ";
			for (int k = 0; k < 15; ++k)
			{
				cout<<"|   ";
			}
		}
		if (i == 14)
		{
			cout << endl;
			for (int l = 0; l < 15; ++l)
			{
				if (l == 0)
				{
					cout.width(6);
					cout << right << l+1<<"   ";
				}
				else
				{
					cout.width(4);
					cout << left << l + 1;
				}
			}
		}
		cout << endl;
	}
}

void Board::reset_board(int** tab)//czysci tablice
{
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			tab[i][j] = 0;
		}
	}
}

int** Board::get_tab() { return tab; }

