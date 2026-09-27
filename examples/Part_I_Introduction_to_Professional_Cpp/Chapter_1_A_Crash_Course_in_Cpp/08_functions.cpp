#include <cstdlib>
#include <format>
#include <iostream>

void myFunction(int i, char c); // function prototype/header before it is implemented

auto addNumbers(int number1, int number2)
{
    std::cout << std::format("Entering function {}", __func__) << std::endl;
    return number1 + number2;
}

auto addNumbers(double a, double b) // overloading function
{
    return a + b;
}

int main()
{
    int someInt { 6 };
    char someChar { 'c' };

    myFunction(8, 'a');
    myFunction(someInt, 'b');
    myFunction(5, someChar);

    int sum { addNumbers(5, 3) };
    std::cout << std::format("sum: {}", sum) << std::endl;
    std::cout << std::format("sum (double): {}", addNumbers(1.11, 2.22)) << std::endl;

    return 0;
}


void myFunction(int i, char c)
{
    std::cout << std::format("The value of i is {}.", i) << std::endl;
    std::cout << std::format("The value of c is {}.", c) << std::endl;
}