#include <format>
#include <iostream>
#include <string>

int main()
{

    // --- Strings in C++
    // There are two ways to work with strings in C++:
    // - C style: representing strings as arrays of characters.
    // - C++ style: a C-style representation wrapper making it easier-to-use and safer
    // The C++ style is recommended

    std::string myString { "Hello, World" };
    
    std::cout << std::format("The value of myString is {}", myString) << std::endl;
    std::cout << std::format("The second letter is {}", myString[1]) << std::endl;

}