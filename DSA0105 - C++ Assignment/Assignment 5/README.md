# OBJECT ORIENTED PROGRAMMING WITH C++ – ASSIGNMENT 5 (CO5)
## Reliable Software with Runtime Polymorphism and Exceptions

This solution pack contains four implementation folders and design notes for Part A.

## Folder guide
- `Task01_PolymorphicBilling`: abstract Bill hierarchy, OP/IP/day-care/emergency bills, SelfPay/Insurance/GovernmentScheme payers, common processing.
- `Task02_ExceptionHandling`: completed TODO 1 and TODO 2 for claim approval, invalid text/package tests, allocation failure test, RAII and top-level catch. Includes A2 and A5 prediction programs.
- `Task03_PerformanceBenchmark`: virtual vs switch vs `std::variant` timings for 1,000, 1,000,000 and 10,000,000 bills; return-code vs exception validation for 0%, 1% and 50% invalid claims.
- `Task04_ExtensionAndSanitizer`: adds MaternityBill and CorporateTieUp without editing existing base/derived classes; RAII exception test.

## Compile and run
Use g++ with C++17:
```bash
g++ --version
g++ -std=c++17 -Wall -Wextra main.cpp -o main
./main
```
On Windows PowerShell, run `.\main.exe` after compiling. If Windows Smart App Control blocks local EXE files, use WSL/Ubuntu or an online compiler; do not disable Windows security just for the assignment.

For sanitizer builds (GCC/Clang on a supported environment):
```bash
g++ -std=c++17 -Wall -Wextra -g -O1 -fsanitize=address -fno-omit-frame-pointer main.cpp -o main_asan
./main_asan
```
For performance measurements:
```bash
g++ -std=c++17 -O2 -DNDEBUG -Wall -Wextra main.cpp -o benchmark
./benchmark
```
Record your own timings. Results depend on CPU, compiler, operating system and load. Do not copy fabricated timing values into the report.

## Part A – Design notes

### A1.1 Common Bill interface
Every bill has a patient identifier/name and provides:
- `total() const`: calculate the complete bill amount.
- `type() const`: return the bill category.
- `print() const`: display category, patient and total.

Common data: patient identifier/name. Category-specific data stays in derived classes.

### A1.2 UML hierarchy (text form)
```text
                         <<abstract>> Bill
                 --------------------------------
                 # patient : string
                 + total() : double {pure virtual}
                 + type() : string {pure virtual}
                 + print() : void {virtual}
                 + ~Bill() {virtual}
                   /       |        |        \\
                  /        |        |         \\
       OutPatientBill InPatientBill DayCareBill EmergencyBill
       total() override total() override total() override total() override
       type() override  type() override  type() override  type() override

                         <<abstract>> Payer
                 --------------------------------
                 + amountCovered(Bill) : double {pure virtual}
                 + name() : string {pure virtual}
                    /          |             \\
               SelfPay     Insurance     GovernmentScheme
```

### A1.3 SIMATS-style pseudocode – total for all bills
```text
ALGORITHM CalculateDayTotal(Bills, N)
BEGIN
    SET DayTotal = 0
    FOR i = 0 TO N - 1 DO
        DayTotal = DayTotal + Bills[i]->total()
    END FOR
    DISPLAY DayTotal
END
```
Time complexity O(n); auxiliary space O(1). Each bill total is assumed O(1).

### A1 alternative: one struct and switch
Store `type`, patient and all possible charge fields in one `BillRecord`. `total(record)` uses `switch(type)`. Totaling n bills remains O(n), with O(1) per record, but every new category requires editing the switch and shared structure. The structure may waste space because it reserves fields for categories that do not use them. Polymorphism stores only relevant derived data but normally adds a vptr and uses dynamic dispatch.

### A2.1 Early vs late binding
Early binding selects a function at compile time (non-virtual call). Late binding selects the final overrider at run time when a virtual function is called through a base pointer/reference. `b->total()` dispatches to the actual object's `total()` implementation.

### A2.2 Conceptual vtable
```text
Bill vtable (abstract)
  destructor -> Bill destructor
  total      -> pure virtual slot
  type       -> pure virtual slot

OutPatientBill vtable
  destructor -> OutPatientBill destructor
  total      -> OutPatientBill::total
  type       -> OutPatientBill::type

InPatientBill vtable
  destructor -> InPatientBill destructor
  total      -> InPatientBill::total
  type       -> InPatientBill::type

b -> object vptr -> derived vtable -> correct total()
```
Vtables are a common implementation technique, not a layout mandated in exact form by the C++ standard.

### A2.3 Virtual destructor
Deleting a derived object through `Bill*` requires a virtual base destructor so the derived destructor and base destructor execute. Without it, deleting through a base pointer is undefined behavior.

### A2 prediction
Expected output:
```text
500 ~OPBill ~Bill
```
`show()` itself is non-virtual, but it calls virtual `total()`. The inner call dispatches to `OPBill::total()`. Deletion through `Bill*` calls derived then base destructors because `~Bill` is virtual. Removing `virtual` makes deletion through `Bill*` undefined behavior; do not rely on any particular output. Run sanitizer as an experiment, but a sanitizer may or may not diagnose every undefined behavior case.

### A3 Payer design
`Payer` is abstract and declares `amountCovered(const Bill&) const`. `SelfPay` covers the full bill. `Insurance` stores a cover limit and co-payment percentage; amount covered is the lesser of the cover limit and the amount remaining after patient co-payment. `GovernmentScheme` stores a package rate and covers the lesser of package rate and bill total. Add a new `CorporateTieUp : public Payer`; implement the interface without changing existing payer classes.

Alternative: store a callable policy (`std::function<double(const Bill&)>`) plus configuration data. Call cost is O(1) for simple policies in either design. A class groups data and behavior; a function object needs a separate configuration object or captured values.

### A4 Exception strategy
Errors: negative charge, invalid days/rates, claim exceeding cover, unknown package code, missing patient record, malformed numeric input, out-of-range numeric input and allocation failure. Example hierarchy:
```text
std::exception
  std::runtime_error
    BillingError
      ClaimError
```
Use `std::invalid_argument` for malformed/negative input, `std::out_of_range` for range errors, `ClaimError` for policy rejection, and `std::bad_alloc` for allocation failure. Constructors/validation/claim functions may throw. Destructors and cleanup functions should be `noexcept`; destructors should not throw during stack unwinding because a second active exception can terminate the program.

Alternative return-code design: return `{status, amount, message}` or `bool` plus output/error object. Normal-path cost is predictable and avoids exception machinery; every caller must check the status and propagate the error data. Error paths require explicit branches and can be missed.

### A5 Recovery and rethrowing
Catch low-level errors at the layer that can add useful context or log them. Use `throw;` to rethrow the currently handled exception unchanged. Catch at the application boundary to report a safe message. Do not use `throw e;` when the original dynamic exception type must be preserved: it can copy/slice to the static type of `e`.

Stack unwinding destroys automatic objects in reverse construction order as an exception leaves scopes. RAII types (`std::string`, `std::vector`, `std::unique_ptr`, file streams and custom guards) release resources automatically.

A5 prediction expected output:
```text
~f ~main caught 42
```
`f()`'s local guard is destroyed first while unwinding out of `f`; then `main`'s guard is destroyed as the exception exits the try block. The statement after `f()` is skipped.

Alternative manual `delete` in catch blocks is fragile: every error path must free each resource; adding a new throw point can create a leak. RAII keeps cleanup code in the resource-owning object's destructor.

## Part B – interpretation and report guidance

### B1 Complete Code expected output
```text
OP Ravi: 1700
IP Meena: 47500
Total 49200
```
The provided `Task01` source implements the TODO functions with pure virtual `total()` and virtual `type()`. If `total()` is made non-virtual while declared pure virtual, the declaration is invalid: a pure virtual function must be virtual. If the keyword is removed but `= 0` remains, the compiler diagnoses that a non-virtual function cannot be pure.

### B2 prediction program expected output
For the supplied `validate/process` code:
```text
ok done caught negative [log too large] caught too large
```
The negative value throws `invalid_argument`, which is not caught in `process`; it reaches `main`. The too-large value throws `out_of_range`, is logged in `process`, then rethrown with `throw;` and caught in `main`. Only the out-of-range exception matches the logging handler.

Completed TODO claim program expected output:
```text
approved 40000
audit: exceeds cover
claim rejected: exceeds cover
error: negative amount
```
`throw;` rethrows the original exception. Replacing it with `throw e;` throws a new exception expression based on the static type of `e` (here `ClaimError`); in more general base-reference handlers it can slice a derived exception.

### B3 benchmarking
The benchmark source prints your measured wall-clock times and checksums. Run optimized (`-O2`) and record the actual output from your machine. Repeat at least 3 times and compare median or best stable result. Keep hardware/compiler details. Virtual calls, switch dispatch and `std::visit` are all O(n) for n bills. Exception validation can be expensive when exceptions are frequent; exceptions are generally best for exceptional paths, not routine control flow. Do not claim a universal winner from one run.

### B4 production decision
For 15 hospitals, 200,000 bills/day and frequent new bill/payer types, polymorphic interfaces are maintainable and support extension without editing stable existing classes. Exceptions are suitable for exceptional failures; expected policy rejection may be better represented as a normal result/status. Production deployment also needs persistent transactions, audit logs, input validation, access control, tests, monitoring and safe retry/idempotency. A plug-in/configuration rules engine reduces code releases for rate changes but needs schema validation, versioning and rule governance; interpreted rules may cost more per bill than a direct virtual call.

## Submission checklist
- Create GitHub repository: `DSA01-<RegisterNumber>-Assignment5`.
- Add your name, register number, g++ version and exact commands to README.
- Keep one folder per task; include source, input/output evidence and screenshots.
- Make at least one meaningful commit per task.
- Include Part A UML, vtable, pseudocode, exception hierarchy and alternatives.
- Include actual benchmark measurements and sanitizer logs. Do not invent measurements.
