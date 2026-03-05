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

bool IsValidDate(stDate Date)
{
    if (Date.Month < 1 || Date.Month > 12)
    {
        return false;
    }
    if (Date.Day < 1 || Date.Day > DaysInMonth(Date.Year, Date.Month))
    {
        return false;
    }
    if (Date.Year < 1)
    {
        return false;
    }
    return true;
}

int main()
{
    stDate Date = ReadFullDate();

    if (IsValidDate(Date))
    {
        cout << "\nYes, Date is a Valid date.\n";
    }
    else
    {
        cout << "\nNo, Date is a NOT Valid date\n";
    }

    return 0;
}