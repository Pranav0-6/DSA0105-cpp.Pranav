
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
using namespace std;

// Abstract Base Class
class Staff {
protected:
    string name;
    int id;

public:
    Staff(string n, int i) {
        name = n;
        id = i;
    }

    virtual double pay() = 0;

    virtual void print() {
        cout << name << " (ID " << id << ") : Rs "
             << fixed << setprecision(2) << pay() << endl;
    }

    virtual ~Staff() {}
};

// Professor Class
class Professor : public Staff {
private:
    double basic;
    double researchAllowance;

public:
    Professor(string n, int i, double b, double r)
        : Staff(n, i) {
        basic = b;
        researchAllowance = r;
    }

    double pay() override {
        return basic + (basic * 0.42) + researchAllowance;
    }
};

// LabAssistant Class
class LabAssistant : public Staff {
private:
    double basic;

public:
    LabAssistant(string n, int i, double b)
        : Staff(n, i) {
        basic = b;
    }

    double pay() override {
        return basic + (basic * 0.42);
    }
};

// GuestFaculty Class
class GuestFaculty : public Staff {
private:
    int hours;
    double rate;

public:
    GuestFaculty(string n, int i, int h, double r)
        : Staff(n, i) {
        hours = h;
        rate = r;
    }

    double pay() override {
        return hours * rate;
    }
};

// Main Function
int main() {

    vector<unique_ptr<Staff> > payroll;

    // Create Staff Objects (C++11 syntax)
    payroll.push_back(
        unique_ptr<Staff>(new Professor("Anitha", 101, 50000, 8000))
    );

    payroll.push_back(
        unique_ptr<Staff>(new LabAssistant("Bala", 102, 30000))
    );

    payroll.push_back(
        unique_ptr<Staff>(new GuestFaculty("Charan", 103, 40, 600))
    );

    cout << "COLLEGE PAYROLL" << endl;
    cout << "------------------------" << endl;

    for (size_t i = 0; i < payroll.size(); i++) {
        payroll[i]->print();
    }

    cout << "------------------------" << endl;
    cout << "Total staff: " << payroll.size() << endl;

    return 0;
}
