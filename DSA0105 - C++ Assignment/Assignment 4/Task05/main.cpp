#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class Cart {
    string items[10];
    double prices[10];
    int n = 0;
    double discount = 0.0;

public:
    Cart& add(const string& item, double price) {
        if (n < 10 && price >= 0) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        if (this->discount < 0) this->discount = 0;
        if (this->discount > 100) this->discount = 100;
        return *this;
    }

    double total() const {
        double sum = 0;
        for (int i = 0; i < n; ++i) sum += prices[i];
        return sum * (100.0 - discount) / 100.0;
    }

    void print() const {
        for (int i = 0; i < n; ++i)
            cout << items[i] << ": Rs " << prices[i] << '\n';
    }
};

int main() {
    Cart c;
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* p = &c;
    p->add("Oil", 180);

    cout << fixed << setprecision(2);
    cout << "Chained cart total: " << p->total() << '\n';

    Cart second;
    second.add("Milk", 50).add("Bread", 40);
    Cart third;
    third.add("Laptop", 50000).setDiscount(5);

    Cart* carts[] = { &c, &second, &third };
    Cart* highest = carts[0];
    for (Cart** it = carts; it != carts + 3; ++it) {
        if ((*it)->total() > highest->total()) highest = *it;
    }
    cout << "Highest cart total: " << highest->total() << '\n';

    Cart* heapCart = new Cart;
    heapCart->add("Apple", 30);
    cout << "Heap cart total: " << heapCart->total() << '\n';
    delete heapCart;
    return 0;
}