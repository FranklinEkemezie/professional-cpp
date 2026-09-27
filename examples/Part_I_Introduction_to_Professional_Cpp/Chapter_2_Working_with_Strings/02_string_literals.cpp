#include <format>
#include <iostream>

int main()
{

    // --- Literal pooling
    // String literals are stored in a read-only part of memory. This allows the
    // compiler to optimise memory usage by reusing references to equivalent
    // string literials. That is, the compiler can create just one instance of 
    // the string literal "hello" even if your program uses it multiplie times.
    // This is known as literal pooling.
    // While useful, this feature can make assigning string literals to variables
    // risky since modifying the string could cause unexpected side-effects for 
    // other string variables referencing the same strings, and to the program
    // as a whole. For this reason, the C++ standard officially states that a 
    // string literal is a type of "array of n const char". That is, they must
    // not be modified. However, many compilers do not enforce this for backward
    // compatibility. Thus, modifying a string literal is undefined and the
    // behaviour depends on your compiler and compiler settings: it could crash
    // your program, keep working with inexplicable sidee effects, silently
    // ignored, or if your are lucky, just work.

    // char* ptr { "hello" };  // assigning the string literal to a non-const variable
    // ptr[1] = 'a';           // undefined behaviour

    // std::cout << std::format("ptr: {}", ptr) << std::endl; // crashes!

    // to be safe, always assign string literals to "const char*"

    [[maybe_unused]] const char* ptr { "hello" };
    // ptr[1] = 'a';       // compiler error

    // you can, however, assign string literal a `char arr[]`.
    // here, the compiler create an array of big enough to hold the string 
    // (plus "\0") and copies the string to this array. Thus, no literal pooling
    // occurs which means it's safe to modify it.
    char arr[] { "hello" };
    arr['1'] = 'a';

    std::cout << std::format("arr: {}", arr) << std::endl;

    // --- Raw string literals
    // These are string literals that can span multiple lines of code. They don't
    // require escaping of double quotes and process escape sequences like \t and
    // \n as normal text and not as escape sequences. A raw string literal starts
    // with R"( and ends with )":

    std::cout << std::format("{}", R"(Hello "World"!)") << std::endl;
    std::cout << std::format("{}", R"(Line 1
        Line 2)") << std::endl;

    // Since raw-string literals end with )", you cannot use it in a raw-string
    // literal. Instead, you can go for the extended raw string literal syntax:
    // R"<delimiter>(<actual raw string>)<delimiter>"
    // where `<delimiter>` is the string (of at most 16 characters) you wish to use
    // as delimiter and must not appear with the raw string.
    // Raw string literals make it work with database querying strings, regular
    // expression, file paths, etc. Below we use "-" as delimiter:

    std::cout << std::format("{}", R"-(Embedded )" characters)-") << std::endl;

    return 0;

}