#include <iostream>
using std::cout;
using std::exit;

#include "string 2-2.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const size_type count, const char ch )  // fill constructor
   : bx(),            // Fills the string with "count" consecutive copies of character ch.
     mySize( 0 ),
     myRes( 15 )
{
   // construct from count * ch
   mySize = count;
   myRes = ( mySize / 16 ) * 16 + 15;

   //---
   if (myRes >= 16)
       bx.ptr = new value_type[myRes + 1];
   for (size_type i = 0; i < mySize; ++i) // 複製 right 字符串的內容到當前字符串
       myPtr()[i] = ch;
   myPtr()[mySize] = '\0'; // 添加結尾空字符
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

string& string::assign( const string &right ) // assign constructor
{
   if( this != &right )
   {
      if( right.mySize > myRes )
      {
         if( myRes > 15 )
            delete[] bx.ptr;

         myRes = myRes * 3 / 2;
         if( myRes < ( right.mySize / 16 ) * 16 + 15 )
            myRes = ( right.mySize / 16 ) * 16 + 15;

         bx.ptr = new value_type[myRes + 1];  //---動態陣列
      }

      //---
      for (size_type i = 0; i < right.mySize; ++i) // 複製 right 字符串的內容到當前字符串
          myPtr()[i] = right.myPtr()[i];

      mySize = right.mySize; // 更新當前字符串的大小

      myPtr()[mySize] = '\0';  // 添加結尾空字符
   }

   return *this;
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return myPtr();
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

string::iterator string::end()
{
   return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::at( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::const_reference string::at( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}