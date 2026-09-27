#include <array>
#include <iostream>
#include <initializer_list>

int sum(std::initializer_list<int> values)
{
    int total { 0 };
    for (int value : values) { total += value; }
    return total;
}

int main()
{


    // --- while loop
    std::cout << "--- while loop" << std::endl;

    int i { 0 };
    while (i < 5)
    {
        std::cout << "This is silly.\n";
        i++;
    }

    // --- do/while loop
    std::cout << "--- do/while loop" << std::endl;
    i = 100;
    do
    {
        std::cout << "This is silly.\n";
        ++i;
    } while (i < 5);

    // --- for loop
    std::cout << "--- for loop" << std::endl;
    for (int i { 0 }; i < 5; ++i)
    {
        std::cout << "This is silly.\n";
    }
    
    // --- range-based for loop
    std::cout << "--- range-based for loop" << std::endl;

    // This type of loop can be used for C-style arrays, initialiser lists, and
    // any type that supports `begin()` and `end()` functions returning iterators
    // such as `std::array`, `std::vector`, and other Standard Library containers.

    std::array arr { 1, 2, 3, 4 };
    for (int i : arr) { std::cout << i << "\n"; }

    // you can also use initialisers directly in the range-based for loop, similar
    // to `if` and `switch` statements.

    for (std::array arr { 1, 2, 3, 4 }; int i : arr) { std::cout << i << "\n"; }

    // --- Initialiser Lists (from <initializer_list>)
    // This makes it easy to write functions that can accept a variable number of arguments.
    // The `std::initializer_list` type is a class template, and it requires you to
    // specify the type of elements.

    // the `sum()` function is declared above and can take variable number of arguments
    int a { sum({ 1, 2, 3 }) };
    int b { sum({ 10, 20, 30, 40, 50, 60 }) };

    std::cout << "sum a: " << a << std::endl;
    std::cout << "sum b: " << b << std::endl;

    // the `sum()` is also type-safe, we can't pass another type in the braced initialiser
    // int c { sum({ 1, 2, 3.0 }) };

}