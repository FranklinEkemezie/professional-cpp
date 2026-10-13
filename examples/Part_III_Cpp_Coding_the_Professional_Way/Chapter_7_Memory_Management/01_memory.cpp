#include <format>
#include <iostream>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')

int main()
{

    [[maybe_unused]]
    int i { 7 }; // `i` is an automatic variable allocated on the stack
    // it is automatically deallocated when it goes out of scope.

    // Using `new` keyword allocates memory on the free store

    int* ptr { nullptr }; // `ptr` is still on the stack
    ptr = new int; // memory is allocated on the free store and a pointer 
    // to it stored in `ptr` variable. `ptr` is automatically deallocated,
    // but the memory on free store is not

    delete ptr; ptr = nullptr; // most always free

    // Pointers can also live on the free store
    int** handle { nullptr };

    handle = new int*;  // allocate memory for pointer to integer
    *handle = new int;  // allocate memory for integer

    // here, `handle` resides on the stack (freed automatically)
    // but `*handle` resides on the free store

    delete *handle; *handle = nullptr;
    delete handle; handle = nullptr;

    // Do not use C-style memory management functions:
    // `malloc()`, `realloc()` and `free()`, etc.
    // `new` constructs proper objects, while `malloc()` just allocates
    // memory big enough to store the object. Accessing object data
    // members and functions of free-store object is safe with `new` but
    // not with `malloc()`. Also, `delete` calls the object's destructor
    // but `free()` does not

    // -- when memory allocation fails
    // by default, an exception is thrown when `new` fails.
    // you can "catch" this error gracefully, but most times, there's
    // probably no need to run the program if there's no memory.
    // you can also use the alternative version that does not throw exception

    ptr = new(std::nothrow) int; // `ptr` is `nullptr` if `new` fails


}

void leaky()
{
    new int; // Orphaned memory, potential leak
    
    println("I just leaked an int!");
}