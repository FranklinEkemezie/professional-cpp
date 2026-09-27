#include <cstring>
#include <format>
#include <iostream>
#include <string>


char* copyString(const char* str)
{
    char *result { new char[strlen(str) + 1] }; // take note of + 1 for NULL terminator "\0"

    strcpy(result, str);

    return result;
}

char *appendStrings(const char* str1, const char* str2, const char* str3)
{
    char *result { new char[strlen(str1) + strlen(str2) + strlen(str3 + 1)] };
    
    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, str3);

    return result;
}

int main()
{

    // C-style strings (see <cstring> for C string functions)
    // While it is discouraged to use C-style strings in C++, it is beneficial
    // to introduce them. C strings are a sequence of characters terminated by
    // the null-terminator character '\0' (also called NUL, which is distinct
    // from the NULL pointer). Since it is easy to forget the NULL-terminator
    // or allocate space for them, C strings are largely unsafe and harder to
    // work with. The functions below demonstrate using the C string functions
    // defined in <cstring> and how to properly allocate enough memory for
    // C strings.

    auto* myString = copyString("Hello world");
    std::cout << std::format("myString: {}", myString) << std::endl;

    auto* myStrings = appendStrings("Hello", ", ", "world!");
    std::cout << std::format("myStrings: {}", myStrings) << std::endl;

    // While C string functions generally do not handle memory allocation, and 
    // expect the caller to allocate enough memory for the operation, the
    // defined here (which use them) do allocate memory for the returned string, 
    // the client is responsible for deallocating/freeing them:

    delete myString; myString = nullptr;
    delete myStrings; myStrings = nullptr;

    // size of string
    char text1[] { "abcdef" };
    std::cout << std::format("sizeof(text1): {}", sizeof(text1)) << std::endl;
    std::cout << std::format("strlen(text1): {}", strlen(text1)) << std::endl;

    const char* text2 { "abcdef" };
    std::cout << std::format("sizeof(text2): {}", sizeof(text2)) << std::endl;
    std::cout << std::format("strlen(text2): {}", strlen(text2)) << std::endl;

    return 0;

}