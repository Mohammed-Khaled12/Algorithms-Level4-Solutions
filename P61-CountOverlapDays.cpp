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

bool IsDate1AfterDate2(stDate Date1, stDate Date2)
{
    if (Date1.Year != Date2.Year)
    {
        return (Date1.Year > Date2.Year);
    }

    if (Date1.Month != Date2.Month)
    {
        return (Date1.Month > Date2.Month);
    }

    return (Date1.Day > Date2.Day);
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

bool IsOverlapPeriods(stDate Period1Start, stDate Period1End, stDate Period2Start, stDate Period2End)
{
    if (IsDate1BeforeDate2(Period1End, Period2Start))
    {
        return false;
    }
    if (IsDate1BeforeDate2(Period2End, Period1Start))
    {
        return false;
    }
    return true;
}

int CountOverlapDays(stDate Period1Start, stDate Period1End, stDate Period2Start, stDate Period2End)
{
    stDate OverLapStart, OverLapEnd;
    if (!IsOverlapPeriods(Period1Start, Period1End, Period2Start, Period2End))
    {
        return 0;
    }

    if (IsDate1AfterDate2(Period1Start, Period2Start))
    {
        OverLapStart = Period1Start;
    }
    else
    {
        OverLapStart = Period2Start;
    }

    if (IsDate1AfterDate2(Period2End, Period1End))
    {
        OverLapEnd = Period1End;
    }
    else
    {
        OverLapEnd = Period2End;
    }

    return GetDifferenceInDays(OverLapStart, OverLapEnd);
}

int main()
{
    cout << "\nEnter Period 1 Start Date:\n";
    stDate Period1Start = ReadFullDate();
    cout << "\nEnter Period 1 End Date:\n";
    stDate Period1End = ReadFullDate();

    cout << "\nEnter Period 2 Start Date:\n";
    stDate Period2Start = ReadFullDate();
    cout << "\nEnter Period 2 End Date:\n";
    stDate Period2End = ReadFullDate();

    cout << "OverLap Days: " << CountOverlapDays(Period1Start, Period1End, Period2Start, Period2End);
    return 0;
}