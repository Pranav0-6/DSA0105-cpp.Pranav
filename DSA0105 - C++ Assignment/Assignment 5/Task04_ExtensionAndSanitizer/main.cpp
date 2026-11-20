
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Bill {
protected:
    string patient;
public:
    explicit Bill(string p) : patient(move(p)) {}
    virtual ~Bill() {}
    virtual double total() const = 0;
    virtual string type() const = 0;
};

class OPBill : public Bill {
    double consultation, tests;
public:
    OPBill(string p, double c, double t)
        : Bill(move(p)), consultation(c), tests(t) {
        if (c < 0 || t < 0)
            throw invalid_argument("negative OP charge");
    }

    double total() const override {
        return consultation + tests;
    }

    string type() const override {
        return "OP";
    }
};

class IPBill : public Bill {
    int days;
    double rate, procedure;
public:
    IPBill(string p, int d, double r, double pr)
        : Bill(move(p)), days(d), rate(r), procedure(pr) {
        if (d < 0 || r < 0 || pr < 0)
            throw invalid_argument("invalid IP charge");
    }

    double total() const override {
        return days * rate + procedure;
    }

    string type() const override {
        return "IP";
    }
};

class MaternityBill : public Bill {
    double package, extra;
public:
    MaternityBill(string p, double pkg, double extras)
        : Bill(move(p)), package(pkg), extra(extras) {
        if (pkg < 0 || extras < 0)
            throw invalid_argument("invalid maternity charge");
    }

    double total() const override {
        return package + extra;
    }

    string type() const override {
        return "MATERNITY";
    }
};

class Payer {
public:
    virtual ~Payer() {}
    virtual double amountCovered(const Bill&) const = 0;
    virtual string name() const = 0;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill& b) const override {
        return b.total();
    }

    string name() const override {
        return "SelfPay";
    }
};

class Insurance : public Payer {
    double limit, copay;
public:
    Insurance(double l, double c) : limit(l), copay(c) {}

    double amountCovered(const Bill& b) const override {
        return min(limit, b.total() * (1.0 - copay / 100.0));
    }

    string name() const override {
        return "Insurance";
    }
};

class CorporateTieUp : public Payer {
    double percentage;
public:
    explicit CorporateTieUp(double p) : percentage(p) {
        if (p < 0 || p > 100)
            throw invalid_argument("invalid corporate percentage");
    }

    double amountCovered(const Bill& b) const override {
        return b.total() * percentage / 100.0;
    }

    string name() const override {
        return "CorporateTieUp";
    }
};

struct ResourceGuard {
    string label;

    explicit ResourceGuard(string s) : label(move(s)) {
        cout << "acquired " << label << '\n';
    }

    ~ResourceGuard() noexcept {
        cout << "released " << label << '\n';
    }
};

int main() {
    try {
        vector<unique_ptr<Bill> > bills;

        bills.push_back(
            unique_ptr<Bill>(new OPBill("Ravi", 500, 1200))
        );

        bills.push_back(
            unique_ptr<Bill>(new IPBill("Meena", 3, 2500, 40000))
        );

        bills.push_back(
            unique_ptr<Bill>(new MaternityBill("Latha", 30000, 5000))
        );

        SelfPay self;
        Insurance insurer(50000, 10);
        CorporateTieUp corporate(70);

        vector<const Payer*> payers;
        payers.push_back(&self);
        payers.push_back(&insurer);
        payers.push_back(&corporate);

        for (const auto& b : bills) {
            cout << b->type() << " total=" << b->total() << '\n';

            for (const auto* p : payers) {
                cout << "  " << p->name()
                     << " covers=" << p->amountCovered(*b) << '\n';
            }
        }

        try {
            ResourceGuard guard("claim-file");
            throw runtime_error("demonstration exception");
        }
        catch (const exception& e) {
            cout << "caught: " << e.what() << '\n';
        }
    }
    catch (const exception& e) {
        cerr << "fatal: " << e.what() << '\n';
        return 1;
    }

    cout << "completed without leaks expected" << endl;

    return 0;
}
