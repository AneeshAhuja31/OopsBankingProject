#include"Account.h"
using namespace std;

class SecuredAccount : public Account {
    private:
    int PinTemp;
    int action;
    string modifiedName;
    string modifiedFatherName;

    public:
    SecuredAccount(): PinTemp(0){}

    //Transaction History Function
    void transactionHistory(){
        //asking pin
        cout<<"\nEnter pin to get your transaction history : ";
        cin>>PinTemp;
        cout << endl;
        if (PinTemp < 1000 || PinTemp > 9999) {
            cout << "Invalid PIN. It must be a 4-digit number.\n";
            return; // Exit if the entered PIN is not valid
        }

        //Opening file to print
        if(checkPassword(PinTemp)){
            string userFileName = USER_ACCOUNT_DIR + "id" + to_string(id) +".txt";
            ifstream userFile(userFileName);
            string line;
            int currentLine = 1;

            if (userFile.is_open()){
                while (getline(userFile, line)) {
                    if (currentLine >= 7) {
                        cout << line << endl;  // Print the history
                    }
                    currentLine++;
                }
                userFile.close();
            }else{
                cout << "Error: Could not open your file ." << endl;
            }
        } else{
            cout<<"\nIncorrect PIN.\n";
        }
    }

    //balance-Inquiry Function
    void balanceInquiry(){

        //asking pin
        cout<<"\nEnter pin to check balance : ";
        cin>>PinTemp;

        if (PinTemp < 1000 || PinTemp > 9999) {
            cout << "Invalid PIN. It must be a 4-digit number.\n";
            return; // Exit if the entered PIN is not valid
        }

        if(checkPassword(PinTemp)){
            cout<<endl<<"Your current balnce is "<<balance<<".";
        } else{
            cout<<"\nIncorrect PIN.\n";
        }


    }

};