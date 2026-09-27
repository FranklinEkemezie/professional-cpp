#include <string>
#include <vector>

int main()
{

    // Since a string literal is typically interpreted as `const char *` or a
    // `const char[]`, you can use the standard string literal 's' defined in 
    // `std::literals::string_literals` namespace to indicate that a string
    // literal should be interpreted as `std::string`.
    // NB: Both `string_literals` and `literals` namespaces are inline namespaces
    // so any one of the follow `using` declarations should work:

    // using namespace std;
    // using namespace std::literals;
    // using namespace std::string_literals;
    using namespace std::literals::string_literals;

    // Basically, everything declared in an inline namespace is automatically
    // available in the parent namespace as can observed in the `using`
    // declarations above. To define an inline namespace, the `inline` keyword
    // is used. For ex:
    // namespace std { 
    //  inline namespace literals { 
    //      inline namespace string_literals { 
    //          // ... 
    //      } 
    //  } 
    // }

    // 

    [[maybe_unused]] auto string1 { "Hello World" };     // string1 is a const char*.
    [[maybe_unused]] auto& string2 { "Hello World" };    // string2 is a const char[12] (reference)
    [[maybe_unused]] auto string3 { "Hello World"s };    // string3 is an std::string

    // Similarly, when allowing C++ compiler to use class template argument 
    // deduction (CTAD) to deduce the type of a `std::vector` and similar ones,
    // you should the standard string literal to let the compiler properly deduce
    // the correct type

    [[maybe_unused]] std::vector names1 { "John", "Sam", "Joe" };
    [[maybe_unused]] std::vector names2 { "John"s, "Sam"s, "Joe"s };

    return 0;
}