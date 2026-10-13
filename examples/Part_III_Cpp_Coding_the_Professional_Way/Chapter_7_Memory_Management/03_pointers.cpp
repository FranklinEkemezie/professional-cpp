#include <format>
#include <iostream>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')

void printArray(int arr[], int N);

void doubleInts(int* theArray, size_t size);
void doubleInts(int theArray[], size_t size);   // identical to  first one
void doubleInts(int theArray[2], size_t size);  // also identical
// technically, the compiler does not care about length since it does not
// copy it which takes time and can be memory consuming

// to pass known-length stack-based arrays "by reference" to a function,
// you can use the syntax below (this does not work for free store-based arrays)
void doubleIntsStack(int (&theArray)[4]) { doubleInts(theArray, 4); }

// we can let the compiler deduce the size by using a function template

template <size_t N>
void doubleIntsStack(int (&theArray) [N])
{
    for (size_t i { 0 }; i < N; i++)
    {
        theArray[i] *= 2;
    }
}


int main()
{

    // pointers get their bad name from the fact they're easy to abuse
    // for example, you could do this:
    // char* scaryPointer { (char *) 7 };
    // you probably don't know what is at memory address 7.
    // doing things like this could crash your program, if you are lucky,
    // or results in unexpected behaviour.

    // We can think of pointers in two ways:
    // - as memory address, that allows the program to jump around in memory
    // - as arrows from the pointer to the memory
    // When you dereference a pointer, you "jump" to memory address or you 
    // follow the arrow to where it points in memory.

    // since pointers are just memory addresses, they are weakly typed.
    // you can perform a C-style cast from one pointer to another

    class Document {  };

    Document* documentPtr { new Document { } };
    char* myCharPtr { (char *) documentPtr }; // works, but unsafe

    println("myChar: {}", *myCharPtr); // crashes?? weird bugs??

    // C++ static_cast provides more safety

    // char* myCharPtr1 { static_cast<char *>(documentPtr) }; // won't compile: types are unrelated

    delete documentPtr; documentPtr = nullptr; myCharPtr = nullptr;

    // --- Array-Pointer duality

    // 1) Arrays can "decay" to pointers

    int myIntArray[10] { };
    int *myIntPtr { myIntArray };   // `myIntArray` is used as ("decays to") pointer to first element

    myIntPtr[4] = 5;    // `myIntPtr` pointer access array using array index syntax

    size_t arrSize { 4 };
    int* freeStoreArray { new int[arrSize] { 1, 5, 3, 4 } };

    printArray(freeStoreArray, arrSize);
    doubleInts(freeStoreArray, arrSize); // pass free-store array
    printArray(freeStoreArray, arrSize);


    delete[] freeStoreArray; freeStoreArray = nullptr;

    int stackArray[] { 5, 7, 9, 11 };
    arrSize = std::size(stackArray);    // pass stack array
    // arrSize = sizeof(stackArray);  
    
    printArray(stackArray, arrSize);
    doubleInts(stackArray, arrSize);
    printArray(stackArray, arrSize);

    doubleInts(&stackArray[0], arrSize); // pass address of first element
    printArray(stackArray, arrSize);

    doubleIntsStack(stackArray);
    printArray(stackArray, arrSize);

    int someStackArray[] { 5, 6, 1, -3, 0, -8, 2 };

    printArray(someStackArray, std::size(someStackArray));
    doubleIntsStack(someStackArray); // uses function template overload
    printArray(someStackArray, std::size(someStackArray));


    // --- Not all pointers are arrays
    // For example:

    int* ptr { new int }; // `ptr` is a valid pointer
    *ptr = 5;

    // you can do access the value as if it were an array, but this pointer
    // is not array; the memory at `ptr[1]` could be anything!
    println("ptr value: {}", ptr[0]);

}

void printArray(int arr[], int N)
{
    for (int i { 0 }; i < N; i++)
    {
        print("{}, ", arr[i]);
    }
    println("");
}


/**
 * @param theArray - you can pass stack-based or free-store array.
 * Stack-based array treats the variable as a pointer to the array
 */
void doubleInts(int* theArray, size_t size)
{
    for (size_t i { 0 }; i < size; i++) { theArray[i] *= 2; }
}