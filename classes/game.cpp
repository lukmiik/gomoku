#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include "game.hpp"
using namespace std;

Game::Game() : Board()//konstruktor domyślny klasy Game inicjalizujący konstruktor domyślny klasy Board
{
}

Game::Game(Game* o)
{
	game = o;//przypisanie do obiektu game obiekt o
	board = o->get_tab();//przypisuje do zmiennej board plansze przypisaną do obiektu o
}
	
int Game :: game_pvp_or_pc()//pyta się czy użytkownić chce grać z innym użytkownikiem czy z komputerem
{
	int wybor = -1;
	cout << "Chcesz grac pvp(0) czy przeciwko pc(1) ?\t";
	while (!(cin >> wybor) || (wybor != 0 && wybor != 1) || getc(stdin)!='\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledne dane. sprobuj ponowenie:\t";
	}
	if (wybor == 0)
		return 0;
	else if (wybor == 1)
		return 1;
}

void Game::game_pvp_start()//pyta się o nicki użytkowników i kto zaczyna
{
	cout<<"Gracz 1 podaj swow nick:\t";
	while (!(cin >> nick1) || getc(stdin) != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledne dane. sprobuj ponowenie:\t";
	}
	cout<<"Gracz 2 podaj swoj nick:\t";
	while (!(cin >> nick2) ||  strcmp(nick1, nick2) == 0 || getc(stdin) != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledne dane. sprobuj ponowenie:\t";
	}
	cout<<"Kto zaczyna? " <<nick1 <<"(1) czy "<<nick2<<"(2) : \t";
	while (!(cin >> start) || (start != 1 && start != 2) || getc(stdin) != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledne dane. sprobuj ponowenie:\t";
	}
}

void Game::game_pc_start()//pyta się o nick użytkownika i kto zaczyna
{
	cout<<"Podaj swow nick:\t";
	while (!(cin >> nick1) || getc(stdin) != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledne dane. sprobuj ponowenie:\t";
	}
	cout << "Chcesz zaczynac " << nick1 << "? tak(1) czy nie(2) : \t";
	while (!(cin >> start) || (start != 1 && start != 2) || getc(stdin) != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledne dane. sprobuj ponowenie:\t";
	}
}

char* Game::get_nick1() { return nick1; }
char* Game::get_nick2() { return nick2; }
int Game::get_start() { return start; }

int Game::next_game()//pyta sie czy użytkownik chce dalej grać
{
	int dalej;
	cout<<endl<<endl<<endl<<"Chcesz grac dalej tak (1) nie (0):\t";
	while (!(cin >> dalej) || (dalej != 1 && dalej != 0) || getc(stdin) != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledne dane. sprobuj ponowenie:\t";
	}
	return dalej;
}

void Game::player_turn(char nick[50], int x)//wirtualna metoda wykonująca ruch użytkownika
{
	int c[2];
	cout<<"Wprowadz wspolrzedne(Np: 2\\n1) pola na ktory chcesz postawic krzyzyk:\t";
	while (!(cin >> c[0]>> c[1]) || c[0] < 1 || c[0] > 15 || c[1] < 1 || c[1] > 15 || tab[15 - c[0]][c[1] - 1] != 0 || getc(stdin) != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledne dane. sprobuj ponowenie:\t";
	}
	board[15 - c[0]][c[1] - 1] = 1;
	system("CLS");
}


int Game::check_win(int** tab, int x, char nick[50])//sprawdza czy ktoś wygrał lub czy jest remis
{
	int flag = 0;
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			//sprawdza czy pięć tych samych znaków jest ustawionych pionowo
			if (i == 0)
			{
				if (tab[i][j] == x && tab[i + 1][j] == x && tab[i + 2][j] == x && tab[i + 3][j] == x && tab[i + 4][j] == x && tab[i + 5][j] != x)
				{
					cout << "Gratulacje " << nick << ",WYGRALES"<<endl<<endl<<endl<<endl;
					flag = 1;
					return 1;
					break;
				}
			}
			else if (i > 0 && i < 10)
			{
				if (tab[i - 1][j] != x && tab[i][j] == x && tab[i + 1][j] == x && tab[i + 2][j] == x && tab[i + 3][j] == x && tab[i + 4][j] == x && tab[i + 5][j] != x)
				{
					cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
					flag = 1;
					return 1;
				}
			}
			else if (i == 10)
			{
				if (tab[i -1][j] != x && tab[i][j] == x && tab[i + 1][j] == x && tab[i + 2][j] == x && tab[i + 3][j] == x && tab[i + 4][j] == x)
				{
					cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
					flag = 1;
					return 1;
				}
			}
			//sprawdza czy pięć tych samych znaków jest ustawionych poziomo
			if (j == 0)
			{
				if (tab[i][j] == x && tab[i][j+1] == x && tab[i][j + 2] == x && tab[i][j + 3] == x && tab[i][j + 4] == x && tab[i][j + 5] != x)
				{
					cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
					flag = 1;
					return 1;
					break;
				}
			}
			else if (j > 0 && j < 10)
			{
				if (tab[i][j - 1] != x && tab[i][j] == x && tab[i][j + 1] == x && tab[i][j+2] == x && tab[i][j + 3] == x && tab[i][j + 4] == x && tab[i][j + 5] != x)
				{
					cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
					flag = 1;
					return 1;
				}
			}
			else if (j == 10)
			{
				if (tab[i][j - 1] != x && tab[i][j] == x && tab[i][j + 1] == x && tab[i][j + 2] == x && tab[i][j + 3] == x && tab[i][j + 4] == x)
				{
					cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
					flag = 1;
					return 1;
				}
			}
			//sprawdza czy pięć tych samych znaków jest ustawionych na ukos w prawo i do dołu
			if (i == 0)
			{
				if (j >= 0 && j < 10)
				{
					if (tab[i][j] == x && tab[i + 1][j + 1] == x && tab[i + 2][j + 2] == x && tab[i + 3][j + 3] == x && tab[i + 4][j + 4] == x && tab[i + 5][j + 5] != x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
						break;
					}
				}
				else if (j == 10)
				{
					if (tab[i][j] == x && tab[i + 1][j + 1] == x && tab[i + 2][j + 2] == x && tab[i + 3][j + 3] == x && tab[i + 4][j + 4] == x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
			}
			else if (j == 0)
			{
				if (i > 0 && i < 10)
				{
					if (tab[i][j] == x && tab[i + 1][j + 1] == x && tab[i + 2][j + 2] == x && tab[i + 3][j + 3] == x && tab[i + 4][j + 4] == x && tab[i + 5][j + 5] != x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
				else if (i == 10)
				{
					if (tab[i][j] == x && tab[i + 1][j + 1] == x && tab[i + 2][j + 2] == x && tab[i + 3][j + 3] == x && tab[i + 4][j + 4] == x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
			}
			else if (i > 0 && i < 10)
			{
				if (j > 0 && j < 10)
				{
					if (tab[i-1][j-1] != x && tab[i][j] == x && tab[i + 1][j + 1] == x && tab[i + 2][j + 2] == x && tab[i + 3][j + 3] == x && tab[i + 4][j + 4] == x && tab[i + 5][j + 5] != x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
				else if (j == 10)
				{
					if (tab[i - 1][j - 1] != x && tab[i][j] == x && tab[i + 1][j + 1] == x && tab[i + 2][j + 2] == x && tab[i + 3][j + 3] == x && tab[i + 4][j + 4] == x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
			}
			else if (i == 10)
			{
				if (j > 0 && j <= 10)
				{
					if (tab[i - 1][j - 1] != x && tab[i][j] == x && tab[i + 1][j + 1] == x && tab[i + 2][j + 2] == x && tab[i + 3][j + 3] == x && tab[i + 4][j + 4] == x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
			}
			//sprawdza czy pięć tych samych znaków jest ustawionych na ukos w prawo i do góry
			if (i == 4)
			{
				if (j > 0 && j <= 10)
				{
					if (tab[i + 1][j -1] != x && tab[i][j] == x && tab[i -1][j + 1] == x && tab[i - 2][j + 2] == x && tab[i - 3][j + 3] == x && tab[i - 4][j + 4] == x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
				else if (j == 0)
				{
					if (tab[i][j] == x && tab[i - 1][j + 1] == x && tab[i - 2][j + 2] == x && tab[i - 3][j + 3] == x && tab[i - 4][j + 4] == x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
			}
			else if (j == 0)
			{
				if (i > 4 && i <= 14)
				{
					if (tab[i][j] == x && tab[i - 1][j + 1] == x && tab[i - 2][j + 2] == x && tab[i - 3][j + 3] == x && tab[i - 4][j + 4] == x && tab[i - 5][j + 5] != x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
			}
			else if (i > 4 && i < 14)
			{
				if (j > 0 && j < 10)
				{
					if (tab[i + 1][j - 1] != x && tab[i][j] == x && tab[i - 1][j + 1] == x && tab[i - 2][j + 2] == x && tab[i - 3][j + 3] == x && tab[i - 4][j + 4] == x && tab[i - 5][j + 5] != x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
				else if (j == 10)
				{
					if (tab[i + 1][j - 1] != x && tab[i][j] == x && tab[i - 1][j + 1] == x && tab[i - 2][j + 2] == x && tab[i - 3][j + 3] == x && tab[i - 4][j + 4] == x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
			}
			else if (i == 14)
			{
				if (j > 0 && j < 10)
				{
					if (tab[i][j] == x && tab[i - 1][j + 1] == x && tab[i - 2][j + 2] == x && tab[i - 3][j + 3] == x && tab[i - 4][j + 4] == x && tab[i - 5][j + 5] != x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
				else if (j == 10)
				{
					if (tab[i][j] == x && tab[i - 1][j + 1] == x && tab[i - 2][j + 2] == x && tab[i - 3][j + 3] == x && tab[i - 4][j + 4] == x)
					{
						cout << "Gratulacje " << nick << ",WYGRALES" << endl << endl << endl << endl;
						flag = 1;
						return 1;
					}
				}
			}
		}
		if (flag == 1)
			break;
	}
	int flag2 = 0;
	if (flag == 0)//wykona się jesli nikt nie wygrał oraz sprawdza czy cała plansza jest zapełniona (remis)
	{	
		for (int i = 0; i < 15; ++i)
		{
			for (int j = 0; j < 15; ++j)
			{
				if (tab[i][j] == 0)
				{
					flag2 = 1;
					break;
				}
			}
			if (flag2 == 1)
				break;
		}
		if (flag2 == 0)
		{
			cout<<"REMIS";
			return 2;
		}
	}
	if (flag2 == 1 && flag == 0)//nikt nie wygrał ani nie ma remisu
	{
		return 0;
	}

}


