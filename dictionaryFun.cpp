/*
Finds the word with the lowest ratio of unique letters to word length (i.e. what word repeats the most)

Expects a dictionary written in a file called "dictionary.txt" in this directory
*/


#include<iostream>
#include<fstream>
#include<string>
using namespace std;

double calcRatio(string word)
{
	// ratio = (number unique letters) / (total number letters)
	bool alphabet[26] = { 0 };
	int uniqueLetters = 0;
	for (int i = 0; i < word.length(); i++) {
		if (!alphabet[(int)word[i] - 97]) {
			uniqueLetters++;
			alphabet[(int)word[i] - 97] = 1;
		}
	}
	return uniqueLetters / (double)word.length();
}

int main()
{	
	ifstream dictionary("dictionary.txt");
	if (dictionary.fail())
		cout << "File load failed";
	string word;
	double ratio;
	string bestword;
	double minratio = 1;
	while (getline(dictionary, word)) {
		ratio = calcRatio(word);
		if (ratio < minratio) {
			minratio = ratio;
			bestword = word;
		}
	}

	cout << bestword << ", " << minratio;

	dictionary.close();
}