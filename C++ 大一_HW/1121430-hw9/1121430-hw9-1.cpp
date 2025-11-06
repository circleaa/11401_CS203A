#include <iostream>
#include <fstream>
#include <string>
using namespace::std;

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords( string &dictionaryWord, string &inputtedWord );

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord );

void embeddedWords(string &dictionaryWord, string &inputtedWord)
{
	ifstream inFile("Dictionary.txt", ios::in);
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	ofstream outFile("word.txt", ios::out);
	if (!outFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	while (inFile >> dictionaryWord)
	{
		if (dictionaryWord.size() > inputtedWord.size())
			break;
		if (isSubstring(dictionaryWord, inputtedWord))
			outFile << dictionaryWord << endl;
	}
	
	inFile.close();
	outFile.close();
}

bool isSubstring(string &dictionaryWord, string &inputtedWord)
{
	for (int j = 0; j <= inputtedWord.size() - dictionaryWord.size(); j++)
	{
		int i;
		for (i = 0;i < dictionaryWord.size();i++)
			if (dictionaryWord[i] != inputtedWord[i + j])
				break;
		if (i == dictionaryWord.size())
			return true;
	}
	return false;
}

int main()
{
   string inputtedWord;
   cout << "Enter a word: ";
   cin >> inputtedWord;

   string dictionaryWord;
   embeddedWords( dictionaryWord, inputtedWord );

   system( "pause" );
}