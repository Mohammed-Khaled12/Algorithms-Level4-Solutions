#include <iostream>
#include <limits>
using namespace std;

int readNumber()
{
    int num;
    cout << "Please enter a Year: ";
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

short DaysInYear(short year)
{
    return (IsLeapYear(year)) ? 366 : 365;
}

int HoursInYear(short year)
{
    return DaysInYear(year) * 24;
}

int MinutesInYear(short year)
{
    return HoursInYear(year) * 60;
}

long long SecondsInYear(short year)
{
    return MinutesInYear(year) * 60;
}

int main()
{
    short Year = readNumber();
    cout << "Number of Days in Year [" << Year << "] is " << DaysInYear(Year) << "\n";
    cout << "Number of Hours in Year [" << Year << "] is " << HoursInYear(Year) << "\n";
    cout << "Number of Minutes in Year [" << Year << "] is " << MinutesInYear(Year) << "\n";
    cout << "Number of Seconds in Year [" << Year << "] is " << SecondsInYear(Year) << "\n";

    return 0;
}