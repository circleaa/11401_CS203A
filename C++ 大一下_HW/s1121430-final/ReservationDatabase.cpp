#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

// call loadReservations and removes outdated reservation informations
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// call storeReservations
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

// returns true if there is a Reservation object containing specified reservationNumber
bool ReservationDatabase::exist( string reservationNumber )
{
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getReservationNumber() == reservationNumber )
            return true;

   return false;
}

// returns true if there is a Reservation object containing specified reservationNumber and password
bool ReservationDatabase::legal( string reservationNumber, string password )
{
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getReservationNumber() == reservationNumber && it->getPassword() == password )
         return true;

   return false;
}

// for the Reservation object containing specified reservationNumber,
// displays all the reservation informations
void ReservationDatabase::displayReservationInfo( string reservationNumber )
{
   cout << setfill( ' ' ) << setw( 11 ) << "Mobile No." << setw( 10 ) << "Name"
        << setw( 14 ) << "Date" << setw( 9 ) << "Time" << setw( 30 ) << "Email"
        << setw( 19 ) << "No of Customers" << setw( 12 ) << "Password"
        << setw( 19 ) << "Reservation No." << endl;

   vector< Reservation >::iterator it = getReservation( reservationNumber );
   it->displayReservationInfo();
}

// adds newReservation at the end of reservations
void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

// loads reservations from the file Reservations.dat
void ReservationDatabase::loadReservations()
{
    ifstream inreservation("Reservations.dat", ios::in, ios::binary);

    Reservation res;
    Date currentDate = computeCurrentDate();

    while (inreservation.read(reinterpret_cast<char*>(&res), sizeof(Reservation)))
    {
        if (!(res.getDate() < currentDate))
            reservations.push_back(res);
    }
        
    inreservation.close();
}

// stores reservations into the file Reservations.dat
void ReservationDatabase::storeReservations()
{
    ofstream outreservation("Reservations.dat", ios::in, ios::binary);

    for (int i = 0; i < reservations.size(); i++)
        outreservation.write(reinterpret_cast<char*>(&reservations[i]), sizeof(Reservation));
       
    outreservation.close();
}

// returns an iterator that points to the Reservation object containing specified reservationNumber
vector< Reservation >::iterator ReservationDatabase::getReservation( string reservationNumber )
{
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getReservationNumber() == reservationNumber )
         return it;

   return reservations.end(); // if no matching reservation was found, return NULL
}