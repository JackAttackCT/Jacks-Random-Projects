/*
A game of Nim
On your turn you can take 1, 2, or 3 chips. The person who takes the last chip wins
Trust me it's totally fair I beat it every time, if you don't it's a skill issue
*/
#include<iostream>
using namespace std;
int main()
{
	short total = 20;
	short input;
	cout << "There are " << total << " chips.\n";
	while (total > 0) {
		cout << "How many chips would you like to take? ";
		cin >> input;
		while (input > 3 || input < 1 || input > total) {
			cout << "That amount is invalid, please try again.\n";
			cin >> input;
		}
		total -= 4;
		cout << "The computer takes " << 4 - input << " chip" << ((input != 3) ? "s." : ".") << " There are now " << total << " chips.\n";
	}
	cout << "The computer has won.";
}
