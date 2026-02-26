#include <iostream>
#include <limits>
using namespace std;

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

bool IsLeapYear(short year)
{
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

short DaysInMonth(short year, short Month)
{
    if (Month < 1 || Month > 12)
    {
        return 0;
    }
    int arrDaysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return (Month == 2) ? (IsLeapYear(year) ? 29 : 28) : arrDaysPerMonth[Month];
}

short DaysFromTheBeginingOfTheYear(short Year, short Month, short Day)
{
    short sum = 0;
    for (int i = 1; i < Month; i++)
    {
        sum += DaysInMonth(Year, i);
    }
    sum += Day;
    return sum;
}

stDate DateAddDays(stDate Date, short Days)
{
    short RemainingDays = DaysFromTheBeginingOfTheYear(Date.Year, Date.Month, Date.Day) + Days;
    short MonthDays = 0;

    Date.Month = 1;

    while (true)
    {
        MonthDays = DaysInMonth(Date.Year, Date.Month);

        if (RemainingDays > MonthDays)
        {
            RemainingDays -= MonthDays;
            Date.Month++;
            if (Date.Month > 12)
            {
                Date.Month = 1;
                Date.Year++;
            }
        }
        else
        {
            Date.Day = RemainingDays;
            break;
        }
    }

    return Date;
}

int main()
{
    stDate Date = ReadFullDate();
    short Days = readNumber("Days to Add");

    Date = DateAddDays(Date, Days);
    cout << "\nDate after adding [" << Days << "] days is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;
    return 0;
}