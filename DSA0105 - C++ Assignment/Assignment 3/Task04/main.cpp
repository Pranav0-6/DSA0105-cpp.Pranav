#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Money {
private:
    long long paise;

public:
    Money(long long rupees = 0, int p = 0)
        : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        Money result;
        result.paise = paise + other.paise;
        return result;
    }

    Money operator-(const Money& other) const {
        Money result;
        result.paise = paise - other.paise;
        return result;
    }

    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const {
        return paise == other.paise;
    }

    bool operator<(const Money& other) const {
        return paise < other.paise;
    }

    friend ostream& operator<<(ostream& out, const Money& m) {
        bool negative = m.paise < 0;
        long long absolute = negative ? -m.paise : m.paise;
        if (negative) out << "-";
        out << "Rs " << absolute / 100 << '.'
            << setw(2) << setfill('0') << absolute % 100
            << setfill(' ');
        return out;
    }

    friend istream& operator>>(istream& in, Money& m) {
        long long rupees;
        int p;
        if (in >> rupees >> p) m.paise = rupees * 100 + p;
        return in;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    cout << c << '\n' << boolalpha << (c == Money(200)) << '\n';

    Money x(0, 75), y(0, 50);
    cout << "Paise carry: " << x + y << '\n';

    Money small(1, 0), large(2, 0);
    cout << "Negative subtraction: " << small - large << '\n';

    Money bill(250, 0);
    bill += Money(49, 50);
    cout << "Bill total: " << bill << '\n';
    return 0;
}