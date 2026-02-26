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

bool IsDate1EqualDate2(stDate Date1, stDate Date2)
{
    if (Date1.Year != Date2.Year)
    {
        return false;
    }
    if (Date1.Month != Date2.Month)
    {
        return false;
    }
    return Date1.Day == Date2.Day;
}

int main()
{
    stDate Date1 = ReadFullDate();
    stDate Date2 = ReadFullDate();

    if (IsDate1EqualDate2(Date1, Date2))
    {
        cout << "Yes, Date1 is Equal to Date2.\n";
    }
    else
    {
        cout << "No, Date1 is NOT Equal to Date2.\n";
    }

    return 0;
}