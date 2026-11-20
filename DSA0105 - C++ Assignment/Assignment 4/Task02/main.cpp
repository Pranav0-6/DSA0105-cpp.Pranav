#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int id;
    string phone;

public:
    Person(const string& n = "", int i = 0, const string& p = "")
        : name(n), id(i), phone(p) {}
    virtual ~Person() = default;

    void printPerson() const {
        cout << "Name: " << name << ", ID: " << id << ", Phone: " << phone << '\n';
    }
};

class Student : virtual public Person {
protected:
    string programme;
    double cgpa;

public:
    Student(const string& n = "", int i = 0, const string& p = "",
            const string& prog = "", double g = 0.0)
        : Person(n, i, p), programme(prog), cgpa(g) {}
    void printStudent() const {
        cout << "Programme: " << programme << ", CGPA: " << cgpa << '\n';
    }
};

class Staff : virtual public Person {
protected:
    string department;
    double salary;

public:
    Staff(const string& n = "", int i = 0, const string& p = "",
          const string& dept = "", double sal = 0.0)
        : Person(n, i, p), department(dept), salary(sal) {}
    void printStaff() const {
        cout << "Department: " << department << ", Salary: " << salary << '\n';
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const string& n, int i, const string& p,
                      const string& prog, double g,
                      const string& dept, double sal)
        : Person(n, i, p),
          Student(n, i, p, prog, g),
          Staff(n, i, p, dept, sal) {}

    void print() const {
        printPerson();
        printStudent();
        printStaff();
    }
};

class ResearchScholar : public Student {
private:
    double fellowship;

public:
    ResearchScholar(const string& n, int i, const string& p,
                    const string& prog, double g, double f)
        : Person(n, i, p), Student(n, i, p, prog, g), fellowship(f) {}

    void print() const {
        printPerson();
        printStudent();
        cout << "Fellowship: " << fellowship << '\n';
    }
};

int main() {
    TeachingAssistant ta("Kavya", 201, "9876543210", "B.Tech IT", 8.7,
                         "Computer Science", 25000);
    cout << "TEACHING ASSISTANT\n";
    ta.print();

    cout << "\nRESEARCH SCHOLAR\n";
    ResearchScholar rs("Arun", 202, "9876501234", "M.Tech", 9.1, 12000);
    rs.print();

    cout << "\nPerson subobject size in this build: " << sizeof(Person) << " bytes\n";
    cout << "TeachingAssistant size in this build: " << sizeof(TeachingAssistant) << " bytes\n";
    return 0;
}