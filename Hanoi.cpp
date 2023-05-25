/*
Solves the Towers of Hanoi problem

Note - I wrote this code after hearing the problem, but before being told the solution. Oooh look at me aren't I clever.
*/

#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

vector<vector<int>>towers = { {}, {}, {} };//tracks what rings are on what poles
int steps = 0;//tracks number of steps taken

//displays the state of the poles and rings at a given time
void display() {
	//for each pole display the rings on it
	for (int i = 0; i < 3; i++) {
		cout << "|";//formatting
		//for each ring display the corresponding number to indicate size
		for (int j = 0; j < towers[i].size(); j++) {
			cout << setw(3) << towers[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

//moves a stack of arbitrary size from an initial position to a target position, while following puzzle rules
void move(int initialPole, int targetPole, int stackSize) {
	//if stack has size 1, move that one ring to the target
	if (stackSize == 1) {
		towers[targetPole - 1].push_back(towers[initialPole - 1].back());
		towers[initialPole - 1].pop_back();
		display();
		//increment movement counter
		steps++;
	}
	else {
		//find non-target pole
		int sum = initialPole + targetPole;
		int nonTargetPole = (sum == 3 ? 3 : (sum == 4 ? 2 : 1));
		//move all but bottom ring of stack to non-target pole
		move(initialPole, nonTargetPole, stackSize - 1);

		//move bottom ring to target
		move(initialPole, targetPole, 1);

		//move rest of stack back onto bottom ring
		move(nonTargetPole, targetPole, stackSize - 1);
	}
}

int main()
{
	//get size of initial stack
	int startsize;
	cout << "How many rings? ";
	cin >> startsize;
	cout << endl;
	//fill stack with rings in decreasing order
	for (int i = startsize; i > 0; i--)
		towers[0].push_back(i);
	//display initial configuration
	display();
	//solve the puzzle
	move(1, 3, startsize);
	//output number of moves required, equal to (2^n)-1 moves (optimal?)
	cout << "Solved in " << steps << " moves.\n";
	return 0;
}