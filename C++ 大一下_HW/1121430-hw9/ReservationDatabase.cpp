// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h"

extern int computeCurrentDate( Date &currentDate );
extern void computeCurrentHour( Date &currentDate, int &currentHour );

ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
   saveReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::exist( string IDNumber )
{
    //--- returns true if the ReservationDatabase has a reservation containing specified IDNumber
    for (int i = 0; i < reservations.size(); i++)
    {
        if (IDNumber.compare(reservations[i].getIDNumber()) == 0)//比較有沒有相同ID
            return true;
    }
    return false;
}

bool ReservationDatabase::allowed( string IDNumber, Date date, int hour )
{
    //--- 如果前一個訂單時間為六小時內，則return false
    for (int i = 0; i < reservations.size(); i++)
    {
        if (IDNumber.compare(reservations[i].getIDNumber()) == 0)
        {
            if (date == reservations[i].getDate()) //同一天
            {
                if (hour - reservations[i].getHour() <= 6)
                    return false;
            }
            else if (date - reservations[i].getDate() == 1)  //晚一天
            {
                if ((hour+24) - reservations[i].getHour() <= 6)
                    return false;
            }
            else if(reservations[i].getDate() - date == 1) //早一天
            {
                if ((reservations[i].getHour() + 24) - hour <= 6)
                    return false;
            }
        }
    }
    return true;
}

int ReservationDatabase::displayReservationInfo( string IDNumber )
{
   cout << endl << setw( 25 ) << "Branch"
                << setw( 14 ) << "Date" << setw( 8 ) << "Hour"
                << setw( 19 ) << "No of Customers" << endl;

   int count = 0;
   vector< Reservation >::iterator it;
   for( it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIDNumber() == IDNumber )
      {
         cout << ++count << ". ";
         it->displayReservationInfo();
      }

   return count;
}

void ReservationDatabase::cancelReservation( string IDNumber, int n,
                                             int &branchCode, int &dateCode, int &startingHour, int &numHours )
{
   Date currentDate;
   computeCurrentDate( currentDate );

   //---
   int i = 0, m = 0;
   for(; i < reservations.size(); i++)
   {
       if (IDNumber.compare(reservations[i].getIDNumber()) == 0)
       {
           m++;
           if (m == n)
           {
               /*int date = (reservations[i].getDate().getYear() * 10000) + (reservations[i].getDate().getMonth() * 100)
                   + (reservations[i].getDate().getDay());*/
               branchCode = reservations[i].getBranch();
               dateCode = reservations[i].getDate() - currentDate +1;
               startingHour = reservations[i].getHour();
               numHours = reservations[i].getNumHours();
           }
       }

   }
   
   for (size_t j = i + 1; i < reservations.size(); j++)
       reservations[j - 1] = reservations[j];
   reservations.pop_back();
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

void ReservationDatabase::loadReservations()
{
    //---
    ifstream inReservation("ReservationInfo.dat", ios::in | ios::binary);
    if (!inReservation)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    Reservation reservation;
    while (inReservation.read(reinterpret_cast<char*>(&reservation), sizeof(Reservation)))
        reservations.push_back(reservation);
    inReservation.close();
}

void ReservationDatabase::saveReservations()
{
    //---
    ofstream outReservation("ReservationInfo.dat", ios::out | ios::binary | ios::trunc);
    if (!outReservation)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }
    for (int i = 0; i < reservations.size(); i++)
        outReservation.write(reinterpret_cast<char*>(&reservations[i]), sizeof(Reservation));
    outReservation.close();
}