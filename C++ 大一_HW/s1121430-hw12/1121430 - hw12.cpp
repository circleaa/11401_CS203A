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

struct Date
{
    int year;
    int month;
    int day;
};

struct Reservation
{
    char reservationNumber[12]; // used to identify a reservation
    char trainNumber[8];  // used to identify a train
    char idNumber[12];    // the id number of the contact person
    char phone[12];       // the (local or mobile) phone number of the contact person
    char date[12];        // outbound date
    int originStation;      // the origin station code
    int destinationStation; // the destination station code
    int adultTickets;       // the number of adult tickets
    int concessionTickets;  // the number of concession tickets
};

struct Train
{
    char trainNumber[8];          // used to identify a train
    char departureTimes[13][8]; // the departure time of a train for each station,
};   // departureTimes[ 0 ] is not used
// departureTimes[ i ] is the departure time of a train for station #i

struct AvailSeat
{
    char trainNumber[8];        // used to identify a train
    char date[12];             // outbound date
    int numAvailStandSeats[13]; // the number of available seats in standard cars for each station
};

char stations[13][12] = { "",
   "Nangang", "Taipei", "Banqiao", "Taoyuan", "Hsinchu", "Miaoli",
   "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };

const int totalnumStandSeats = 911; // total number of seats in standard cars

// append new data from rear of availSeats
void appendAvailSeats(vector< AvailSeat >& availSeats, vector< Train >& timetable, Date currentDate);

// loads the southbound timetable from the file "Southbound timetable.txt"
void loadTimetable(const char timetableFileName[], vector< Train >& timetable);

// read available seats informations after or equal currentDate, from the file availSeatsFileName
void loadAvailSeats(const char availSeatsFileName[], vector< AvailSeat >& availSeats, Date currentDate);

// read reservation informations after or equal to currentDate, from the file Reservation details.dat
void loadReservations(vector< Reservation >& reservations, Date currentDate);

// write availSeats into the file availSeatsFileName
void saveAvailSeats(const char availSeatsFileName[], vector< AvailSeat >& availSeats);

// write reservations into the file Reservation details.dat
void saveReservations(vector< Reservation >& reservations);

void convert(Date date, char stringDate[]);

// inputs an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

void makingReservation(vector< Reservation >& reservations,
    vector< Train >& southboundTimetable, vector< AvailSeat >& southboundAvailSeats);

// inputs originStation, destinationStation, date,
// departureTime, adultTickets and concessionTickets
void inputReservationDetails(Reservation& reservation, int& departureTime);

void chooseDate(Reservation& reservation, int& dateCode, tm structuredTime);

void chooseTime(Reservation& reservation, int& departureTime, int dateCode, tm structuredTime);

Date computeCurrentDate();

void increment(Date& date);

// displays timetables for 10 coming southbound trains, then let user select one
void selectTrain(Reservation& reservation, int departureTime, vector< Train >& timetable,
    vector< AvailSeat >& availSeats);

int findNumAvailSeats(Reservation& reservation, vector< AvailSeat >& availSeats);

void reduceAvailSeats(Reservation& reservation, vector< AvailSeat >& availSeats);

// inputs idNumber and phone, and randomly generate reservationNumber
void inputContactInfo(Reservation& reservation);

void reservationHistory(vector< Reservation >& reservations, vector< Train >& southboundTimetable);

// inputs idNumber and reservationNumber, and
// checks if the corresponding reservation exists
bool existReservation(int& reservationNo, vector< Reservation >& reservations);

// displays date, originStation, destinationStation, departureTime, arrival time,
// fare for adultTickets, fare for concessionTickets and total fare
void displayReservation(Reservation reservation, vector< Train >& timetable);

int main()
{
    cout << "Taiwan High Speed Rail Booking System\n";
    srand(static_cast<unsigned int>(time(0)));

    vector< Train > southboundTimetable;
    vector< AvailSeat > southboundAvailSeats;
    vector< Reservation > reservations;

    Date currentDate = computeCurrentDate();
    loadTimetable("Southbound timetable.txt", southboundTimetable);
    //   loadAvailSeats( "Southbound Available Seats - 2023-12-19.dat", southboundAvailSeats, currentDate );
    loadAvailSeats("Southbound Available Seats - 2023-12-20.dat", southboundAvailSeats, currentDate);
    appendAvailSeats(southboundAvailSeats, southboundTimetable, currentDate);
    loadReservations(reservations, currentDate);

    int choice;
    while (true)
    {
        cout << "\nEnter Your Choice\n"
            << "1. Booking\n"
            << "2. Booking History\n"
            << "3. End Program\n";

        do cout << "? ";
        while ((choice = inputAnInteger(1, 3)) == -1);

        switch (choice)
        {
        case 1:
            makingReservation(reservations, southboundTimetable, southboundAvailSeats);
            break;
        case 2:
            reservationHistory(reservations, southboundTimetable);
            break;
        case 3:
            saveReservations(reservations);
            saveAvailSeats("Southbound Available Seats - 2023-12-20.dat", southboundAvailSeats);
            cout << "Thank you. Goodbye.\n\n";
            system("pause");
            break;
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

void appendAvailSeats(vector< AvailSeat >& availSeats, vector< Train >& timetable, Date currentDate)//
{
    size_t numDays = availSeats.size() / timetable.size();
    if (numDays < 30)
    {
        Date newDate = currentDate;
        for (int i = 0; i < 30; i++)
            increment(newDate);

        for (int i = 0; i < timetable.size(); i++)
        {
            AvailSeat seat;
            //int date = atoi(seat.date);
            int Date = newDate.year * 10000 + newDate.month * 100 + newDate.day;
            char sDate[9];
            _itoa_s(Date, sDate, 10);

            strcpy_s(seat.trainNumber, timetable[i].trainNumber);
            strcpy_s(seat.date, sDate);
            for (int j = 1; j <= 12; j++)
            {
                seat.numAvailStandSeats[j] = 911;
            }
            availSeats.push_back(seat);
            saveAvailSeats("Southbound Available Seats - 2023 - 12 - 20.dat", availSeats);
        }

        cout << "\nThe current date: ";
        cout << setfill('0') << currentDate.year << "/"
            << setw(2) << currentDate.month << '/'
            << setw(2) << currentDate.day << endl << endl;
        cout << setfill(' ');

        for (size_t i = numDays * timetable.size(); i < availSeats.size(); i++)
        {
            cout << setw(4) << availSeats[i].trainNumber << setw(9) << availSeats[i].date;

            for (size_t j = 1; j <= 12; j++)
                cout << setw(4) << availSeats[i].numAvailStandSeats[j];
            cout << endl;
        }
    }
}

void loadAvailSeats(const char availSeatsFileName[], vector< AvailSeat >& availSeats, Date currentDate)//從座位資料檔讀出
{
    ifstream inSeat(availSeatsFileName, ios::in | ios::binary);
    if (!inSeat)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    AvailSeat seat;
    int Date = currentDate.year * 10000 + currentDate.month * 100 + currentDate.day;
    int date;

    while (inSeat.read(reinterpret_cast<char*>(&seat), sizeof(AvailSeat)))
    {
        date = atoi(seat.date);
        if (date >= Date)
            availSeats.push_back(seat);
    }
    inSeat.close();
}

void loadReservations(vector< Reservation >& reservations, Date currentDate)//從訂票資料檔讀出
{
    ifstream inReservation("Reservation details.dat", ios::in | ios::binary);
    if (!inReservation)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    Reservation reservation;
    int Date = currentDate.year * 10000 + currentDate.month * 100 + currentDate.day;
    int date = atoi(reservation.date);

    while (inReservation.read(reinterpret_cast<char*>(&reservation), sizeof(Reservation)))
    {
        date = atoi(reservation.date);
        if (date >= Date)
            reservations.push_back(reservation);
    }

    inReservation.close();
}

void saveAvailSeats(const char availSeatsFileName[], vector< AvailSeat >& availSeats)//把座位資料放入二元檔中
{
    ofstream outSeats(availSeatsFileName, ios::out | ios::binary | ios::app);
    if (!outSeats)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }
    for (int i = 0; i < availSeats.size(); i++)
        outSeats.write(reinterpret_cast<char*>(&availSeats[i]), sizeof(Reservation));
    outSeats.close();
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

void convert(Date date, char stringDate[])
{
    stringDate[0] = date.year / 1000 + '0';
    stringDate[1] = date.year / 100 % 10 + '0';
    stringDate[2] = date.year / 10 % 10 + '0';
    stringDate[3] = date.year % 10 + '0';

    stringDate[4] = date.month / 10 + '0';
    stringDate[5] = date.month % 10 + '0';

    stringDate[6] = date.day / 10 + '0';
    stringDate[7] = date.day % 10 + '0';
    stringDate[8] = '\0';
}

int inputAnInteger(int begin, int end)
{
    char string[80];
    cin >> string;

    if (strlen(string) == 0)
        exit(0);

    for (size_t i = 0; i < strlen(string); i++)
        if (string[i] < '0' || string[i] > '9')
            return -1;

    int number = atoi(string);

    if (number >= begin && number <= end)
        return number;
    else
        return -1;
}

void makingReservation(vector< Reservation >& reservations,
    vector< Train >& southboundTimetable, vector< AvailSeat >& southboundAvailSeats)
{
    Reservation reservation;
    int departureTime;

    int numAvailSeats;
    do
    {
        do
        {
            inputReservationDetails(reservation, departureTime);
            selectTrain(reservation, departureTime, southboundTimetable, southboundAvailSeats);
            numAvailSeats = findNumAvailSeats(reservation, southboundAvailSeats);
        } while (numAvailSeats == 0);

        do
        {
            cout << "\nHow many adult tickets? ";
            cin >> reservation.adultTickets;

            cout << "\nHow many concession tickets? ";
            cin >> reservation.concessionTickets;
        } while (reservation.adultTickets + reservation.concessionTickets > 10);

    } while (reservation.adultTickets + reservation.concessionTickets > numAvailSeats);

    reduceAvailSeats(reservation, southboundAvailSeats);

    displayReservation(reservation, southboundTimetable);

    inputContactInfo(reservation);

    reservations.push_back(reservation);

    cout << "\nReservation Completed!\n";
}

void inputReservationDetails(Reservation& reservation, int& departureTime)
{
    cout << "\nOrigin Station\n";
    for (int i = 1; i < 12; i++)
        cout << setw(2) << i << ". " << setw(8) << stations[i] << endl;

    do cout << "? ";
    while ((reservation.originStation = inputAnInteger(1, 11)) == -1);

    cout << "\nDestination Station\n";
    for (int i = reservation.originStation + 1; i < 13; i++)
        cout << setw(2) << i << ". " << setw(8) << stations[i] << endl;

    do cout << "? ";
    while ((reservation.destinationStation = inputAnInteger(reservation.originStation + 1, 12)) == -1);

    tm structuredTime;
    time_t rawTime = time(0);
    localtime_s(&structuredTime, &rawTime);


    int dateCode;
    chooseDate(reservation, dateCode, structuredTime);

    chooseTime(reservation, departureTime, dateCode, structuredTime);
}

void chooseDate(Reservation& reservation, int& dateCode, tm structuredTime)
{
    Date date = computeCurrentDate();

    int currentHour = structuredTime.tm_hour;
    int currentMinute = structuredTime.tm_min;
    int currentSecond = structuredTime.tm_sec;

    cout << "\nThe current date and time: " << setfill('0');
    cout << date.year << "/" << setw(2) << date.month << '/' << setw(2) << date.day << "  ";
    cout << setw(2) << currentHour << ":"
        << setw(2) << currentMinute << ':'
        << setw(2) << currentSecond << endl;

    int begin;
    if (currentHour >= 23 || (currentHour == 22 && currentMinute > 30))
    {
        begin = 1;
        increment(date);
    }
    else
        begin = 1;

    cout << "\nDeparture Date\n";
    Date dates[31];
    for (int i = begin; i <= 30; i++)
    {
        cout << setfill(' ') << setw(2) << i << ". "
            << setw(4) << date.year << "/" << setfill('0')
            << setw(2) << date.month << '/' << setw(2) << date.day << endl;

        dates[i] = date;
        increment(date);
    }

    do cout << "? ";
    while ((dateCode = inputAnInteger(begin, 30)) == -1);

    convert(dates[dateCode], reservation.date);
}

void chooseTime(Reservation& reservation, int& departureTime, int dateCode, tm structuredTime)
{
    Date date = computeCurrentDate();
    int currentHour = structuredTime.tm_hour;
    int currentMinute = structuredTime.tm_min;
    int currentSecond = structuredTime.tm_sec;

    int begin = 1;
    if (dateCode == 1 && !(currentHour >= 22 && currentMinute > 30 || currentHour >= 23))
    {
        begin = 3;
        int p = 5; //從5:00開始有車
        for (p; p < 24; p++)
            if (currentHour + 1 - p >= 1)//只能訂一小時後的車
                begin += 2;
            else
                break;
        if (currentMinute > 0)
            begin++;
        if (currentMinute > 30)
            begin++;
    }

    cout << "\nDeparture Time\n";
    for (int i = begin; i <= 40; i++)
        cout << setfill(' ') << setw(2) << i << ". " << departureTimes[i] << endl;

    do cout << "? ";
    while ((departureTime = inputAnInteger(begin, 40)) == -1);
}

Date computeCurrentDate()
{
    tm structuredTime;
    time_t rawTime = time(0);
    localtime_s(&structuredTime, &rawTime);

    Date currentDate;
    currentDate.year = structuredTime.tm_year + 1900;
    currentDate.month = structuredTime.tm_mon + 1;
    currentDate.day = structuredTime.tm_mday;

    return currentDate;
}

void increment(Date& date)
{
    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((date.year % 400 == 0) || (date.year % 4 == 0 && date.year % 100 != 0))
        days[2] = 29;

    if (date.month == 12 && date.day == 31)
    {
        date.year++;
        date.month = 1;
        date.day = 1;
    }
    else if (date.day == days[date.month])
    {
        date.month++;
        date.day = 1;
    }
    else
        date.day++;
}

void selectTrain(Reservation& reservation, int departureTime, vector< Train >& timetable,
    vector< AvailSeat >& availSeats)//列出十輛班車
{
    int s;
    for (s = 0; s < availSeats.size(); s++)
    {
        if (strcmp(reservation.date, availSeats[s].date) == 0)
            break;
    }
    cout << "Train No.    Departure    Arrival\n";
    int k = 0;
    string tmpNumber[10];
    for (int n = 0; n < timetable.size(); n++)
    {
        if (strcmp(timetable[n].departureTimes[reservation.originStation], departureTimes[departureTime]) >= 0)
            if (timetable[n].departureTimes[reservation.originStation][0] != '-' && timetable[n].departureTimes[reservation.destinationStation][0] != '-')
            {
                int j = 1;
                for (int p = reservation.originStation; p < reservation.destinationStation; p++)
                    if (availSeats[s].numAvailStandSeats[p] == 0)
                    {
                        j = 0;
                        break;
                    }
                if (j == 1)
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
        if (s < availSeats.size() && strcmp(reservation.date, availSeats[s].date) == 0)
            s++;
        else
            break;
    }

    cout << "Train Number: ";
    while (cin >> reservation.trainNumber)
    {
        int i = 0;
        cout << endl;
        while (reservation.trainNumber != tmpNumber[i] && i < k)
            i++;
        if (reservation.trainNumber == tmpNumber[i])
            break;
        if (i == k)
            cout << "Train Number: ";
    }
}

int findNumAvailSeats(Reservation& reservation, vector< AvailSeat >& availSeats)//找出最少的座位數量
{
    int minNumAvailSeats = totalnumStandSeats;

    int n;
    for (n = 0; n < availSeats.size(); n++)
        if (strcmp(reservation.trainNumber, availSeats[n].trainNumber) == 0 && strcmp(reservation.date, availSeats[n].date) == 0)
            break;

    int p = availSeats[n].numAvailStandSeats[reservation.originStation];
    for (int i = reservation.originStation + 1;i < reservation.destinationStation;i++)
    {
        if (availSeats[n].numAvailStandSeats[i] < p)
        {
            p = availSeats[n].numAvailStandSeats[i];
        }
    }
    minNumAvailSeats = p;

    return minNumAvailSeats;
}

void reduceAvailSeats(Reservation& reservation, vector< AvailSeat >& availSeats)//減去被訂走的票
{
    int n;
    for (n = 0; n < availSeats.size(); n++)
        if (strcmp(reservation.trainNumber, availSeats[n].trainNumber) == 0 && strcmp(reservation.date, availSeats[n].date) == 0)
            break;

    for (int i = reservation.originStation; i < reservation.destinationStation; i++)
    {
        availSeats[n].numAvailStandSeats[i] -= (reservation.adultTickets + reservation.concessionTickets);
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

void reservationHistory(vector< Reservation >& reservations, vector< Train >& southboundTimetable)
{
    int reservationNo;
    if (!existReservation(reservationNo, reservations))
    {
        cout << "\nReservation record not found.\n\n";
        return;
    }

    displayReservation(reservations[reservationNo], southboundTimetable);
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
        if (strcmp(reservationNumber, reservations[i].reservationNumber) == 0 && strcmp(idNumber, reservations[i].idNumber) == 0)
        {
            reservationNo = i;
            return true;
        }
    }
    return false;
}

void displayReservation(Reservation reservation, vector< Train >& timetable)//
{
    int i;
    for (i = 0; i < timetable.size(); i++)
        if (strcmp(reservation.trainNumber, timetable[i].trainNumber) == 0)
            break;

    cout << "Trip Details\n";
    cout << "      Date" << "  Train No." << "        From" << "          To" << "  Departure"
        << "  Arrival" << "     Adult" << "  Concession" << "     Fare\n";

    cout << setw(10) << reservation.date;
    cout << setw(11) << reservation.trainNumber;
    cout << setw(12) << stations[reservation.originStation];
    cout << setw(12) << stations[reservation.destinationStation];
    cout << setw(11) << timetable[i].departureTimes[reservation.originStation];
    cout << setw(9) << timetable[i].departureTimes[reservation.destinationStation];

    cout << setw(8) << adultTicketPrice[reservation.destinationStation][reservation.originStation] << "*" << reservation.adultTickets;
    cout << setw(10) << (adultTicketPrice[reservation.destinationStation][reservation.originStation] / 2) << "*" << reservation.concessionTickets;
    cout << setw(9) << (adultTicketPrice[reservation.destinationStation][reservation.originStation] * reservation.adultTickets) + ((adultTicketPrice[reservation.destinationStation][reservation.originStation] / 2) * reservation.concessionTickets);
}