#include <iostream>
using namespace std;

// Q1: Call by value, reference and pointer
void concessionByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
    cout << "Inside value function: " << fee << '\n';
}
void concessionByReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}
void concessionByPointer(long long* fee, int percent) {
    if (fee != nullptr) *fee -= (*fee) * percent / 100;
}

// Return by reference: returns the larger variable itself.
int& bigger(int& p, int& q) {
    return (p > q) ? p : q;
}
void show(int x, int y = 5, int z = 10) {
    cout << x + y + z << ' ';
}

int main() {
    long long fee1 = 45000, fee2 = 45000, fee3 = 45000;
    concessionByValue(fee1, 10);
    concessionByReference(fee2, 10);
    concessionByPointer(&fee3, 10);
    cout << "After value: " << fee1 << '\n';
    cout << "After reference: " << fee2 << '\n';
    cout << "After pointer: " << fee3 << '\n';

    int a = 1, b = 2, c = 3;
    // The assignment below demonstrates the original prediction question.
    int x = a, y = b, z = c;
    x += 10; y += 10; z += 10; // equivalent effects of change(x,y,&z)
    cout << "Predict-output example: " << x - 10 << ' ' << y << ' ' << z << '\n';
    bigger(a, c) = 100;
    cout << "After bigger assignment: " << a << ' ' << c << '\n';
    cout << "Default arguments: ";
    show(1); show(1, 2); show(1, 2, 3);
    cout << '\n';
    return 0;
}