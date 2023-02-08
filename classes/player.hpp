#include "game.hpp"
#ifndef player1_hpp
#define player1_hpp
using namespace std;

class Player :public Game
{
public:
	Player(Game* o);
	void player_turn(char nick[50], int x);
};
#endif