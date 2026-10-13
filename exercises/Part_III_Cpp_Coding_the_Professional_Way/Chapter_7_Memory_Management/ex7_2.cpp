#include <format>
#include <iostream>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')

// See `ex7_1.cpp` for problems
// You can run `diff` to compare changes (or select files on VS Code File Explorer and compare)

int main()
{
    const size_t numberOfElements { 10 };
    std::array<int, numberOfElements> values { };

    // Set values to their index value.
    for (size_t index { 0 }; index < numberOfElements; ++index)
    {
        values[index] = index;
    }

    // Set last value to 99.
    values[numberOfElements - 1] = 99; // FIX 1: Out-of-bounds memory access

    // Print all values.
    for (size_t index { 0 }; index < numberOfElements; ++index)
    {
        println("{} ", values[index]);  // FIX 2: Out-of-bounds memory access when `numberOfElements` equals 10
    }
}