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

    if (IsOverlapPeriods(Period1Start, Period1End, Period2Start, Period2End))
        cout << "\nYes, Periods Overlap\n";
    else
        cout << "\nNo, Periods do not Overlap\n";
    return 0;
}