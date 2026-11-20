
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

// Custom Exceptions
class BillingError : public runtime_error {
public:
    BillingError(const string& msg) : runtime_error(msg) {}
};

class ClaimError : public BillingError {
public:
    ClaimError(const string& msg) : BillingError(msg) {}
};

// Abstract Bill Class
class Bill {
protected:
    string patient;

public:
    explicit Bill(const string& p) : patient(p) {}

    virtual ~Bill() {}

    virtual double total() const = 0;
    virtual string type() const = 0;

    virtual void print() const {
        cout << type() << ' ' << patient << ": Rs "
             << fixed << setprecision(2) << total() << '\n';
    }
};

// OutPatient Bill
class OutPatientBill : public Bill {
    double consultation, tests;

public:
    OutPatientBill(const string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) {
        if (c < 0 || t < 0)
            throw BillingError("negative OP charge");
    }

    double total() const override {
        return consultation + tests;
    }

    string type() const override {
        return "OP";
    }
};

// InPatient Bill
class InPatientBill : public Bill {
    int days;
    double perDay, procedure, medicines;

public:
    InPatientBill(const string& p, int d, double rate,
                  double proc, double med)
        : Bill(p), days(d), perDay(rate),
          procedure(proc), medicines(med) {
        if (d < 0 || rate < 0 || proc < 0 || med < 0)
            throw BillingError("invalid IP charge");
    }

    double total() const override {
        return days * perDay + procedure + medicines;
    }

    string type() const override {
        return "IP";
    }
};

// DayCare Bill
class DayCareBill : public Bill {
    double packagePrice;

public:
    DayCareBill(const string& p, double price)
        : Bill(p), packagePrice(price) {
        if (price < 0)
            throw BillingError("negative day-care package");
    }

    double total() const override {
        return packagePrice;
    }

    string type() const override {
        return "DAYCARE";
    }
};

// Emergency Bill
class EmergencyBill : public Bill {
    double baseCharge, hourlyRate;
    int hours;

public:
    EmergencyBill(const string& p, double base,
                  double rate, int h)
        : Bill(p), baseCharge(base),
          hourlyRate(rate), hours(h) {
        if (base < 0 || rate < 0 || h < 0)
            throw BillingError("invalid emergency charge");
    }

    double total() const override {
        return baseCharge + hourlyRate * hours;
    }

    string type() const override {
        return "EMERGENCY";
    }
};

// Abstract Payer Class
class Payer {
public:
    virtual ~Payer() {}

    virtual double amountCovered(const Bill& bill) const = 0;
    virtual string name() const = 0;
};

// SelfPay Class
class SelfPay : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        return bill.total();
    }

    string name() const override {
        return "SelfPay";
    }
};

// Insurance Class
class Insurance : public Payer {
    double coverLimit, copayPercent;

public:
    Insurance(double limit, double copay)
        : coverLimit(limit), copayPercent(copay) {
        if (limit < 0 || copay < 0 || copay > 100)
            throw BillingError("invalid insurance policy");
    }

    double amountCovered(const Bill& bill) const override {
        double patientShare =
            bill.total() * copayPercent / 100.0;

        return min(coverLimit, bill.total() - patientShare);
    }

    string name() const override {
        return "Insurance";
    }
};

// Government Scheme Class
class GovernmentScheme : public Payer {
    double packageRate;

public:
    explicit GovernmentScheme(double rate)
        : packageRate(rate) {
        if (rate < 0)
            throw BillingError("invalid government package rate");
    }

    double amountCovered(const Bill& bill) const override {
        return min(packageRate, bill.total());
    }

    string name() const override {
        return "GovernmentScheme";
    }
};

// Main Function
int main() {
    try {
        vector<unique_ptr<Bill> > bills;

        // Creating bill objects using C++11
        bills.push_back(
            unique_ptr<Bill>(
                new OutPatientBill("Ravi", 500, 1200)
            )
        );

        bills.push_back(
            unique_ptr<Bill>(
                new InPatientBill("Meena", 3, 2500, 40000, 3500)
            )
        );

        bills.push_back(
            unique_ptr<Bill>(
                new DayCareBill("Kumar", 18000)
            )
        );

        bills.push_back(
            unique_ptr<Bill>(
                new EmergencyBill("Asha", 2000, 750, 4)
            )
        );

        // Creating payer objects
        SelfPay self;
        Insurance insurance(50000, 10);
        GovernmentScheme scheme(20000);

        vector<const Payer*> payers;
        payers.push_back(&self);
        payers.push_back(&insurance);
        payers.push_back(&scheme);

        double dayTotal = 0;

        cout << "HOSPITAL BILLING SUMMARY\n";
        cout << "-------------------------------\n";

        for (size_t i = 0; i < bills.size(); i++) {

            bills[i]->print();

            dayTotal += bills[i]->total();

            for (size_t j = 0; j < payers.size(); j++) {
                cout << "  " << payers[j]->name()
                     << " covers Rs "
                     << fixed << setprecision(2)
                     << payers[j]->amountCovered(*bills[i])
                     << '\n';
            }

            cout << '\n';
        }

        cout << "-------------------------------\n";

        cout << "Day total: Rs "
             << fixed << setprecision(2)
             << dayTotal << '\n';

    }
    catch (const exception& e) {
        cerr << "Billing failed: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
