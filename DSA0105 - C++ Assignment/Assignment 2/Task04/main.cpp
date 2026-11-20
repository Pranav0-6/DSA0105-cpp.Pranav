#include <iostream>
#include <string>
using namespace std;

class SavingsAccount {
private:
    string accountNumber;
    double balance;
    double transactions[10];
    int count;
    int next; // next position to write; circular buffer

public:
    SavingsAccount(const string& number, double openingBalance)
        : accountNumber(number), balance(openingBalance), count(0), next(0) {}

    void deposit(double amount);  // defined outside the class
    void withdraw(double amount); // defined outside the class
    void miniStatement() const;   // defined outside the class

    double getBalance() const { return balance; } // defined inside the class
};

void SavingsAccount::deposit(double amount) {
    if (amount <= 0) {
        cout << "Invalid deposit\n";
        return;
    }
    balance += amount;
    transactions[next] = amount;
    next = (next + 1) % 10;
    if (count < 10) ++count;
}

void SavingsAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        cout << "Invalid withdrawal\n";
        return;
    }
    balance -= amount;
    transactions[next] = -amount; // negative value represents withdrawal
    next = (next + 1) % 10;
    if (count < 10) ++count;
}

void SavingsAccount::miniStatement() const {
    cout << "Account: " << accountNumber << "\nBalance: " << balance
         << "\nLast transactions (oldest to newest):\n";
    int start = (count == 10) ? next : 0;
    for (int i = 0; i < count; ++i) {
        int index = (start + i) % 10;
        if (transactions[index] >= 0)
            cout << "Deposit: ";
        else
            cout << "Withdrawal: ";
        cout << (transactions[index] >= 0 ? transactions[index] : -transactions[index]) << '\n';
    }
}

int main() {
    SavingsAccount account("SA1001", 5000);
    account.deposit(1000);
    account.withdraw(500);
    account.deposit(250);
    account.withdraw(100);
    account.miniStatement();
    cout << "Current balance: " << account.getBalance() << '\n';
    return 0;
}