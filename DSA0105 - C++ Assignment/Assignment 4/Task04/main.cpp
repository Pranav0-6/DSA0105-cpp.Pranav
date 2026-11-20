
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Account {
public:
    virtual double rate() const {
        return 3.5;
    }

    virtual void show() const {
        cout << "Regular account: " << rate() << "%\n";
    }

    virtual ~Account() {
        cout << "Account destructor\n";
    }
};

class SeniorAccount : public Account {
private:
    double* history;

public:
    SeniorAccount() : history(new double[100]()) {}

    double rate() const override {
        return 4.0;
    }

    void show() const override {
        cout << "Senior account: " << rate() << "%\n";
    }

    ~SeniorAccount() override {
        delete[] history;
        cout << "SeniorAccount destructor (history released)\n";
    }
};

int main() {

    vector<unique_ptr<Account> > accounts;

    // C++11 compatible object creation
    accounts.push_back(
        unique_ptr<Account>(new Account())
    );

    accounts.push_back(
        unique_ptr<Account>(new SeniorAccount())
    );

    cout << "POLYMORPHIC ACCOUNT RATES\n";

    for (const auto& account : accounts) {
        account->show();
    }

    cout << "\nOUTPUT PREDICTION PROGRAM\n";

    SeniorAccount s;
    Account* p = &s;

    // Object slicing
    Account copy = s;

    cout << p->rate() << ' '
         << p->rate() << ' '
         << copy.rate() << '\n';

    return 0;
}
