#include"header.h"
int main() {
    Account account;
    int choice, accountId;

    while (true) {
        cout << "\nBanking System Menu:\n";
        cout << "1. Create New Account\n";
        cout << "2. Select Account by ID\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Input validation for menu choice
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                account.accountCreation();
                break;

            case 2:
                cout << "Enter Account ID to select: ";
                cin >> accountId;

                // Input validation for account ID
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid Account ID. Please enter a number.\n";
                    break;
                }

                if (account.loadAccountFromFile(accountId)) {
                    int action;
                    while (true) {
                        cout << "\nSelect Action:\n";
                        cout << "1. Deposit\n";
                        cout << "2. Withdraw\n";
                        cout << "3. Display Account Info\n";
                        cout << "4. Go Back to Main Menu\n";
                        cout << "Enter your choice: ";
                        cin >> action;

                        // Input validation for action choice
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid input. Please enter a number.\n";
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
                                account.displayAccountInfo();
                                break;
                            case 4:
                                cout << "Going back to the main menu...\n";
                                break;
                            default:
                                cout << "Invalid choice. Try again.\n";
                        }
                        if (action == 4) break;  // Break out of the loop to return to the main menu
                    }
                }
                break;

            case 3:
                cout << "Exiting program. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}