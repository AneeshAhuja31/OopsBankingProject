#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<ctime>
#include<iomanip>

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

    //function to get time
    string getCurrentTime() {
        time_t now = time(0);  // Get current time
        tm *local_time = localtime(&now);  // Convert to local time

        // Format and return the time in "HH:MM:SS" format
        char time[100];  // Buffer to hold the formatted time
        strftime(time, sizeof(time), "%H:%M:%S", local_time);  // Format time
        return string(time);  // Convert the character array to a string
    }

    //function to get date
    string getCurrentDate() {
        time_t now = time(0);  // Get current time
        tm *local_time = localtime(&now);  // Convert to local time

        // Format and return the date in "Day Month Date Year" format
        char date[100];  // Buffer to hold the formatted date
        strftime(date, sizeof(date), "%a %b %d %Y", local_time);  // Format date
        return string(date);  // Convert the character array to a string
    }

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
            adminFile << left << setw(10) << id            // Account ID
                    << setw(20) << name                 // Account Holder Name
                    << setw(20) << fathername << endl;  // Father's Name
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
            userFile << "PIN: " << pin << endl;
            
            userFile << "-----------------------------------------------------------------------------------" << endl;
            userFile << "Transaction Record :" << endl;
            userFile << left << setw(20) << "Date"                
                            << setw(20) << "Time"                
                            << setw(20) << "Transaction Type"    
                            << setw(20) << "Amount"              
                            << setw(20) << "Current Balance"     
                            << endl;
            userFile.close();
            cout << "Dedicated file created: " << userFileName << endl;
        }
        else {
            cout << "Error: Could not create user file " << userFileName << endl;
        }
    }

    // Function to edit User File and update balance with transaction history
    void updateUserFile(string transactionType, int amount) {
        string userFileName = USER_ACCOUNT_DIR + "id" + to_string(id) + ".txt";
        ifstream userFile(userFileName);
        string line;
        stringstream updatedContent;
        bool balanceUpdated = false;

        if (userFile.is_open()) {
            // Read each line of the file
            while (getline(userFile, line)) {
                // When we reach the balance line (4th line), update the balance
                if (!balanceUpdated && line.find("Balance:") != string::npos) {
                    updatedContent << line.substr(0, line.find(":") + 2) << to_string(balance) << endl;
                    balanceUpdated = true;
                } else {
                    updatedContent << line << endl;
                }
            }
            userFile.close();

            // Write the transaction to the file
            ofstream userFileOut(userFileName, ios::trunc);  // Truncate the file and overwrite with updated content
            if (userFileOut.is_open()) {
                // Write all updated content back to file
                userFileOut << updatedContent.str();
                
                // Now log the transaction in the transaction history
                userFileOut << left << setw(20) << getCurrentDate()        
                            << setw(20) << getCurrentTime()               
                            << setw(20) << transactionType                
                            << setw(20) << amount                         
                            << setw(20) << balance                        
                            << endl;
                userFileOut.close();
            } 
            else {
                cout << "Error: Could not update user file " << userFileName << endl;
            }
        } 
        else {
            cout << "Error: Could not open user file " << userFileName << endl;
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
        string userFileName = USER_ACCOUNT_DIR + "id" + to_string(id) + ".txt";
        ifstream userFile(userFileName);
        if (!userFile.is_open()) {
            cout << "Error: Could not open user file " << userFileName << endl;
            return false;
        }
        string line;
        int filePin = -1;
        while(getline(userFile,line)){
            if(line.find("PIN:")!=string::npos){
                stringstream ss(line.substr(line.find(":")+1));
                ss >> filePin;
                break;
            }
        }
        userFile.close();
        //check and return boolean
        if (filePin == enteredPin) {
            return true;
        } else {
            cout << "Incorrect PIN.\n";
            return false;
        }
    }
    //Deposit function
    void deposit() {
        int amount;
        int enteredPin;

        cout << "Enter PIN to proceed with deposit: ";
        cin >> enteredPin;

        if (enteredPin < 1000 || enteredPin > 9999) {
            cout << "Invalid PIN. It must be a 4-digit number.\n";
            return;
        }

        if (checkPassword(enteredPin)) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            if (amount > 0) {
                balance += amount;
                cout << "Deposited: " << amount << endl;
                cout << "New Balance: " << balance << endl;

                // Update user's account file and transaction history
                updateUserFile("Deposit", amount);
            } else {
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

        if (enteredPin < 1000 || enteredPin > 9999) {
            cout << "Invalid PIN. It must be a 4-digit number.\n";
            return;
        }

        if (checkPassword(enteredPin)) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            
            if (amount > 0 && amount <= balance) {
                balance -= amount;
                cout << "Withdrawn: " << amount << endl;
                cout << "New Balance: " << balance << endl;

                // Update user's account file and transaction history
                updateUserFile("Withdraw", amount);
            } else if (amount > balance) {
                cout << "Insufficient balance for this withdrawal.\n";
            } else {
                cout << "Withdrawal amount must be positive.\n";
            }
        } else {
            cout << "Incorrect Pin. Transaction denied.\n";
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

