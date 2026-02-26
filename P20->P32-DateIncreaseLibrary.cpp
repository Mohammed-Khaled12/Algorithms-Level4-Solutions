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

void IncreaseDateByXDays(stDate &Date, int Days)
{
    while (Days--)
    {
        IncreaseDate(Date);
    }
}

void IncreaseDateByXWeeks(stDate &Date, int Weeks)
{
    while (Weeks--)
    {
        IncreaseDateByXDays(Date, 7);
    }
}

void IncreaseDateByOneMonth(stDate &Date)
{
    if (Date.Month == 12)
    {
        Date.Year++;
        Date.Month = 1;
    }
    else
    {
        Date.Month++;
    }

    if (Date.Day > DaysInMonth(Date.Year, Date.Month))
    {
        Date.Day = DaysInMonth(Date.Year, Date.Month);
    }
}

void IncreaseDateByXMonth(stDate &Date, int Months)
{
    while (Months--)
    {
        IncreaseDateByOneMonth(Date);
    }
}

void IncreaseDateByOneYear(stDate &Date)
{
    if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year + 1))
    {
        Date.Year++;
        Date.Day = 28;
    }
    else
    {
        Date.Year++;
    }
}

void IncreaseDateByXYears(stDate &Date, int Years)
{
    while (Years--)
    {
        IncreaseDateByOneYear(Date);
    }
}

void IncreaseDateByXDecades(stDate &Date, int Decades)
{
    while (Decades--)
    {
        IncreaseDateByXYears(Date, 10);
    }
}

void IncreaseDateByXCentury(stDate &Date, int Centuries)
{
    while (Centuries--)
    {
        IncreaseDateByXYears(Date, 100);
    }
}

void IncreaseDateByXMillennium(stDate &Date, int Millenniums)
{
    while (Millenniums--)
    {
        IncreaseDateByXYears(Date, 1000);
    }
}

int main()
{
    stDate Date = ReadFullDate();

    cout << "\nDate after:\n";

    IncreaseDate(Date);
    cout << "01-Adding one Day is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXDays(Date, 10);
    cout << "02-Adding 10 Days is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXWeeks(Date, 1);
    cout << "03-Adding One Week is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXWeeks(Date, 10);
    cout << "04-Adding 10 Weeks is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXMonth(Date, 1);
    cout << "05-Adding One Month is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXMonth(Date, 5);
    cout << "06-Adding 5 Months is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByOneYear(Date);
    cout << "07-Adding One Year is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXYears(Date, 10);
    cout << "08-Adding 10 Years is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXDecades(Date, 1);
    cout << "09-Adding one Decade is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXDecades(Date, 10);
    cout << "10-Adding 10 Decades is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXCentury(Date, 1);
    cout << "11-Adding one Century is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    IncreaseDateByXMillennium(Date, 1);
    cout << "12-Adding One Millennium is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    return 0;
}