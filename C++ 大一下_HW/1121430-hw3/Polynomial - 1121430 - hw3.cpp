#include <iostream>
using std::cout;
using std::endl;

#include "Polynomial.h" // include definition of class Polynomial

Polynomial::Polynomial( size_t n )
   : polynomial( n )
{
}

Polynomial::Polynomial( size_t n, int coefficient[], int exponent[] )
   : polynomial( n )
{
   for( size_t i = 0; i < n; i++ )
   {
      polynomial.at( i ).coef = coefficient[ i ];
      polynomial.at( i ).expon = exponent[ i ];
   }
}

Polynomial::Polynomial( const Polynomial &right )
   : polynomial( right.polynomial )
{
}

Polynomial::~Polynomial()
{
}

const Polynomial Polynomial::assign( const Polynomial &right )
{
   if( &right != this ) // avoid self-assignment
      polynomial.assign( right.polynomial );

   return *this; // enables x = y = z, for example
}

bool Polynomial::equal( const Polynomial &right ) const
{
   return polynomial.equal( right.polynomial );
}

void Polynomial::addition( const Polynomial &adder )
{
   Polynomial sum( polynomial.size() + adder.polynomial.size() );
   size_t i = 0;
   size_t j = 0;
   size_t k = 0;
   
   while (i < polynomial.size() && j < adder.polynomial.size())
   {
       if (polynomial.at(i).expon > adder.polynomial.at(j).expon) //比次方大小
       {
           sum.polynomial.at(k) = polynomial.at(i);
           i++;
       }
       else if (polynomial.at(i).expon < adder.polynomial.at(j).expon)
       {
           sum.polynomial.at(k) = adder.polynomial.at(j);
           j++;
       }
       else //次方相等
       {
           sum.polynomial.at(k).expon = polynomial.at(i).expon;
           sum.polynomial.at(k).coef = polynomial.at(i).coef + adder.polynomial.at(j).coef;
           i++;j++;
       }
       
       if (sum.polynomial.at(k).coef != 0) //如其中一項係數為0，則k不變
           k++;
   }
   // Add remaining terms from the larger polynomial 
   while (i < polynomial.size())
   {
       sum.polynomial.at(k) = polynomial.at(i);
       i++;
       k++;
   }
   while (j < adder.polynomial.size())
   {
       sum.polynomial.at(k) = adder.polynomial.at(j);
       j++;
       k++;
   }

   if( sum.polynomial.size() != k )
      sum.polynomial.resize( k );

   polynomial.assign( sum.polynomial );

   if( !zero() && hasZeroTerm() )
      cout << "addend has a zero term!\n";
}

void Polynomial::subtraction( const Polynomial &subtrahend )
{
   Polynomial buffer( subtrahend.minus() );

   addition( buffer ); // minuend = minuend + buffer = minuend - subtrahend

   if( !zero() && hasZeroTerm() )
      cout << "minuend has a zero term!\n";
}

Polynomial Polynomial::multiplication( const Polynomial &multiplier ) const
{
   Polynomial product;
   //---
   Polynomial buffer(multiplier.polynomial.size());

   for (int i = 0;i < polynomial.size();i++)
   {
       for (int j = 0;j < multiplier.polynomial.size();j++)
       {
           // buffer = multiplier * 當前物件
           buffer.polynomial.at(j).coef = multiplier.polynomial.at(j).coef * polynomial.at(i).coef;
           buffer.polynomial.at(j).expon = multiplier.polynomial.at(j).expon + polynomial.at(i).expon;
       }

       if (product.polynomial.empty())
           product.assign(buffer);
       else
           product.addition(buffer); // product += buffer
   }

   if( !product.zero() && product.hasZeroTerm() )
      cout << "product has a zero term!\n";

   return product;
}

Polynomial Polynomial::division( const Polynomial &divisor ) const
{
    //---
    Polynomial quotient;
    Polynomial remainder(*this); //將當前對象(正在操作的多項式)的內容copy到remainder中
    Polynomial monomial(1); //只有一項
    Polynomial buffer(divisor.polynomial.size());
    
    while (remainder.degree() >= divisor.degree())
    {
        // monomial = remainder最高項 / divisor最高項
        monomial.polynomial.at(0).expon = remainder.degree() - divisor.degree();
        monomial.polynomial.at(0).coef = remainder.leadingCoef() / divisor.leadingCoef();

        quotient.polynomial.push_back(monomial.polynomial.at(0)); //把 monomial 的值copy到 quotient   
        
        buffer.assign(divisor.multiplication(monomial)); //buffer = divisor * monomial      
        remainder.subtraction(buffer); // remainder-= buffer
        
        if (remainder.zero())
            break;
    }

   if( !quotient.zero() && quotient.hasZeroTerm() )
      cout << "quotient has a zero term!\n";

   return quotient;
}

Polynomial Polynomial::modulus( const Polynomial &divisor ) const
{
    //---
    Polynomial remainder(*this);
    Polynomial monomial(1);
    Polynomial buffer(divisor.polynomial.size());
    
    while (remainder.degree() >= divisor.degree())
    {     
        monomial.polynomial.at(0).expon = remainder.degree() - divisor.degree();
        monomial.polynomial.at(0).coef = remainder.leadingCoef() / divisor.leadingCoef();
        
        buffer.assign(divisor.multiplication(monomial));
        remainder.subtraction(buffer);
        
        if (remainder.zero())
            break;
    }

   if( !remainder.zero() && remainder.hasZeroTerm() )
      cout << "remainder has a zero term!\n";

   return remainder;
}

void Polynomial::output() const
{
   // the current polynomial is zero polynomial
   if( zero() )
      cout << 0;
   else
   {
      if( leadingCoef() < 0 )
         cout << "-" << -leadingCoef();
      else if( leadingCoef() > 0 )
         cout << leadingCoef();

      if( degree() > 0 )
      {
         if( degree() == 1 )
            cout << "x";
         else
            cout << "x^" << degree();
      }

      for( size_t i = 1; i < polynomial.size(); i++ )
      {
         if( polynomial.at( i ).coef < 0 )
            cout << " - " << -polynomial.at( i ).coef;
         else if( polynomial.at( i ).coef > 0 )
            cout << " + " << polynomial.at( i ).coef;

         if( polynomial.at( i ).expon > 0 )
         {
            if( polynomial.at( i ).expon == 1 )
               cout << "x";
            else
               cout << "x^" << polynomial.at( i ).expon;
         }
      }
   }

   cout << endl;
}

bool Polynomial::hasZeroTerm() const
{
   if( !zero() )
      for( size_t i = 0; i < polynomial.size(); i++ )
         if( polynomial.at( i ).coef == 0 )
            return true;

   return false;
}

Polynomial Polynomial::minus() const
{
   Polynomial minus( polynomial.size() );
   for( size_t i = 0; i < minus.polynomial.size(); i++ )
   {
      minus.polynomial.at( i ).coef = -polynomial.at( i ).coef;
      minus.polynomial.at( i ).expon = polynomial.at( i ).expon;
   }

   return minus;
}

bool Polynomial::zero() const
{
   return polynomial.empty();
}

int Polynomial::degree() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().expon;
}

int Polynomial::leadingCoef() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().coef;
}