#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class ClaimError : public runtime_error {
public:
    using runtime_error::runtime_error;
};

double approve(double billed, double cover) {
    // TODO 1 completed
    if (billed < 0 || cover < 0)
        throw invalid_argument("negative amount");
    if (billed > cover)
        throw ClaimError("exceeds cover");
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& e) {
        // TODO 2 completed: log and rethrow the same exception
        cout << "audit: " << e.what() << '\n';
        throw;
    }
}

struct Tracked {
    string name;
    explicit Tracked(string n) : name(std::move(n)) {
        cout << "created " << name << '\n';
    }
    ~Tracked() noexcept { cout << "destroyed " << name << '\n'; }
};

void validateTextAmount(const string& text) {
    double amount = stod(text); // invalid_argument for text; out_of_range for huge value
    if (amount < 0) throw invalid_argument("negative charge");
    cout << "valid amount " << amount << '\n';
}

void unknownPackage(const string& code) {
    if (code != "GOV-A" && code != "GOV-B")
        throw ClaimError("unknown package: " + code);
}

int main() {
    cout << "CLAIM SETTLEMENT TESTS\n";
    double cases[][2] = {{40000, 50000}, {60000, 50000}, {-1, 50000}};
    for (auto& c : cases) {
        try {
            double paid = settle(c[0], c[1]);
            cout << "approved " << paid << '\n';
        } catch (const ClaimError& e) {
            cout << "claim rejected: " << e.what() << '\n';
        } catch (const exception& e) {
            cout << "error: " << e.what() << '\n';
        }
    }

    cout << "\nOTHER ERROR TESTS\n";
    try { validateTextAmount("abc"); }
    catch (const invalid_argument& e) { cout << "text error: " << e.what() << '\n'; }

    try { unknownPackage("GOV-X"); }
    catch (const ClaimError& e) { cout << "package error: " << e.what() << '\n'; }

    try {
        Tracked resource("temporary-record");
        throw runtime_error("simulated processing failure");
    } catch (...) {
        cout << "top-level catch(...) handled failure\n";
    }

    // A deliberately impossible allocation request. The implementation should
    // reject this size with bad_alloc/bad_array_new_length; no huge memory is touched.
    try {
        size_t impossible = static_cast<size_t>(-1);
        unique_ptr<char[]> data(new char[impossible]);
        (void)data;
    } catch (const bad_alloc&) {
        cout << "allocation error: bad_alloc\n";
    } catch (const exception& e) {
        cout << "allocation request rejected: " << e.what() << '\n';
    }
    return 0;
}