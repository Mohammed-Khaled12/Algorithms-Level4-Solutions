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

bool IsWeekEnd(stDate Date)
{
    // Weekends are Fri and Sat
    short DayIndex = DayOfWeekOrder(Date);
    return (DayIndex == 5 || DayIndex == 6);
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

int ActualVacation(stDate StartDate, stDate EndDate)
{
    int ActualDays = 0;
    while (IsDate1BeforeDate2(StartDate,EndDate))
    {
        if (!IsWeekEnd(StartDate))
        {
            ActualDays++;
        }
        StartDate = IncreaseDate(StartDate);
    }
    return ActualDays;
}

int main()
{
    cout << "Vacation Starts: \n";
    stDate StartDate = ReadFullDate();
    cout << "\nVacation Ends: \n";
    stDate EndDate = ReadFullDate();

    cout << "\nVacation From: " << DayShortName(DayOfWeekOrder(StartDate));
    cout << " , " << StartDate.Day << "/" << StartDate.Month << "/" << StartDate.Year << endl;

    cout << "Vacation To: " << DayShortName(DayOfWeekOrder(EndDate));
    cout << " , " << EndDate.Day << "/" << EndDate.Month << "/" << EndDate.Year << endl;

    cout << "\nActual Vacation Days is: " << ActualVacation(StartDate, EndDate) << "\n";

    return 0;
}