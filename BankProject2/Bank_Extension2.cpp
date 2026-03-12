#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;

const string ClientsFileName = "bank.txt";
const string UserFileName = "User.txt";

enum enMenuNumber
{
    Show = 1,
    Add,
    Delete,
    Update,
    Find,
    Transaction,
    MangeUsers,
    Logout
};

enum enTransactionsMenuNumber
{
    Deposite = 1,
    Withdraw,
    TotalBalances,
    MainMenu,
};

enum enUserMangeMenuNumber
{
    List_U = 1,
    Add_U,
    Delete_U,
    Update_U,
    Find_U,
    MainMenu_U
};

enum enPermissions
{
    ShowPermission = 1,
    AddPermission = 2,
    DeletePermission = 4,
    UpdatePermission = 8,
    FindPermission = 16,
    TransactionPermission = 32,
    MangeUsersPermission = 64,
    allPermissions = -1
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

struct stUser
{
    string Name;
    string Password;
    short Permission;
};

enMenuNumber Start();
void Login();
bool CheckAccessPermission(enPermissions Permission);
void UsersManger(vector<stUser> &vUser);
stUser CurrentUser;

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

void GoBackToManageUsersMenu()
{
    cout << "\n\nPress Enter to go back To Manage Users Menu...";
    cin.get();
}

void ShowMainMenu()
{
    cout << "======================================================\n";
    cout << "\t\t Main Menu Screen \n";
    cout << "======================================================\n";
    cout << "\t [1] Show Client List.\n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transaction.\n";
    cout << "\t [7] Mange Users.\n";
    cout << "\t [8] Logout.\n";
    cout << "======================================================\n";
    cout << "Choose What do you Want to do? [1 to 8]? \n";
}

void ShowTransactionMenu()
{
    cout << "======================================================\n";
    cout << "\t\t Transaction Menu Screen \n";
    cout << "======================================================\n";
    cout << "\t [1] Deposite.\n";
    cout << "\t [2] Withdraw.\n";
    cout << "\t [3] Total Balances.\n";
    cout << "\t [4] Main Menu.\n";
    cout << "======================================================\n";
    cout << "Choose What do you Want to do? [1 to 4]? \n";
}

void AccessDeniedScreen()
{
    system("clear");
    cout << "-------------------------------------------\n";
    cout << "Access Denied! \n";
    cout << "You don't have permission to do this.\n";
    cout << "Please contact your Admin.\n";
    cout << "-------------------------------------------\n";
}

void ShowMangeUserMenu()
{
    cout << "======================================================\n";
    cout << "\t\t Manage User Menu Screen \n";
    cout << "======================================================\n";
    cout << "\t [1] List Users.\n";
    cout << "\t [2] Add New User.\n";
    cout << "\t [3] Delete User.\n";
    cout << "\t [4] Update User.\n";
    cout << "\t [5] Find User.\n";
    cout << "\t [6] Main Menu.\n";
    cout << "======================================================\n";
    cout << "Choose What do you Want to do? [1 to 6]? \n";
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

stUser ConvertLinetoRecordUser(string Line, string Seperator = "#//#")
{
    stUser User;

    vector<string> vUserData = split(Line, Seperator);

    User.Name = vUserData.at(0);
    User.Password = vUserData.at(1);
    User.Permission = stoi(vUserData.at(2));

    return User;
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

string ConvertRecordToLine(stUser User, string Seperator = "#//#")
{
    string UserRecord = "";

    UserRecord += User.Name + Seperator;
    UserRecord += User.Password + Seperator;
    UserRecord += to_string(User.Permission);

    return UserRecord;
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

vector<stUser> LoadUsersDataFromFile()
{
    vector<stUser> vUser;
    fstream MyFile;
    MyFile.open(UserFileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stUser user;
        while (getline(MyFile, Line))
        {
            user = ConvertLinetoRecordUser(Line);
            vUser.push_back(user);
        }
        MyFile.close();
    }
    return vUser;
}

// Printing Section
void PrintClientRecord(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(const vector<stClient> &vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";
    for (stClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";
}

void PrintTotalBalancesClientRecord(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    // cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    // cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintTotalBalances(const vector<stClient> &vClients)
{
    double sum = 0;
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";
    cout << "| " << left << setw(15) << "Accout Number";
    // cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    // cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";
    for (stClient Client : vClients)
    {
        PrintTotalBalancesClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";
    for (const stClient &i : vClients)
    {
        sum += i.AccountBalance;
    }

    cout << "\t\t\t Total Balances = " << sum << "\n";
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccount Number: " << Client.AccountNumber;
    cout << "\nPin Code      : " << Client.PinCode;
    cout << "\nName          : " << Client.Name;
    cout << "\nPhone         : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

void PrintUserRecord(stUser User)
{
    cout << "| " << setw(15) << left << User.Name;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permission;
}

void PrintAllUsersData(const vector<stUser> &vUser)
{
    cout << "\n\t\t\t\t\tUser List (" << vUser.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";
    for (stUser User : vUser)
    {
        PrintUserRecord(User);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n\n";
}

void PrintUserCard(stUser User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUser Name: " << User.Name;
    cout << "\nPassword      : " << User.Password;
    cout << "\nPermission          : " << User.Permission;
    cout << "\n-----------------------------------\n";
}

// Searching Section
bool IsClientExists(const vector<stClient> &vClients, string TargetAccountNum)
{
    for (const stClient &i : vClients)
    {
        if (i.AccountNumber == TargetAccountNum)
        {
            return true;
        }
    }
    return false;
}

bool FindClientByAccountNumber(string AccountNumber, const vector<stClient> &vClients, stClient &Client)
{
    for (const stClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void FindClient(const vector<stClient> &vClients)
{
    string TargetNum;
    stClient Client;
    cout << "Please Enter Account Number To Search For? \n";
    getline(cin, TargetNum);

    if (FindClientByAccountNumber(TargetNum, vClients, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "Not Found\n";
    }
}

bool IsUserExists(const vector<stUser> &vUser, string TargetUserName, string TargetPassword)
{
    for (const stUser &i : vUser)
    {
        if (i.Name == TargetUserName && i.Password == TargetPassword)
        {
            CurrentUser.Name = i.Name;
            CurrentUser.Password = i.Password;
            CurrentUser.Permission = i.Permission;
            return true;
        }
    }
    return false;
}

bool IsUserExists(const vector<stUser> &vUser, string TargetUserName)
{
    for (const stUser &i : vUser)
    {
        if (i.Name == TargetUserName)
        {
            return true;
        }
    }
    return false;
}

bool IsUserExists(const vector<stUser> &vUser, string TargetUserName, stUser &User)
{
    for (const stUser &U : vUser)
    {
        if (U.Name == TargetUserName)
        {
            User = U;
            return true;
        }
    }
    return false;
}

void FindUser(const vector<stUser> &vUser)
{
    string TargetName;
    stUser User;
    cout << "Please Enter User Name To Search For? \n";
    getline(cin, TargetName);

    if (IsUserExists(vUser, TargetName, User))
    {
        PrintUserCard(User);
    }
    else
    {
        cout << "Not Found\n";
    }
}

// Adding Section
stClient ReadNewClient()
{
    stClient newClient;
    vector<stClient> vClients = LoadCleintsDataFromFile();
    do
    {
        cout << "Enter Account Number?\n";
        getline(cin, newClient.AccountNumber);
        if (IsClientExists(vClients, newClient.AccountNumber))
        {
            cout << "Client with Account Number (" << newClient.AccountNumber << ") already Exists, Enter Another Number\n";
        }
    } while (IsClientExists(vClients, newClient.AccountNumber));

    cout << "Enter pinCode?\n";
    getline(cin, newClient.PinCode);

    cout << "Enter Name?\n";
    getline(cin, newClient.Name);

    cout << "Enter phone?\n";
    getline(cin, newClient.Phone);

    cout << "Enter Account Balance?\n";
    cin >> newClient.AccountBalance;

    cin.ignore(1000, '\n');

    return newClient;
}

void AddDataLineToFile(string dataLine)
{
    fstream MyFile;

    MyFile.open(ClientsFileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << dataLine << "\n";
        MyFile.close();
    }
}

void addNewClient()
{
    cout << "\nPlease Enter Client Data: \n\n";
    stClient Client = ReadNewClient();

    string dataLine = ConvertRecordToLine(Client);

    AddDataLineToFile(dataLine);
}

void addClients()
{
    char addMore;
    do
    {
        addNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> addMore;
        cin.ignore(1000, '\n');
    } while (toupper(addMore) == 'Y');
}

short ReadPermissionsToSet()
{
    short Permission = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n? \n";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give access to : \n";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermissions::ShowPermission;
    }
    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermissions::AddPermission;
    }
    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermissions::DeletePermission;
    }
    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermissions::UpdatePermission;
    }
    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermissions::FindPermission;
    }
    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermissions::TransactionPermission;
    }
    cout << "\nMange Users? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermissions::MangeUsersPermission;
    }
    return Permission;
}

stUser ReadNewUser()
{
    stUser newUser;
    vector<stUser> vUser = LoadUsersDataFromFile();
    do
    {
        cout << "Enter User Name?\n";
        getline(cin, newUser.Name);
        if (IsUserExists(vUser, newUser.Name))
        {
            cout << "User with Name (" << newUser.Name << ") already Exists, Enter Another User Name\n";
        }
    } while (IsUserExists(vUser, newUser.Name));

    cout << "Enter Password?\n";
    getline(cin, newUser.Password);

    newUser.Permission = ReadPermissionsToSet();

    return newUser;
}

void AddDataLineToFileUser(string dataLine)
{
    fstream MyFile;

    MyFile.open(UserFileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << dataLine << "\n";
        MyFile.close();
    }
}

void addNewUser()
{
    cout << "\nPlease Enter User Data: \n\n";
    stUser User = ReadNewUser();

    string dataLine = ConvertRecordToLine(User);

    AddDataLineToFileUser(dataLine);
}

void addUsers()
{
    char addMore;
    do
    {
        addNewUser();
        cout << "\n User Added Successfully, do you want to add more Users? Y/N? ";
        cin >> addMore;
        cin.ignore(1000, '\n');
    } while (toupper(addMore) == 'Y');
}

// Delete Section
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

void DeleteClientRecord(vector<stClient> &vClients, stClient ClientToDelete)
{
    for (int i = 0; i < vClients.size(); i++)
    {
        if (ClientToDelete.AccountNumber == vClients[i].AccountNumber)
        {
            vClients.erase(vClients.begin() + i);
            SaveClientsDataToFile(vClients);
            cout << "Deleted Succesfully\n";
            break;
        }
    }
}

void DeleteClient(vector<stClient> &vClients)
{
    string TargetNum;
    stClient Client;
    do
    {
        cout << "Enter Account Number To Delete?\n";
        getline(cin, TargetNum);
    } while (!IsClientExists(vClients, TargetNum));

    FindClientByAccountNumber(TargetNum, vClients, Client);
    PrintClientCard(Client);
    if (ConfirmOP("Delete", "Client"))
    {
        DeleteClientRecord(vClients, Client);
    }
}

void SaveUserDataToFile(const vector<stUser> &vUser)
{
    fstream MyFile;
    MyFile.open(UserFileName, ios::out);

    if (MyFile.is_open())
    {
        for (const stUser &C : vUser)
        {
            MyFile << ConvertRecordToLine(C) << endl;
        }
        MyFile.close();
    }
}

void DeleteUserRecord(vector<stUser> &vUser, stUser UserToDelete)
{
    for (int i = 0; i < vUser.size(); i++)
    {
        if (UserToDelete.Name == vUser[i].Name)
        {
            vUser.erase(vUser.begin() + i);
            SaveUserDataToFile(vUser);
            cout << "Deleted Succesfully\n";
            break;
        }
    }
}

void DeleteUser(vector<stUser> &vUser)
{
    string TargetName;
    stUser User;
    do
    {
        cout << "Enter User Name To Delete?\n";
        getline(cin, TargetName);
        if (TargetName == CurrentUser.Name)
        {
            cout << "\nCannot delete the currently logged-in user!\n";
            return;
        }
    } while (!IsUserExists(vUser, TargetName));

    IsUserExists(vUser, TargetName, User);
    PrintUserCard(User);
    if (ConfirmOP("Delete", "User"))
    {
        DeleteUserRecord(vUser, User);
    }
}

// Update Section
void UpdateClientRecord(vector<stClient> &vClients, stClient &ClientToUpdate)
{
    cout << "\n\nEnter PinCode? ";
    getline(cin, ClientToUpdate.PinCode);

    cout << "Enter Name? ";
    getline(cin, ClientToUpdate.Name);

    cout << "Enter Phone? ";
    getline(cin, ClientToUpdate.Phone);

    cout << "Enter AccountBalance? ";
    cin >> ClientToUpdate.AccountBalance;
    cin.ignore(1000, '\n');
}

void UpdateClientByAccountNumber(vector<stClient> &vClients)
{
    string TargetNum;
    stClient Client;
    do
    {
        cout << "Enter Account Number To Update?\n";
        getline(cin, TargetNum);
    } while (!IsClientExists(vClients, TargetNum));
    FindClientByAccountNumber(TargetNum, vClients, Client);
    PrintClientCard(Client);
    if (ConfirmOP("Update", "Client"))
    {
        UpdateClientRecord(vClients, Client);
        for (stClient &C : vClients)
        {
            if (C.AccountNumber == TargetNum)
            {
                C = Client;
                break;
            }
        }
        SaveClientsDataToFile(vClients);
    }
}

void UpdateUserRecord(vector<stUser> &vUsers, stUser &UserToUpdate)
{
    cout << "\n\nEnter Password? ";
    getline(cin, UserToUpdate.Password);
    UserToUpdate.Permission = ReadPermissionsToSet();
}

void UpdateUserByUserName(vector<stUser> &vUser)
{
    string TargetName;
    stUser User;
    do
    {
        cout << "Enter User Name To Update?\n";
        getline(cin, TargetName);
    } while (!IsUserExists(vUser, TargetName));
    IsUserExists(vUser, TargetName, User);
    PrintUserCard(User);
    if (ConfirmOP("Update", "User"))
    {
        UpdateUserRecord(vUser, User);
        for (stUser &U : vUser)
        {
            if (U.Name == TargetName)
            {
                U = User;
                break;
            }
        }
        SaveUserDataToFile(vUser);
    }
}

// Deposite
void DepositeFunc(vector<stClient> &vClients)
{
    stClient Client;
    string TargetNum;
    double Amount;
    cout << "Enter Account Number? \n";
    getline(cin, TargetNum);
    while (!FindClientByAccountNumber(TargetNum, vClients, Client))
    {
        cout << "Wrong Number, Please Enter Account Number?\n";
        getline(cin, TargetNum);
    }
    PrintClientCard(Client);

    cout << "Please Enter Deposite Amount?\n";
    cin >> Amount;
    Client.AccountBalance += Amount;
    if (ConfirmOP("Deposite", "Client"))
    {
        for (stClient &i : vClients)
        {
            if (i.AccountNumber == TargetNum)
            {
                i = Client;
                SaveClientsDataToFile(vClients);
                cout << "\n\nDone Successfully. New balance is: " << Client.AccountBalance;
            }
        }
    }
}

// Withdraw
void WithdrawFunc(vector<stClient> &vClients)
{
    stClient Client;
    string TargetNum;
    double Amount;
    cout << "Enter Account Number? \n";
    getline(cin, TargetNum);
    while (!FindClientByAccountNumber(TargetNum, vClients, Client))
    {
        cout << "Wrong Number, Please Enter Account Number?\n";
        getline(cin, TargetNum);
    }
    PrintClientCard(Client);

    cout << "\nYour Current Balance is: " << Client.AccountBalance << endl;
    do
    {
        cout << "Please Enter Withdraw Amount? ";
        cin >> Amount;
        if (Amount > Client.AccountBalance)
            cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
    } while (Amount > Client.AccountBalance);

    Client.AccountBalance -= Amount;
    if (ConfirmOP("Withdraw", "Client"))
    {
        for (stClient &i : vClients)
        {
            if (i.AccountNumber == TargetNum)
            {
                i = Client;
                SaveClientsDataToFile(vClients);
                cout << "\n\nDone Successfully. New balance is: " << Client.AccountBalance;
            }
        }
    }
}

// Transactions Manger
void TransactionsManger(vector<stClient> &vClients)
{
    enTransactionsMenuNumber TransNum;
    do
    {
        system("clear");
        ShowTransactionMenu();
        short TransChoice;
        cin >> TransChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        TransNum = static_cast<enTransactionsMenuNumber>(TransChoice);
        switch (TransNum)
        {
        case enTransactionsMenuNumber::Deposite:
            system("clear");
            DepositeFunc(vClients);
            GoBackToMainMenu();
            break;
        case enTransactionsMenuNumber::Withdraw:
            system("clear");
            WithdrawFunc(vClients);
            GoBackToMainMenu();
            break;
        case enTransactionsMenuNumber::TotalBalances:
            system("clear");
            PrintTotalBalances(vClients);
            GoBackToMainMenu();
            break;
        case enTransactionsMenuNumber::MainMenu:
            break;
        default:
            break;
        }
    } while (TransNum != enTransactionsMenuNumber::MainMenu);
}
// Start And End
void EndScreen()
{
    system("clear");
    cout << "======================================================\n";
    cout << "\t Program Ends :-)\n";
    cout << "======================================================\n\n";
}

enMenuNumber Start()
{
    short Choice;
    ShowMainMenu();
    cin >> Choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    enMenuNumber MenuOption = static_cast<enMenuNumber>(Choice);
    vector<stClient> vClients = LoadCleintsDataFromFile();
    vector<stUser> vUser = LoadUsersDataFromFile();

    switch (MenuOption)
    {
    case enMenuNumber::Show:
        if (!CheckAccessPermission(enPermissions::ShowPermission))
        {
            AccessDeniedScreen();
            GoBackToMainMenu();
            break;
        }
        system("clear");
        cout << "--- Show Client List Screen ---\n";
        PrintAllClientsData(vClients);
        GoBackToMainMenu();
        break;
    case enMenuNumber::Add:
        if (!CheckAccessPermission(enPermissions::AddPermission))
        {
            AccessDeniedScreen();
            GoBackToMainMenu();
            break;
        }
        system("clear");
        cout << "--- Add Client Screen ---\n";
        addClients();
        GoBackToMainMenu();
        break;
    case enMenuNumber::Delete:
        if (!CheckAccessPermission(enPermissions::DeletePermission))
        {
            AccessDeniedScreen();
            GoBackToMainMenu();
            break;
        }
        system("clear");
        cout << "--- Delete Client Screen ---\n";
        DeleteClient(vClients);
        GoBackToMainMenu();
        break;
    case enMenuNumber::Update:
        if (!CheckAccessPermission(enPermissions::UpdatePermission))
        {
            AccessDeniedScreen();
            GoBackToMainMenu();
            break;
        }
        system("clear");
        cout << "--- Update Client Screen ---\n";
        UpdateClientByAccountNumber(vClients);
        GoBackToMainMenu();
        break;
    case enMenuNumber::Find:
        if (!CheckAccessPermission(enPermissions::FindPermission))
        {
            AccessDeniedScreen();
            GoBackToMainMenu();
            break;
        }
        system("clear");
        cout << "--- Find Client Screen ---\n";
        FindClient(vClients);
        GoBackToMainMenu();
        break;
    case enMenuNumber::Transaction:
        if (!CheckAccessPermission(enPermissions::TransactionPermission))
        {
            AccessDeniedScreen();
            GoBackToMainMenu();
            break;
        }
        system("clear");
        TransactionsManger(vClients);
        break;
    case enMenuNumber::MangeUsers:
        if (!CheckAccessPermission(enPermissions::MangeUsersPermission))
        {
            AccessDeniedScreen();
            GoBackToMainMenu();
            break;
        }
        system("clear");
        UsersManger(vUser);
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

// Users
void Login()
{
    string Username;
    string UserPassword;

    while (true)
    {
        vector<stUser> vUser = LoadUsersDataFromFile();
        system("clear");
        cout << "======================================================\n";
        cout << "\t\t Login Screen \n";
        cout << "======================================================\n";

        cout << "Enter Username? \n";
        getline(cin, Username);
        cout << "Enter Password? \n";
        getline(cin, UserPassword);

        if (IsUserExists(vUser, Username, UserPassword))
        {
            system("clear");
            StartProgram();
        }
        else
        {
            system("clear");
            cout << "Invalid UserName/Password \n";
            cout << "Press Enter to try again...";
            cin.get();
        }
    }
}

bool CheckAccessPermission(enPermissions Permission)
{
    if (CurrentUser.Permission == enPermissions::allPermissions)
    {
        return true;
    }
    if ((Permission & CurrentUser.Permission) == Permission)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void UsersManger(vector<stUser> &vUser)
{
    enUserMangeMenuNumber MangeNum;
    do
    {
        system("clear");
        ShowMangeUserMenu();
        short MangeUserChoice;
        cin >> MangeUserChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        MangeNum = static_cast<enUserMangeMenuNumber>(MangeUserChoice);
        switch (MangeNum)
        {
        case enUserMangeMenuNumber::List_U:
            system("clear");
            PrintAllUsersData(vUser);
            GoBackToManageUsersMenu();
            break;
        case enUserMangeMenuNumber::Add_U:
            system("clear");
            addUsers();
            GoBackToManageUsersMenu();
            break;
        case enUserMangeMenuNumber::Delete_U:
            system("clear");
            cout << "--- Delete User Screen ---\n";
            DeleteUser(vUser);
            GoBackToManageUsersMenu();
            break;
        case enUserMangeMenuNumber::Update_U:
            system("clear");
            cout << "--- Update User Screen ---\n";
            UpdateUserByUserName(vUser);
            GoBackToManageUsersMenu();
            break;
        case enUserMangeMenuNumber::Find_U:
            system("clear");
            cout << "--- Find User Screen ---\n";
            FindUser(vUser);
            GoBackToManageUsersMenu();
            break;
        case enUserMangeMenuNumber::MainMenu_U:
            // system("clear");
            break;
        default:
            break;
        }
    } while (MangeNum != enUserMangeMenuNumber::MainMenu_U);
}

int main()
{
    Login();
    return 0;
}