#include"SecuredAccount.h"
#include <cstdio>

class AdminAccount : public SecuredAccount{
    int ID;

    public:
    AdminAccount():ID(0){}
    //check Admin pin
    bool checkAdminPin(int adminPin){
        if(adminPin==1012){
            return true;
        }
        return false;
    }

    //display all account functoion
    void displayAllAccounts(){
        ifstream adminFile(ADMIN_FILE);
        string line;

        if (adminFile.is_open()){
            while (getline(adminFile, line)) {
                cout<< endl << line << endl;  // Print all accounts
            }
            adminFile.close();
        }
        else{
            cout << "\nError: Could not Print all account." << endl;
        }

    }

    //check and get ID function
    int searchID(const string& searchID) {
        ifstream adminFile(ADMIN_FILE);
        string line;

        if (adminFile.is_open()) {
            while (getline(adminFile, line)) {
                istringstream iss(line);
                string id, userName, fatherName;

                // Extract ID, USER NAME, and FATHER'S NAME from the line
                iss >> id >> userName >> fatherName;

                // Check if the extracted ID matches the searchID
                if (id == searchID) {
                    adminFile.close();  // Close the file
                    return stoi(id);   // Convert string ID to integer and return it
                }
            }
            adminFile.close();
        } 
        else {
            cout << "Error: Could not open the file to print all accounts." << endl;
        }

        return -1;  // Return -1 if no match is found
    }

    //serach account function
    void accountSearch(){
        cout<<"\nEnter the id of the account you want to search :";
        cin>>ID;

        if(searchID(to_string(ID))>0){
            cout<<"\nAccount found.";
            loadAccountFromFile(ID);
            displayAccountInfo();
        }
        else{
            cout<<"\nAccount not found.";
        }
    }

    //account Deletion Function
    void accountDeletion(){
        cout<<"\nEnter the id of the account you want to delete :";
        cin>>ID;
        //check if file not available
        if(searchID(to_string(ID))>0){
            string fileName=USER_ACCOUNT_DIR+"id"+to_string(ID)+".txt";
            if (remove(fileName.c_str()) == 0) {//personal file deleted

                ifstream adminFile(ADMIN_FILE);               // Original file
                ofstream tempFile("temp.txt");              // Temporary file
                string line;
                if (adminFile.is_open() && tempFile.is_open()) {
                    // Copy lines from inputFile to tempFile, excluding the target line
                    while (getline(adminFile, line)) {
                        istringstream iss(line);
                        string id;

                        // Extract the ID from the line
                        iss >> id;

                        // If the ID matches, skip copying this line
                        if (id == to_string(ID)) {
                            continue;
                        }

                        // Write the line to the temporary file
                        tempFile << line << endl;
                    }

                    adminFile.close();
                    tempFile.close();

                    remove(ADMIN_FILE.c_str());
                    rename("temp.txt",ADMIN_FILE.c_str());
                    
                    cout << "\nFile with id "<<ID << " deleted successfully." << endl;//file deleted
                } 
            }else {
                 cout << "\nError: Could not delete the file." << endl;
            }
        }else{
            cout<<"\nAccount not found.";
        }

    }
};