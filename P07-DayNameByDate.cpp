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

short DayOfWeekOrder(short Year, short Month, short Day)
{
    short a, y, m;
    a = (14 - Month) / 12;
    y = Year - a;
    m = Month + (12 * a) - 2;
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

string DayShortName(short DayOfWeekOrder)
{
    string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return arrDayNames[DayOfWeekOrder];
}

int main()
{
    short Year = readNumber("Year");
    short Month = readNumber("Month");
    short Day = readNumber("Day");

    cout << "Date: " << Day << "/" << Month << "/" << Year << "\n";
    cout << "Day Order: " << DayOfWeekOrder(Year, Month, Day) << "\n";
    cout << "Day Name: " << DayShortName(DayOfWeekOrder(Year, Month, Day)) << "\n";

    return 0;
}