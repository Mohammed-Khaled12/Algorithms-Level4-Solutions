#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;

const string ClientsFileName = "bank.txt";

enum enMenuNumber
{
    QuickWithdraw = 1,
    NormalWithdraw,
    Deposite,
    CheckBalance,
    Logout
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

enMenuNumber Start();
void Login();
stClient CurrentClient;

// Menu Design and Controll
void GoBackToMainMenu()
{
    // Using System Commends
    // cout << "\n\nPress any key to go back to Main Menu...";
    // cin.ignore(1000, '\n');
    // system("read -n 1 -s -p \"\"");

    // Using C++ , add <limits>
    cout << "\n\nPress Enter to go back To Main Menu...";
    cin.get();
}

void ShowMainMenu()
{
    cout << "======================================================\n";
    cout << "\t\t Main Menu Screen \n";
    cout << "======================================================\n";
    cout << "\t [1] Quick Withdraw.\n";
    cout << "\t [2] Normal Withdraw.\n";
    cout << "\t [3] Deposite.\n";
    cout << "\t [4] Check Balance.\n";
    cout << "\t [5] Logout.\n";
    cout << "======================================================\n";
    cout << "Choose What do you Want to do? [1 to 5]? \n";
}

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

stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    stClient Client;

    vector<string> vClientData = split(Line, Seperator);

    Client.AccountNumber = vClientData.at(0);
    Client.PinCode = vClientData.at(1);
    Client.Name = vClientData.at(2);
    Client.Phone = vClientData.at(3);
    Client.AccountBalance = stod(vClientData.at(4));

    return Client;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{
    string clientRecord = "";

    clientRecord += Client.AccountNumber + Seperator;
    clientRecord += Client.PinCode + Seperator;
    clientRecord += Client.Name + Seperator;
    clientRecord += Client.Phone + Seperator;
    clientRecord += to_string(Client.AccountBalance);

    return clientRecord;
}

vector<stClient> LoadCleintsDataFromFile()
{
    vector<stClient> vClients;
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

// Searching Section
bool IsClientExists(const vector<stClient> &vClients, string TargetAccountNum, string TargetPin)
{
    for (const stClient &C : vClients)
    {
        if (C.AccountNumber == TargetAccountNum && C.PinCode == TargetPin)
        {
            CurrentClient.Name = C.Name;
            CurrentClient.AccountNumber = C.AccountNumber;
            CurrentClient.PinCode = C.PinCode;
            CurrentClient.Phone = C.Phone;
            CurrentClient.AccountBalance = C.AccountBalance;
            return true;
        }
    }
    return false;
}

// Confirm Section
bool ConfirmOP(string OP, string UserOrClient)
{
    char Confirm;
    cout << "Are You Sure You Want To " << OP << " This " << UserOrClient << "? Y/N\n";
    cin >> Confirm;

    cin.ignore(1000, '\n');
    return (toupper(Confirm) == 'Y');
}

void SaveClientsDataToFile(const vector<stClient> &vClients)
{
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::out);

    if (MyFile.is_open())
    {
        for (const stClient &C : vClients)
        {
            MyFile << ConvertRecordToLine(C) << endl;
        }
        MyFile.close();
    }
}

// Deposite
void ShowDepositeMenu()
{
    cout << "======================================================\n";
    cout << "\t\t Deposite Screen \n";
    cout << "======================================================\n";
    cout << "Enter a Positive Deposite Amount? \n";
}

void DepositeFunc(vector<stClient> &vClients)
{
    double Amount;

    do
    {
        ShowDepositeMenu();
        cin >> Amount;
    } while (Amount <= 0);

    if (ConfirmOP("Deposite", "Client"))
    {
        CurrentClient.AccountBalance += Amount;

        for (stClient &i : vClients)
        {
            if (i.AccountNumber == CurrentClient.AccountNumber)
            {
                i = CurrentClient;
                break;
            }
        }
        SaveClientsDataToFile(vClients);
        cout << "\n\nDone Successfully. New balance is: " << CurrentClient.AccountBalance;
    }
}

// Withdraw
void ShowQuickWithdrawMenu()
{
    cout << "======================================================\n";
    cout << "\t\t Qucik Withdraw \n";
    cout << "======================================================\n";

    cout << "\t [1] 20" << setw(15) << "" << "[2] 50" << endl;
    cout << "\t [3] 100" << setw(14) << "" << "[4] 200" << endl;
    cout << "\t [5] 400" << setw(14) << "" << "[6] 600" << endl;
    cout << "\t [7] 800" << setw(14) << "" << "[8] 1000" << endl;
    cout << "\t [9] Exit" << endl;

    cout << "======================================================\n";

    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
    cout << "Choose what to withdraw from [1] to [8] ? ";
}

void QuickWithdrawFunc(vector<stClient> &vClients)
{
    short Choice;
    bool isWithdrawDone = false;
    double Amounts[] = {0, 20, 50, 100, 200, 400, 600, 800, 1000};

    while (!isWithdrawDone)
    {
        ShowQuickWithdrawMenu();
        cin >> Choice;

        if (Choice == 9)
            return;

        if (Choice < 1 || Choice > 8)
        {
            cout << "\nInvalid Choice! Press Enter to try again...";
            cin.ignore(100, '\n');
            cin.get();
        }
        else if (Amounts[Choice] > CurrentClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the balance! Press Enter to try again...";
            cin.ignore(100, '\n');
            cin.get();
        }
        else
        {
            isWithdrawDone = true;
        }
    }

    if (ConfirmOP("Withdraw", "Client"))
    {
        CurrentClient.AccountBalance -= Amounts[Choice];

        for (stClient &i : vClients)
        {
            if (i.AccountNumber == CurrentClient.AccountNumber)
            {
                i = CurrentClient;
                break;
            }
        }
        SaveClientsDataToFile(vClients);
        cout << "\n\nDone Successfully. New balance is: " << CurrentClient.AccountBalance;
    }
}

void ShowNormalWithdrawMenu()
{
    cout << "======================================================\n";
    cout << "\t\t Normal Withdraw \n";
    cout << "======================================================\n";
    cout << "Enter an Amount Multiple of 5's? \n";
}

void NormalWithdrawFunc(vector<stClient> &vClients)
{
    int amount = 0;

    while (true)
    {
        ShowNormalWithdrawMenu();
        cin >> amount;

        if (amount % 5 != 0)
        {
            cout << "\nError: Amount must be a multiple of 5!";
        }
        else if (amount > CurrentClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the balance! Your balance is: " << CurrentClient.AccountBalance;
        }
        else
        {
            break;
        }

        cout << "\nPress Enter to try again...";
        cin.ignore(100, '\n');
        cin.get();
    }

    if (ConfirmOP("Withdraw", "Client"))
    {
        CurrentClient.AccountBalance -= amount;

        for (stClient &i : vClients)
        {
            if (i.AccountNumber == CurrentClient.AccountNumber)
            {
                i = CurrentClient;
                break;
            }
        }
        SaveClientsDataToFile(vClients);
        cout << "\n\nDone Successfully. New balance is: " << CurrentClient.AccountBalance;
    }
}

void CheckBalanceFunc()
{
    cout << "======================================================\n";
    cout << "\t\t Check Balance \n";
    cout << "======================================================\n";

    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
}

// Start And End
enMenuNumber Start()
{
    short Choice;
    ShowMainMenu();
    cin >> Choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    enMenuNumber MenuOption = static_cast<enMenuNumber>(Choice);
    vector<stClient> vClients = LoadCleintsDataFromFile();

    switch (MenuOption)
    {
    case enMenuNumber::QuickWithdraw:
        system("clear");
        QuickWithdrawFunc(vClients);
        GoBackToMainMenu();
        break;
    case enMenuNumber::NormalWithdraw:
        system("clear");
        NormalWithdrawFunc(vClients);
        GoBackToMainMenu();
        break;
    case enMenuNumber::Deposite:
        system("clear");
        DepositeFunc(vClients);
        GoBackToMainMenu();
        break;
    case enMenuNumber::CheckBalance:
        system("clear");
        CheckBalanceFunc();
        GoBackToMainMenu();
        break;
    case enMenuNumber::Logout:
        system("clear");
        break;

    default:
        break;
    }
    return MenuOption;
}

void StartProgram()
{
    enMenuNumber Choice;
    while (Choice != enMenuNumber::Logout)
    {
        system("clear");
        Choice = Start();
    }
}

void Login()
{
    string ClientAccountNum;
    string ClientPin;

    while (true)
    {
        vector<stClient> vClient = LoadCleintsDataFromFile();
        system("clear");
        cout << "======================================================\n";
        cout << "\t\t Login Screen \n";
        cout << "======================================================\n";

        cout << "Enter Account Number? \n";
        getline(cin, ClientAccountNum);
        cout << "Enter Password? \n";
        getline(cin, ClientPin);

        if (IsClientExists(vClient, ClientAccountNum, ClientPin))
        {
            system("clear");
            StartProgram();
        }
        else
        {
            system("clear");
            cout << "Invalid Account Number/Password \n";
            cout << "Press Enter to try again...";
            cin.get();
        }
    }
}

int main()
{
    Login();
    return 0;
}