#include<iostream>
#include<fstream>
#include<string>
#include<sstream> 

using namespace std;
// strings that store addresses of frequently accessed files and folders
const string ADMIN_FILE = "administrator.txt";
const string USER_ACCOUNT_DIR = "User_Accounts/";

class Account {
protected:
    //Member variables
    string name;
    string fathername;
    int id;
    int pin;
    int balance;

public:
    //Constructor
    Account() : id(0), pin(0), balance(0) {}

    // Function to create a new account and save it to "administrator.txt"
    void accountCreation() {
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Father's Name: ";
        getline(cin, fathername);

        cout << "Enter Account ID: ";
        cin >> id;
        cin.ignore();
        
        // Check if the account ID already exists
        string userFileName = USER_ACCOUNT_DIR + "id" + to_string(id) + ".txt";  //create a directory
        ifstream checkFile(userFileName);  //read only
        if (checkFile.is_open()) {
            cout << "Error: Account ID already exists.\n";
            checkFile.close();
            return; // Exit the function if the account already exists
        }

        // Ensure the PIN is a 4-digit number
        do {
            cout << "Set a 4-digit PIN: ";
            cin >> pin;
            cin.ignore();
            if (pin < 1000 || pin > 9999) {
                cout << "PIN must be a 4-digit number. Please enter again.\n";
            }
        } while (pin < 1000 || pin > 9999); // Repeat until a valid PIN is entered

        cout << "Enter Initial Balance: ";
        cin >> balance;
        cin.ignore();

        // Append account details in administrator.txt
        ofstream adminFile(ADMIN_FILE, ios::app); //append mode
        if (adminFile.is_open()) {
            adminFile << name << " " << fathername << " " << id << endl;
            adminFile.close();
            cout << "Account created successfully in administrator.txt.\n";
        }
        else {
            cout << "Error: Could not open administrator.txt.\n";
            return; // Exit if adminFile could not be opened
        }

        // Create a dedicated file for the user in User_Accounts folder
        ofstream userFile(userFileName);
        if (userFile.is_open()) {
            userFile << "Account Holder: " << name << endl;
            userFile << "Father's Name: " << fathername << endl;
            userFile << "Account ID: " << id << endl;
            userFile << "Balance: " << balance << endl;
            userFile.close();
            cout << "Dedicated file created: " << userFileName << endl;
        }
        else {
            cout << "Error: Could not create user file " << userFileName << endl;
        }
    }

    // Function to load account details from file
    bool loadAccountFromFile(int accountId) {
        string userFileName = USER_ACCOUNT_DIR + "id" + to_string(accountId) + ".txt";
        ifstream userFile(userFileName);
        if (userFile.is_open()) {
            string line; 

            // Read each line
            getline(userFile,line); //Account Holder's name
            size_t pos = line.find(":"); //pos stores position of ":"
            if(pos!=string::npos){  //npos is like NULL 
                //use stringstream to parse the line
                stringstream ss(line.substr(pos+2)); // Skip ": " and get the name
                getline(ss,name); // store ss in name
            }

            getline(userFile, line); // Father's Name
            pos = line.find(":");
            if (pos != string::npos) {
                stringstream ss(line.substr(pos+2));  // Skip ": " and get the father's name
                getline(ss,fathername);
            }

            getline(userFile, line); // Account ID
            pos = line.find(":");
            if (pos != string::npos) {
                stringstream(line.substr(pos + 2)) >> id;  // Skip ": " and convert to integer
            }
        
            getline(userFile, line); // Balance
            pos = line.find(":");
            if (pos != string::npos) {
                stringstream(line.substr(pos + 2)) >> balance;  // Skip ": " and convert to integer
            }

            userFile.close();
            return true;
        }
        else {
            cout << "Account with ID " << accountId << " does not exist.\n";
            return false;
        }
    }
    //Function for PIN verification
    bool checkPassword(int enteredPin) {
        return pin == enteredPin;
    }
    //Deposit function
    void deposit() {
        int amount;
        int enteredPin;

        cout << "Enter PIN to proceed with deposit: ";
        cin >> enteredPin;

        // Ensure the entered PIN is 4 digits
        if (enteredPin < 1000 || enteredPin > 9999) {
            cout << "Invalid PIN. It must be a 4-digit number.\n";
            return; // Exit if the entered PIN is not valid
        }
        //Check PIN
        if (checkPassword(enteredPin)) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            if (amount > 0) {
                balance += amount;
                cout << "Deposited: " << amount << endl;
                cout << "New Balance: " << balance << endl;
            }
            else {
                cout << "Deposit amount must be positive.\n";
            }
        }
        else {
            cout << "Incorrect Pin. Transaction denied.\n";
        }
    }
    //Function to withdraw
    void withdraw() {
        int amount;
        int enteredPin;

        cout << "Enter PIN to proceed with withdrawal: ";
        cin >> enteredPin;

        // Ensure the entered PIN is 4 digits
        if (enteredPin < 1000 || enteredPin > 9999) {
            cout << "Invalid PIN. It must be a 4-digit number.\n";
            return; // Exit if the entered PIN is not valid
        }

        if (checkPassword(enteredPin)) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;

            if (amount > 0 && amount <= balance) {
                balance -= amount;
                cout << "Withdrew: " << amount << endl;
                cout << "Remaining Balance: " << balance << endl;
            }
            else {
                cout << "Insufficient balance or invalid amount.\n";
            }
        }
        else {
            cout << "Incorrect PIN. Transaction denied.\n";
        }
    }
    //Function to display account information
    void displayAccountInfo() const {
        cout << "\nAccount Holder: " << name << endl;
        cout << "Father's Name: " << fathername << endl;
        cout << "Account ID: " << id << endl;
        cout << "Balance: " << balance << endl;
    }
};
