#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct stDate
{
    short Day;
    short Month;
    short Year;
};

vector<string> split(string S1, string delim)
{
    short pos = 0;
    string word;
    vector<string> vString;
    while ((pos = S1.find(delim)) != string::npos)
    {
        word = S1.substr(0, pos);
        if (word != "")
        {
            vString.push_back(word);
        }
        S1.erase(0, pos + delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

stDate StringToDate(string DateString)
{
    stDate Date;
    vector<string> vStringDate;
    vStringDate = split(DateString, "/");
    Date.Day = stoi(vStringDate.at(0));
    Date.Month = stoi(vStringDate.at(1));
    Date.Year = stoi(vStringDate.at(2));
    return Date;
}

string DateToString(stDate Date)
{
    return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
}

int main()
{
    string DateString;
    stDate Date;
    cout << "Please Date dd/mm/yyyy? \n";
    getline(cin, DateString);

    Date = StringToDate(DateString);

    cout << "Day: " << Date.Day << "\n";
    cout << "Month: " << Date.Month << "\n";
    cout << "Year: " << Date.Year << "\n";

    cout << "You Entered: " << DateToString(Date) << "\n";

    return 0;
}