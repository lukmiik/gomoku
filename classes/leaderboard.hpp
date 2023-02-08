#include <fstream>
#ifndef leaderboard_hpp
#define leaderboard_hpp
#define MAX 500
using namespace std;

class Leaderboard
{
protected:
	fstream file;
	char scoreboard[MAX][50];
public:
	Leaderboard();
	int check_file_exists();
	void take_data();
	void print_leaderboard();
	void new_data_new_file(char* nick_win, char* nick_lose, int x, int y, int d); //Wpisuje dane jesli byl to pierwszy mecz uzytkownika
	void new_data(char* nick, char* nick_lose, int d); //wpisuje dane do tablicy
	void sorting();
	void new_file(); //Wpisuje dane do pliku
	void all_leaderboard(char* nick_win, char* nick_lose, int d); //Wywoluje odpowiednie funkcje z klasy Leaderboard
};
#endif