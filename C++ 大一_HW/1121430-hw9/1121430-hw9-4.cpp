#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

class string
{
public:
   // prints all English words which are contiguous substrings of inputtedWord into a file
   void embeddedWords( string &inputtedWord );

   // returns true if and only if dictionaryWord is a substring of inputtedWord
   bool isSubstring( string &inputtedWord );

   size_t size = 0;
   char *charArray = new char[ 21 ]();
};

void string::embeddedWords(string& inputtedWord)
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

	while (inFile >> charArray)
	{
		size = strlen(charArray);
		if (size > inputtedWord.size)
			break;
		if (isSubstring(inputtedWord))
			outFile << charArray << endl;
	}
	inFile.close();
	outFile.close();
}

bool string::isSubstring(string& inputtedWord)
{
	for (int j = 0; j <= inputtedWord.size - size; j++)
	{
		int i;
		for (i = 0;i < size;i++)
			if (charArray[i] != inputtedWord.charArray[i + j])
				break;
		if (i == size)
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
   dictionaryWord.embeddedWords( inputtedWord );

   system( "pause" );
}