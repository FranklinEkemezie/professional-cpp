#include <format>
#include <iostream>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')

// See `ex7_1.cpp` for fixes
// You can run `diff` to compare changes (or select files on VS Code File Explorer and compare)

int main()
{
    const size_t numberOfElements { 10 };
    int* values { new int[numberOfElements] };

    // Set values to their index value.
    for (int index { 0 }; index < numberOfElements; ++index)
    {
        values[index] = index;
    }

    // Set last value to 99.
    values[10] = 99; // PROBLEM 1: Out-of-bounds memory access

    // Print all values.
    for (int index { 0 }; index <= numberOfElements; ++index)
    {
        println("{} ", values[index]);  // PROBLEM 2: Out-of-bounds memory access when `numberOfElements` equals 10
    }
}