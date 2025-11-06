#include <iostream>
using namespace std; 

int main()
{
   int side1;
   int side2;
   int side3;

   cout << "Enter side 1: ";
   cin >> side1;

   cout << "Enter side 2: ";
   cin >> side2;

   cout << "Enter side 3: ";
   cin >> side3;
      
   if (side1* side1 + side2 * side2 == side3 * side3 || side1 * side1 + side3 * side3 == side2 * side2 || side2 * side2 + side3 * side3 == side1 * side1)
       cout << "These are the sides of a right triangle.";
   else
       cout << "These do not form a right triangle.";
}