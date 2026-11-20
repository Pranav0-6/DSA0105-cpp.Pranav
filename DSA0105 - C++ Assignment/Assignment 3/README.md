# OOP with C++ – Assignment 3 (CO3)

Seven independent C++17 programs are provided, one per task.

## Folder structure
- Task01: constructors, delegation, validation, explicit constructor
- Task02: deep copy constructor, copy assignment, destructor (Rule of Three)
- Task03: dynamic 2D seat allocation, booking/cancelling, destructor
- Task04: Money arithmetic and stream operator overloading
- Task05: Time increment/comparison and checked Playlist subscript
- Task06: dynamically allocated Text class, Rule of Three and operators
- Task07: Complex class and series/parallel impedance

## Compile and run in VS Code PowerShell
Open the terminal in the required task folder. Example for Task01:

```powershell
cd ".\Assignment 3\Task01"
g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe
.\main.exe
```

For each other task, enter its folder and repeat the compile/run commands.

## Address sanitizer (if supported by your GCC build)
```powershell
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g main.cpp -o main.exe
.\main.exe
```
If your Windows MinGW build does not support AddressSanitizer, use a supported GCC/WSL environment or Valgrind. Do not claim sanitizer results unless you actually run it.

## Expected / reference results
- Q2 main output line:
  `Ibuprofen ORS | Paracetamol Cetirizine | Paracetamol ORS`
- Q4:
  `Rs 200.00`
  `true`
  Paise carry result: `Rs 1.25`
- Q5: `a=0:59:59, b=1:00:01, t=1:00:01`
- Q7: series impedance is `10 - j15`; magnitude is approximately `18.03`.
  Parallel impedance for 10 ohm and j10 ohm is `5.00 + j5.00`; magnitude approximately `7.07`.

## Important report work still required
The source programs are executable starting implementations. Your assignment report must additionally contain:
1. Your name, register number, compiler/version, exact commands and GitHub URL.
2. Q1 object-state table, compiler default-constructor explanation, explicit test, negative-copy test and -Wreorder experiment.
3. Q2 shallow-copy demonstration (keep it separate and do not use it as the final safe implementation), memory diagrams, sanitizer results and timing measurements for 10, 1,000 and 100,000 medicines.
4. Q3 object lifetime order, memory diagram, missing-delete sanitizer experiment, allocation measurements and zero-row test.
5. Q4 negative subtraction policy, member/friend decision, and comparison with a double-based implementation.
6. Q5 prediction of the supplied Counter program: `5 7 7`; prefix/postfix timing at -O0 and -O2; invalid index tests.
7. Q6 forbidden-operator rules, copy count for `a + b + c`, sanitizer result and std::string timing comparison.
8. Q7 hand calculations, std::complex comparison and one limitation.

## Required prediction answers (write these in your report BEFORE running the supplied snippets)
- Q3 Logger snippet:
  `+A +B -B copyAc use -Ac +P -P end -A`
- Q5 Counter snippet:
  `5 7 7`

The Q3 Logger output above follows the supplied program's lifetime and copy rules. Record your own actual compiler output and explain any formatting differences.

## GitHub
Create `DSA01-<RegisterNumber>-Assignment3`, add one folder per task, include terminal screenshots and commit progressively (at least one commit per task).
