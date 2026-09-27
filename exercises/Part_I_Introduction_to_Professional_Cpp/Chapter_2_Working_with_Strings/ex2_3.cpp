#include <format>
#include <iostream>
#include <string>
#include <string_view>

std::string str_replace_all(
    std::string_view haystack, 
    std::string_view needle, 
    std::string_view replace
)
{
    // comparison, par, rap => comrapison

    if (needle.empty()) return std::string { haystack };

    size_t needle_len = needle.length();

    std::string result;

    unsigned int i { 0 };
    while (i < haystack.length())
    {
        if (haystack.substr(i, needle_len) == needle)
        {
            result += replace;
            i += needle_len;
        }
        else
        {
            result += haystack[i];
            i++;
        }
    }

    return result;

}

int main()
{

    std::string src, to_find, replace;

    std::cout << std::format("Enter source string: ");
    getline(std::cin, src);

    std::cout << std::format("Enter string to find: ");
    getline(std::cin, to_find);

    std::cout << std::format("Enter replacement string: ");
    getline(std::cin, replace);

    std::string result = str_replace_all(src, to_find, replace);

    std::cout << '\n' << std::format("{:=^20}", " Result ") << '\n';

    const size_t label_len { 16 };
    std::cout << std::format("{:{}}{}", "Source: ", label_len, src) << '\n';
    std::cout << std::format("{:{}}{}", "To find: ", label_len, to_find) << '\n';
    std::cout << std::format("{:{}}{}", "Replacement: ", label_len, replace) << '\n';
    std::cout << std::format("{:{}}{}", "Result: ", label_len, result) << '\n';

    return 0;
}
