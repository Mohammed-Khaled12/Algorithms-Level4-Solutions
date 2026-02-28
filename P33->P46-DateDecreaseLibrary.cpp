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

bool IsFirstDayInMonth(stDate Date)
{
    return Date.Day == 1;
}

bool IsFirstMonthInYear(stDate Date)
{
    return Date.Month == 1;
}

void DecreaseDate(stDate &Date)
{
    if (IsFirstMonthInYear(Date) && IsFirstDayInMonth(Date))
    {
        Date.Year--;
        Date.Month = 12;
        Date.Day = 31;
    }
    else if (IsFirstDayInMonth(Date))
    {
        Date.Month--;
        Date.Day = DaysInMonth(Date.Year, Date.Month);
    }
    else
    {
        Date.Day--;
    }
}

void DecreaseDateByXDays(stDate &Date, int Days)
{
    while (Days--)
    {
        DecreaseDate(Date);
    }
}

void DecreaseDateByXWeeks(stDate &Date, int Weeks)
{
    while (Weeks--)
    {
        DecreaseDateByXDays(Date, 7);
    }
}

void DecreaseDateByOneMonth(stDate &Date)
{
    if (Date.Month == 1)
    {
        Date.Year--;
        Date.Month = 12;
    }
    else
    {
        Date.Month--;
    }

    if (Date.Day > DaysInMonth(Date.Year, Date.Month))
    {
        Date.Day = DaysInMonth(Date.Year, Date.Month);
    }
}

void DecreaseDateByXMonth(stDate &Date, int Months)
{
    while (Months--)
    {
        DecreaseDateByOneMonth(Date);
    }
}

void DecreaseDateByOneYear(stDate &Date)
{
    if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year - 1))
    {
        Date.Year--;
        Date.Day = 28;
    }
    else
    {
        Date.Year--;
    }
}

void DecreaseDateByXYears(stDate &Date, int Years)
{
    while (Years--)
    {
        DecreaseDateByOneYear(Date);
    }
}

void DecreaseDateByXDecades(stDate &Date, int Decades)
{
    while (Decades--)
    {
        DecreaseDateByXYears(Date, 10);
    }
}

void DecreaseDateByXCentury(stDate &Date, int Centuries)
{
    while (Centuries--)
    {
        DecreaseDateByXYears(Date, 100);
    }
}

void DecreaseDateByXMillennium(stDate &Date, int Millenniums)
{
    while (Millenniums--)
    {
        DecreaseDateByXYears(Date, 1000);
    }
}

int main()
{
    stDate Date = ReadFullDate();

    cout << "\nDate after:\n";

    DecreaseDate(Date);
    cout << "01-Subtracting one Day is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXDays(Date, 10);
    cout << "02-Subtracting 10 Days is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXWeeks(Date, 1);
    cout << "03-Subtracting One Week is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXWeeks(Date, 10);
    cout << "04-Subtracting 10 Weeks is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXMonth(Date, 1);
    cout << "05-Subtracting One Month is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXMonth(Date, 5);
    cout << "06-Subtracting 5 Months is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByOneYear(Date);
    cout << "07-Subtracting One Year is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXYears(Date, 10);
    cout << "08-Subtracting 10 Years is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXDecades(Date, 1);
    cout << "09-Subtracting one Decade is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXDecades(Date, 10);
    cout << "10-Subtracting 10 Decades is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXCentury(Date, 1);
    cout << "11-Subtracting one Century is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    DecreaseDateByXMillennium(Date, 1);
    cout << "12-Subtracting One Millennium is:" << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    return 0;
}