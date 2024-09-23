#include <cstdio>
#include <iostream>

using namespace std;

// Checks if user writes a character or string in an int input
bool cinIntCheck() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        return true;
    }

    return false;
}

// Pauses the terminal and asks the user for input to proceed
void continueToNext() {
    string next;
    cout << "\nType any letter and press enter to continue: ";
    cin >> next;
    system("clear");
}

// Parent Account Class
class Account {
    private:
        float balanceAmt;

    protected:
        Account(float accBalance) : balanceAmt(accBalance) {}

    public:
        // Abstraction
        virtual bool withdraw() = 0;

        virtual bool deposit() = 0;

        // Encapsulation
        
        // Getter
        float balanceGet() {
            return balanceAmt;
        }

        // Setters
        void addBalance(float add) {
            if (add > 0) {
                balanceAmt += add;
            }
        }

        void lessBalance(float input) {
            if (balanceAmt >= input) {
                balanceAmt -= input;
            }
            else {
                cout << "\nAmount to be withdrawn exceeds the balance currently in you account, please try again." << endl;
            }
        }
};

// Child Current Account Class
class CurrentAccount : public Account {
    public:
        CurrentAccount(float balance) : Account(balance) {}

        bool withdraw() override {
            float input;
            cout << "\nYour Current Account Balance: " <<  balanceGet() << endl;
            cout << "\nAmount to be withdrawn: ";
            cin >> input;

            if (cinIntCheck()) {
                cout << "\nInvalid input! Please put an integer!" << endl;
                continueToNext();
                return false;
            }

            if (input < 0) {
                cout << "\nInvalid input! Please input a positive value" << endl;
                continueToNext();
                return false;
            }

            if (input > balanceGet()) {
                cout << "\nError! You are trying to withdraw an amount higher than your current balance. Please try again." << endl;
                continueToNext();
                return false;
            }
            
            cout << "\nAmount successfully withdrawn!" << endl;
            lessBalance(input);
            cout << "\nYour Current Account Balance: " <<  balanceGet() << endl;
            continueToNext();
            return true;
        }

        bool deposit() override {
            float input;
            cout << "\nAmount to be deposited: ";
            cin >> input;
            
            if (cinIntCheck())
            {
                cout << "\nInvalid input! Please put an integer!" << endl;
                continueToNext();
                return false;
            }

            if (input < 0)
            {
                cout << "\nInvalid input! Please input a positive value" << endl;
                continueToNext();
                return false;
            }

            cout << "\nAmount successfully deposited!" << endl;
            addBalance(input);
            cout << "\nYour Curent Account Balance: " <<  balanceGet() << endl;
            continueToNext();
            return true;
        }

        bool currentBalance() {
            cout <<"\nCurrent balance is: " << balanceGet() << endl;
            continueToNext();
            return true;
        }
};

class SavingsAccount : public Account {
    public:
        SavingsAccount(float balance) : Account(balance) {}

        bool withdraw() override {
            float input;
            if (balanceGet() < 1000)
            {
                cout << "\nSince your balance is lower than 1000, you cannot withdraw from your account. Please deposit to maintain your minimum balance of 1000 pesos" << endl;
                continueToNext();
                return false;
            }
            cout << "\nYour Savings Account Balance: " <<  balanceGet() << endl;
            cout << "\nAmount to be withdrawn: ";
            cin >> input;
            if (cinIntCheck())
            {
                cout << "\nInvalid input! Please put an integer!" << endl;
                continueToNext();
                return false;
            }

            if (input < 0)
            {
                cout << "\nInvalid input! Please input a positive value" << endl;
                continueToNext();
                return false;
            }

            if (input > balanceGet()) {
                cout << "\nError! You are trying to withdraw an amount higher than your current balance. Please try again." << endl;
                continueToNext();
                return false;
            }

            if (balanceGet() - input < 1000)
            {
                cout << "\nYou must maintain a balance of 1000 pesos in your savings account! Try again" << endl;
                continueToNext();
                return false;
            }
            
            cout << "\nAmount successfully withdrawn!" << endl;
            lessBalance(input);
            cout << "\nYour Savings Account Balance: " <<  balanceGet() << endl;
            continueToNext();
            return true;
        }

        bool deposit() override {
            float input;
            cout << "\nAmount to be deposited: ";
            cin >> input;
            
            if (cinIntCheck())
            {
                cout << "\nInvalid input! Please put an integer!" << endl;
                continueToNext();
                return false;
            }

            if (input < 0)
            {
                cout << "\nInvalid input! Please input a positive value" << endl;
                continueToNext();
                return false;
            }

            cout << "\nAmount successfully deposited!" << endl;

            addBalance(input);
            cout << "\nYour Savings Account Balance: " <<  balanceGet() << endl;
            continueToNext();
            return true;
        }

        bool currentBalance() {
            cout <<"\nCurrent balance is: " << balanceGet() << endl;
            continueToNext();
            return true;
        }
};

// Show main menu and returns the user's chosen option
int mainMenu()
{
    int choice;

    cout << "Main Menu" << endl;
    cout << "\n1 — Savings Account";
    cout << "\n2 - Current Account";
    cout << "\n3 - Exit" << endl;
        
    cout << "\nType the number to where you want to go: ";
    cin >> choice;

    system("clear");
    if (cinIntCheck()){
        return 999; // Returns very unlikely number to catch error
    }

    return choice;
}

// Show sub menu for both accounts and returns the user's chosen option
int subMenu(string accType)
{
    int choice;

    do
    {
        cout << "Sub Menu - " << accType << endl;
        cout << "\n1 — Deposit";
        cout << "\n2 - Withdraw";
        cout << "\n3 - Check Balance";
        cout << "\n4 - Back" << endl;
            
        cout << "\nType the number to where you want to go: ";
        cin >> choice;
        system("clear");

        if (cinIntCheck())
        {
            cout << "\nInvalid input, please put an integer!" << endl;
            continueToNext();
        }
        else if(choice > 4 || choice < 1)
        {
            cout << "Invalid input, please input a number between 1 and 3!" << endl;
            continueToNext();
        }
    } while (choice > 4 || choice < 1 || cinIntCheck());

    return choice;
}

int main(void) {
    system("clear");
    CurrentAccount userCA(0);

    // Array of functions for current account
    bool (CurrentAccount::*methodCA[3])() = {&CurrentAccount::deposit, &CurrentAccount::withdraw, &CurrentAccount::currentBalance};

    SavingsAccount userSA(0);

    // Array of functions for savings account
    bool (SavingsAccount::*methodSA[3])() = {&SavingsAccount::deposit, &SavingsAccount::withdraw, &SavingsAccount::currentBalance};

    int chosen = 0;
    char confirm;
    bool close;

    do
    {
        chosen = mainMenu();

        switch (chosen) {
            case 1: // Savings Account
                do
                {
                    chosen = subMenu("Savings Account");
                    if (chosen == 4) {
                        break;
                    } 
                    close = (userSA.*methodSA[chosen - 1])();
                } while (!close);
                break;

            case 2: // Current Account
                do
                {
                    chosen = subMenu("Current Account");
                    if (chosen == 4) {
                        break;
                    } 
                    close = (userCA.*methodCA[chosen - 1])();
                } while (!close);
                break;

            case 3: // Exit
                do {
                    cout << "\nAre you sure you want to exit? [Y/N]: ";
                    cin >> confirm;
                    cin.ignore(100, '\n');
                } while (toupper(confirm) != 'Y' && toupper(confirm) != 'N');
                system("clear");
                break;

            case 999: // Triggers unlikely case where program detects char / string in int input
                cout << "\nInvalid input, please put an integer!" << endl;
                continueToNext();
                break;

            default: // User inputs int but its not in the options
                cout << "\nInvalid input, please put a number between 1 and 3!" << endl;
                continueToNext();
                break;
            }
    } while (toupper(confirm) != 'Y');

    return 0;
}