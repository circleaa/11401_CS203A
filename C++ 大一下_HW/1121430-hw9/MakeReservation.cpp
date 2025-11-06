// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

#include "MakeReservation.h"

char branchNames[ 19 ][ 24 ] = { "", "Taipei Dunhua South",   "Taipei Linsen",
                                    "Taipei Zhongxiao", "Taipei Songjiang",
                                     "Taipei Nanjing",       "Taipei Zhonghua New",
                                     "Banqiao Guanqian",    "Yonghe Lehua",
                                     "Taoyuan Zhonghua",    "Taoyuan Nankan",
                                     "Zhongli Zhongyang",   "Hsinchu Beida",
                                     "Taichung Ziyou",      "Chiayi Ren'ai",
                                     "Tainan Ximen",        "Kaohsiung Zhonghua New",
                                     "Kaohsiung Jianxing",  "Pingtung Kending" };

extern int inputAnInteger( int begin, int end );
extern void computeCurrentHour( Date &currentDate, int &currentHour );

MakeReservation::MakeReservation( string userIDNumber,
                                  ReservationDatabase &theReservationDatabase,
                                  AvailBoxes &theAvailBoxes )
   : Transaction( userIDNumber, theReservationDatabase, theAvailBoxes )
{
}

// make reservation
void MakeReservation::execute()
{
   ReservationDatabase &reservationDatabase = getReservationDatabase();

   Date currentDate;
   int currentHour;
   computeCurrentHour( currentDate, currentHour );

   //---
   int hour, numHours, branchCode, numCustomers, numdate;
   Date date;
   do {
       cout << endl;
       cout << "The current hour: " << currentDate << ":" << currentHour << endl;
       cout << endl;

       cout << "Available days:" << endl;
       vector<Date> d(9, 0); //d被初始化為9個值為0的Date
       d[1] = currentDate;
       int i = 1;
       while (i <= 7)
       {
           cout << i << ". " << d[i] << endl;
           d[i + 1] = d[i] + 1;
           i++;
       }
       cout << endl;
       do cout << "Enter your choice (0 to end): ";
       while ((numdate = inputAnInteger(0, 7)) == -1);
       if (numdate == 0)
           return;
       cout << endl;
       date = d[numdate];

       if (date == currentDate && currentHour + 1 != 24)
       {
           do cout << "Enter hour (" << currentHour + 1 << "~23): ";
           while ((hour = inputAnInteger(currentHour + 1, 23)) == -1);
       }
       else
           do cout << "Enter hour (00 ~23): ";
           while ((hour = inputAnInteger(0, 23)) == -1);
       //cin >> hour;
       cout << endl;

       if(reservationDatabase.allowed(getIDNumber(), date, hour) ==0)  //六小時內有訂單
           cout << "You already have a reservation within six hours!" << endl;

   } while (reservationDatabase.allowed(getIDNumber(), date, hour) ==0); //false
       
   
   do cout << "How many hours (1~6): ";
   while ((numHours = inputAnInteger(1, 6)) == -1);
   cout << endl;

   for (int i = 1;i <= 18;i++)
   {
       if (getAvailBoxes().available(i, numdate, hour, numHours) == 1)
           cout << i << ". " << branchNames[i] << endl;
   }
   cout << endl;
   cout << "Enter your choice (0 to end): ";
   cin >> branchCode;
   cout << endl;

   cout << "Enter the number of customes (1~20,0 to end): ";
   cin >> numCustomers;
   cout << endl;

   int dateCode = date - currentDate + 1;
   getAvailBoxes().decrease(branchCode, dateCode, hour, numHours);

   Reservation newReservation( getIDNumber(), branchCode, date, hour, numHours, numCustomers );

   cout << endl << setw( 22 ) << "Branch"
                << setw( 14 ) << "Date" << setw( 8 ) << "Hour"
                << setw( 19 ) << "No of Customers" << endl;

   newReservation.displayReservationInfo();
   cout << "\nReservation Completed!\n";

   reservationDatabase.pushBack( newReservation );
}

int MakeReservation::inputBranchCode( bool available[] )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number == 0 )
      return number;

   if( number >= 1 && number <= 18 && available[ number ] )
      return number;
   else
      return -1;
}