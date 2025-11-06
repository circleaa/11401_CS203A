#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "SpellCheck.h"

SpellCheck::SpellCheck()
   : legalWords()
{
}

// Find every word w in the vector "dictionary" which satisfies two conditions:
// 1. the length of w is equal to the length of wordToCheck, and
// 2. wordToCheck and w are different on exactly one character.
// Put these words into the vector "legalWords".
void SpellCheck::equalLength( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size();
   vector words;

   findWords( words, dictionary, length );

   //---
   // 找到與 wordToCheck 只相差一个字符的單詞
   for (int v=0; v < words.size(); v++)
   {
       size_t diffCount = 0; // 不同字符計數器
       
       for (size_t i = 0; i < length; i++) // 檢查當前單詞與 wordToCheck 的每个字符是否相同
       {
           if (wordToCheck[i] != words[v][i])
               diffCount++;
           
           if (diffCount > 1) // 如果不同字符數超过一个，則跳出循環
               break;
       }
       
       if (diffCount == 1) // 如果只相差一个字符，將該單詞添加到 legalWords
       {
           legalWords.push_back(words[v]);
           cout << "1";
       }
   }
}

// Find every word w in the vector "dictionary" which satisfies two conditions:
// 1. the length of w is one greater than the length of wordToCheck, and
// 2. wordToCheck is equal to the substring obtained by deleting a character from w.
// Put these words into the vector "legalWords".
void SpellCheck::shorter( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() + 1;
   vector words;

   findWords( words, dictionary, length );

   //---
   for (int v = 0; v < words.size(); v++)
   {
       string word = words[v];

       for (int i = 0;i < length;i++)
       {
           word.erase(i,1);
           if(word == wordToCheck)
           {
               legalWords.push_back(words[v]);
               break;
           }

           word = words[v];
       }
   }
}

// Find every word w in the vector "dictionary" which satisfies two conditions:
// 1. the length of w is one less than the length of wordToCheck, and
// 2. w is equal to the substring obtained by deleting a character from wordToCheck.
// Put these words into the vector "legalWords".
void SpellCheck::longer( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() - 1;
   vector words;

   findWords( words, dictionary, length );

   //---
   for (int v = 0; v < words.size(); v++)
   {
       string wordtocheck = wordToCheck;

       for (int i = 0;i < wordToCheck.size();i++)
       {
           wordtocheck.erase(i, 1);
           if (wordtocheck == words[v])
           {
               legalWords.push_back(words[v]);
               break;
           }

           wordtocheck = wordToCheck;
       }
       /*size_t diffCount = 0;
       int i = 0;
       int k = 0;
       for (size_t j = 0; j < length; j++) 
       {
           if (wordToCheck[j] != words[v][i])
               diffCount++;
           i++;
        
           if (diffCount > 0) 
           {
               k = 1;
               break;
           }
       }
       diffCount = 0;
       int x = 0;
       for (size_t j = 1; j < length + 1; j++)
       {
           if (wordToCheck[j] != words[v][i])
               diffCount++;
           i++;

           if (diffCount > 0)
           {
               x = 1;
               break;
           }
       }

       if (k==0 && x==1 || k==1 && x==0) 
       {
           legalWords.push_back(words[v]);
           cout << "3";
       }*/
   }
}

// Find the words in the vector "dictionary" whose length is equal to "length",
// and put these words into the vector "words"
void SpellCheck::findWords( vector &words, const vector &dictionary, size_t length )
{
    //---
    words.clear(); // 清空目標單詞向量
    
    for (size_t i = 0; i < dictionary.size(); i++) // 找到長度为 length 的單詞並添加到目標向量中
    {
        if (dictionary[i].size() == length)
        {
            words.push_back(dictionary[i]);
        }
    }
}

const vector SpellCheck::getLegalWords() const
{
   return legalWords;
}

void SpellCheck::output()
{
   cout << legalWords[ 0 ].c_str();
   for( size_t i = 1; i < legalWords.size(); i++ )
      cout << ", " << legalWords[ i ].c_str();
   cout << endl << endl;
}