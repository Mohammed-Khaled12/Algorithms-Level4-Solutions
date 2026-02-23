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

string MonthName(short Month)
{
    string Months[12] = {"Jan", "Feb", "Mar",
                        "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep",
                        "Oct", "Nov", "Dec"};

    return Months[Month - 1];
}

void PrintMonthCalendar(short Year, short Month, short Day)
{

    cout << "\n________________________" << MonthName(Month) << "________________________\n";
    cout << "Sun\tMon\tTue\tWed\tThu\tFri\tSat\n";
    int current = DayOfWeekOrder(Year, Month, 1);
    for (int i = 0; i < current; i++)
    {
        cout << "\t";
    }
    for (int i = 1; i <= DaysInMonth(Year, Month); i++)
    {
        cout << i << "\t";
        if (++current % 7 == 0)
        {
            cout << "\n";
        }
    }
    cout << "___________________________________________________\n";
}

int main()
{
    short Day = 1;
    short Year = readNumber("Year");
    short Month = readNumber("Month");

    PrintMonthCalendar(Year, Month, Day);

    return 0;
}