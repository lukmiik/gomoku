#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include "player.hpp"
#include "board.hpp"
#include "game.hpp"
using namespace std;

Player::Player(Game* o) : Game(o)//wykonuje konstruktor klasy Game
{}

void Player::player_turn(char nick[50], int x)//pyta użytkownika o współrzędne, sprawdza czy dane są poprawne oraz przypisuje odpowiednią liczbę do tablicy
{
	int c[2];
	print_board(board);
	if (x ==1)
		cout << nick << " wprowadz wspolrzedne(Np: 12 1) pola na ktory chcesz postawic krzyzyk:\t";
	else if (x==2)
		cout << nick << " wprowadz wspolrzedne(Np: 12 1) pola na ktory chcesz postawic kolko:\t";
	while (!(cin >> c[0] >> c[1]) || c[0] < 1 || c[0] > 15 || c[1] < 1 || c[1] > 15 || board[15 - c[0]][c[1] - 1] != 0 || getc(stdin) != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledne dane. sprobuj ponowenie:\t";
	}
	board[15 - c[0]][c[1] - 1] = x;
	system("CLS");
}