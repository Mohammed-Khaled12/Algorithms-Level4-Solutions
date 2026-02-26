#include <iostream>
#include <ctime>
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
    Date.Year = readNumber("Year Of Birth");
    Date.Month = readNumber("Month Of Birth");
    Date.Day = readNumber("Day Of Birth");
    return Date;
}

stDate GetSystemDate()
{
    stDate DateNow;
    time_t now = time(nullptr);
    struct tm *LocalTime = localtime(&now);
    DateNow.Year = LocalTime->tm_year + 1900;
    DateNow.Month = LocalTime->tm_mon + 1;
    DateNow.Day = LocalTime->tm_mday;
    return DateNow;
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

void IncreaseDate(stDate &Date)
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
}

int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false)
{
    int days = 0;
    while (IsDate1BeforeDate2(Date1, Date2))
    {
        days++;
        IncreaseDate(Date1);
    }
    return IncludeEndDay ? ++days : days;
}

int main()
{
    stDate Date1 = ReadFullDate();
    stDate Date2 = GetSystemDate();

    cout << "Your Age in Days Is: " << GetDifferenceInDays(Date1, Date2, true);

    return 0;
}