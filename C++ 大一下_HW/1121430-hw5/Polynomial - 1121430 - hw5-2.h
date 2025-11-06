#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
using std::sqrt;

#include "vector - Student ID - hw5.h"

// Polynomial class template definition
template< typename T1, typename T2 >
class Polynomial
{
   // Overloaded stream insertion operator
   template< typename T1, typename T2 >
   friend ostream &operator<<( ostream &output, Polynomial< T1, T2 > a );
public:

   // Constructs an empty polynomial, with no terms.
   Polynomial( size_t n = 0 )
      : polynomial( n )
   {
   }

   // Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
   Polynomial( const Polynomial &right )
      : polynomial( right.polynomial )
   {
   }

   // Destructor with empty body
   ~Polynomial()
   {
   }

   // Copies all the terms from "right" into the polynomial
   const Polynomial operator=( const Polynomial &right )
   {
      if( &right != this ) // avoid self-assignment
         polynomial = right.polynomial;

      return *this; // enables x = y = z, for example
   }

   bool operator==( const Polynomial &right )
   {
      return polynomial == right.polynomial;
   }

   void setPolynomial( T2 coefficient[], T2 exponent[], int numTerms )
   {
      for( int i = 0; i < numTerms; i++ )
      {
         polynomial[ i ].coef = coefficient[ i ];
         polynomial[ i ].expon = exponent[ i ];
      }
   }

   // addition assignment operator; Polynomial += Polynomial
   void operator+=( Polynomial &op2 )
   {
      Polynomial sum;

      //---
      size_t i = 0, j = 0;

      while (i < polynomial.size() && j < op2.polynomial.size())
      {
          if (polynomial[i].expon > op2.polynomial[j].expon)
          {
              sum.polynomial.push_back(polynomial[i]);
              i++;
          }
          else if (polynomial[i].expon < op2.polynomial[j].expon)
          {
              sum.polynomial.push_back(op2.polynomial[j]);
              j++;
          }
          else //次方相等
          {
              if (polynomial[i].coef + op2.polynomial[j].coef != 0)
              {
                  Term<T2> term;
                  term.coef = polynomial[i].coef + op2.polynomial[j].coef;
                  term.expon = polynomial[i].expon;
                  sum.polynomial.push_back(term);
              }
              i++;
              j++;
          }
      }

      while (i < polynomial.size())
      {
          sum.polynomial.push_back(polynomial[i]);
          i++;
      }

      while (j < op2.polynomial.size())
      {
          sum.polynomial.push_back(op2.polynomial[j]);
          j++;
      }

      polynomial = sum.polynomial;

      *this = sum;
   }

   // subtraction assignment operator; Polynomial -= Polynomial
   void operator-=( Polynomial &op2 )
   {
      Polynomial minus = -op2;
      *this += minus;
   }

   // multiplication operator; Polynomial * Polynomial
   Polynomial operator*( Polynomial &op2 )
   {
      Polynomial product;

      //---
      Polynomial buffer(op2.polynomial.size());

      for (int i = 0;i < polynomial.size();i++)
      {
          for (int j = 0;j < op2.polynomial.size();j++)
          {
              // buffer = op2 * 當前物件
              buffer.polynomial[j].coef = op2.polynomial[j].coef * polynomial[i].coef;
              buffer.polynomial[j].expon = op2.polynomial[j].expon + polynomial[i].expon;
          }

          product.operator+=(buffer); // product += buffer
      }

      return product;
   }

   // computes the square root of the current polynomial
   Polynomial compSquareRoot()
   {
      Polynomial monomial( 1 );
      Polynomial squareRoot;
      Polynomial divisor;
      Polynomial buffer;
      Polynomial remainder( *this );

      //---
      int i = 0;
      //第一次
      {
          //monomial = (remainder首項) 開根號
          monomial.polynomial[0].expon = remainder.polynomial.front().expon / 2;
          monomial.polynomial[0].coef = sqrt(remainder.polynomial.front().coef);

          squareRoot.operator+=(monomial); //將 monomial copy 到 squareRoot    

          divisor.operator+=(monomial); //將 monomial copy 到 divisor

          buffer.operator=(divisor.operator*(monomial)); //buffer= monomial*divisor
          remainder.operator-=(buffer); //remainder-= buffer

          divisor.polynomial[i].coef *= 2; //divisor 當前項(i)*2
          i++;
      }

      while (!remainder.zero())
      {
          //monomial = (remainder首項) / (divisor首項)
          monomial.polynomial[0].expon = remainder.polynomial.front().expon - divisor.polynomial.front().expon;
          monomial.polynomial[0].coef = remainder.polynomial.front().coef / divisor.polynomial.front().coef;

          squareRoot.operator+=(monomial); //將 monomial copy 到 squareRoot

          divisor.operator+=(monomial); //將 monomial copy 到 divisor        

          buffer.operator=(divisor.operator*(monomial)); //buffer= monomial*divisor
          remainder.operator-=(buffer); //remainder-= buffer      
          if (remainder.zero())
              break;

          divisor.polynomial[i].coef *= 2; //divisor 當前項(i)*2
          i++;
      }

      return squareRoot;
   }

private:
   T1 polynomial; // a polynomial

   // Attaches a new term to the polynomial
   void attach( T2 coefficient, T2 exponent )
   {
      Term< T2 > tempTerm( coefficient, exponent );
      polynomial.push_back( tempTerm );
   }

   // Returns the minus of the current polynomial
   Polynomial operator-()
   {
      Polynomial minus( polynomial.size() );
      typename T1::iterator it2 = minus.polynomial.begin();
      typename T1::iterator it1 = polynomial.begin();
      for( ; it1 != polynomial.end(); ++it1, ++it2 )
      {
         it2->coef = -it1->coef;
         it2->expon = it1->expon;
      }

      return minus;
   }

   // Returns true if and only if polynomial is a zero polynomial
   bool zero() const
   {
      return polynomial.empty();
   }

   // Returns the highest of degrees of polynomial's terms
   int degree() const
   {
      if( polynomial.empty() )
         return 0;
      else
         return polynomial.begin()->expon;
   }

}; // end class template Polynomial

// Overloaded stream insertion operator
template< typename T1, typename T2 >
ostream& operator<<( ostream &output, Polynomial< T1, T2 > a )
{
   if( a.zero() )
   {
      output << 0 << endl;
      return output;
   }

   typename T1::iterator it = a.polynomial.begin();

   if( it->coef < 0 )
      cout << "-" << -it->coef;
   else if( it->coef > 0 )
      cout << it->coef;

   if( it->expon > 0 )
   {
      if( it->expon == 1 )
         cout << "x";
      else
         cout << "x^" << it->expon;
   }

   for( ++it; it != a.polynomial.end(); ++it )
   {
      if( it->coef < 0 )
         cout << " - " << -it->coef;
      else if( it->coef > 0 )
         cout << " + " << it->coef;

      if( it->expon > 0 )
      {
         if( it->expon == 1 )
            cout << "x";
         else
            cout << "x^" << it->expon;
      }
   }

   return output; // enables cout << x << y;
} // end function operator<<

#endif