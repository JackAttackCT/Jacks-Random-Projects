/*
Snake AI that plays perfectly and wins every time






(except when it doesn't and we don't talk about that)
((also this mess of spaghetti code took way to long to make))
*/

#include<iostream>
#include<ctime>
#include<math.h>
#include<thread>
#include<chrono>
#include<string>
using namespace std;

int const width = 10;//EVEN NUMBERS > 0
int const height = 10;
int const horizspace = 3;
int const vertspace = 1;
int const framerate = 5;

void display(int tailPos[width][height], int length)//show screen based on array param width x height
{
	string outputtext = " ";

	//cout << " ";
	for (int i = 0; i < width; i++) {
		//cout.width(horizspace);
		//cout << "-";
		outputtext.resize(outputtext.length() - 1 + horizspace);
		outputtext += "-";
	}
	//cout << endl;
	outputtext += "\n";
	for (int y = height - 1; y >= 0; y--) {
		//cout << "|";
		outputtext += "|";
		for (int x = 0; x < width; x++) {
			outputtext.resize(outputtext.length() - 1 + horizspace);
			if (tailPos[x][y] == 0) {
				//cout << ' ';
				outputtext += " ";
			}
			else if (tailPos[x][y] == -1) {
				//cout << '@';
				outputtext += "A";
			}
			else if (tailPos[x][y] == length) {
				//cout << "O";
				outputtext += "O";
			}
			else {
				//cout << '#';
				outputtext += "#";
			}
		}
		//cout << "|";
		outputtext += "|";
		for (int i = 0; i < vertspace; i++)
			//cout << endl;
			outputtext += "\n";
	}
	//cout << " ";
	outputtext += " ";
	for (int i = 0; i < width; i++) {
		//cout.width(horizspace);
		//cout << "-";
		outputtext.resize(outputtext.length() - 1 + horizspace);
		outputtext += "-";
	}
	//cout << endl << "Length: " << length;
	outputtext += "\n";
	outputtext += "Length: ";
	outputtext += to_string(length);
	outputtext += "\n";

	system("CLS");
	cout << outputtext;
}
void generatecycle(int cycle[width][height])//take array with dimensions width x height, and set those to the hamiltonia cycle
{
	bool walls[width + 1][height + 1];//create array representing the walls of a maze, which will be solved in order to create the cycle
	for (int w = 0; w <= width; w++) {
		for (int h = 0; h <= height; h++)
			walls[w][h] = 0;//set all items of array to 0 by default
	}
	for (int w = 0; w < width / 2 - 1; w++) {//loop for a select number of nodes in middle of array, if random number is 1 put wall below, if number is zero put wall to left
		for (int h = 0; h < height / 2 - 1; h++) {
			if (rand() % 2 == 1)
				walls[w * 2 + 2][h * 2 + 1] = 1;
			else
				walls[w * 2 + 1][h * 2 + 2] = 1;
		}
	}
	for (int w = 0; w <= width; w++) {//set walls at top and bottom to 1
		walls[w][0] = 1;
		walls[w][height] = 1;
	}
	for (int h = 0; h <= height; h++) {//set walls at left and right to 1
		walls[0][h] = 1;
		walls[width][h] = 1;
	}
	int x = 0;//start at 0,0
	int y = 0;
	int i = 0;//i keeps track of how many steps have been taken so far
	int direction = 1;//start going right
	/*   0
	  3 -+- 1
	     2
	*/
	do {
		direction = (direction + 2) % 4;//turn 180 degrees before starting turn loop
		bool invalid = 1;//invalid is set to 0 if it is found during the loop that the direction being tested can be used
		while (invalid) {//loop until good direction is found
			direction--;//turn left
			if (direction == -1) {//if turning left from 0, make sure it goes back to 3
				direction = 3;
			}
			if ((direction == 0) & ((y % 2 == 0) || (!walls[x / 2 * 2 + 1][y / 2 * 2 + 2]))) {//if facing up and there is no wall above current position, break loop
				invalid = 0;
				y++;
			}
			else if ((direction == 1) && ((x % 2 == 0) || (!walls[x / 2 * 2 + 2][y / 2 * 2 + 1]))) {//if facing right and there is no wall right of current position, break loop
				invalid = 0;
				x++;
			}
			else if ((direction == 2) && ((y % 2 == 1) || (!walls[x / 2 * 2 + 1][y / 2 * 2]))) {//if facing down and there is no wall below current position, break loop
				invalid = 0;
				y--;
			}
			else if ((direction == 3) && ((x % 2 == 1) || (!walls[x / 2 * 2][y / 2 * 2 + 1]))) {//if facing left and there is no wall left of current position, break loop
				invalid = 0;
				x--;
			}
		}
		i++;//increase counter by one
		cycle[x][y] = i;
	} while (x != 0 || y != 0);
	cycle[0][0] = 0;//set start position to 0
}

int finddirection(int x, int y, int cycle[width][height], int tailPos[width][height])//use in algorithm after shifting tailPos around (head of snake is in array, and end of tail shortened)
{
	int direction = -1;//direction defaults to -1. If this gets returned, the only possibility is that the snake has filled the board and the program should end
	int searchx = x;
	int searchy = y;
	do {
		//move along cycle by one
		if (cycle[searchx][(int)fmin(searchy + 1, height - 1)] == (cycle[searchx][searchy] + 1) % (width * height))//check to move up
			searchy++;
		else if (cycle[(int)fmin(searchx + 1, width - 1)][searchy] == (cycle[searchx][searchy] + 1) % (width * height))//check to move right
			searchx++;
		else if (cycle[searchx][(int)fmax(searchy - 1, 0)] == (cycle[searchx][searchy] + 1) % (width * height))//check to move down
			searchy--;
		else
			searchx--;
		
		if (tailPos[searchx][searchy]  > 0)
			break;

		if (searchx == x && searchy == y + 1)//see if we have reached one of the points yet. This means that when the loop breaks from hitting something, the last encountered point will be returned
			direction = 0;
		else if (searchx == x + 1 && searchy == y)
			direction = 1;
		else if (searchx == x && searchy == y - 1)
			direction = 2;
		else if (searchx == x - 1 && searchy == y)
			direction = 3;
	} while (tailPos[searchx][searchy] == 0);
	return direction;

}
int main()
{
	srand(time(0));
	if (!(width % 2 != 1 && height % 2 != 1 && width >= 2 && height >= 2)) {//quit program with error message if width or height are invalid; e.i odd or less than 2
		cout << "Program failed; width and height must be even numbers above 0\n";
		return 0;
	}

	int cycle[width][height];
	generatecycle(cycle);
	int tailPos[width][height];
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++)
			tailPos[x][y] = 0;
	}
	tailPos[width / 2][height / 2] = -1;
	tailPos[0][0] = 1;
	int x = 1;
	int y = 0;
	int direction = 1;
	int length = 2;
	do {
		if (direction > -1) {
			//move
			if (direction == 0)
				y++;
			else if (direction == 1)
				x++;
			else if (direction == 2)
				y--;
			else
				x--;
			//check if apple gotten
			if (tailPos[x][y] == -1) {
				length++;//increase length
				//relocate apple
				int randomx;
				int randomy;
				bool open = 0;
				for (int applex = 0; applex < width; applex++) {
					for (int appley = 0; appley < height; appley++) {
						if (tailPos[applex][appley] == 0) {
							open = 1;
							break;
						}
						if (open)
							break;
					}
				}
				do {
					randomx = rand() % width;
					randomy = rand() % height;
				} while (tailPos[randomx][randomy] != 0 && open);
				if (open)
					tailPos[randomx][randomy] = -1;
			}
			else {//if no apple
				for (int tailx = 0; tailx < width; tailx++) {//loop across tail, decrease all lifetimes by 1
					for (int taily = 0; taily < height; taily++) {
						if (tailPos[tailx][taily] > 0)
							tailPos[tailx][taily]--;
					}
				}
			}
			tailPos[x][y] = length;//move head forward
			direction = finddirection(x, y, cycle, tailPos);//find new direction
			this_thread::sleep_for(std::chrono::milliseconds(framerate));
		}
		display(tailPos, length);
	} while (direction != -1);
	return 0;
}