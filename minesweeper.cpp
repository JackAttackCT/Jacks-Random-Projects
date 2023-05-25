/*

Minesweeper I made because I was bored

*/

#include<iostream>
#include<ctime>
using namespace std;

double const density = 0.15;
int const width = 10;
int const height = 10;
/*       X
	  0 1 2 3 4 5
	  _ _ _ _ _ _
	0|
	1|
Y   2|
	3|
	4|
	5|

	0 = unflagged no mine, 1 = flagged no mine, 2 = unflagged mine, 3 = flagged mine, 4 = tripped mine, 5-13 = 0-8 surrounding mines
*/

bool checkwin(char board[width][height]) //true=player has won, all non-mined tiles are revealed (can still have unflagged mines)
{
	bool won = 1;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (board[x][y] < 2)//any flagged or unflagged spaces without mines (not revealed) means player hasn't won
				won = 0;
		}
	}

	if (won == 1)
		cout << "YOU WIN\n";
	return won;
}

void drawBoard(char board[width][height])
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			switch (board[x][y]) {
			case 0:
				cout << '#';
				break;
			case 2:
				cout << 'M';
				break;
			case 1:
			case 3:
				cout << 'Y';
				break;
			case 4:
				cout << 'O';
				break;
			case 5:
				cout << ' ';
				break;
			default:
				cout << (char)(board[x][y] + 43);
				break;
			}
			cout << ' ';
		}
		cout << endl;
	}
}

bool updateboard(char board[width][height], int x, int y, bool mode)//return true if mine has been tripped
{
	if (board[x][y] == 3 || board[x][y] == 1) {//1, 3
		if (mode) {
			board[x][y] = (board[x][y] == 1) ? 0 : 2;
			drawBoard(board);
		}
		else
			cout << "Cannot dig up tile with flag on it\n";
	}
	else if (board[x][y] == 2) {//2
		if (mode) {
			board[x][y] = 3;
			drawBoard(board);
		}
		else {
			board[x][y] = 4;
			drawBoard(board);
			cout << "GAME OVER\n";
			return 1;
		}
	}

	else if (board[x][y] > 4)//5+
		cout << "Already dug up this tile\n";

	else {//0
		if (mode) {
			board[x][y] = 1;
			drawBoard(board);
		}
		else {
			char minesum = 0;
			for (int ex = -1; ex < 2; ex++) {
				for (int why = -1; why < 2; why++) {
					if (x + ex >= 0 && x + ex < width && y + why >= 0 && y + why < height) {
						if (board[x + ex][y + why] == 2 || board[x + ex][y + why] == 3)
							minesum++;
					}
				}
			}
			board[x][y] = minesum + 5;
			drawBoard(board);
		}
	}
	return 0;
}

int main()
{
	srand(time(0));
	char board[width][height] = { 0 };
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (rand() % 1000 < density * 1000)
				board[x][y] = 2;
		}
	}

	drawBoard(board);
	char storage;
	int x;
	int y;
	bool mode;//1 for flag, 0 for dig
	while (1) {
		cout << "x coord: ";
		cin >> x;
		cout << "y coord: ";
		cin >> y;
		cout << "mode (l to dig, r to flag): ";
		cin >> storage;
		if (tolower(storage) == 'l')
			mode = 0;
		else
			mode = 1;
		if (updateboard(board, x, y, mode) || checkwin(board)) {
			break;
		}
	}
}