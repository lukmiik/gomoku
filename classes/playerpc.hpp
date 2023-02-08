#include "game.hpp"
#include "board.hpp"
#ifndef playerpc_hpp
#define playerpc_hpp
using namespace std;

class Playerpc :public Game
{
protected:
	int i;
	int j;
public:
	Playerpc(Game* o);
	void player_turn(int x);
};
#endif