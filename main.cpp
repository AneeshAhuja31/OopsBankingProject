#include"AdminAccount.h"

int main() {
    AdminAccount account;
    int choice, accountId, adminPin;

    while (true) {
        mainmenu:
        cout << "\nBanking System Menu:\n";
        cout << "1. Create New Account\n";
        cout << "2. Select Account by ID\n";
        cout << "3. Sign in as admin\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Input validation for menu choice
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                account.accountCreation();
                break;

            case 2:
                cout << "\nEnter Account ID to select: ";
                cin >> accountId;

                // Input validation for account ID
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nInvalid Account ID. Please enter a number.\n";
                    break;
                }

                if (account.loadAccountFromFile(accountId)) {
                    int action;
                    while (true) {
                        cout << "\nSelect Action:\n";
                        cout << "1. Deposit\n";
                        cout << "2. Withdraw\n";
                        cout << "3. Check Balance\n";
                        cout << "4. Display Account Info\n";
                        cout << "5. Get Transaction History\n";
                        cout << "6. Go Back to Main Menu\n";
                        cout << "Enter your choice: ";
                        cin >> action;

                        // Input validation for action choice
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "\nInvalid input. Please enter a number.\n";
                            continue;
                        }

                        switch (action) {
                            case 1:
                                account.deposit();
                                break;
                            case 2:
                                account.withdraw();
                                break;
                            case 3:
                                account.balanceInquiry();
                                break;
                            case 4:
                                account.displayAccountInfo();
                                break;
                            case 5:
                                account.transactionHistory();
                                break;
                            case 6:
                                cout << "\nGoing back to the main menu...\n";
                                goto mainmenu;
                            default:
                                cout << "\nInvalid choice. Try again.\n";
                        }
                        if (action == 4) break;  // Break out of the loop to return to the main menu
                    }
                }
                break;

            case 3:
                cout << "\nEnter Admin PIN:-";
                cin>>adminPin;
                if(account.checkAdminPin(adminPin)){
                    int action;
                    while (true) {
                        cout << "\nSelect Action:\n";
                        cout << "1. Display all accounts\n";
                        cout << "2. Search an account\n";
                        cout << "3. Delete an account\n";
                        cout << "4. Go Back to Main Menu\n";
                        cout << "Enter your choice: ";
                        cin >> action;

                        switch (action) {
                            case 1:
                                account.displayAllAccounts();
                                break;
                            case 2:
                                account.accountSearch();
                                break;
                            case 3:
                                account.accountDeletion();
                                break;
                            case 4:
                                cout << "\nGoing back to the main menu...\n";
                                goto mainmenu;
                            default:
                                cout << "\nInvalid choice. Try again.\n";
                        }
                    }
                }else{
                    cout<<"\nIncorrect PIN!";
                    goto mainmenu;
                }
                return 0;
                
            case 4:
                cout << "\nExiting program. Goodbye!\n";
                return 0;

            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}