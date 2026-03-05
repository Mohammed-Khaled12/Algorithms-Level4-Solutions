#include <iostream>
#include <limits>
using namespace std;

enum enDateCompare
{
    Before = -1,
    Equal = 0,
    After = 1
};

struct stDate
{
    short Day;
    short Month;
    short Year;
};

int readNumber(string msg)
{
    int num;
    cout << "Please enter a " << msg << ": ";
    cin >> num;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a numeric value: ";
        cin >> num;
    }
    return num;
}

stDate ReadFullDate()
{
    stDate Date;
    Date.Year = readNumber("Year");
    Date.Month = readNumber("Month");
    Date.Day = readNumber("Day");
    return Date;
}

bool IsDate1AfterDate2(stDate Date1, stDate Date2)
{
    if (Date1.Year != Date2.Year)
    {
        return (Date1.Year > Date2.Year);
    }

    if (Date1.Month != Date2.Month)
    {
        return (Date1.Month > Date2.Month);
    }

    return (Date1.Day > Date2.Day);
}

bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
{
    if (Date1.Year != Date2.Year)
    {
        return (Date1.Year < Date2.Year);
    }

    if (Date1.Month != Date2.Month)
    {
        return (Date1.Month < Date2.Month);
    }

    return (Date1.Day < Date2.Day);
}

enDateCompare CompareDates(stDate Date1, stDate Date2)
{
    if (IsDate1AfterDate2(Date1, Date2))
    {
        return enDateCompare::After;
    }
    if (IsDate1BeforeDate2(Date1, Date2))
    {
        return enDateCompare::Before;
    }
    return enDateCompare::Equal;
}

int main()
{
    cout << "Enter Date 1: \n";
    stDate Date1 = ReadFullDate();
    cout << "\nEnter Date 2: \n";
    stDate Date2 = ReadFullDate();

    cout << "\nCompare Result = " << CompareDates(Date1, Date2) << endl;

    return 0;
}