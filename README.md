# C++ Banking System

## Overview

This is a college project. The Admin Pin is 1012 (if you want to access admin features) and if you want to access data or make a transaction in any of our prexisting accounts, please open the .txt file of the repected user in the User_Accounts folder.

## Features

- **Account Creation**: Allows users to create a new account by entering personal details, account ID, PIN, and initial balance.
- **Password Protection**: A 4-digit PIN is required for performing deposits and withdrawals.
- **Deposit and Withdrawal**: Users can deposit money into their account or withdraw funds, with sufficient balance and PIN validation.
- **Account Information Display**: Users can view their account details including balance.
- **Account File System**: User details are saved in the `administrator.txt` file for general account information, while each user has a dedicated file in the `User_Accounts/` folder for detailed account data.
- **Search By ID**: Admins can search for specifc users by their ID.
- **Account Deletion**: Allows admin to delete an account by it's id.
- **Recorded Transcations**: Every Transactions you make while depositing or withdrawing are recorded and saved in the respected user file.

## Contributors

1. Aneesh Ahuja
2. Aakash Sharma
3. Divyansh Tulsiani

## How to Clone the Repository

To get a local copy of this project, follow these steps:

1. **Install Git**: Ensure Git is installed on your computer. [Download Git](https://git-scm.com/downloads) if needed.
2. **Clone the Repository**:
   - Open a terminal or command prompt.
   - Run the following command to clone the repository:

     ```bash
     git clone https://github.com/AneeshAhuja31/OopsBankingProject.git
     ```

3. **Navigate to the Project Directory**:
   - After cloning, navigate to the project directory with:

     ```bash
     cd OopsBankingProject
     ```

You now have a local copy of the project, which you can open in a code editor or build as instructed in the overview.


## Directory Structure

OopsBankingProject/ 
|
├── BANKINGSYSTEMPROJECT/ 
│ 
├── administrator.txt # Stores general account information 
│ 
├── User_Accounts/ # Folder for individual account files 
│ 
├── Account.h # Header file with base class for the program 
│ 
├── SecuredAccount.h # Header file with derived class for the program  
│ 
├── AdminAccount.h # Header file with derived class for the program
│ 
├── main.cpp # C++ source code for the program


