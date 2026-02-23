#include <iostream>
#include <limits>
using namespace std;

bool IsLeapYear(int year)
{
    // if (year % 400 == 0)
    // {
    //     return true;
    // }
    // if (year % 4 == 0 && year % 100 != 0)
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}
int main()
{
    int year;
    cout << "Enter a Year\n";
    cin >> year;

    if (IsLeapYear(year))
    {
        cout << "Yes, Year [" << year << "] is a leap year.\n";
    }
    else
    {
        cout << "No, Year [" << year << "] is NOT a leap\n";
    }

    return 0;
}