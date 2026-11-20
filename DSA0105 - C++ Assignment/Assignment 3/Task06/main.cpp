#include <iostream>
#include <cstring>
using namespace std;

class Text {
private:
    char* data;

public:
    Text(const char* value = "") {
        size_t len = strlen(value);
        data = new char[len + 1];
        strcpy(data, value);
    }

    Text(const Text& other) {
        size_t len = strlen(other.data);
        data = new char[len + 1];
        strcpy(data, other.data);
        cout << "[copy] ";
    }

    Text& operator=(const Text& other) {
        if (this != &other) {
            size_t len = strlen(other.data);
            char* fresh = new char[len + 1];
            strcpy(fresh, other.data);
            delete[] data;
            data = fresh;
        }
        return *this;
    }

    Text& operator+=(const Text& other) {
        size_t left = strlen(data);
        size_t right = strlen(other.data);
        char* fresh = new char[left + right + 1];
        strcpy(fresh, data);
        strcat(fresh, other.data);
        delete[] data;
        data = fresh;
        return *this;
    }

    friend Text operator+(const Text& a, const Text& b) {
        Text result(a);
        result += b;
        return result;
    }

    friend bool operator==(const Text& a, const Text& b) {
        return strcmp(a.data, b.data) == 0;
    }

    friend bool operator!=(const Text& a, const Text& b) {
        return !(a == b);
    }

    friend ostream& operator<<(ostream& out, const Text& t) {
        return out << t.data;
    }

    ~Text() { delete[] data; }
};

int main() {
    Text a("Hello"), b(" "), c("World");
    Text message = a + b + c;
    cout << "\nMessage: " << message << '\n';

    Text copy = message;
    cout << "Copy: " << copy << '\n';
    cout << boolalpha << "Equal: " << (copy == message)
         << ", Not equal: " << (a != c) << '\n';

    Text empty;
    cout << "Empty text: [" << empty << "]\n";

    message = message; // self-assignment
    cout << "After self-assignment: " << message << '\n';
    return 0;
}