# OOP with C++ – Assignment 2 Solutions

Create one folder per question: Task01 through Task07. Each folder contains `main.cpp`.

## Compile and run (Windows / MinGW)
Open the terminal in the task folder:

```bash
g++ -std=c++17 -Wall -Wextra -O0 main.cpp -o main.exe
main.exe
```

For optimisation measurements in Q6/Q7, compile again using `-O2`:
```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o main.exe
main.exe
```

## Task overview
- Task01: call by value, reference, pointer, return by reference, default arguments.
- Task02: return by reference, const reference, index and pointer alternatives. The dangling-reference function is intentionally not called because doing so is undefined behaviour.
- Task03: default arguments and overloads for grams, kilograms and Parcel.
- Task04: class with private transaction array and circular storage of the latest 10 transactions.
- Task05: static data/function members and an array of ticket objects.
- Task06: friend and inline functions for time comparison.
- Task07: redesign of a shifting history as a circular buffer, with a simple timing comparison.

## Important submission steps
1. Read each source file and understand every line.
2. Before running the prediction questions in Q1 and Q5, write your predicted output in your report.
3. Compile and run every task yourself.
4. Save screenshots of the terminal output in the matching task folder.
5. Add your name, register number, compiler version and actual results to this README.
6. Create GitHub repository `DSA01-<RegisterNumber>-Assignment2`.
7. Commit progressively, one task at a time. Do not make only one final upload.

## Notes for the report
- Q1 expected stored fees: value = 45000; reference = 40500; pointer = 40500.
- Q1 given predict-output snippet: `1 12 13`, then `1 100`, then `16 13 6`.
- Q5 given Token snippet: `101 103 104 4`.
- Q5 BusTicket expected output:
  Asha: Seat 1
  Bala: Seat 2
  Chitra: Seat 3
  Dev: Waiting
  Issued: 3
- Q6 expected first line: `205 false`.
- Q7 timing values depend on your computer and compiler. Record your own measured values; do not copy sample timings.
