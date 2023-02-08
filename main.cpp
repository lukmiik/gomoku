#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include "classes/board.hpp"
#include "classes/game.hpp"
#include "classes/player.hpp"
#include "classes/playerpc.hpp"
#include "classes/leaderboard.hpp"
using namespace std;

int main()
{
	Game* game = new Game;
	Game *player1 = new Player(game);
	Game *player2 = new Player(game);
	Playerpc * pc = new Playerpc(game);
	Leaderboard* leaderboard = new Leaderboard();
	int dalej = 1;//zapisuje czy użytkownik chce dalej grać
	int start = 0;//zapisuje kto zaczyna grę

	while (1)
	{
		int wybor = -1;
		int win = 0; //zapisuje kto wygral
		wybor = game->game_pvp_or_pc();
		char nick1[50];
		char nick2[50];
		int** tab = game->get_tab();
		if (wybor == 0)//gra pvp
		{			
			game->game_pvp_start();
			strcpy(nick1, game->get_nick1());
			strcpy(nick2, game->get_nick2());
			start = game->get_start();
			system("CLS");//czyści ekran
			if (start == 1) //zaczyna gracz który pierwszy podał nick
			{
				while (1)
				{
					player1->player_turn(nick1, 1);
					int x = game->check_win(tab, 1, nick1);
					if (x == 1) //player1 win
					{
						win = 1;
						break;
					}
					else if (x == 2) //draw
					{
						win = 3;
						break;
					}						
					player2->player_turn(nick2,2);
					if (game->check_win(tab, 2, nick2) == 1) //player2 win
					{
						win =2;
						break;
					}
				}
			}
			else if (start == 2) //zaczyna gracz który drugi podał nick
			{
				while (1)
				{
					player2->player_turn(nick2, 1);
					int x = game->check_win(tab, 1, nick2);
					if ( x== 1)//player2 win
					{
						win = 2;
						break;
					}
					else if (x == 2)//draw
					{
						win = 3;
						break;
					}
					player1->player_turn(nick1,  2);
					if (game->check_win(tab, 2, nick1) == 1) //player1 win
					{
						win = 1;
						break;
					}
				}
			}

		}
		else if (wybor == 1)//gra z pc
		{
			strcpy(nick2, "pc");
			game->game_pc_start();
			strcpy(nick1, game->get_nick1());
			start = game->get_start();
			system("CLS");//czyści ekran
			if (start == 1) //zaczyna użytkownik
			{
				while (1)
				{
					player1->player_turn(nick1, 1);
					int x = game->check_win(tab, 1, nick1);
					if (x == 1)//player1 win
					{
						win = 1;
						break;
					}
					else if (x == 2)//draw
					{
						win = 3;
						break;
					}
					pc->player_turn(2);
					if (game->check_win(tab, 2, nick2) == 1) //pc win
					{
						win = 2;
						break;
					}
				}
			}
			else if (start == 2)//zaczyna komputer
			{
				while (1)
				{
					pc->player_turn(1);
					int x = game->check_win(tab, 1, nick2);
					if ( x== 1)//pc win
					{
						win = 2;
						break;
					}
					else if (x == 2)//draw
					{
						win = 3;
						break;
					}
					player1->player_turn(nick1, 2);
					if (game->check_win(tab, 2, nick1) == 1)//player1 win
					{
						win = 1;
						break;
					}
				}
			}
		}
		if (win == 1)//player1 win
		{
			leaderboard->all_leaderboard(nick1, nick2, 0);
		}
		else if (win == 2)//player2 or pc win
		{
			leaderboard->all_leaderboard(nick2, nick1, 0);
		}
		else if (win == 3)//draw
		{
			leaderboard->all_leaderboard(nick2, nick1,1);
		}
		if (game->next_game() == 0)//pyta się czy użytkownik chce jeszcze raz zagrać
		{
			break;
		}			
		game->reset_board(tab);
	}
	system("pause");
	return 0;
}