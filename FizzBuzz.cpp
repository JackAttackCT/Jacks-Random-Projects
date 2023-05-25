/*
FizzBuzz. That's it
It's easily customizable to work with any collection of factors and dumb words
*/
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int>factors = { 3, 5, 7 };
	vector<string>phrases = {"Fizz", "Buzz", "Bizz"};
	for (int i = 1; i <= 10000; i++) {
		string output;
		for (int j = 0; j < factors.size(); j++) {
			if (i % factors[j] == 0)
				output += phrases[j];
		}
		if (output == "")
			cout << i << endl;
		else
			cout << output << endl;
	}
}