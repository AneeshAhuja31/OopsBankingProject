# C++ Banking System

## Overview

This is a college project. This C++ Banking System is a simple command-line program that allows users to perform basic banking operations such as creating an account, making deposits, withdrawals, recording and display transcation history of every account.We also have an Admin Menu which allows one to delete an account, display all accounts, etc. The program stores account details in text files, ensuring each user has a dedicated file for their account information. The system also includes a secure password handling feature for transactions.

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

## Directory Structure

OopsBankingProject/ ├── BANKINGSYSTEMPROJECT/ │ ├── administrator.txt # Stores general account information │ ├── User_Accounts/ # Folder for individual account files │ ├── Account.h # Header file with base class for the program │ ├── SecuredAccount.h # Header file with derived class for the program  │ ├── AdminAccount.h # Header file with derived class for the program│ ├── main.cpp # C++ source code for the program


