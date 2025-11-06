// Member-function definitions for class MemberDatabase.
#include <iostream>
#include <fstream>
using namespace::std;

#include "MemberDatabase.h"

MemberDatabase::MemberDatabase()
{
   loadFromMemberFile();
}

MemberDatabase::~MemberDatabase()
{
   saveToMemberFile();
}

// returns true if userPassword match that of an Account with userIDNumber
bool MemberDatabase::authenticateUser( string userIDNumber, string userPassword )
{
    //---
    for (int i = 0; i < members.size(); i++)
    {
        if (userIDNumber.compare(members[i].getIDNumber()) == 0)
        {
            if(userPassword.compare(members[i].getPassword()) == 0)
            return true;
        }
    }
    return false;
}

// returns true if there is an Account containing userIDNumber
bool MemberDatabase::exist( string &userIDNumber )
{
    //---
    for (int i = 0; i < members.size(); i++)
    {
        if (members[i].getIDNumber()== userIDNumber )//比較有沒有相同ID
            return true;
    }
    return false;
}

// add newMember at the end of members
void MemberDatabase::pushBack( MemberInfo &newMember )
{
   members.push_back( newMember );
}

// loads members from the file MemberInfo.dat
void MemberDatabase::loadFromMemberFile()
{
    //---
    ifstream inMemberFile("MemberInfo.dat", ios::in | ios::binary);
    if (!inMemberFile)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    MemberInfo member;
    while (inMemberFile.read(reinterpret_cast<char*>(&member), sizeof(MemberInfo)))
        members.push_back(member);

    inMemberFile.close();
}

// stores members into the file MemberInfo.dat
void MemberDatabase::saveToMemberFile()
{
    //---
    ofstream outMemberFile("MemberInfo.dat", ios::out | ios::binary | ios::app);
    if (!outMemberFile)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    for (int i = 0; i < members.size(); i++)
        outMemberFile.write(reinterpret_cast<char*>(&members[i]), sizeof(MemberInfo));
    
    outMemberFile.close();
}