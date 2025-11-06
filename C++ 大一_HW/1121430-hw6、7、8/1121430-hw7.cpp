// Compute the square root of a huge integer.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstring>
#include <cmath>

struct HugeInt
{
   size_t size = 0;
   long long int *integer = nullptr;
};

// put the square root of hugeInt into the array squareRoot
HugeInt compSquareRoot( HugeInt &hugeInt );

// put the square of hugeInt into the array square
HugeInt compSquare( HugeInt &hugeInt );

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// if hugeInt1 < hugeInt2, return true; otherwise, return false
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 );

int main()
{
   int testCase;
   cin >> testCase;
   for( int i = 1; i <= testCase; i++ )
   {
      char str[ 1010 ] = {};
      cin >> str;

      size_t numDigits = strlen( str );
      if( numDigits < 10 )
         cout << sqrt( atoi( str ) ) << endl;
      else
      {
         int *digits = new int[ numDigits + 3 ]();
         for( size_t j = 0; j < numDigits; ++j )
            digits[ j ] = static_cast< int >( str[ numDigits - 1 - j ] ) - '0';

         size_t last = ( numDigits - 1 ) / 4;
         HugeInt hugeInt;
         hugeInt.size = last + 1;
         hugeInt.integer = new long long int[ hugeInt.size ](); // the square root of hugeInt
         for( size_t j = 0; j <= last; j++ )
            hugeInt.integer[ j ] = digits[ 4 * j ] +
                                  digits[ 4 * j + 1 ] * 10 +
                                  digits[ 4 * j + 2 ] * 100 +
                                  digits[ 4 * j + 3 ] * 1000;

         HugeInt squareRoot = compSquareRoot( hugeInt );

         cout << squareRoot.integer[ squareRoot.size - 1 ];
         for( int j = squareRoot.size - 2; j >= 0; j-- )
            cout << setw( 4 ) << setfill( '0' ) << squareRoot.integer[ j ];
         cout << endl;

         delete[] squareRoot.integer;
         delete[] hugeInt.integer;
         delete[] digits;
      }

      if( i < testCase )
         cout << endl;
   }
}

// put the square root of hugeInt into the array squareRoot
HugeInt compSquareRoot( HugeInt &hugeInt )
{
   HugeInt squareRoot;
   squareRoot.size = (hugeInt.size + 1) / 2;
   squareRoot.integer = new long long int[squareRoot.size]();
   HugeInt square;
   
   for (int i = squareRoot.size- 1;i >= 0;i--)
   {
       int high = 9999;
       int low = 0;
       while (low <= high)
       {
           squareRoot.integer[i] = (high + low) / 2;
           square = compSquare(squareRoot); //square=squareRoot*squareRoot,進位
           
           if (equal(square, hugeInt))//square=hugeInt
           {
               delete[] square.integer;
               return squareRoot;
           }
          
           else if (less(square, hugeInt))//hugeInt>square
               low = squareRoot.integer[i] + 1;
           else
               high = squareRoot.integer[i] - 1;
       }
       if (less(hugeInt, square))
           (squareRoot.integer[i])--;
   }

   delete[] square.integer;
   return squareRoot;
}

// put the square of hugeInt into the array square
HugeInt compSquare( HugeInt &hugeInt )
{
   HugeInt square;
   square.size = hugeInt.size*2;
   square.integer = new long long int[square.size]();
   
   for (int i = 0; i < square.size; i++)
       square.integer[i] = 0;
   for (int i = 0; i < hugeInt.size; i++)
   {
       for (int j = 0; j < hugeInt.size; j++)
           square.integer[i + j] += (hugeInt.integer[i] * hugeInt.integer[j]);
   }
   for (int i = 0; i < square.size - 1; i++)//進位
   {
       if (square.integer[i] >= 10000)
       {
           square.integer[i + 1] += (square.integer[i] / 10000);
           square.integer[i] %= 10000;
       }
   }
   if (square.integer[square.size - 1] == 0)
       square.size--;

   return square;
}

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
    if(hugeInt1.size != hugeInt2.size)
        return false;
    for (int i= hugeInt1.size-1;i>=0;i--)
    {
        if (hugeInt1.integer[i] != hugeInt2.integer[i])
            return false;
    }
    return true;

}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
    if (hugeInt1.size < hugeInt2.size)
        return true;
    if (hugeInt1.size > hugeInt2.size)
        return false;
    for(int i = hugeInt1.size - 1;i >= 0;i--)
    {
        if (hugeInt1.integer[i] < hugeInt2.integer[i])
            return true;
        if (hugeInt1.integer[i] > hugeInt2.integer[i])
            return false;
    }
    return false;
}