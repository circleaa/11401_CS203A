#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

int adultTicketPrice[13][13] = {
   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,    0,  260,  310,  500,  700,  920, 1330, 1510, 1660, 1880, 2290, 2500,
   0,   40,    0,  260,  440,  640,  850, 1250, 1430, 1600, 1820, 2230, 2440,
   0,   70,   40,    0,  400,  590,  800, 1210, 1390, 1550, 1780, 2180, 2390,
   0,  200,  160,  130,    0,  400,  620, 1010, 1210, 1370, 1580, 1990, 2200,
   0,  330,  290,  260,  130,    0,  410,  820, 1010, 1160, 1390, 1790, 2000,
   0,  480,  430,  400,  280,  140,    0,  610,  790,  950, 1160, 1580, 1790,
   0,  750,  700,  670,  540,  410,  270,    0,  400,  550,  770, 1180, 1390,
   0,  870,  820,  790,  670,  540,  390,  130,    0,  370,  580, 1000, 1210,
   0,  970,  930,  900,  780,  640,  500,  230,  110,    0,  430,  830, 1040,
   0, 1120, 1080, 1050,  920,  790,  640,  380,  250,  150,    0,  620,  820,
   0, 1390, 1350, 1320, 1190, 1060,  920,  650,  530,  420,  280,    0,  410,
   0, 1530, 1490, 1460, 1330, 1200, 1060,  790,  670,  560,  410,  140,    0 };

char departureTimes[41][8] = { "",
   "00:00", "00:30", "05:00", "05:30", "06:00", "06:30", "07:00", "07:30",
   "08:00", "08:30", "09:00", "09:30", "10:00", "10:30", "11:00", "11:30",
   "12:00", "12:30", "13:00", "13:30", "14:00", "14:30", "15:00", "15:30",
   "16:00", "16:30", "17:00", "17:30", "18:00", "18:30", "19:00", "19:30",
   "20:00", "20:30", "21:00", "21:30", "22:00", "22:30", "23:00", "23:30" };

struct Reservation
{
    char reservationNumber[12]; // used to identify a reservation
    char trainNumber[8];  // used to identify a train
    char idNumber[12];    // the id number of the contact person
    char phone[12];       // the (local or mobile) phone number of the contact person
    char date[12];        // outbound date
    int direction;          // 1: southbound, 2: northbound
    int originStation;      // the origin station code
    int destinationStation; // the destination station code
    int carClass;           // the car class code; 1:standard car, 2:business car
    int adultTickets;       // the number of adult tickets
    int concessionTickets;  // the number of concession tickets
};

struct Train
{
    char trainNumber[8];          // used to identify a train
    char departureTimes[13][8]; // the departure time of a train for each station,
};   // departureTimes[ 0 ] is not used
// departureTimes[ i ] is the departure time of a train for station #i

char southboundStations[13][12] = { "",
   "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli",
   "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };

char northboundStations[13][12] = { "",
   "Zuoying", "Tainan", "Chiayi", "Yunlin", "Changhua", "Taichung",
   "Miaoli", "Hsinchu", "Taoyuan", "Banqiao", "Taipei", "Nangang" };

// loads the southbound timetable from the file "Southbound timetable.txt"
void loadTimetable(const char timetableFileName[], vector< Train >& timetable);

void loadReservations(vector< Reservation >& reservations);

// save reservation to the end of the file Reservation details.dat
void saveReservations(vector< Reservation >& reservations);

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

void makingReservation(vector< Reservation >& reservations, vector< Train >& southboundTimetable,
    vector< Train >& northboundTimetable);

// inputs originStation, destinationStation, carClass,
// date, departureTime, adultTickets and concessionTickets
void inputReservationDetails(Reservation& reservation, int& departureTime, char stations[][12]);

// displays timetables for 10 coming southbound trains, then let user select one
void selectTrain(Reservation& reservation, int departureTime, vector< Train >& timetable, char stations[][12]);

// inputs idNumber and phone, and randomly generate reservationNumber
void inputContactInfo(Reservation& reservation);

void reservationHistory(vector< Reservation >& reservations, vector< Train >& southboundTimetable,
    vector< Train >& northboundTimetable);

// inputs idNumber and reservationNumber, and
// checks if the corresponding reservation exists
bool existReservation(int& reservationNo, vector< Reservation >& reservations);

void cancelReservation(int reservationNo, vector< Reservation >& reservations);

// displays date, originStation, destinationStation, departureTime, arrival time,
// fare for adultTickets, fare for concessionTickets and total fare
void displayReservation(Reservation reservation, vector< Train >& timetable, char stations[][12]);

// reduces adultTickets and/or concessionTickets in reservation
void reduceSeats(int reservationNo, vector< Reservation >& reservations);

int main()
{
    cout << "Taiwan High Speed Rail Booking System\n";
    srand(static_cast<unsigned int>(time(0)));

    vector< Train > southboundTimetable;
    vector< Train > northboundTimetable;
    vector< Reservation > reservations;

    loadTimetable("Southbound timetable.txt", southboundTimetable);
    loadTimetable("Northbound timetable.txt", northboundTimetable);
    loadReservations(reservations);

    int choice;
    while (true)
    {
        cout << "\nEnter Your Choice\n"
            << "1. Booking\n"
            << "2. Booking History\n"
            << "3. End Program\n";

        do cout << "? ";
        while ((choice = inputAnInteger(1, 3)) == -1);
        cout << endl;

        switch (choice)
        {
        case 1:
            makingReservation(reservations, southboundTimetable, northboundTimetable);
            break;
        case 2:
            reservationHistory(reservations, southboundTimetable, northboundTimetable);
            break;
        case 3:
            saveReservations(reservations);
            cout << "Thank you. Goodbye.\n\n";
            system("pause");
            return 0;
        default: // display error if user does not select valid choice
            cout << "Incorrect Choice!\n";
            break;
        }
    }

    system("pause");
}

void loadTimetable(const char timetableFileName[], vector< Train >& timetable)//
{
    ifstream inFile(timetableFileName, ios::in);
    if (!inFile)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    Train train;
    while (inFile >> train.trainNumber)
    {
        for (int i = 1; i < 13; i++)
            inFile >> train.departureTimes[i];
        timetable.push_back(train);
    }

    inFile.close();
}

void loadReservations(vector< Reservation >& reservations)//從訂票資料檔讀出
{
    ifstream inReservation("Reservation details.dat", ios::in | ios::binary);
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

void saveReservations(vector< Reservation >& reservations)//把訂票資料放入二元檔中
{
    ofstream outReservation("Reservation details.dat", ios::out | ios::binary | ios::app);
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

int inputAnInteger(int begin, int end)
{
    char string[80];
    cin >> string;

    if (strlen(string) == 0)
        exit(0);

    for (unsigned int i = 0; i < strlen(string); i++)
        if (string[i] < '0' || string[i] > '9')
            return -1;

    int number = atoi(string);

    if (number >= begin && number <= end)
        return number;
    else
        return -1;
}

void makingReservation(vector< Reservation >& reservations, vector< Train >& southboundTimetable,
    vector< Train >& northboundTimetable)
{
    Reservation reservation;
    int departureTime;

    cout << "1. Southbound\n" << "2. Northbound\n";

    do cout << "? ";
    while ((reservation.direction = inputAnInteger(1, 2)) == -1);
    cout << endl;

    if (reservation.direction == 1)
    {
        inputReservationDetails(reservation, departureTime, southboundStations);
        selectTrain(reservation, departureTime, southboundTimetable, southboundStations);
    }
    else
    {
        inputReservationDetails(reservation, departureTime, northboundStations);
        selectTrain(reservation, departureTime, northboundTimetable, northboundStations);
    }

    inputContactInfo(reservation);

    reservations.push_back(reservation);

    cout << "\nReservation Completed!\n";
}

void inputReservationDetails(Reservation& reservation, int& departureTime, char stations[][12])
{
    cout << "Origin Station\n";
    for (int i = 1; i < 13; i++)
        cout << setw(2) << i << ". " << stations[i] << endl;

    do cout << "? ";
    while ((reservation.originStation = inputAnInteger(1, 12)) == -1);

    cout << "\nDestination Station\n";
    for (int i = 1; i < 13; i++)
        cout << setw(2) << i << ". " << stations[i] << endl;

    do cout << "? ";
    while ((reservation.destinationStation = inputAnInteger(1, 12)) == -1);

    cout << "\n1. Standard Car\n" << "2. Business Car\n";

    do cout << "? ";
    while ((reservation.carClass = inputAnInteger(1, 2)) == -1);

    cout << "\nDeparture Date: ";
    cin >> reservation.date;

    cout << "\nDeparture Time\n";
    for (int i = 1; i <= 40; i++)
        cout << setw(2) << i << ". " << departureTimes[i] << endl;

    do cout << "? ";
    while ((departureTime = inputAnInteger(1, 40)) == -1);

    cout << "\nHow many adult tickets? ";
    cin >> reservation.adultTickets;

    cout << "\nHow many concession tickets? ";
    cin >> reservation.concessionTickets;
}

void selectTrain(Reservation& reservation, int departureTime, vector< Train >& timetable, char stations[][12])//
{
    cout << "Train No.    Departure    Arrival\n";
    int k = 0;
    string tmpNumber[10];
    for (int n = 0; n < timetable.size(); n++)
    {

        if (strcmp(timetable[n].departureTimes[reservation.originStation], departureTimes[departureTime]) >= 0)
            if (timetable[n].departureTimes[reservation.originStation][0] != '-' && timetable[n].departureTimes[reservation.destinationStation][0] != '-')
            {
                tmpNumber[k] = timetable[n].trainNumber;
                cout << setw(9) << timetable[n].trainNumber;
                cout << setw(13) << timetable[n].departureTimes[reservation.originStation];
                cout << setw(11) << timetable[n].departureTimes[reservation.destinationStation] << endl;
                k++;

                if (k == 10)
                    break;
            }
    }

    cout << "Train Number: ";
    while (cin >> reservation.trainNumber)
    {
        cout << endl;
        int stop_while = 0;
        for (int i = 0; i < k; i++)
        {
            if (reservation.trainNumber != tmpNumber[i] && i == k-1) 
                cout << "Train Number: ";
            if (reservation.trainNumber == tmpNumber[i]) 
            {
                displayReservation(reservation, timetable, stations);
                stop_while = 1;
                break;
            }
        }
        if (stop_while == 1) 
            break;       
    }
}

void inputContactInfo(Reservation& reservation)
{
    cout << "\nEnter Contact Person Information\n\n";

    cout << "Identification: ";
    cin >> reservation.idNumber;

    cout << "\nPhone: ";
    cin >> reservation.phone;

    for (int k = 0; k < 8; k++)
        reservation.reservationNumber[k] = rand() % 10 + '0';
    reservation.reservationNumber[8] = '\0';

    cout << "\nReservation Number: " << reservation.reservationNumber << endl;
}

void reservationHistory(vector< Reservation >& reservations, vector< Train >& southboundTimetable,
    vector< Train >& northboundTimetable)
{
    int reservationNo;
    while (!existReservation(reservationNo, reservations))
        cout << "\nReservation record not found.\n\n";

    if (reservations[reservationNo].direction == 1)
        displayReservation(reservations[reservationNo], southboundTimetable, southboundStations);
    else
        displayReservation(reservations[reservationNo], northboundTimetable, northboundStations);

    int choice = 0;

    // enable user to specify action
    while (true)
    {
        cout << "\nEnter Your Choice\n"
            << "1. Cancel\n"
            << "2. Reduce\n"
            << "3. End\n";

        do cout << "? ";
        while ((choice = inputAnInteger(1, 3)) == -1);
        cout << endl;

        switch (choice)
        {
        case 1:
            cancelReservation(reservationNo, reservations);
            return;
        case 2:
            reduceSeats(reservationNo, reservations);
            return;
        case 3:
            return;
        default: // display error if user does not select valid choice
            cout << "Incorrect Choice!\n";
            break;
        }
    }
}

bool existReservation(int& reservationNo, vector< Reservation >& reservations)//
{
    cout << "Identification: ";
    char idNumber[12];
    cin >> idNumber;

    cout << "\nReservation Number: ";
    char reservationNumber[12];
    cin >> reservationNumber;

    for (int i = 0; i < reservations.size(); i++)
    {
        if (strcmp(reservationNumber, reservations[i].reservationNumber)==0 && strcmp(idNumber, reservations[i].idNumber)==0)
        {
            reservationNo = i;
            return true;
        }
    }
    return false;
}

void cancelReservation(int reservationNo, vector< Reservation >& reservations)
{
    for (size_t i = reservationNo + 1; i < reservations.size(); i++)
        reservations[i - 1] = reservations[i];
    reservations.pop_back();

    cout << "Reservation Cancelled.\n";
}

void displayReservation(Reservation reservation, vector< Train >& timetable, char stations[][12])//
{
    int i;
    for (i = 0; i < timetable.size(); i++)
        if (strcmp(reservation.trainNumber, timetable[i].trainNumber) == 0)
            break;

    cout << "Trip Details\n";
    cout << "Date" << "  Train No." << "        From" << "          To" << "  Departure"
        << "  Arrival" << "     Adult" << "  Concession" << "     Fare" << "        Class\n";

    cout << setw(4) << reservation.date;
    cout << setw(11) << reservation.trainNumber;
    cout << setw(12) << stations[reservation.originStation];
    cout << setw(12) << stations[reservation.destinationStation];
    cout << setw(11) << timetable[i].departureTimes[reservation.originStation];
    cout << setw(9) << timetable[i].departureTimes[reservation.destinationStation];

    if(reservation.direction==2)
    { 
        reservation.destinationStation = 13 - reservation.destinationStation;
        reservation.originStation = 13 - reservation.originStation;
        int p;
        p =reservation.originStation;
        reservation.originStation = reservation.destinationStation;
        reservation.destinationStation = p;
    }
    if (reservation.carClass == 1)
    {
        cout << setw(8) << adultTicketPrice[reservation.destinationStation][reservation.originStation] << "*" << reservation.adultTickets;
        cout << setw(10) << (adultTicketPrice[reservation.destinationStation][reservation.originStation] / 2) << "*" << reservation.concessionTickets;
        cout << setw(9) << (adultTicketPrice[reservation.destinationStation][reservation.originStation] * reservation.adultTickets) + ((adultTicketPrice[reservation.destinationStation][reservation.originStation] / 2) * reservation.concessionTickets);
        cout << setw(14) << "Standard\n";
    }
    if (reservation.carClass == 2)
    {
        cout << setw(8) << adultTicketPrice[reservation.originStation][reservation.destinationStation] << "*" << reservation.adultTickets;
        cout << setw(10) << (adultTicketPrice[reservation.originStation][reservation.destinationStation] / 2) << "*" << reservation.concessionTickets;
        cout << setw(9) << (adultTicketPrice[reservation.originStation][reservation.destinationStation] * reservation.adultTickets) + ((adultTicketPrice[reservation.originStation][reservation.destinationStation] / 2) * reservation.concessionTickets);
        cout << setw(14) << "Business\n";
    }
}

void reduceSeats(int reservationNo, vector< Reservation >& reservations)//
{
    int acancel;
    cout << "How many adult tickets to cancel?";
    cin >> acancel;
    while (acancel > reservations[reservationNo].adultTickets)
    {
        cout << "How many adult tickets to cancel?";
        cin >> acancel;
    }
    cout << endl;
    int ccancel;
    cout << "How many concession tickets to cancel?";
    cin >> ccancel;
    while (ccancel > reservations[reservationNo].concessionTickets)
    {
        cout << "How many concession tickets to cancel?";
        cin >> ccancel;
    }
    if (acancel == reservations[reservationNo].adultTickets && ccancel == reservations[reservationNo].concessionTickets)
        cancelReservation(reservationNo, reservations);
    else
    {
        reservations[reservationNo].adultTickets -= acancel;
        reservations[reservationNo].concessionTickets -= ccancel;
        cout << endl;
        cout << "You have successfully reduce the number of tickets!";
    }
}