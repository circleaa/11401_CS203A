#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

struct string
{
   size_t size = 0;
   char *charArray = new char[ 21 ]();
};

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords( string &dictionaryWord, string &inputtedWord );

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord );


void embeddedWords(string& dictionaryWord, string& inputtedWord)
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

	while (inFile >> dictionaryWord.charArray)
	{
		dictionaryWord.size = strlen(dictionaryWord.charArray);
		if (dictionaryWord.size > inputtedWord.size)
			break;
		if (isSubstring(dictionaryWord,inputtedWord))
			outFile << dictionaryWord.charArray << endl;
	}
	inFile.close();
	outFile.close();
}

bool isSubstring(string& dictionaryWord,string& inputtedWord)
{
	for (int j= 0; j <= inputtedWord.size - dictionaryWord.size; j++)
	{
		int i;
		for (i = 0;i < dictionaryWord.size;i++)
			if (dictionaryWord.charArray[i] != inputtedWord.charArray[i + j])
				break;
		if (i == dictionaryWord.size)
			return true;
	}
	return false;
}

int main()
{
   string inputtedWord;
   cout << "Enter a word: ";
   cin >> inputtedWord.charArray;
   inputtedWord.size = strlen( inputtedWord.charArray );

   string dictionaryWord;

   embeddedWords( dictionaryWord, inputtedWord );

   system( "pause" );
}