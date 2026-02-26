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

bool IsLastDayInMonth(stDate Date)
{
    return Date.Day == DaysInMonth(Date.Year, Date.Month);
}

bool IsLastMonthInYear(stDate Date)
{
    return Date.Month == 12;
}

int main()
{
    stDate Date = ReadFullDate();

    if (IsLastDayInMonth(Date))
        cout << "Yes, Day is Last Day in Month.\n";
    else
        cout << "No, Day is Not Last Day in Month.\n";
    if (IsLastMonthInYear(Date))
        cout << "Yes, Month is Last Month in Year.\n";
    else
        cout << "No, Month is Not Last Month in Year.\n";

    return 0;
}