#include <iostream>
#include <ctime>
using namespace std;

struct stDate
{
    short Day;
    short Month;
    short Year;
};

stDate GetSystemDate()
{
    stDate Date;

    time_t now = time(nullptr);
    struct tm *LocalTime = localtime(&now);
    Date.Year = LocalTime->tm_year + 1900;
    Date.Month = LocalTime->tm_mon + 1;
    Date.Day = LocalTime->tm_mday;

    return Date;
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

stDate IncreaseDate(stDate &Date)
{
    if (IsLastMonthInYear(Date) && IsLastDayInMonth(Date))
    {
        Date.Year++;
        Date.Month = 1;
        Date.Day = 1;
    }
    else if (IsLastDayInMonth(Date))
    {
        Date.Month++;
        Date.Day = 1;
    }
    else
    {
        Date.Day++;
    }
    return Date;
}

int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false)
{
    int days = 0;
    while (IsDate1BeforeDate2(Date1, Date2))
    {
        days++;
        Date1 = IncreaseDate(Date1);
    }
    return IncludeEndDay ? ++days : days;
}

short DayOfWeekOrder(short Year, short Month, short Day)
{
    short a, y, m;
    a = (14 - Month) / 12;
    y = Year - a;
    m = Month + (12 * a) - 2;

    // Gregorian:
    // 0:sun, 1:Mon, 2:Tue...etc
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

short DayOfWeekOrder(stDate Date)
{
    return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
}

string DayShortName(short DayOfWeekOrder)
{
    string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return arrDayNames[DayOfWeekOrder];
}

bool IsEndOfWeek(stDate Date)
{
    return (DayOfWeekOrder(Date) == 6);
}

bool IsWeekEnd(stDate Date)
{
    // Weekends are Fri and Sat
    short DayIndex = DayOfWeekOrder(Date);
    return (DayIndex == 5 || DayIndex == 6);
}

bool IsBusinessDay(stDate Date)
{
    return !IsWeekEnd(Date);
}

short DaysUntilTheEndOfWeek(stDate Date)
{
    return 6 - DayOfWeekOrder(Date);
}

short DaysUntilTheEndOfMonth(stDate Date)
{
    return DaysInMonth(Date.Year, Date.Month) - Date.Day;
}

short DaysUntilTheEndOfYear(stDate Date)
{
    stDate Date2;
    Date2.Year = Date.Year;
    Date2.Month = 12;
    Date2.Day = 31;
    return GetDifferenceInDays(Date, Date2, true);
}

int main()
{
    stDate Date = GetSystemDate();

    cout << "Today is " << DayShortName(DayOfWeekOrder(Date)) << " , ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    cout << "\nIs it End of Week? \n";
    if (IsEndOfWeek(Date))
    {
        cout << "Yes it is Saturday, it's end of Week. \n";
    }
    else
    {
        cout << "No it's Not end of Week. \n";
    }

    cout << "\nIs it Weekend?\n";
    if (IsWeekEnd(Date))
    {
        cout << "Yes it is a week end. \n";
    }
    else
    {
        cout << "No today is " << DayShortName(DayOfWeekOrder(Date)) << ", Not a weekend.\n";
    }

    cout << "\nIs it Business Day?\n";
    if (IsBusinessDay(Date))
    {
        cout << "Yes it is a business day. \n";
    }
    else
    {
        cout << "No it is NOT a business day.\n";
    }

    cout << "\nDays until end of week: " << DaysUntilTheEndOfWeek(Date) << "Day(s). \n";

    cout << "\nDays until end of Month: " << DaysUntilTheEndOfMonth(Date) << "Day(s). \n";

    cout << "\nDays until end of Year: " << DaysUntilTheEndOfYear(Date) << "Day(s). \n";

    return 0;
}