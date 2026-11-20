#include <iostream>
#include <string>
using namespace std;

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

// Integer input means grams.
double charge(int weightGrams) {
    return (weightGrams / 1000.0) * 50.0;
}

// Double input means kilograms. Optional arguments are supplied from the right.
double charge(double weightKg, bool express = false, bool insured = false) {
    double total = weightKg * 50.0;
    if (express) total += 30.0;
    if (insured) total += 20.0;
    return total;
}

double charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    cout << "charge(2000): " << charge(2000) << '\n';
    cout << "charge(2): " << charge(2) << '\n';
    cout << "charge(2.0): " << charge(2.0) << '\n';
    cout << "charge(2.0f): " << charge(2.0f) << '\n';
    cout << "charge(2.0, true): " << charge(2.0, true) << '\n';
    Parcel p{2.0, true, true};
    cout << "charge(Parcel): " << charge(p) << '\n';
    return 0;
}