#include <iostream>
using namespace std;

int& highestMark(int marks[], int size) {
    int highest = 0;
    for (int i = 1; i < size; ++i)
        if (marks[i] > marks[highest]) highest = i;
    return marks[highest];
}

// DO NOT call this function: it returns a reference to a local variable.
// Uncommenting the function may produce a compiler warning and using its
// returned reference causes undefined behaviour.
int& dangerousLocalReference() {
    int local = 99;
    return local; // intentionally unsafe demonstration
}

int main() {
    int marks[] = {78, 92, 85, 88, 90};
    cout << "Highest mark: " << highestMark(marks, 5) << '\n';
    highestMark(marks, 5) += 2;
    cout << "After moderation: " << highestMark(marks, 5) << '\n';

    const int& readOnlyHighest = highestMark(marks, 5);
    cout << "Read-only reference: " << readOnlyHighest << '\n';

    int highestIndex = 0;
    for (int i = 1; i < 5; ++i)
        if (marks[i] > marks[highestIndex]) highestIndex = i;
    cout << "Index alternative: " << highestIndex << '\n';
    int* highestPointer = &marks[highestIndex];
    cout << "Pointer alternative: " << *highestPointer << '\n';
    return 0;
}