#include <compare>
#include <format>
#include <iostream>
#include <string>


int main()
{

    std::string s1;
    std::string s2;

    std::cout << "Enter first string: ";
    getline(std::cin, s1);

    std::cout << "Enter second string: ";
    getline(std::cin, s2);

    auto cmp = s1 <=> s2;

    if (is_lt(cmp)) std::cout << std::format("{} < {}", s1, s2) << '\n';
    else if (is_gt(cmp)) std::cout << std::format("{} > {}", s1, s2) << '\n';
    else { std::cout << std::format("{} == {}", s1, s2) << '\n'; }

    return 0;
}