/*
Interprets and runs a Braind*ck program written in a text file

Brainf*ck source code should be written in a file in the same directory and named "brainfck source.txt"
*/


#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void jumpForward(int& ipointer, string program)//moves instruction pointer to the position of the corrosponding close bracket
{
	int openbrackets = 1;

	while (openbrackets != 0) {

		ipointer++;

		if (program[ipointer] == '[')
			openbrackets++;
		else if (program[ipointer] == ']')
			openbrackets--;
	}
}

void jumpBack(int& ipointer, string program)//moves instruction pointer to position of corrosponding open bracket
{
	int closebrackets = 1;

	while (closebrackets != 0) {

		ipointer--;

		if (program[ipointer] == '[')
			closebrackets--;
		else if (program[ipointer] == ']')
			closebrackets++;
	}
}

int main()
{
	fstream source("brainfck source.txt");

	if (source.fail()){
		cout << "file open failed";
		return 0;
	}

	int ipointer = 0;
	int dpointer = 0;
	char array[30000] = {0};
	string program;
	string inputline;

	while (getline(source, inputline)) {
		program += inputline;
	}

	source.close();

	while (ipointer != program.length()) {

		switch (program[ipointer]) {

		case '>':
			if (dpointer + 1 < 30000)
				dpointer++;
			break;

		case '<':
			if (dpointer > 0)
				dpointer--;
			break;

		case '+':
			array[dpointer]++;
			break;

		case '-':
			array[dpointer]--;
			break;

		case '.':
			cout << array[dpointer];
			break;

		case ',':
			cin >> array[dpointer];
			break;

		case '[':
			if (array[dpointer] == 0)
				jumpForward(ipointer, program);
			break;

		case ']':
			if (array[dpointer] != 0)
				jumpBack(ipointer, program);
			break;

		default:
			break;
		}

		ipointer++;
	}

	return 0;
}