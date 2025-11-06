#include <iostream>
using namespace std;

int main()
{
   int number;
   cout << "Enter a five-digit positive integer: ";
   cin >> number;
   
   cout << number / 10000 << "   ";
   cout << (number % 10000) / 1000 << "   ";
   cout << (number % 1000) / 100 << "   ";
   cout << (number % 100) / 10 << "   ";
   number = number%10;
   cout << number << endl;
}