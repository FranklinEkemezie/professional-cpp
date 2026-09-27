#include <cmath>
#include <format>
#include <iostream>
#include <limits>


int main()
{

    int uninitialisedInt;
    int initialisedInt { 7 };

    std::cout << std::format("Uninitialised int: {}", uninitialisedInt) << std::endl;
    std::cout << std::format("Initialised int: {}", initialisedInt) << std::endl;

    std::byte b { 42 };

    std::cout << std::format("b: {}", (int) b) << std::endl;


    // Numerical limits

    std::cout << "------ Numerical Limits ----------" << std::endl;

    std::cout << "int: " << std::endl;
    std::cout << std::format("Max int value: {}", std::numeric_limits<int>::max()) << std::endl;
    std::cout << std::format("Min int value: {}", std::numeric_limits<int>::min()) << std::endl;
    std::cout << std::format("Lowest int value: {}", std::numeric_limits<int>::lowest()) << std::endl;

    std::cout << "\ndouble: " << std::endl;
    std::cout << std::format("Max double value: {}", std::numeric_limits<double>::max()) << std::endl;
    std::cout << std::format("Min double value: {}", std::numeric_limits<double>::min()) << std::endl;
    std::cout << std::format("Lowest double value: {}", std::numeric_limits<double>::lowest()) << std::endl;

    // Zero initialisation
    float myFloat {};
    int myInt {};

    std::cout << std::format("myFloat: {}", myFloat) << std::endl;
    std::cout << std::format("myInt: {}", myInt) << std::endl;

    // Casting

    myFloat = 3.14f;

    std::cout << std::format("myFloat: {}", myFloat) << std::endl;
    std::cout << std::format("(int) myFloat: {}", (int) myFloat) << std::endl;
    std::cout << std::format("int (myFloat): {}", int (myFloat)) << std::endl;
    std::cout << std::format("static_cast<int>(myFloat): {}", 
        static_cast<int>(myFloat)) << std::endl;
    
    short someShort {321 }; // `short` - typically 2 bytes
    long someLong { someShort }; // `short` coerced into `long`

    std::cout << std::format("someLong: {}", someLong) << std::endl;

    double myInf = std::numeric_limits<double>::infinity();
    double myNan = std::numeric_limits<double>::quiet_NaN();

    std::cout << std::format("is inf? {}", std::isinf(myInf)) << std::endl;
    std::cout << std::format("is NaN? {}", std::isnan(myNan)) << std::endl;

    // Floating-Point types
    //      Type            Name                    Mantissa Bits   Exponent Bits
    // -    float           Single precision        24              8
    // -    double          Double precision        53              11
    // -    long double     Extended precision      64              15
    // -    std::float16_t  Half precision          11              5
    // -    std::float32_t  Single precision        24              8
    // -    std::float64_t  Double precision        53              11
    // -    std::float128_t Quadruple precision     113             15
    // -    std::bfloat16_t Brain floating point    8               8


    return 0;
}