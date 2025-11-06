// Compute the square root of a huge integer.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <vector>
using std::vector;

#include <cstring>
#include <cmath>

// put the square root of hugeInt into the array squareRoot
vector< long long int > compSquareRoot( vector< long long int > &hugeInt );

// put the square of hugeInt into the array square
vector< long long int > compSquare( vector< long long int > &hugeInt );

bool equal( vector< long long int > &hugeInt1, vector< long long int > &hugeInt2 );

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( vector< long long int > &hugeInt1, vector< long long int > &hugeInt2 );

const int arraySize = 1010;

int main()
{
   int testCase;
   cin >> testCase;
   for( int i = 1; i <= testCase; i++ )
   {
      char str[ arraySize ] = {};
      cin >> str;

      size_t numDigits = strlen( str );
      if( numDigits < 10 )
         cout << sqrt( atoi( str ) ) << endl;
      else
      {
         vector< long long int > digits( numDigits + 3 );
         for( size_t j = 0; j < numDigits; ++j )
            digits[ j ] = static_cast< int >( str[ numDigits - 1 - j ] ) - '0';

         size_t last = ( numDigits - 1 ) / 4;
         vector< long long int > hugeInt( last + 1 );
         for( size_t j = 0; j <= last; j++ )
            hugeInt[ j ] = digits[ 4 * j ] +
                          digits[ 4 * j + 1 ] * 10 +
                          digits[ 4 * j + 2 ] * 100 +
                          digits[ 4 * j + 3 ] * 1000;

         // put the square root of hugeInt into the array squareRoot
         vector< long long int > squareRoot = compSquareRoot( hugeInt );

         cout << squareRoot[ squareRoot.size() - 1 ];
         for( int j = squareRoot.size() - 2; j >= 0; j-- )
            cout << setw( 4 ) << setfill( '0' ) << squareRoot[ j ];
         cout << endl;
      }

      if( i < testCase )
         cout << endl;
   }

   system( "pause" );
}

// put the square root of hugeInt into the array squareRoot
vector< long long int > compSquareRoot( vector< long long int > &hugeInt )
{
   size_t sqrtSize = ( hugeInt.size() + 1 ) / 2; // the number of digits of squareRoot is sqrtSize
   vector< long long int > squareRoot( sqrtSize ); // the square root of hugeInt
   vector< long long int > square;
 
   for (int i = sqrtSize - 1;i >= 0;i--)
   {
       int high = 9999;
       int low = 0;
       while (low <= high)
       {
           squareRoot[i] = (high + low) / 2;
           square = compSquare(squareRoot); //square=squareRoot*squareRoot,進位
          
           if (equal(square, hugeInt))//square=hugeInt
               return squareRoot;

           else if (less(square, hugeInt))//square<hugeInt
               low = squareRoot[i] + 1;
           else
               high = squareRoot[i] - 1;
       }
       if (less(hugeInt, square))
           (squareRoot[i])--;
   }
   return squareRoot;
}

// put the square of hugeInt into the array square
vector< long long int > compSquare( vector< long long int > &hugeInt )
{
   size_t hugeIntSize = hugeInt.size();
   size_t squareSize = 2 * hugeIntSize;
   vector< long long int > square( squareSize );

   for (int i = 0; i < squareSize; i++)
       square[i] = 0;
   for (size_t i = 0; i < hugeInt.size(); i++)
   {
       for (size_t j = 0; j < hugeInt.size(); j++)
           square[i + j] += (hugeInt[i] * hugeInt[j]);
   }
   for (size_t i = 0; i < squareSize - 1; i++)//進位
   {
       if (square[i] >= 10000)
       {
           square[i + 1] += (square[i] / 10000);
           square[i] %= 10000;
       }
   }
   if (square[squareSize - 1] == 0)
       square.pop_back();

   return square;
}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool equal( vector< long long int > &hugeInt1, vector< long long int > &hugeInt2 )
{
    if (hugeInt1 == hugeInt2)
        return true;
    else
        return false;
}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( vector< long long int > &hugeInt1, vector< long long int > &hugeInt2 )
{
    if (hugeInt1.size() < hugeInt2.size())
        return true;
    if (hugeInt1.size() > hugeInt2.size())
        return false;
    for (int i = hugeInt1.size() - 1;i >= 0;i--)
    {
        if (hugeInt1[i] < hugeInt2[i])
            return true;
        if (hugeInt1[i] > hugeInt2[i])
            return false;
    }
    return false;
}