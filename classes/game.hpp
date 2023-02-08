#include "board.hpp"
#ifndef game_hpp
#define game_hpp
using namespace std;

class Game:public Board
{
protected:
	int** board;
	char nick1[50];
	char nick2[50];
	int start = -1;	
	Game* game;
public:	
	Game();
	Game(Game* o);
	char* get_nick1();
	char* get_nick2();
	int get_start();
	int game_pvp_or_pc();//Uzytkownik decyduje czy chce grac z kims czy z komputerem
	void game_pvp_start();//Uzytkownik decyduje kto zaczyna
	void game_pc_start();//Uzytkownik decyduje kto zaczyna
	int next_game();//Uzytkownik decyduje czy chce grac dalej
	int check_win(int** tab, int x, char nick[50]);
	virtual void player_turn(char nick[50],int x);
};
#endif