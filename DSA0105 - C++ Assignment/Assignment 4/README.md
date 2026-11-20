# OOP with C++ – Assignment 4 (CO4): Designing Reusable Class Hierarchies

Six independent C++17 programs are included.

## Task map
1. **Task01** – Payroll hierarchy; abstract `Staff`, `Professor`, `LabAssistant`, `GuestFaculty`; runtime polymorphism.
2. **Task02** – `Person`, `Student`, `Staff`, `TeachingAssistant`, `ResearchScholar`; virtual inheritance resolves the diamond.
3. **Task03** – Base/member constructors and destructors; `Address` and `Course` member classes; virtual diamond.
4. **Task04** – Virtual functions, `override`, virtual destructor, `unique_ptr`, and object slicing demonstration.
5. **Task05** – Cart objects, pointer/reference/direct access, `this`, chaining, heap object, array of pointers and maximum total.
6. **Task06** – Abstract Vehicle hierarchy and extensible fleet; bicycle, two-wheeler, car, electric car and newly added electric bus.

## Compile and run
In VS Code terminal, move to one task folder, for example:
```powershell
cd ".\Assignment 4\Task01"
g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe
.\main.exe
```
Repeat from Task02 through Task06. If Smart App Control blocks locally compiled EXEs on your Windows laptop, use WSL/Ubuntu GCC or an online C++ compiler; do not weaken Windows security just to run an assignment.

## Key expected/predicted outputs
- **Task02:** one `Person` base subobject is shared by `Student` and `Staff` in `TeachingAssistant` because both inherit `virtual public Person`.
- **Task03 Complete Code:** `192311001 Kavya (19) Salem-636001` is the required output for the Student constructor example in the assignment. The source includes the corresponding member initializer approach and additional construction/destruction traces.
- **Task03 Vehicle prediction:** `Vehicle Engine Car | ~Car ~Engine ~Vehicle` (each message appears with the spacing in the supplied snippet).
- **Task04 prediction snippet:** `3.5 4 3.5` for the original code in the assignment: non-virtual `rate()` call through base pointer is statically bound; virtual `vrate()` dispatches to SeniorAccount; sliced Account copy has only base behavior.
- **Task05 Complete Code:** `324.00`.
- **Task06:** demonstrates successful rent/return of each vehicle type and extension by adding ElectricBus.

## Written report requirements
Include the following in your report:
- Task 1: at least five design deficiencies, UML diagram, <=100-word design defence, compare one class + switch alternative.
- Task 2: is-a/has-a table, inheritance types, diamond explanation, class declarations, access table, composition alternative and `sizeof` observations.
- Task 3: initializer lists, direct initialization of virtual base by most-derived class, constructor/destructor order, member-class explanation, pointer-to-Address alternative.
- Task 4: explain static vs dynamic binding, virtual destructor, object slicing, sanitizer evidence, `unique_ptr` alternative.
- Task 5: direct/pointer/reference/heap access, `this` and `*this`, chaining, pointer-array maximum, vector reallocation caveat.
- Task 6: testable requirements, UML, pseudocode, rent/return behavior, late charge, extension proof, switch alternative.

## Useful theory answers
### Task 1 deficiencies
Repeated name/id/basic fields and DA calculation; public data breaks encapsulation; GuestFaculty uses inconsistent names; `da` is unused; 0.42 is a magic number; no common base interface; mixed staff types cannot be processed uniformly; adding categories requires changing client code.

### Task 2 relationships
Student is-a Person; Staff is-a Person; TeachingAssistant is-a Student and Staff (multiple inheritance); ResearchScholar is-a Student (multilevel extension); fellowship is a data member (has-a/value attribute). Student and Staff use virtual public Person to avoid duplicate Person subobjects in TeachingAssistant.

### Task 2 access under inheritance
For a public member of Person: public inheritance -> public; protected inheritance -> protected; private inheritance -> private.
For a protected member: public inheritance -> protected; protected inheritance -> protected; private inheritance -> private.
For a private member: not directly accessible in Student under any inheritance mode.

### Task 3 constructor/destructor rule
Construction: virtual bases first, then direct base classes in declaration order, then member objects in declaration order, then derived constructor body. Destruction is reverse order.

### Task 4 rules
If a class is intended to be used polymorphically, give it a virtual destructor. Use `override` on derived overrides. Use references/pointers to preserve dynamic type; copying a derived object into a base object slices the derived portion.

### Task 5
`this` is a pointer to the current object; `*this` is the current object as an lvalue. Returning `Cart&` allows chaining without copying. A pointer to a local object must not outlive that object. `new` must be paired with `delete`; prefer automatic objects or smart pointers.

### Task 6 complexity
Listing or finding a vehicle among n vehicles is O(n); one charge calculation is O(1). `vector<unique_ptr<Vehicle>>` owns objects safely and permits polymorphism. Adding a new derived vehicle type does not require modifying the base class or existing derived classes.
