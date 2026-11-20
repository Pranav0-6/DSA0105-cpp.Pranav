#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int K = 10;
const int OPERATIONS = 200000;

class ShiftingHistory {
    int data[K]{};
    int count = 0;
public:
    void add(int value) {
        if (count < K) data[count++] = value;
        else {
            for (int i = 1; i < K; ++i) data[i - 1] = data[i];
            data[K - 1] = value;
        }
    }
    int checksum() const {
        int sum = 0;
        for (int i = 0; i < count; ++i) sum += data[i];
        return sum;
    }
};

class CircularHistory {
    int data[K]{};
    int count = 0;
    int next = 0;
public:
    void add(int value) {
        data[next] = value;
        next = (next + 1) % K;
        if (count < K) ++count;
    }
    int checksum() const {
        int sum = 0;
        for (int i = 0; i < count; ++i)
            sum += data[(next - count + i + K) % K];
        return sum;
    }
};

int main() {
    ShiftingHistory original;
    CircularHistory redesigned;

    auto start1 = steady_clock::now();
    for (int i = 0; i < OPERATIONS; ++i) original.add(i);
    auto end1 = steady_clock::now();

    auto start2 = steady_clock::now();
    for (int i = 0; i < OPERATIONS; ++i) redesigned.add(i);
    auto end2 = steady_clock::now();

    auto oldUs = duration_cast<microseconds>(end1 - start1).count();
    auto newUs = duration_cast<microseconds>(end2 - start2).count();

    cout << "Operations: " << OPERATIONS << '\n';
    cout << "Original shifting checksum: " << original.checksum() << '\n';
    cout << "Redesigned circular checksum: " << redesigned.checksum() << '\n';
    cout << "Shifting add time (microseconds): " << oldUs << '\n';
    cout << "Circular add time (microseconds): " << newUs << '\n';
    cout << "Both designs retain only the latest " << K << " values.\n";
    return 0;
}