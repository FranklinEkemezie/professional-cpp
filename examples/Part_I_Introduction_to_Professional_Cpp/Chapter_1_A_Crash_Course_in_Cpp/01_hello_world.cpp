#include <format>
#include <iostream>

int main()
{
    // I/O streams
    std::cout << "Hello, World!" << std::endl;
    std::cout << std::format("There are {} ways I love you.", 219) << std::endl;
    std::cout << std::format("{} + {} = {}", 2, 4, 6) << std::endl;
    std::cerr << std::format("Error: {}", 6) << std::endl;

    int value;
    std::cin >> value;
    std::cout << std::format("You entered {}", value) << std::endl;

    return 0;
}