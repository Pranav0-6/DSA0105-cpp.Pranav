#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Book {
private:
    string title;
    string author;
    int copies;

    static int validateCopies(int n) {
        if (n < 0) throw invalid_argument("Number of copies cannot be negative");
        return n;
    }

public:
    // Default constructor
    Book() : Book("Untitled", "Unknown", 0) {}

    // Donated book: title only (delegates to the full constructor)
    explicit Book(const string& t) : Book(t, "Unknown", 1) {}

    // Parameterized constructor
    Book(const string& t, const string& a, int c)
        : title(t), author(a), copies(validateCopies(c)) {}

    void print() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Copies: " << copies << '\n';
    }
};

int main() {
    try {
        Book empty;
        Book donated("Wings of Fire");
        Book full("The Guide", "R. K. Narayan", 5);

        cout << "Default book:\n";
        empty.print();
        cout << "Donated book:\n";
        donated.print();
        cout << "Full book:\n";
        full.print();

        // Uncomment to test invalid input:
        // Book invalid("Bad Book", "Unknown", -2);

        // explicit demonstration:
        // void receiveBook(Book b) {}
        // receiveBook("Direct conversion"); // fails if constructor is explicit
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}