#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "AvailBoxes.h"

extern int computeCurrentDate( Date &currentDate );

AvailBoxes::AvailBoxes()
{
   loadNumAvailBoxes();

   Date currentDate;

   computeCurrentDate( currentDate );

   //---
   int days = currentDate - startingDate;
   startingDate = currentDate;
   if (days > 7)
       days = 7;
   for (int i = 1;i <= 18;i++) //刪掉過期的資料
   {
       for (int j = 1; j <= 7 - days; j++)
       {
           for (int k = 0; k <= 23; k++)
               numAvailBoxes[i][j][k] = numAvailBoxes[i][j + days][k];
       }
   }
   for (int i = 1;i <= 18;i++) //補足七天資料
   {
       for (int j = 7 - days + 1; j <= 7; j++)//計算要補的天數
       {
           for (int k = 0; k <= 23; k++)
               numAvailBoxes[i][j][k] = totalnumAvailBoxes;
       }
   }
   saveNumAvailBoxes();

   cout << startingDate.getYear() << "/"
      << startingDate.getMonth() << "/"
      << startingDate.getDay() << endl;

   for( int branch = 1; branch <= 18; branch++ )
   {
       for (int k = 1; k <= 7; k++)
       {
           for (int i = 0; i <= 23; i++)
               cout << setw(4) << numAvailBoxes[branch][k][i];
           cout << endl;
       }
   }
}

AvailBoxes::~AvailBoxes()
{
   saveNumAvailBoxes();
}

bool AvailBoxes::available( int branchCode, int date, int startingHour, int numHours )
{
    //---
    for (int hour = startingHour; hour < startingHour + numHours; ++hour)
    {
        if (numAvailBoxes[branchCode][date][hour] == 0)
            return false;
    }
    return true;
}

void AvailBoxes::decrease( int branchCode, int date, int startingHour, int numHours )
{
    //---
    for (int hour = startingHour; hour < startingHour + numHours; ++hour)
    {
        numAvailBoxes[branchCode][date][hour]--;
    }
}

void AvailBoxes::increase( int branchCode, int date, int startingHour, int numHours )
{
    //---
    for (int hour = startingHour; hour < startingHour + numHours; ++hour)
    {
        numAvailBoxes[branchCode][date][hour]++;
    }
}

void AvailBoxes::loadNumAvailBoxes()
{
    //---
    ifstream inAvailBoxes("NumAvailBoxes.txt", ios::in);
    if (!inAvailBoxes)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    int y, m, d;
    inAvailBoxes >> y >> m >> d;
    startingDate.setYear(y);
    startingDate.setMonth(m);
    startingDate.setDay(d);
   
    for (int i = 1;i <= 18;i++)
    {
        for (int j = 1;j <= 7;j++)
        {
            for (int k = 0;k <= 23;k++)
                inAvailBoxes >> numAvailBoxes[i][j][k];
        }
    }
    
    inAvailBoxes.close();
}

void AvailBoxes::saveNumAvailBoxes()
{
    //---
    ofstream outAvailBoxes("NumAvailBoxes.txt", ios::out| ios::trunc);
    if (!outAvailBoxes)
    {
        cout << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    outAvailBoxes << startingDate.getYear() << " "
        << startingDate.getMonth() << " "
        << startingDate.getDay() << endl;
  
    for (int i = 1; i <= 18; i++)
    {
        for (int j = 1; j <= 7; j++)
        {
            for (int k = 0; k <= 23; k++)
                outAvailBoxes << numAvailBoxes[i][j][k] << " ";
            outAvailBoxes << endl;
        }
    }
    
    outAvailBoxes.close();
}