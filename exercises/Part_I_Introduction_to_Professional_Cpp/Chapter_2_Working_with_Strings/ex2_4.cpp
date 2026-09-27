#include <format>
#include <iostream>
#include <vector>


int main()
{

    std::vector<float> numbers;

    std::string buffer;
    float number;

    std::cout << "Enter numbers. Press 'Enter' after each number.  [Enter 0 to exit]: " << std::endl;
    while (true)
    {
        getline(std::cin, buffer);

        auto result { std::from_chars(
            buffer.data(), buffer.data() + buffer.length(), number) };

        if (result.ec != std::errc{}) std::cout << "Invalid input!" << '\n';
        else if (number == 0) break;
        else numbers.push_back(number);
    }

    const size_t col_width { 20 };
    const size_t sno_col_width { 5 };

    std::cout << '\n' << std::format("|{2:_^{1}}|{3:_^{0}}|{4:_^{0}}|{5:_^{0}}|",
        col_width, sno_col_width, "S/N", "Default", "Fixed", "Scientific") << '\n';
    for (unsigned int i { 0 }; i < numbers.size(); i++)
    {
        std::cout << std::format("|{2:^{1}}|{3:{0}}|{3:{0}.4f}|{3:{0}g}|", 
            col_width, sno_col_width, i, numbers[i]) << '\n';
    }
}