#include <array>
#include <format>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

std::optional<int> getData(bool giveIt)
{
    if (giveIt) return 42;
    return std::nullopt; // or simply return {}
}

int main()
{


    // --- C-style arrays: 
    // Not recommended, use `std::array` and `vector` below

    int myArray[3];
    myArray[0] = 0;
    myArray[1] = 0;
    myArray[2] = 0;

    // all three ways to accomplish zero initialisation (fills up the array with zeros)
    // int myArray[3] = { 0 };
    // int myArray[3] = {};
    int myArr1[3] {};

    // the compiler can deduce the size when initialised with an initialiser list
    int myArr2[] { 1, 2, 3, 4 };

    // when the initialiser list has fewer elements than the given size, 
    // the remaining elements are set to zero
    int myArr3[3] { 2 };

    // get the size of a stack-based array using `std::size()` which returns a
    // `std::size_t` an unsigned integer type (defined in <cstddef> header)
    std::size_t myArraySize { std::size(myArray) };

    std::cout << std::format("myArray size: {}", myArraySize) << std::endl;
    std::cout << std::format("myArr1 size: {}", std::size(myArr1)) << std::endl;
    std::cout << std::format("myArr2 size: {}", std::size(myArr2)) << std::endl;
    std::cout << std::format("myArr3 size: {}", std::size(myArr3)) << std::endl;

    // literal suffix for `std::size_t` type
    std::size_t i { 42uz };

    std::cout << std::format("i: {}", i) << std::endl;

    // an older way to get the size of a stack-based C-style array:
    // using sizeof operator which returns the size of its argument in bytes.
    // you can then divide that size in bytes by the size of the item

    std::cout << std::format("myArray size (using `sizeof`): {}", 
        sizeof(myArray) / sizeof(int)) << std::endl;

    // We can create 2D arrays (arrays of array of some size)
    // char ticTacToeBoard[3][3];


    // --- `std::array`
    // `std::array` defined in <array> is essentially a thin wrapper 
    // around C-style arrays. Unlike a C-style array, it knows its size,
    // are not automatically cast to pointers to avoid certain types of bugs,
    // and have iterators to easily loop over the elements.
    // The `array` type is a class template which accepts the element type and 
    // size as template arguments.

    std::array<int, 3> arr { 9, 8, 7 };
    std::cout << std::format("Array size = {}", arr.size()) << std::endl;
    std::cout << std::format("2nd element = {}", arr[1]) << std::endl;

    // when you provide an initialiser, C++ can use it deduce the values for the
    // template parameters. This is known as class template argument deduction (CTAD)

    std::array arr1 { 9, 8, 7 };
    std::cout << std::format("arr1 size = {}", arr1.size()) << std::endl;

    // --- `std::vector`
    // Arrays have a fixed size which must be known at compile-time. They may not
    // grow or shrink. The C++ Standard Library provides different non-fixed-size 
    // containers of which `std::vector` (declared in <vector>) is one of them.
    // This container manages it memory, allocated enough memory to hold its elements
    // which can be added and removed at run time.

    std::vector<int> myVector { 11, 22 };

    // add items
    myVector.push_back(33);
    myVector.push_back(44);

    // access items
    std::cout << std::format("1st element: {}", myVector[0]);

    // `std::vector` also supports CTAD
    std::vector<int> myVector1 { 11, 22 };
    std::cout << std::format("myVector1 size: {}", myVector1.size()) << std::endl;

    // --- `std::pair`
    // This class template defined in <utility> is used to group two values of 
    // possibly different types accessing using `first` and `second` public data members.
    // While it is possible to write a function returning an `std::pair`, it is recommended 
    // to write a small `struct` or `class` containing the `std::pair` and return it instead.
    // This allows you to give meaningful name to the values e.g. (x, y) for coordinates

    std::pair<double, int> myPair { 1.23, 5 }; // or just std::pair myPair { 1.23, 5 };
    std::cout << std::format("{} {}", myPair.first, myPair.second) << std::endl;

    // --- `std::optional`

    std::optional<int> data1 { getData(true) };
    std::optional<int> data2 { getData(false) };

    std::cout << std::format("data1.has_value = {}", data1.has_value()) << std::endl;
    if (! data2) // can be as boolean values
    { 
        std::cout << std::format("data2 has no value.") << std::endl; 
    }

    // if an `optional` has a value you can retrieve it using `value()`
    // or using the dereferencing operator *
    std::cout << std::format("data1.value = {}", data1.value()) << std::endl;
    std::cout << std::format("data1.value (pointer) = {}", *data2) << std::endl;

    // when `value()` on an empty `optional`, it throws an `std::bad_optional` exception
    // the line below will throw the exception since `data2` is "empty"
    // std::cout << std::format("data2.value = {}", data2.value()) << std::endl;

    std::cout << std::format("data2.value = {}", data2.value_or(0)) << std::endl;

    // --- Structured Bindings
    // This allows you to declare multiple variables initialised with elements from a 
    // data structure such as an `array`, `struct`, or `pair`.
    // The variables must be declared `auto`.

    std::array values { 11, 22, 33 };

    auto [x, y, z] { values };  // number of variables must match number of values

    std::cout << std::format("x={}, y={}, z={}", x, y, z) << std::endl;

    struct Point { double m_x, m_y, m_z; };

    Point point;
    point.m_x = 1.0; point.m_y = 2.0; point.m_z = 3.0;

    auto [px, py, pz] { point };    // all non-static members of `Point` struct must be public

    std::cout << std::format("px={}, py={}, pz={}", px, py, pz) << std::endl;

    std::pair myPair1 { "hello", 5 };

    auto [theString, theInt] { myPair1 };   // decompose using structured bindings.

    std::cout << std::format("theString: {}; theInt: {}", theString, theInt) << std::endl;

    


}