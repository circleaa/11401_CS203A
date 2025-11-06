#include <iostream>
using std::cout;
using std::exit;

#include "string 2-3.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const size_type count, const char ch ) // fill constructor
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

// Appends character ch to the end of the string, increasing its length by one.
void string::push_back( const char ch ) // insert element at end
{
   if( mySize == myRes )
   {
      size_type newMyRes = myRes * 3 / 2;
      if( newMyRes < ( ( mySize + 1 ) / 16 ) * 16 + 15 )
         newMyRes = ( ( mySize + 1 ) / 16 ) * 16 + 15;

      //---
      value_type* newPtr = new value_type[newMyRes + 1]; // 分配新的內存
      
      for (size_type i = 0; i < mySize; ++i) // 複製舊的內容到新的內存
          newPtr[i] = myPtr()[i];
      
      if (myRes > 15) // 釋放舊的內存
          delete[] bx.ptr;
      
      // 更新指針和容量
      bx.ptr = newPtr;
      myRes = newMyRes;
   }

   myPtr()[mySize] = ch; // 將新的字符添加到字符串尾部
   ++mySize;
   
   myPtr()[mySize] = '\0'; // 添加結尾空字符
}

// Erases the last character of the string,
// effectively reducing its length by one.
void string::pop_back()
{
   if( mySize > 0 )
      --mySize;
   myPtr()[ mySize ] = '\0';
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