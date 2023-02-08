#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <time.h> 
#include "playerpc.hpp"
using namespace std;

Playerpc::Playerpc(Game* o) : Game(o)//wykonuje konstruktor klasy Game
{}

void Playerpc::player_turn(int x)//losowo przypisuje do planszy kółko
{
	srand(time(NULL));
	while (1)
	{
		i = rand() % 15;
		j = rand() % 15;
		if (board[i][j] == 0)//sprawdza czy wylosowane pole jest wolne
		{
			board[i][j] = x;
			break;
		}
	}
}