#include <format>
#include <iostream>
#include <stdexcept>

double divideNumbers(double numerator, double denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument { "Denominator cannot be 0." };
    }
    
    return numerator / denominator;
}

int main()
{

    // --- Exceptions
    // An exception, like its name, is an exceptional situation, that is a
    // situation that you don't expect or want in the normal flow of program
    // execution. When a piece of code detects an exceptional situation, it may
    // decide to **throw** and exception while another piece of code **catches**
    // it and takes appropriate action.
    // Common exceptions are defined in <stdexcept> header.

    try 
    {
        std::cout << std::format("{}", divideNumbers(2.5, 0.5)) << std::endl;   // executes
        std::cout << std::format("{}", divideNumbers(2.3, 0)) << std::endl;     // causes exception to be thrown, code moves to `catch` block
        std::cout << std::format("{}", divideNumbers(4.5, 2.5)) << std::endl;   // not reached
    } 
    catch (const std::invalid_argument& exception)  // it is recommended to catch exceptions by reference-to-`const`
    {
        std::cout << std::format("Exception caught: {}", exception.what());
    }

    // If you need to include more information about an error in an exception,
    // you can write your own exception types. Lastly, the C++ compiler does
    // not mandate you to catch any or every exception that might occur. If your
    // code fails to catch any exception thrown, the program terminates.
}