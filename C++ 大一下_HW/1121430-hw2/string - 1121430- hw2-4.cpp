#include <iostream>
using std::cout;
using std::exit;

//#include <algorithm>
//using std::max;

#include "string 2-4.h" // include definition of class String

string::string()
    : bx(),
    mySize(0),
    myRes(15)
{
}

string::string(const size_type count, const char ch) // fill constructor
    : bx(),            // Fills the string with "count" consecutive copies of character ch.
    mySize(0),
    myRes(15)
{
    // construct from count * ch
    mySize = count;
    myRes = (mySize / 16) * 16 + 15;

    //---
    if (myRes >= 16)
        bx.ptr = new value_type[myRes + 1];
    for (size_type i = 0; i < mySize; ++i) // 複製 right 字符串的內容到當前字符串
        myPtr()[i] = ch;
    myPtr()[mySize] = '\0'; // 添加結尾空字符
}

string::~string()
{
    if (myRes > 15)
        delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
    if (myRes < 16)
        return bx.buf;
    else
        return bx.ptr;
}

const string::value_type* string::myPtr() const
{
    if (myRes < 16)
        return bx.buf;
    else
        return bx.ptr;
}

void string::clear()
{
    mySize = 0;
    myPtr()[0] = value_type();
}

string::iterator string::begin()
{
    return myPtr();
}

string::const_iterator string::begin() const
{
    return const_iterator(myPtr());
}

string::iterator string::end()
{
    return myPtr() + static_cast<difference_type>(mySize);
}

string::const_iterator string::end() const
{
    return const_iterator(myPtr() + static_cast<difference_type>(mySize));
}

string::reference string::at(const size_type off)
{
    if (off > mySize)
    {
        cout << "string subscript out of range\n";
        exit(1);
    }

    return myPtr()[off];
}

string::const_reference string::at(const size_type off) const
{
    if (off > mySize)
    {
        cout << "string subscript out of range\n";
        exit(1);
    }

    return myPtr()[off];
}

string::reference string::front()
{
    return myPtr()[0];
}

string::const_reference string::front() const
{
    return myPtr()[0];
}

string::reference string::back()
{
    return myPtr()[mySize - 1];
}

string::const_reference string::back() const
{
    return myPtr()[mySize - 1];
}

const char* string::c_str() const
{
    return myPtr();
}

string::size_type string::size() const
{
    return mySize;
}

void string::resize(const size_type newSize, const char ch)
{
    // determine new length, padding with ch elements as needed
    if (newSize > mySize)
    {
        if (newSize > myRes)
        {
            size_type newMyRes = myRes * 3 / 2;
            if (newMyRes < (newSize / 16) * 16 + 15)
                newMyRes = (newSize / 16) * 16 + 15;

            //---
            value_type* newPtr = new value_type[newMyRes + 1]; // 分配新的內存

            for (size_type i = 0; i < mySize; ++i) // 複製舊的內容到新的內存
                newPtr[i] = myPtr()[i];

            if (myRes > 15)
                delete[] bx.ptr; // 釋放舊的內存

            // 更新指針和容量
            bx.ptr = newPtr;
            myRes = newMyRes;
        }

        for (size_type i = mySize; i < newSize; ++i)
            myPtr()[i] = ch; // 將字符 'ch' 添加到字符串尾部直到達到新的大小
    }
    mySize = newSize; // 新大小小於當前大小，直接截斷字符串    
    myPtr()[mySize] = '\0'; // 添加結尾空字符
}

string::size_type string::capacity() const
{
    return myRes;
}

bool string::empty() const
{
    return mySize == 0;
}