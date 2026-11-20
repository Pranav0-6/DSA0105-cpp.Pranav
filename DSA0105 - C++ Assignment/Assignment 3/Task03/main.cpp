#include <iostream>
#include <string>
using namespace std;

class Event {
private:
    string name;
    int rows;
    int seatsPerRow;
    bool** seats;
    int booked;

public:
    Event(const string& eventName, int r, int s)
        : name(eventName), rows(r > 0 ? r : 0),
          seatsPerRow(s > 0 ? s : 0), seats(nullptr), booked(0) {
        if (seatsPerRow == 0) rows = 0;
        if (rows > 0 && seatsPerRow > 0) {
            seats = new bool*[rows];
            int made = 0;
            try {
                for (; made < rows; ++made) {
                    seats[made] = new bool[seatsPerRow]{};
                }
            } catch (...) {
                for (int i = 0; i < made; ++i) delete[] seats[i];
                delete[] seats;
                throw;
            }
        }
        cout << "Created event: " << name << '\n';
    }

    bool book(int r, int s) {
        if (!valid(r, s) || seats[r][s]) return false;
        seats[r][s] = true;
        ++booked;
        return true;
    }

    bool cancel(int r, int s) {
        if (!valid(r, s) || !seats[r][s]) return false;
        seats[r][s] = false;
        --booked;
        return true;
    }

    bool valid(int r, int s) const {
        return r >= 0 && r < rows && s >= 0 && s < seatsPerRow;
    }

    ~Event() {
        for (int r = 0; r < rows; ++r) delete[] seats[r];
        delete[] seats;
        cout << "Closed event: " << name << ", booked seats: " << booked << '\n';
    }
};

int main() {
    cout << "1. Stack object\n";
    Event college("College Day", 2, 3);
    college.book(0, 0);
    college.book(1, 2);
    college.cancel(0, 0);

    cout << "2. Heap object\n";
    Event* concert = new Event("Music Concert", 3, 4);
    concert->book(1, 1);
    delete concert;

    cout << "3. Block-scope object\n";
    {
        Event workshop("Workshop", 1, 2);
        workshop.book(0, 1);
    }

    cout << "4. Zero-row event\n";
    Event empty("No Seat Event", 0, 5);
    return 0;
}