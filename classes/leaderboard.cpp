#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "leaderboard.hpp"
using namespace std;

Leaderboard::Leaderboard() //konstruktor domyślny tworzący tablice do rankingu
{
	char scoreboard[MAX][50] = { NULL };
}

int Leaderboard::check_file_exists() //sprawdza czy istnieje już plik
{
	file.open("leaderboard.txt", ios::in);
	if (file.good())
		return 1;
	else
	{
		return 0;
	}
}

void Leaderboard::take_data() //pobiera dane z pliku i zapisuje je do tablicy
{
	for (int i = 0; i < MAX; ++i)
	{
		file >> scoreboard[i];
		if (file.eof())
			break;
	}
	file.close();
}

void Leaderboard::print_leaderboard() //wypisuje ranking z tablicy
{
	int j = 1;
	cout.width(110);
	cout << right << "LEADERBOARD"<<endl<<endl<<endl;
	cout.width(50);
	cout << left << "RANK";
	cout.width(50);
	cout << left << "NICK";
	cout.width(50);
	cout << left << "WINS";
	cout.width(50);
	cout << left << "LOSES";
	cout.width(50);
	cout << left << "DRAW";
	for (int i = 0; i < MAX; ++i)
	{
		if (scoreboard[i][0] == '\0')
		{
			break;
		}
		if (i == 0 || (i) % 4 == 0)
		{
			cout << endl;
			cout.width(50);
			cout << left << j;
			++j;
		}
		cout.width(50);
		cout << left << scoreboard[i];		
	}
	cout << endl;
}

void Leaderboard::new_data_new_file(char* nick_win, char* nick_lose, int x, int y, int d) //zapisuje dane do tablicy jesli użytkownik o podanym nicku grał pierwszy raz
{
	int flag_win = x;//przechowuje informacje czy użytkownik który wygrał został już zapisany do rankingu
	int flag_lose = y;//przechowuje informacje czy użytkownik który przegrał został już zapisany do rankingu
	for (int i = 0; i < MAX; ++i)
	{
		if (d == 1)
		{
			if (flag_win == 0)
			{
				if (scoreboard[i][0] == '\0')
				{
					strcpy(scoreboard[i], nick_win);
					strcpy(scoreboard[i + 1], "0");
					strcpy(scoreboard[i + 2], "0");
					strcpy(scoreboard[i + 3], "1");
					++flag_win;
				}
			}
			if (flag_lose == 0)
			{
				if (scoreboard[i][0] == '\0')
				{
					strcpy(scoreboard[i], nick_lose);
					strcpy(scoreboard[i + 1], "0");
					strcpy(scoreboard[i + 2], "0");
					strcpy(scoreboard[i + 3], "1");
					++flag_lose;
				}
			}
		}
		else
		{
			if (flag_win == 0)
			{
				if (scoreboard[i][0] == '\0')
				{
					strcpy(scoreboard[i], nick_win);
					strcpy(scoreboard[i + 1], "1");
					strcpy(scoreboard[i + 2], "0");
					strcpy(scoreboard[i + 3], "0");
					++flag_win;
				}
			}
			if (flag_lose == 0)
			{
				if (scoreboard[i][0] == '\0')
				{
					strcpy(scoreboard[i], nick_lose);
					strcpy(scoreboard[i + 1], "0");
					strcpy(scoreboard[i + 2], "1");
					strcpy(scoreboard[i + 3], "0");
					++flag_lose;
				}
			}
		}
		if ((flag_win + flag_lose) == 2)//Wszyscy gracze zostali zapisani do rankingu
			break;
	}

}

void Leaderboard::new_data(char* nick_win, char* nick_lose, int d) //zapisuje nowe dane do tablicy po skończonej grze
{
	int flag_win = 0;//przechowuje informacje czy użytkownik który wygrał został już zapisany do rankingu
	int flag_lose = 0;//przechowuje informacje czy użytkownik który przegrał został już zapisany do rankingu
	for (int i = 0; i < MAX; ++i)
	{
		if (d == 1)
		{
			if (strcmp(scoreboard[i], nick_win) == 0)
			{
				int x = atoi(scoreboard[i + 3]); //konwertuje dane z tablicy z char do int
				x++;
				string s = to_string(x); //konwertuje x z int na string
				const char* new_number = s.c_str();//konwertuje string na ciąg który może być zapisany w tablicy znaków
				strcpy(scoreboard[i + 3], new_number);
				++flag_win;
			}
			if (strcmp(scoreboard[i], nick_lose) == 0)
			{
				int x = atoi(scoreboard[i + 3]); //konwertuje dane z tablicy z char do int
				x++;
				string s = to_string(x); //konwertuje x z int na string
				const char* new_number = s.c_str(); //konwertuje string na ciąg który może być zapisany w tablicy znaków
				strcpy(scoreboard[i + 3], new_number);
				++flag_lose;
			}
		}
		else
		{
			if (strcmp(scoreboard[i], nick_win) == 0)
			{
				int x = atoi(scoreboard[i + 1]);//konwertuje dane z tablicy z char do int
				x++;
				string s = to_string(x); //konwertuje x z int na string
				const char* new_number = s.c_str();//konwertuje string na ciąg który może być zapisany w tablicy znaków
				strcpy(scoreboard[i + 1], new_number);
				++flag_win;
			}
			if (strcmp(scoreboard[i], nick_lose) == 0)
			{
				int x = atoi(scoreboard[i + 2]);//konwertuje dane z tablicy z char do int
				x++;
				string s = to_string(x); //konwertuje x z int na string
				const char* new_number = s.c_str();//konwertuje string na ciąg który może być zapisany w tablicy znaków
				strcpy(scoreboard[i + 2], new_number);
				++flag_lose;
			}
		}
		if ((flag_win + flag_lose) == 2)//Wszyscy gracze zostali zapisani do rankingu
			break;
		if (scoreboard[i][0] == '\0')//Graczy o podanych nickach nie ma w rankingu
		{
			break;
		}
	}
	if ((flag_win + flag_lose) < 2) //meotda się wywołuje jeśli conajmniej jeden z użytkowników jest wpisywany pierwszy raz do rankingu
	{
		new_data_new_file(nick_win, nick_lose, flag_win,  flag_lose, d);
	}
}

void Leaderboard::sorting() //sortuje ranking w tablicy od użytkownika z największą ilością wygranych do tego z najmniejszą
{
	for (int i = 0; i < MAX/4; ++i)
	{
		char temp1[50];
		char temp2[50];
		char temp3[50];
		char temp4[50];
		int x = 0; //liczba wygranych
		int max = 0;
		int n = -1; //indeks najwięcej wygranych
		for (int j = 4*i; j < MAX; ++j)//znajdowanie największej ilości wygranych
		{
			if (j % 4 == 1)
			{
				x = atoi(scoreboard[j]);//konwertuje dane z tablicy z char do int
				if (x > max)
				{
					max = x;
					n = j;
				}				
			}
		}
		if (n>0 && n != (i * 4 + 1))
		{
			strcpy(temp1, scoreboard[i * 4]);
			strcpy(temp2, scoreboard[i * 4 + 1]);
			strcpy(temp3, scoreboard[i * 4 + 2]);
			strcpy(temp4, scoreboard[i * 4 + 3]);
			strcpy(scoreboard[i * 4], scoreboard[n -1]);
			strcpy(scoreboard[i * 4+1], scoreboard[n ]);
			strcpy(scoreboard[i * 4+2], scoreboard[n +1]);
			strcpy(scoreboard[i * 4+3], scoreboard[n +2]);
			strcpy(scoreboard[n -1], temp1);
			strcpy(scoreboard[n ], temp2);
			strcpy(scoreboard[n +1], temp3);
			strcpy(scoreboard[n +2], temp4);
		}		
	}		
}

void Leaderboard::new_file() //zapisuje nowy ranking do pliku
{
	file.open("leaderboard.txt", ios::out);
	for (int i = 0; i < MAX; ++i)
	{
		if (scoreboard[i][0] == '\0')
		{
			break;
		}
		file << scoreboard[i] << " ";
		if (i!=0 && i %4 ==3)
			file << endl;
		}
	file.close();
}

void Leaderboard::all_leaderboard(char* nick_win, char* nick_lose, int d) //wywołuje odpowiednie metody w zależności od tego czy plik istnieje czy tworzymy go pierwszy raz
{
	if (check_file_exists() == 1)
	{
		take_data();
		new_data(nick_win, nick_lose, d);
		sorting();
		print_leaderboard();
		new_file();
	}
	else
	{
		new_data_new_file(nick_win, nick_lose, 0, 0, d);
		sorting();
		print_leaderboard();
		new_file();
	}
}
