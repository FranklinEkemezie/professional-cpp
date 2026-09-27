#include <format>
#include <iostream>

int main()
{

    int someInteger { 256 };
    short someShort;
    long someLong;
    float someFloat;
    double someDouble;

    someInteger++;
    someInteger *= 2;

    // conversion from larger integer type to a smaller can cause warning or
    // error, hence we use static_cast()
    someShort = static_cast<short>(someInteger);
    someLong = someShort * 1000;
    someFloat = someLong + 0.785f;

    // to make sure the division is performed with double precision, we convert
    // someFloat to double first
    someDouble = static_cast<double>(someFloat) / 100000;

    std::cout << std::format("someDouble: {}", someDouble) << std::endl;

    // Precendence

    int i { 34 + 8 * 2 + 21 / 7 % 2 }; // same as: 34 + (8 * 2) + ((21 / 7) % 2)

    std::cout << std::format("i: {}", i) << std::endl;
}