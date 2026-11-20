#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Prescription {
private:
    int n;
    string* medicines;

public:
    explicit Prescription(int count)
        : n(count < 0 ? 0 : count),
          medicines(n ? new string[n] : nullptr) {}

    // Deep-copy constructor
    Prescription(const Prescription& other)
        : n(other.n), medicines(n ? new string[n] : nullptr) {
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
        cout << "[copy constructor] copied " << n << " medicine(s)\n";
    }

    // Deep-copy assignment operator; safe for self-assignment
    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            string* fresh = other.n ? new string[other.n] : nullptr;
            for (int i = 0; i < other.n; ++i) fresh[i] = other.medicines[i];
            delete[] medicines;
            medicines = fresh;
            n = other.n;
        }
        return *this;
    }

    ~Prescription() {
        delete[] medicines;
    }

    void set(int i, const string& medicine) {
        if (i >= 0 && i < n) medicines[i] = medicine;
    }
    string get(int i) const {
        return (i >= 0 && i < n) ? medicines[i] : "";
    }
    int size() const { return n; }
};

void inspectByValue(Prescription p) {
    cout << "Passed by value: " << p.get(0) << '\n';
}
void inspectByReference(const Prescription& p) {
    cout << "Passed by const reference: " << p.get(0) << '\n';
}

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;             // copy constructor
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;                           // copy assignment
    p.set(0, "Ibuprofen");

    cout << p.get(0) << ' ' << p.get(1) << " | "
         << q.get(0) << ' ' << q.get(1) << " | "
         << r.get(0) << ' ' << r.get(1) << '\n';

    r = r;                           // self-assignment test
    inspectByValue(p);               // makes a copy
    inspectByReference(p);           // no copy
    return 0;
}