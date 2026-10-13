#include <format>
#include <iostream>
#include <cstring>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')

wchar_t* toCaps(const wchar_t* text);
void printWChar(const wchar_t *text);

int main()
{

    // --- Pointer Arithmetic

    int *myArray { new int[8] };

    *(myArray + 2) = 33; // same as `myArray[2]` but using pointer arithmetic
    println("{}", myArray[2]);

    // adding an integer x, to a pointer p of type T gives us another pointer to the 
    // memory at location: p + (x * sizeof(T)). This allows us to move in the steps
    // of the bytes or size of the pointer type.

    const wchar_t* myString { L"Hello, World" };

    print("myString toCaps: ");
    printWChar(toCaps(myString));
    println("");

    // We can choose to pass a specific portion,

    print("myString toCaps: ");
    // the number of bytes that the `wchar_t` takes up varies, but is usually
    // more than 1 byte, but we don't need to handle it ourselves; it just works
    printWChar(toCaps(myString) + 7); 
    println("");

    // Similarly, subtracting pointers, gives us the number of elements of the
    // pointed-to type between the two pointers, and not the absolute number of
    // bytes between them

    // --- Custom Memory Management

    // While the built-in memory allocation facilities in C++ are adequate, you
    // may be in a position that you really need to implement custom management
    // for example in when resource constraints are extremely tight, considering
    // that built-in memory allocation facilities typically have some overheads,
    // which while minimal can accumulate for larger programs. When managing
    // memory yourselves, you typically have classes that allocate a large chunk
    // of memory and the give them out in pieces, deallocating and/or reusing when
    // necessary. Performing custom memory management requires overloading the 
    // `new` and `delete` operators covered in Chapter 15 "Overlaoding C++ Operators"


    // --- Garbage Collections

    // C++ does not include a garbage collector. In programming languages that
    // support garbage collection, the programmer does not explicitly free memory
    // rather, objects to which there are no longer any references will be cleaned
    // up automatically at some point by the garbage collector runtime library.

    // In modern C++, you use smart pointers to manage memory, while in legacy code
    // you may see `new` and `delete` being used. You should avoid writing your own
    // garbage collector from scratch, if you'll every need to do so. You can research
    // existing specialised garbage-collection libraries which you can reuse.


    // --- Object Pools

    // Object pools allows many objects of the same type are reused instead of
    // being garbage-collected. They are ideal where you need to use many objects
    // of the same type over time, and creating each one incurs overhead.
    // Chapter 29 "Writing Efficient C++" contains further details on using object
    // pools for performance efficiency.

}

wchar_t* toCaps(const wchar_t* text)
{
    size_t textLen { wcslen(text) };
    wchar_t *result { new wchar_t[textLen + 1] };

    for (size_t i { 0 }; i < textLen; i++)
    {
        if (isupper(text[i])) result[i] = text[i];
        else result[i] = toupper(text[i]);
    }

    result[textLen] = '\0';

    return result;
}

void printWChar(const wchar_t *text)
{
    for (size_t i { 0 }; i < wcslen(text); i++)
    {
        print("{}", (char) text[i]);
    }
}