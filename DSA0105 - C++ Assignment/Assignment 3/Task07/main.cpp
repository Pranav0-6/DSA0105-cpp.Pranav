#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
using namespace std;

class Complex {
private:
    double realPart;
    double imagPart;

public:
    Complex() : realPart(0.0), imagPart(0.0) {}
    Complex(double real) : realPart(real), imagPart(0.0) {}
    Complex(double real, double imag)
        : realPart(real), imagPart(imag) {}

    double real() const { return realPart; }
    double imag() const { return imagPart; }
    double magnitude() const {
        return sqrt(realPart * realPart + imagPart * imagPart);
    }

    Complex operator+(const Complex& z) const {
        return Complex(realPart + z.realPart, imagPart + z.imagPart);
    }

    Complex operator-(const Complex& z) const {
        return Complex(realPart - z.realPart, imagPart - z.imagPart);
    }

    Complex operator*(const Complex& z) const {
        return Complex(realPart * z.realPart - imagPart * z.imagPart,
                       realPart * z.imagPart + imagPart * z.realPart);
    }

    Complex operator/(const Complex& z) const {
        double denominator = z.realPart * z.realPart + z.imagPart * z.imagPart;
        if (denominator == 0.0) throw runtime_error("Division by zero impedance");
        return Complex((realPart * z.realPart + imagPart * z.imagPart) / denominator,
                       (imagPart * z.realPart - realPart * z.imagPart) / denominator);
    }

    bool operator==(const Complex& z) const {
        const double eps = 1e-9;
        return fabs(realPart - z.realPart) < eps &&
               fabs(imagPart - z.imagPart) < eps;
    }

    friend ostream& operator<<(ostream& out, const Complex& z) {
        out << fixed << setprecision(2) << z.realPart;
        if (z.imagPart >= 0) out << " + j" << z.imagPart;
        else out << " - j" << fabs(z.imagPart);
        return out;
    }
};

int main() {
    try {
        // Example circuit values at a chosen frequency:
        // R = 10 ohm, XL = 5 ohm, XC = 20 ohm
        Complex resistor(10.0, 0.0);
        Complex inductor(0.0, 5.0);
        Complex capacitor(0.0, -20.0);

        Complex series = resistor + inductor + capacitor;
        cout << "Series impedance: " << series << " ohm\n";
        cout << "Series magnitude: " << series.magnitude() << " ohm\n";

        Complex z1(10.0, 0.0);
        Complex z2(0.0, 10.0);
        Complex parallel = (z1 * z2) / (z1 + z2);
        cout << "Parallel impedance: " << parallel << " ohm\n";
        cout << "Parallel magnitude: " << parallel.magnitude() << " ohm\n";

        Complex zero;
        Complex test = z1 / zero; // safely throws
        cout << test << '\n';
    } catch (const exception& e) {
        cout << "Error: " << e.what() << '\n';
    }
    return 0;
}