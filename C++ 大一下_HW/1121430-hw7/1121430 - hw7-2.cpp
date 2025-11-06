#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <string>
using std::string;

// list standard header
#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
   using nodePtr = ListNode *;

   nodePtr next; // successor node, or first element if head
   nodePtr prev; // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
      mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = node *;
   using const_iterator = const node *;

   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      //---
      for (size_type i = 0; i < count; ++i)
      {
          nodePtr newNode = new node;
          newNode->myVal = Ty(); //初始化=0

          newNode->next = myData.myHead;
          newNode->prev = myData.myHead->prev;
          myData.myHead->prev->next = newNode;
          myData.myHead->prev = newNode;
      }

      myData.mySize = count;
   }

   list( const list &right )
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      //---
      for (nodePtr it = right.myData.myHead->next; it != right.myData.myHead; it = it->next)
      {
          nodePtr newNode = new node;
          newNode->myVal = it->myVal;

          newNode->next = myData.myHead;
          newNode->prev = myData.myHead->prev;
          myData.myHead->prev->next = newNode;
          myData.myHead->prev = newNode;

          myData.mySize++;
      }
   }

   ~list()
   {
      clear();
      delete myData.myHead;
   }

   list& operator=( const list &right )
   {
      if( this != &right )
      {
         if( right.myData.mySize == 0 ) // the right list is empty
         {
            if( myData.mySize != 0 ) // the left list is not empty
               clear();
         }
         else // the right list is not empty
         {
             //---
             nodePtr myPtr = myData.myHead->next;
             nodePtr rightPtr = right.myData.myHead->next;

             if (right.myData.mySize >= myData.mySize)
             {
                 nodePtr it = rightPtr;
                 //先把rightPtr的值複製到myPtr
                 for (myPtr; myPtr != myData.myHead; myPtr = myPtr->next, rightPtr = rightPtr->next)
                 {
                     myPtr->myVal = rightPtr->myVal;
                     it = rightPtr->next;
                 }
                 //新增newNode讓myData.mySize==right.myData.mySize
                 //並把rightPtr的值複製到myPtr
                 for (it; it != right.myData.myHead; it = it->next)
                 {
                     nodePtr newNode = new node;
                     newNode->myVal = it->myVal;

                     newNode->next = myData.myHead;
                     newNode->prev = myData.myHead->prev;
                     myData.myHead->prev->next = newNode;
                     myData.myHead->prev = newNode;

                     ++myData.mySize;
                 }
             }
             else if (right.myData.mySize < myData.mySize)
             {
                 //把值複製過去
                 for (rightPtr; rightPtr != right.myData.myHead; rightPtr = rightPtr->next, myPtr = myPtr->next)
                     myPtr->myVal = rightPtr->myVal;

                 //刪除多餘元素
                 size_type diff = myData.mySize - right.myData.mySize;
                 for (size_type i = 0; i < diff; ++i)
                 {
                     nodePtr lastNode = myData.myHead->prev;
                     lastNode->prev->next = myData.myHead;
                     myData.myHead->prev = lastNode->prev;
                     delete lastNode;
                 }
             }
             myData.mySize = right.myData.mySize;
         }
      }

      return *this;
   }

   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   iterator end()
   {
      return iterator( myData.myHead );
   }

   void resize( size_type newSize )
   {
      if( myData.mySize != newSize )
      {
          //---
          if (newSize < myData.mySize)
          {
              // 删除多餘的元素
              size_type diff = myData.mySize - newSize;
              for (size_type i = 0; i < diff; ++i)
              {
                  nodePtr lastNode = myData.myHead->prev;
                  lastNode->prev->next = myData.myHead;
                  myData.myHead->prev = lastNode->prev;
                  delete lastNode;
              }
              myData.mySize = newSize;
          }
          else
          {
              // 添加新元素並初始化為 0
              size_type diff = newSize - myData.mySize;
              for (size_type i = 0; i < diff; ++i)
              {
                  nodePtr newNode = new node;
                  newNode->myVal = Ty();

                  newNode->next = myData.myHead;
                  newNode->prev = myData.myHead->prev;
                  myData.myHead->prev->next = newNode;
                  myData.myHead->prev = newNode;
              }
              myData.mySize = newSize;
          }
      }
   }

   size_type size() const
   {
      return myData.mySize;
   }

   bool empty() const
   {
      return myData.mySize == 0;
   }

   reference front()
   {
      return myData.myHead->next->myVal;
   }

   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   void push_back( const Ty &val )
   {
       //---
       nodePtr newNode = new node;
       newNode->myVal = val;

       newNode->next = myData.myHead;
       newNode->prev = myData.myHead->prev;
       myData.myHead->prev->next = newNode;
       myData.myHead->prev = newNode;

       ++myData.mySize;
   }

   void pop_back()
   {
      if( myData.mySize > 0 )
      {
          //---
          nodePtr lastNode = myData.myHead->prev;
          myData.myHead->prev = lastNode->prev;
          lastNode->prev->next = myData.myHead;

          delete lastNode;
          --myData.mySize;
      }
   }

   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
         while( myData.myHead->next != myData.myHead )
         {
            myData.myHead->next = myData.myHead->next->next;
            delete myData.myHead->next->prev;
         }

         myData.myHead->prev = myData.myHead;
         myData.mySize = 0;
      }
   }

private:
   ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( list< Ty > &left, list< Ty > &right )
{
   if( left.size() != right.size() )
      return false; // vectors of different number of elements

   typename list< Ty >::iterator it1 = left.begin();
   typename list< Ty >::iterator it2 = right.begin();
   for( ; it1 != left.end(); it1 = it1->next, it2 = it2->next )
      if( it1->myVal != it2->myVal )
         return false; // vector contents are not equal

   return true; // vector contents are equal
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( list< Ty > &left, list< Ty > &right )
{
   return !( left == right );
}

#endif // LIST


// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;

   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   HugeInteger( string str );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   bool operator==( HugeInteger &right ); // less than or equal to

   bool operator<( HugeInteger &right );  // less than

   bool operator<=( HugeInteger &right ); // less than or equal to

   HugeInteger square( value_type powerTwo ); // the square of HugeInteger
   HugeInteger squareRoot( value_type powerTwo ); // the square root of HugeInteger

   bool isZero();           // return true if and only if all digits are zero
private:
   T integer;
}; // end class HugeInteger

#endif

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
}

template< typename T >
HugeInteger< T >::HugeInteger( string str )
{
   value_type digits[ 1001 ] = {};
   size_type last = str.size() - 1;
   for( size_type i = 0; i <= last; ++i )
      digits[ i ] = static_cast< value_type >( str[ last - i ] ) - '0';

   size_type numDigits = sizeof( value_type ) - 1;
   for( size_type i = 0; i <= last; i += numDigits )
   {
      value_type bigDigit = digits[ i ] + digits[ i + 1 ] * 10 + digits[ i + 2 ] * 100;
      if( sizeof( value_type ) == 8 )
         bigDigit += digits[ i + 3 ] * 1000 +
         digits[ i + 4 ] * 10000 +
         digits[ i + 5 ] * 100000 +
         digits[ i + 6 ] * 1000000;

      integer.push_back( bigDigit );
   }
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( HugeInteger &right )
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger &right )
{
    //---
    if (integer.size() < right.integer.size())
        return true;
    if (integer.size() > right.integer.size())
        return false;

    typename T::iterator it1 = integer.end();
    typename T::iterator it2 = right.integer.end();

    //integer.size() = right.integer.size() 
    while (it1 != integer.begin() && it2 != right.integer.begin())
    {
        it1= it1->prev;
        it2= it2->prev;

        if (it1->myVal < it2->myVal)
            return true;

        else if (it1->myVal > it2->myVal)
            return false;
    }
    return false;

} // end function operator<

// function that tests if one HugeInteger is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger &right )
{
   return ( *this == right || *this < right );
}

template< typename T >
HugeInteger< T > HugeInteger< T >::square( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_t squareSize = 2 * integer.size();
   HugeInteger square( squareSize );

   //---
   // 初始化 square 的元素為 0
   for (typename T::iterator it = square.integer.begin(); it != square.integer.end(); it=it->next)
       it->myVal = 0;

   typename T::iterator it3 = square.integer.begin();
   typename T::iterator temp = it3;
   for (typename T::iterator it1 = integer.begin(); it1 != integer.end(); it1=it1->next)
   {     
       it3 = temp;
       for (typename T::iterator it2 = integer.begin(); it2 != integer.end(); it2=it2->next)
       {
           value_type product = (it1->myVal) * (it2->myVal);
     
           // 按照 product 的位數加到對應位置
           //typename T::iterator it3 = square.integer.begin() + (it1 - integer.begin()) + (it2 - integer.begin());                        
           (it3->myVal) += product;
           it3 = it3->next;
           
       }
       temp = temp->next;    
   }

   // 進位
   for (typename T::iterator it = square.integer.begin(); it != square.integer.end() -> prev; it=it->next)
   {
       if (it->myVal >= powerTwo)
       {
           (it->next)->myVal += (it->myVal) / powerTwo;
           (it->myVal) %= powerTwo;
       }
   }

   // 删除多餘的 0
   while (!square.integer.empty() && square.integer.back() == 0)
       square.integer.pop_back();
 
   return square;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_type sqrtSize = ( integer.size() + 1 ) / 2;
   HugeInteger sqrt( sqrtSize );
   HugeInteger sq;

   //---
   for (typename T::iterator it = sqrt.integer.end()->prev; it != sqrt.integer.begin()->prev; it = it->prev)
   {
       int high = powerTwo-1;
       int low = 0;
       while (low <= high)
       {      
           it->myVal = (low + high) / 2;
           sq = sqrt.square(powerTwo);

           if (sq == *this)
               return sqrt;

           else if (sq < *this)
               low = it->myVal + 1;

           else
               high = it->myVal - 1;
       }
       if (*this < sq)
           (it->myVal)--;
   }

   return sqrt;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   typename T::iterator it = integer.begin();
   for( ; it != integer.end(); it = it->next )
      if( it->myVal != 0 )
         return false;

   return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::value_type numDigits = sizeof( typename T::value_type ) - 1;
   typename T::iterator it = hugeInteger.integer.end()->prev;
   output << it->myVal;
   for( it = it->prev; it != hugeInteger.integer.begin()->prev; it = it->prev )
      output << setw( numDigits ) << setfill( '0' ) << it->myVal;

   return output; // enables cout << x << y;
}


template< typename T >
void solution()
{
   T powerTwo = 1000;
   if( sizeof( T ) == 8 )
      powerTwo = 10000000;

   int numCases;
   cin >> numCases;
   for( int i = 1; i <= numCases; ++i )
   {
      string str;
      cin >> str;

      HugeInteger< list< T > > hugeInteger( str );

      cout << hugeInteger.squareRoot( powerTwo ) << endl;

      if( i < numCases )
         cout << endl;
   }
}

int main()
{
   // execute the following 4 instructions one by one, each of them should get an AC
   solution< long int >();
 //  solution< unsigned long int >();
 //  solution< long long int >();
 //  solution< unsigned long long int >();
}