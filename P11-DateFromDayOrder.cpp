#include <iostream>
#include <limits>
using namespace std;

struct date
{
    short stDay;
    short stMonth;
    short stYear;
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

short DaysFromTheBeginingOfTheYear(short Year, short Month, short Day)
{
    short sum = 0;
    for (int i = 1; i < Month; i++)
    {
        sum += DaysInMonth(Year, i);
    }
    sum += Day;
    return sum;
}

date GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
{
    date stDate;
    stDate.stYear = Year;
    stDate.stMonth = 1;
    stDate.stDay = 0;
    for (int i = 1; i <= DateOrderInYear; i++)
    {
        stDate.stDay++;
        if (stDate.stDay > DaysInMonth(Year, stDate.stMonth))
        {
            stDate.stDay = 1;
            stDate.stMonth++;
        }
    }

    return stDate;
}

int main()
{
    short Day = readNumber("Day");
    short Month = readNumber("Month");
    short Year = readNumber("Year");

    short DaysOrder = DaysFromTheBeginingOfTheYear(Year, Month, Day);
    cout << "Number of Days from the beginning of the year is: " << DaysOrder << "\n";

    date stDate = GetDateFromDayOrderInYear(DaysOrder, Year);
    cout << "Date for [" << DaysOrder << "] is: ";
    cout << stDate.stDay << "/" << stDate.stMonth << "/" << stDate.stYear << "\n";

    return 0;
}