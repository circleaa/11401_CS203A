#include <iostream>
using namespace std;

int main()
{
   int number;

   cout << "Enter a positive integer: ";
   cin >> number;
   if (number % 2 == 1)
	   cout << "The integer " << number << " is odd.";
   else
	   cout << "The integer " << number << " is even.";
}