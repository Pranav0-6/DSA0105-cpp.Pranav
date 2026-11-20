
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

using Clock = chrono::steady_clock;

// Base Bill Class
struct BillBase {
    virtual ~BillBase() {}
    virtual double total() const = 0;
};

// Outpatient Bill
struct OP : BillBase {
    double c, t;

    OP(double a, double b) : c(a), t(b) {}

    double total() const override {
        return c + t;
    }
};

// Inpatient Bill
struct IP : BillBase {
    double days, rate, surgery;

    IP(double d, double r, double s)
        : days(d), rate(r), surgery(s) {}

    double total() const override {
        return days * rate + surgery;
    }
};

// Daycare Bill
struct Day : BillBase {
    double package;

    explicit Day(double p) : package(p) {}

    double total() const override {
        return package;
    }
};

// Tagged Bill Structure
struct TaggedBill {
    int type;
    double a, b, c;
};

// Switch Calculation
double switchTotal(const TaggedBill& x) {
    switch (x.type) {
        case 0:
            return x.a + x.b;

        case 1:
            return x.a * x.b + x.c;

        default:
            return x.a;
    }
}

// C++11 replacement for variant
struct VariantBill {
    int type;
    double a, b, c;

    double total() const {
        switch (type) {
            case 0:
                return a + b;

            case 1:
                return a * b + c;

            default:
                return a;
        }
    }
};

// Benchmark Function
template<class F>
void measure(const string& label, size_t n, F fn) {
    volatile double checksum = 0;

    Clock::time_point start = Clock::now();

    for (size_t i = 0; i < n; ++i) {
        checksum += fn(i);
    }

    double ms = chrono::duration<double, milli>(
        Clock::now() - start
    ).count();

    cout << label << " n=" << n
         << " time_ms=" << ms
         << " checksum=" << checksum << '\n';
}

// Main Function
int main() {

    cout << "BENCHMARK (times depend on your computer/compiler)\n";

    size_t sizes[] = {
        1000,
        1000000,
        10000000
    };

    for (int sizeIndex = 0; sizeIndex < 3; ++sizeIndex) {

        size_t n = sizes[sizeIndex];

        vector<unique_ptr<BillBase> > poly;
        vector<TaggedBill> tagged;
        vector<VariantBill> variants;

        poly.reserve(n);
        tagged.reserve(n);
        variants.reserve(n);

        for (size_t i = 0; i < n; ++i) {

            int k = static_cast<int>(i % 3);

            if (k == 0) {

                poly.push_back(
                    unique_ptr<BillBase>(new OP(500, 1200))
                );

                TaggedBill t = {0, 500, 1200, 0};
                tagged.push_back(t);

                VariantBill v = {0, 500, 1200, 0};
                variants.push_back(v);
            }
            else if (k == 1) {

                poly.push_back(
                    unique_ptr<BillBase>(new IP(3, 2500, 40000))
                );

                TaggedBill t = {1, 3, 2500, 40000};
                tagged.push_back(t);

                VariantBill v = {1, 3, 2500, 40000};
                variants.push_back(v);
            }
            else {

                poly.push_back(
                    unique_ptr<BillBase>(new Day(18000))
                );

                TaggedBill t = {2, 18000, 0, 0};
                tagged.push_back(t);

                VariantBill v = {2, 18000, 0, 0};
                variants.push_back(v);
            }
        }

        measure("virtual", n, [&poly](size_t i) {
            return poly[i]->total();
        });

        measure("switch", n, [&tagged](size_t i) {
            return switchTotal(tagged[i]);
        });

        measure("variant-style", n, [&variants](size_t i) {
            return variants[i].total();
        });
    }

    // Exception vs Return Code Benchmark
    cout << "\nEXCEPTION VS RETURN-CODE VALIDATION "
         << "(1,000,000 claims)\n";

    const size_t n = 1000000;

    int percentages[] = {0, 1, 50};

    for (int p = 0; p < 3; ++p) {

        int invalidPercent = percentages[p];

        vector<double> amounts(n, 1000);

        size_t invalidCount =
            n * static_cast<size_t>(invalidPercent) / 100;

        for (size_t i = 0; i < invalidCount; ++i) {
            amounts[i] = -1;
        }

        volatile size_t accepted = 0;

        Clock::time_point s1 = Clock::now();

        for (size_t i = 0; i < n; ++i) {
            if (amounts[i] >= 0) {
                ++accepted;
            }
        }

        double e1 = chrono::duration<double, milli>(
            Clock::now() - s1
        ).count();

        volatile size_t acceptedEx = 0;

        Clock::time_point s2 = Clock::now();

        for (size_t i = 0; i < n; ++i) {

            try {
                if (amounts[i] < 0) {
                    throw invalid_argument("negative");
                }

                ++acceptedEx;
            }
            catch (const invalid_argument&) {
                // Invalid claim rejected
            }
        }

        double e2 = chrono::duration<double, milli>(
            Clock::now() - s2
        ).count();

        cout << invalidPercent
             << "% invalid: return_ms=" << e1
             << " exception_ms=" << e2
             << " accepted=" << accepted
             << "/" << acceptedEx << '\n';
    }

    return 0;
}
