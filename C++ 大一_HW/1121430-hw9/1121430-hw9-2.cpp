#include <iostream>
#include <fstream>
#include <vector>
using namespace::std;

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords(vector< char >& dictionaryWord, vector< char >& inputtedWord);

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring(vector< char >& dictionaryWord, vector< char >& inputtedWord);

int main()
{
	vector< char > inputtedWord;

	cout << "Enter a word: ";
	char ch = cin.get();
	while (ch != '\n')
	{
		inputtedWord.push_back(ch);
		ch = cin.get();
	}

	vector< char > dictionaryWord;
	embeddedWords(dictionaryWord, inputtedWord);

	system("pause");
}

void embeddedWords(vector< char >& dictionaryWord, vector< char >& inputtedWord)
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

	char ch = inFile.get();
	while (!inFile.eof())
	{
		while (ch != '\n')
		{
			dictionaryWord.push_back(ch);
			ch = inFile.get();
		}
		//for (int i = 0;i < dictionaryWord.size();i++)
			//inFile >> dictionaryWord[i];

		if (dictionaryWord.size() > inputtedWord.size())
			break;
		if (isSubstring(dictionaryWord, inputtedWord))
		{
			for (int i = 0;i < dictionaryWord.size();i++)
				outFile << dictionaryWord[i];
			outFile << endl;
		}
		dictionaryWord.clear();
		ch = inFile.get();
	}

	inFile.close();
	outFile.close();
}

bool isSubstring(vector< char >& dictionaryWord, vector< char >& inputtedWord)
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



