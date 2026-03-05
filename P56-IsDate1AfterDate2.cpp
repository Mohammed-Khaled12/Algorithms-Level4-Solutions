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

int main()
{
    cout << "Enter Date 1: \n";
    stDate Date1 = ReadFullDate();
    cout << "\nEnter Date 2: \n";
    stDate Date2 = ReadFullDate();

    if (IsDate1AfterDate2(Date1, Date2))
    {
        cout << "Yes Date 1 is After Date 2. \n";
    }
    else
    {
        cout << "No Date 1 is not After Date 2. \n";
    }

    return 0;
}