#include <format>
#include <iostream>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')

void printArray(int arr[], int N);
char** allocateCharacterBoard(size_t xDimension, size_t yDimension);
void releaseCharacterBoard(char**& myArray, size_t xDimension);


int main()
{

    //

    int myArray1[5]; // Allocates contiguous piece of memory on the stack
    // uninitialised, contains garbage values
    printArray(myArray1, 5);

    int myArray2[5] { 1, 2, 3, 4, 5 };
    printArray(myArray2, 5);

    int myArray3[5] { 1, 2 };   // others zero-initialised
    printArray(myArray3, 5);

    int myArray4[5] {  }; // items are zero initialised
    printArray(myArray4, 5);

    int myArray5[]  { 1, 2, 3, 4, 5 };   // array size is induced
    printArray(myArray5, 5);

    // We can instead declare arrays on the free store

    int* myArrayPtr { new int[5] }; // allocates memory for five zero-initialised
    // `int`s; `myArrayPtr` contains the addresss of (i.e. it is a pointer to)
    // the first element in the array
    // you can also use the `new(std::nothrow)` syntax

    printArray(myArrayPtr, 5);

    int* myArrayPtr1 { new int[] { 1, 2, 3, 4, 5 } };
    printArray(myArrayPtr1, 5);

    // every call to `new[]` should be paired with call to `delete[]`

    delete[] myArrayPtr; myArrayPtr = nullptr;
    delete[] myArrayPtr1; myArrayPtr1 = nullptr;

    // --- Array of Objects

    class Simple
    {
        public:
            Simple() { println("Simple constructor called!"); }
            ~Simple() { println("Simple destructor called!"); }
    };

    // Below, `new[]` allocates enough memory for the four `Simple` objects
    // and the pointer to the first element is stored in `mySimpleArray` stack
    // variable

    println("---- array of objects");

    Simple *mySimpleArray = { new Simple[4] };

    // use `mySimpleArray`...

    delete[] mySimpleArray; mySimpleArray = nullptr;

    // Always use the array version of `delete`, i.e. `delete[]`. Failure to 
    // do so will result in odd behaviours. Some compiler may only call the 
    // destructor for the first element, or might result in memory corruption
    // especially when `new` and `new[]` use different memory allocation schemes.

    // With array of pointers, you still need to free the associated memory for
    // each one.

    println("--- array of pointer to objects");

    const size_t size { 4 };
    Simple** mySimplePtrArray { new Simple*[size] }; // allocate memory for array of pointers to `Simple`

    // Allocate an object for each pointer
    for (size_t i  { 0 }; i < size; i++)
    {
        mySimplePtrArray[i] = new Simple { };
    }

    // use `mySimplePtrArray`...

    // delete each allocated object
    for (size_t i { 0 }; i < size; i++)
    {
        delete mySimplePtrArray[i]; mySimplePtrArray[i] = nullptr;
    }

    // delete the array itself
    delete[] mySimplePtrArray;
    mySimplePtrArray = nullptr;

    // --- Multidimensional arrays

    // A tic-tac-toe game might use a two-dimensional array:

    char board[3][3] { };

    // In memory, this is represented as a 1D array: specifically, an array
    // of three array where each of the array contains three elements that
    // is 1 byte (`char`) large - all stored on the stack.

    board[0][0] = 'X'; // go to the 0th array and put 'X' in its 0th index
    board[2][1] = 'O'; // go to the 2nd array and put 'O' in its 1st index

    const size_t w { 3 };

    println("{:-^{}}", "", w * w + w + 1);
    for (int i { 0 }; i < 3; i++)
    {
        print("|");
        for (int j { 0 }; j < 3; j++)
        {
            char c { board[i][j] };

            print("{:^{}}|", !! c ? c : ' ', w);
        }
        print("\n");
        println("{:-^{}}", "", w * w + w + 1);
    }

    // Technically, to the computer there's no x- or y-coordinate: you just
    // have to choose one and be consistent with it. Typically, the first 
    // subscript is the x-axis while the second is the y-axis

    // You can store multidimensional arrays on the free store e.g. when you
    // need to determine the dimensions at run time. Here, you need a pointer
    // to each free-store array ; then you allocate memory for each of the 
    // free-store array. you cannot do this

    const size_t i { 3 };
    const size_t j { 4 };

    // char **board { new char[i][j] };

    // See function definitions for memory allocation implementation

    char **board1 { allocateCharacterBoard(i, j) };

    releaseCharacterBoard(board1, i);

    // For performance, multidimensional arrays should be allocated in a 
    // single block. Multiple allocation for each dimension, results in
    // scattered memory blocks which are inefficient to access.
    // Nonetheless, you should avoid them entirely and adopt C++ Standard
    // Library containers such `std::array`, `std::vector`. For a 2D multi-
    // dimensional of array type `T`, you could use `vector<vector<T>>`.
    // Typically, you should write a class wrapper to make it easier to use.

    


}

void printArray(int arr[], int N)
{
    for (int i { 0 }; i < N; i++)
    {
        print("{}, ", arr[i]);
    }
    println("");
}

char** allocateCharacterBoard(size_t xDimension, size_t yDimension)
{
    char** myArray { new char*[xDimension] };   // allocate first dimension

    for (size_t i { 0 }; i  < xDimension; i++)
    {
        myArray[i] = new char[yDimension];
    }

    return myArray;
}

void releaseCharacterBoard(char**& myArray, size_t xDimension)
{
    for (size_t i { 0 }; i < xDimension; i++)
    {
        delete[] myArray[i];    // delete ith subarray
        myArray[i] = nullptr;
    }

    delete[] myArray;
    myArray = nullptr;
}