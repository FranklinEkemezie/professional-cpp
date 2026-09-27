#include <format>
#include <iostream>

void mysteryFunction(const std::string *someString)
{
    // *someString = "Test"; // will not compiler
}

int main()
{

    // In C++, memory is divided into: stack and free store.

    // When a function is called, a stack frame is added/pushed ontop of the
    // stack. The stack frame acts like a memory workspace for all the variables
    // and data the function needs to execute. The calling function passes data
    // as arguments to the function which are then **copied** to the new stack frame.
    // This means, the executing function can modify and change the data it received
    // in its memory workspace without affect the caller's data since it's working with
    // a copy of it. When the function is done executed, its frame is removed/popped 
    // from the stack returning control to the calling function. For this reason,
    // stack-allocated variables do not need to be deallocated/deleted manually (by 
    // the programmer)

    // The free store, on the other hand, is an area of memory, that is completely 
    // independent of the current function or stack frame. In C, this is called 
    // a "heap", and you can think of it as a sort of messy heap/pile of bits. Your
    // program can add new bits to the pile or modify them. However, you are responsible
    // for deallocating (deleting) any memory allocated on the free store. Failure to
    // do this results in a pile of bits so large that you can run of memory, and your
    // program crashes. This is known as a memory leak (unfreed memory). C++ introduces
    // smart pointers that can help in automatic cleanup and freeing of allocated memory.

    int *myIntegerPointer { nullptr };

    if (! myIntegerPointer) { std::cout << std::format("myIntegerPointer is a null pointer.") << std::endl; }

    // Use the `new` operator to allocate memory
    myIntegerPointer = new int;

    // Note that `myIntegerPointer` is stored on the `main()` function stack frame
    // but the memory allocated via `new int` is in the free store. We can access this
    // value at the free store memory by dereferencing it.

    *myIntegerPointer = 8;  // go to allocated memory and set the value to 8

    delete myIntegerPointer;    // deallocate the memory
    myIntegerPointer = nullptr; // recommended: reset it to `nullptr` to prevent it from being used after deallocation

    // Pointers can also point to variables on the stack or even another pointer.

    int i { 8 };
    myIntegerPointer = &i;  // get the address of `&` of the variable and make the pointer point to it.

    struct Employee
    {
        char firstInitial;
        char lastInitial;
        int employeeNumber;
        int salary { 75'000 };        
    };

    Employee *anEmployee { new Employee { 'J', 'D', 42, 80'000 } };
    std::cout << std::format("{}", (*anEmployee).salary) << std::endl;  // dereference pointer to `Employee` struct and access `salary` data member
    std::cout << std::format("{}", anEmployee->salary) << std::endl;    // clean, less messier syntax to dereference and field access

    // you should check if a pointer is valid before dereferencing it:
    bool isValidSalary { anEmployee && anEmployee->salary > 0 };    // using short-circuiting, more verbose version may check `ptr != nullptr`

    std::cout << std::format("isValidSalary: {}", isValidSalary) << std::endl;

    // --- Dynamically Allocated Arrays
    int arraySize { 8 };
    int *myVariableSizedArray { new int[arraySize] };

    myVariableSizedArray[3] = 2;    // can work with this pointer as if it were an array

    delete[] myVariableSizedArray;  // do not forget to free, this time using `delete[]`
    myVariableSizedArray = nullptr; // ensure pointer is not used as valid pointer (if it is checked before use)

    // Lastly, you should avoid using `malloc()` and `free()` from C and instead use the 
    // `new` (or `new[]`) and `delete` (or `delete[]`) from C++. Modern C++, however, should
    // take advantage of more modern constructs such as Standard Library containers and 
    // smart pointers for dynamically allocated memory.
    // To prevent memory leaks, every call to `new` (or `new[]`) should be paired with a call 
    // to `delete` (or `delete[]`). Failure to do so, or mismatching calls, may result in memory leaks or worse.

    // --- Null Pointer Constant
    // Null pointer `nullptr` was introduced to C++11 to prevent subtle bugs from using the older
    // `NULL` (from <cstddef>) which was merely the constant 0 (zero). The `nullptr` itself is a
    // pointer and must be used as such, unlike `NULL` which could pass as an integer or pointer value.

    // --- The Use of `const`
    // The `const` keyword (short for "constant") can be used in a few different but related
    // ways in C++. In general, it specifies that something remains unchanged. Any attempt to 
    // change them result in compilation error. The compiler also uses this knowledge to produce
    // better, optimised code.

    // `const` as a Qualifier for a Type
    // Here, it is used as an equivalent for #define in C
    // In C++, you can make any variable `const`, including global variables and class data members

    const int versionNumberMajor { 2 };
    const int versionNumberMinor { 1 };
    const std::string productName { "Super Hyper Net Modulator" };
    const double PI { 3.141'592'653'589'793'238'462 };

    // `const` with Pointers

    // Easy-to-remember rule for reading pointers: Read from left to right

    // Below, we have: ip -> * -> int -> const
    // `ip` is a pointer to `int` constant i.e. whatever `int`(s) `ip` points to cannot
    // be changed. You can, however, modify `ip` itself.
    const int* ip; 
    ip = new int[10];   // okay
    // ip[4] = 5;          // does not compile!

    // Below, we have: ip -> * -> const -> int
    // `ip` is a pointer to constant `int`. again, the `int`(s) which `ip` points to cannot
    // be modified. This is equivalent to the previous declaration.
    int const *ip1;
    ip1 = new int[10];  // okay
    // ip1[4] = 5;         // does not compile! 
    
    // Below, we have: ip -> const -> * -> int
    // `ip` is a constant pointer to `int`(s). Here the pointer variable itself is constant
    // and cannot be changed
    int *const ip2 { nullptr };
    // ip2 = new int[10];  // does not compile
    // ip2[4] = 5;         // of course, error: deferencing a null pointer (program crashes), 
    // you should allocate memory and initialise a constant pointer when you declare it.

    // We can mark both pointer and the value to which it points to as `const`
    int const* const ip3 { nullptr };   // constant pointer to constant int, or equivalently:
    const int* const ip4 { nullptr };   // const pointer to int constants.

    // Another simple rule: except from the case where `const` is at the beginning
    // the `const` applies to anything to its left.
    // If the variable is pointer to pointer to pointer and so on, you can extend it any
    // number of levels of indirection, for example:
    // const int * const * const * const ip { nullptr };

    // `const` to protect parameters
    // Here, the `const` keyword is used to cast a non-const parameter variable to a 
    // const one. This is useful for functions which merely uses a parameter but do not
    // need to change it while doing so. When the function definition attempts to modify
    // such parameter, the program fails to compile. This is typically not a big deal for 
    // primitive types such as `int` or `double` etc (compilation still fails) as the
    // function only receives a copy. It is particularly useful for pointers, where the
    // values at memory they point to can be modified, even though the pointer is not modified.
    // Declaring a pointer parameter as `const` prevents modifying it.

    std::string myString { "The string" };
    mysteryFunction(&myString);

    // `const` member functions
    // The `const` keyword can be used to mark class member functions as `const`, preventing
    // them from modifying data members of the class. This is common for read-only member
    // functions (called inspectors) since they do not need to modify the data members like
    // the non-const ones (called mutators)
    // To do so, the `const` keywork is appended to the function declaration and definition:
    // From `AirlineTicket` class from `13_oop.cpp`:
    // double calculatePriceInDollars() const;
    // std::string getPassengerName() { ... }
    



    return 0;
}