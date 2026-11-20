
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// Base Class
class Vehicle {
protected:
    string registration;
    double dailyRate;
    bool rented;

public:
    Vehicle(const string& reg, double rate)
        : registration(reg), dailyRate(rate), rented(false) {}

    virtual double charge(int days) const = 0;
    virtual string type() const = 0;

    bool rent() {
        if (rented)
            return false;

        rented = true;
        return true;
    }

    double returnVehicle(int daysLate = 0) {
        if (!rented)
            return 0.0;

        rented = false;

        int days = 1 + (daysLate > 0 ? daysLate : 0);
        return charge(days);
    }

    virtual void list() const {
        cout << type() << " | " << registration
             << " | Rs " << dailyRate << "/day | "
             << (rented ? "Rented" : "Available") << '\n';
    }

    virtual ~Vehicle() {}
};

// Bicycle Class
class Bicycle : public Vehicle {
public:
    Bicycle(const string& r, double rate)
        : Vehicle(r, rate) {}

    double charge(int days) const override {
        return dailyRate * days;
    }

    string type() const override {
        return "Bicycle";
    }
};

// MotorVehicle Class
class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel;
    string serviceDueDate;

public:
    MotorVehicle(const string& r, double rate,
                 double level, const string& due)
        : Vehicle(r, rate),
          fuelOrChargeLevel(level),
          serviceDueDate(due) {}
};

// TwoWheeler Class
class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const string& r, double rate,
               double fuel, const string& due)
        : MotorVehicle(r, rate, fuel, due) {}

    double charge(int days) const override {
        return dailyRate * days;
    }

    string type() const override {
        return "Two-wheeler";
    }
};

// Car Class
class Car : public MotorVehicle {
protected:
    int seats;

public:
    Car(const string& r, double rate, double fuel,
        const string& due, int s)
        : MotorVehicle(r, rate, fuel, due), seats(s) {}

    double charge(int days) const override {
        return dailyRate * days;
    }

    string type() const override {
        return "Car";
    }

    void list() const override {
        Vehicle::list();

        cout << "  Seats: " << seats
             << ", fuel: " << fuelOrChargeLevel
             << "%, service due: " << serviceDueDate << '\n';
    }
};

// ElectricCar Class
class ElectricCar : public Car {
private:
    double batteryKWh;
    double energyRatePerKWh;

public:
    ElectricCar(const string& r, double rate,
                double battery, double energyRate,
                const string& due, int s)
        : Car(r, rate, 100, due, s),
          batteryKWh(battery),
          energyRatePerKWh(energyRate) {}

    double charge(int days) const override {
        return dailyRate * days +
               batteryKWh * energyRatePerKWh;
    }

    string type() const override {
        return "Electric car";
    }

    void list() const override {
        Vehicle::list();

        cout << "  Seats: " << seats
             << ", battery: " << batteryKWh
             << " kWh, energy rate: Rs "
             << energyRatePerKWh << "/kWh\n";
    }
};

// New ElectricBus Class
class ElectricBus : public Vehicle {
private:
    int capacity;

public:
    ElectricBus(const string& r, double rate, int c)
        : Vehicle(r, rate), capacity(c) {}

    double charge(int days) const override {
        return dailyRate * days;
    }

    string type() const override {
        return "Electric bus";
    }

    void list() const override {
        Vehicle::list();

        cout << "  Passenger capacity: "
             << capacity << '\n';
    }
};

// Main Function
int main() {

    vector<unique_ptr<Vehicle> > fleet;

    // Creating vehicle objects using C++11
    fleet.push_back(
        unique_ptr<Vehicle>(new Bicycle("BI-101", 100))
    );

    fleet.push_back(
        unique_ptr<Vehicle>(
            new TwoWheeler("TW-202", 250, 80, "2026-12-01")
        )
    );

    fleet.push_back(
        unique_ptr<Vehicle>(
            new Car("CA-303", 1200, 65, "2026-12-10", 5)
        )
    );

    fleet.push_back(
        unique_ptr<Vehicle>(
            new ElectricCar("EV-404", 1500, 50, 8, "2026-12-15", 5)
        )
    );

    fleet.push_back(
        unique_ptr<Vehicle>(
            new ElectricBus("EB-505", 4000, 30)
        )
    );

    cout << "FLEET LIST\n";

    for (size_t i = 0; i < fleet.size(); i++) {
        fleet[i]->list();
    }

    cout << "\nRENT AND RETURN DEMONSTRATION\n";

    for (size_t i = 0; i < fleet.size(); i++) {
        cout << fleet[i]->type() << " rent: "
             << (fleet[i]->rent() ? "success" : "already rented")
             << '\n';
    }

    // Returning after two late days
    for (size_t i = 0; i < fleet.size(); i++) {
        cout << fleet[i]->type()
             << " return amount (2 late days): Rs "
             << fleet[i]->returnVehicle(2) << '\n';
    }

    cout << "\nFINAL STATUS\n";

    for (size_t i = 0; i < fleet.size(); i++) {
        fleet[i]->list();
    }

    return 0;
}
