#include <iostream>
#include <string>
using namespace std;

class Address {
    string city;
    int pin;
public:
    Address(const string& c, int p) : city(c), pin(p) {
        cout << "Address constructed\n";
    }
    string str() const { return city + "-" + to_string(pin); }
    ~Address() { cout << "Address destroyed\n"; }
};

class Person {
protected:
    string name;
    int age;
    Address address;

public:
    Person(const string& n, int a, const string& city, int pin)
        : name(n), age(a), address(city, pin) {
        cout << "Person constructed: " << name << '\n';
    }
    virtual ~Person() { cout << "Person destroyed: " << name << '\n'; }
};

class Course {
    string title;
public:
    explicit Course(const string& t) : title(t) {
        cout << "Course constructed: " << title << '\n';
    }
    ~Course() { cout << "Course destroyed: " << title << '\n'; }
};

class Student : virtual public Person {
    long long regNo;
    Course course;
public:
    Student(const string& n, int a, const string& city, int pin,
            long long reg, const string& courseName)
        : Person(n, a, city, pin), regNo(reg), course(courseName) {
        cout << "Student constructed\n";
    }
    void print() const {
        cout << regNo << ' ' << name << " (" << age << ") "
             << address.str() << '\n';
    }
    ~Student() override { cout << "Student destroyed\n"; }
};

class Staff : virtual public Person {
    string department;
public:
    Staff(const string& n, int a, const string& city, int pin, const string& d)
        : Person(n, a, city, pin), department(d) {
        cout << "Staff constructed\n";
    }
    ~Staff() override { cout << "Staff destroyed\n"; }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const string& n, int a, const string& city, int pin,
                      long long reg, const string& courseName, const string& dept)
        : Person(n, a, city, pin),
          Student(n, a, city, pin, reg, courseName),
          Staff(n, a, city, pin, dept) {
        cout << "TeachingAssistant constructed\n";
    }
    ~TeachingAssistant() override { cout << "TeachingAssistant destroyed\n"; }
};

int main() {
    cout << "--- Student object ---\n";
    {
        Student s("Kavya", 19, "Salem", 636001, 192311001, "OOP");
        s.print();
    }

    cout << "\n--- Staff object ---\n";
    {
        Staff st("Ravi", 40, "Chennai", 600001, "IT");
    }

    cout << "\n--- TeachingAssistant object (virtual diamond) ---\n";
    {
        TeachingAssistant ta("Meena", 22, "Madurai", 625001,
                             192311002, "C++", "IT");
    }
    return 0;
}