#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailTableDatabase.h"

// tableTypes[ i ] is the table type for i customers
const int tableTypes[ 10 ] = { 0, 1, 1, 2, 2, 3, 4, 4, 5, 5 };

extern Date computeCurrentDate();

// calls loadAvailTables(), removes outdated available table informations and
// adds new available table informations
AvailTableDatabase::AvailTableDatabase()
{
   loadAvailTables();

   Date currentDate = computeCurrentDate();

   AvailTable avail;

   Date availDate = availTables.size() == 0 ? currentDate + 1 : availTables[availTables.size()-1].getDate() + 1;  //modify
   if (availTables.size() != 0) //add
   {
       int diff = (currentDate - availTables[0].getDate()) +1;  //modify

       for (int k = 0; k < availTables.size() - diff; k++)
           availTables[k] = availTables[k + diff];

       availTables.resize(availTables.size() - diff); //add
   }
   
   for(int k= availTables.size(); k<=30; k++)
   {
       for (int i = 1; i <= 3; i++)
       {
           for (int j = 1; j <= 5; j++)
           {
               avail.setNumAvailTables(i, j, totalNumTables);
               avail.setDate(availDate); //add
           }
       }
       
       availTables.push_back(avail);  //add
       availDate = availDate + 1;  //add
   }
}

// call storeAvailTables
AvailTableDatabase::~AvailTableDatabase()
{
   storeAvailTables();
}

// decreases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::decreaseAvailTables(int numCustomers, Date date, int timeCode)
{
   int tableType = tableTypes[ numCustomers ];
   vector< AvailTable >::iterator it = getAvailTable( date );
   it->decreaseAvailTables( timeCode, tableType );
}

// returns true if there are available tables on date for corresponding table type
bool AvailTableDatabase::availableTables(int numCustomers, Date date)
{
    vector< AvailTable >::iterator it = getAvailTable(date);

    for (int j = 1; j <= 3; j++)
    {
        if (it->getNumAvailTables(j, tableTypes[numCustomers]) != 0)
            return true;
    }

    return false;
}

// returns true if there are available tables on date and timeCode for corresponding table type
bool AvailTableDatabase::availableTables( int numCustomers, Date date, int timeCode )
{
   vector< AvailTable >::iterator it = getAvailTable( date );

   if (it->getNumAvailTables(timeCode, tableTypes[numCustomers]) == 0)
       return false;

   return true;
}

void AvailTableDatabase::loadAvailTables()
{
    ifstream inavail("AvailTables.dat", ios::in, ios::binary);

    AvailTable ava;

    while (inavail.read(reinterpret_cast<char*>(&ava), sizeof(AvailTable)))
            availTables.push_back(ava);
        
    inavail.close();
}

void AvailTableDatabase::storeAvailTables()
{
    ofstream outavail("AvailTables.dat", ios::in, ios::binary| ios::trunc);

    for (int i = 0; i < availTables.size(); i++)
        outavail.write(reinterpret_cast<char*>(&availTables[i]), sizeof(AvailTable));

    outavail.close();
}

// returns an iterator that points to the AvailTable object containing specified date
vector< AvailTable >::iterator AvailTableDatabase::getAvailTable( Date date )
{
   vector< AvailTable >::iterator it = availTables.begin();
   for( ; it != availTables.end(); ++it )
      if( it->getDate() == date )
         return it;
   return availTables.end();
}