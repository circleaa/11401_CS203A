#include<iostream>
using std::cin;
using std::cout;
using std::endl;

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// --hugeInt
void decrement( int hugeInt[], int &size );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize );

// multiplicand *= multiplier
void multiplication( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int hugeInt[], int &size );

const int twoHundred = 200;
const int hundred = 100;

int main()
{
   int t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         int dividend[ twoHundred ] = {};
         int divisor[ hundred ] = {};
         int quotient[ hundred ] = {};
         int remainder[ hundred ] = {};

         int dividendSize = 1;
         int divisorSize = 1;
         int quotientSize = 1;
         int remainderSize = 1;

         // put all digits of t into base
         int base[ twoHundred ] = {};
         int baseSize = 0;
         for( int i = t; i > 0; i /= 10 )
            base[ baseSize++ ] = i % 10;

         // dividend = pow( t, a )
         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiplication( dividend, base, dividendSize, baseSize );
            if( dividendSize > twoHundred - baseSize )
               break;
         }

         if( dividendSize > twoHundred - baseSize )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
            {
               multiplication( divisor, base, divisorSize, baseSize );
               if( divisorSize > hundred - baseSize )
                  break;
            }

            if( divisorSize > hundred - baseSize )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               decrement( dividend, dividendSize ); // --dividend
               decrement( divisor, divisorSize );   // --divisor

               division( dividend, divisor, quotient, remainder,
                  dividendSize, divisorSize, quotientSize, remainderSize );

               // quotient is an integer with less than 100 digits
               if( quotientSize < 100 && isZero( remainder, remainderSize ) )
                  for( int i = quotientSize - 1; i >= 0; i-- )
                     cout << quotient[ i ];
               else
                  cout << "is not an integer with less than 100 digits.";
               cout << endl;
            }
         }
      }
   }
}

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size )
{
   for( int i = 0; i < size; i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
    if (size1 < size2)
        return true;
    else if (size1 > size2)
        return false;
    for (int i = size1 - 1; i >= 0; i--)
    {
        if (hugeInt1[i] < hugeInt2[i])
            return true;
        else if (hugeInt1[i] > hugeInt2[i])
            return false;
    }
    return false;
}

// --hugeInt
void decrement( int hugeInt[], int &size )
{
    for (int i = 0; i < size; i++)
    {
        if (hugeInt[i] != 0)
        {
            hugeInt[i]--;
            break;
        }
        else
            hugeInt[i] = 9;
    }
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize )
{
    int difference[200] = {0};
    int differenceSize= minuendSize;
    for (int i = subtrahendSize; i < minuendSize; i++)
        subtrahend[i] = 0;

    for (int i = 0; i < minuendSize; i++)
        difference[i] = minuend[i] - subtrahend[i];
    for (int i = 0; i < differenceSize; i++)
    {
        if (difference[i] < 0)
        {
            difference[i] += 10;
            difference[i + 1] -= 1;
        }
    }

    for (int i = minuendSize - 1; i >= 0; i--)
    {
        if (difference[i] != 0)
            break;
        else
            differenceSize--;
    }
    minuendSize = differenceSize;
    for (int i = 0;i < differenceSize;i++)
        minuend[i] = difference[i];
    return;
}

// multiplicand *= multiplier
void multiplication( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize )
{
    int product[200] = {0};
    int productSize = multiplicandSize+ multiplierSize;
   
    for (int i = 0; i < multiplicandSize; i++)
    {
        for (int j = 0; j < multiplierSize; j++)
            product[i + j] += multiplicand[i] * multiplier[j];
    }
    for (int i = 0; i < productSize; i++)
    {
        if (product[i] >= 10)
        {
            product[i + 1] += product[i] / 10;
            product[i] %= 10;
        }
    }
    while (product[productSize - 1] == 0)
        productSize--;
    
    multiplicandSize = productSize;
    for (int i = 0; i < productSize; i++)
        multiplicand[i] = product[i]; 
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int dividend[], int divisor[], int quotient[], int remainder[],
    int dividendSize, int divisorSize, int& quotientSize, int& remainderSize)
{
    int buffer[200] = { 0 };
    int bufferSize;
    int n = dividendSize - divisorSize;
    quotientSize = dividendSize - divisorSize;

    for (int i = 0; i < dividendSize; i++)
        remainder[i] = dividend[i];
    remainderSize = dividendSize;

    //shifts left n 
    for (int i = divisorSize - 1; i >= 0; i--)
        buffer[i+n] = divisor[i];
    bufferSize = dividendSize;

    if (less(remainder, buffer, remainderSize, bufferSize))
        divideBy10(buffer, bufferSize);
    else
        quotientSize++;

    for (int k = quotientSize - 1; k >= 0; k--)
    {
        quotient[k]=0;
        while (!less(remainder, buffer, remainderSize, bufferSize))
        {
            subtraction(remainder, buffer, remainderSize, bufferSize);
            quotient[k]++;
            if (isZero(remainder, remainderSize))
                return;
        }
        divideBy10(buffer, bufferSize);
    }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int hugeInt[], int &size )
{
   if( size == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];

      size--;
      hugeInt[ size ] = 0;
   }
}