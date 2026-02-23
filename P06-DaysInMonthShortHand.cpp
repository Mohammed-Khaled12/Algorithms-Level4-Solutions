#include <iostream>
#include <limits>
using namespace std;

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

int HoursInMonth(short year, short Month)
{
    return DaysInMonth(year, Month) * 24;
}

int MinutesInMonth(short year, short Month)
{
    return HoursInMonth(year, Month) * 60;
}

long long SecondsInMonth(short year, short Month)
{
    return MinutesInMonth(year, Month) * 60;
}

int main()
{
    short Year = readNumber("Year");
    short Month = readNumber("Month");
    cout << "Number of Days in Month [" << Month << "] is " << DaysInMonth(Year, Month) << "\n";
    cout << "Number of Hours in Month [" << Month << "] is " << HoursInMonth(Year, Month) << "\n";
    cout << "Number of Minutes in Month [" << Month << "] is " << MinutesInMonth(Year, Month) << "\n";
    cout << "Number of Seconds in Month [" << Month << "] is " << SecondsInMonth(Year, Month) << "\n";

    return 0;
}