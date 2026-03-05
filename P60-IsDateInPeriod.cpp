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

bool IsDateInPeriod(stDate Period1Start, stDate Period1End, stDate Date)
{
    if (IsDate1BeforeDate2(Date, Period1Start))
    {
        return false;
    }
    if (IsDate1AfterDate2(Date, Period1End))
    {
        return false;
    }
    return true;
}

int main()
{
    cout << "\nEnter Period 1 Start Date:\n";
    stDate Period1Start = ReadFullDate();
    cout << "\nEnter Period 1 End Date:\n";
    stDate Period1End = ReadFullDate();

    cout << "\nPLease Enter Date to Check: \n";
    stDate Date = ReadFullDate();

    if (IsDateInPeriod(Period1Start, Period1End, Date))
    {
        cout << "Yes, Date is within period\n";
    }
    else
    {
        cout << "No, Date is NOT within period\n";
    }

    return 0;
}