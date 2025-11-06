#include <iostream>
using namespace std; 

int main()
{
   int number;
   int a, b, c, d, e;
   cout << "Enter a 5-digit positive integer: ";
   cin >> number;
   a = number / 10000;
   b = (number % 10000) / 1000;
   c = (number % 1000) / 100;
   d = (number % 100) / 10;
   e = number % 10;
   if (a == e && b == d)
	   cout << number << " is a palindrome!!!";
   else
	   cout << number << " is not a palindrome.";

}