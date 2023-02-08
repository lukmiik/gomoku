#ifndef board_hpp
#define board_hpp
using namespace std;

class Board
{
protected:
	int** tab;
public:
	Board();
	int** get_tab();
	void print_board(int** tab);
	void reset_board(int** tab);
};
#endif