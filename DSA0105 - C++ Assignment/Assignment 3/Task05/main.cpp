#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Time {
private:
    int totalSeconds;

public:
    Time(int h = 0, int m = 0, int s = 0)
        : totalSeconds(h * 3600 + m * 60 + s) {
        if (totalSeconds < 0) totalSeconds = 0;
    }

    Time& operator++() { // prefix
        ++totalSeconds;
        return *this;
    }

    Time operator++(int) { // postfix
        Time old = *this;
        ++totalSeconds;
        return old;
    }

    bool operator==(const Time& other) const {
        return totalSeconds == other.totalSeconds;
    }

    bool operator<(const Time& other) const {
        return totalSeconds < other.totalSeconds;
    }

    friend ostream& operator<<(ostream& out, const Time& t) {
        int h = t.totalSeconds / 3600;
        int m = (t.totalSeconds % 3600) / 60;
        int s = t.totalSeconds % 60;
        return out << h << ':' << (m < 10 ? "0" : "") << m
                   << ':' << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
private:
    string* tracks;
    int count;

public:
    explicit Playlist(int n) : tracks(n > 0 ? new string[n] : nullptr),
                               count(n > 0 ? n : 0) {}
    ~Playlist() { delete[] tracks; }

    Playlist(const Playlist&) = delete;
    Playlist& operator=(const Playlist&) = delete;

    string& operator[](int index) {
        if (index < 0 || index >= count) throw out_of_range("Track index out of range");
        return tracks[index];
    }

    const string& operator[](int index) const {
        if (index < 0 || index >= count) throw out_of_range("Track index out of range");
        return tracks[index];
    }

    int size() const { return count; }
};

int main() {
    Time t(0, 59, 59);
    Time a = t++;
    Time b = ++t;
    cout << "a=" << a << ", b=" << b << ", t=" << t << '\n';

    Playlist playlist(3);
    playlist[0] = "Song One";
    playlist[1] = "Song Two";
    playlist[2] = "Song Three";
    for (int i = 0; i < playlist.size(); ++i)
        cout << i << ": " << playlist[i] << '\n';

    try {
        cout << playlist[-1] << '\n';
    } catch (const out_of_range& e) {
        cout << "Error: " << e.what() << '\n';
    }

    Time c(1, 0, 0), d(1, 0, 1);
    cout << boolalpha << "c < d: " << (c < d) << '\n';
    return 0;
}