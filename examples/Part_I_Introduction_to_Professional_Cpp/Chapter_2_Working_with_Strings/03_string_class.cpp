#include <compare>
#include <cstring>
#include <format>
#include <iostream>
#include <string>

using std::string;

int main()
{

    // --- The C++ std::string class (defined in <string>)
    // In C++, `std::string` is a class (specifically an instantiation of the
    // `std::basic_string` class template) supporting many of the functionalities
    // as the <cstring> functions, but takes care of memory allocations for you.
    // Even though `string` is a class, you can almost always treat it as if were
    // a built-in type. This is possible through the "magic" of operator overloading
    // and making them easier to reason about.

    // --- Concatenating strings
    string a { "12" };
    string b { "34" };

    string c { a + b };
    std::cout << std::format("c: {}", c) << std::endl;

    a += b;
    std::cout << std::format("a: {}", a) << std::endl;

    // --- Comparing strings
    // One problem with C strings is that you can't directly compare them using
    // == operator since this compares the pointer values and not the contents
    // of the strings

    const char* a1 { "12" };
    char b1[] { "12" };

    std::cout << std::format("a1 == b1? {}", a1 == b1) << std::endl; // always false

    // you must use, use `strcmp()` function which returns a value <, =, or > 0
    // depending on the lexicographic ordering relationship of the strings
    // resulting in hard-to-read and error-prone code.

    std::cout << std::format("strcmp(a1, b1)? {}", strcmp(a1, b1) == 0) << std::endl;

    // With C++ strings, comparison operators (==, !=, <, etc) are all overloaded
    // allowing easier comparisons

    a = "Hello"; b = "World";

    std::cout << std::format("'{}' < '{}' = {}", a, b, a < b) << std::endl;
    std::cout << std::format("'{}' < '{}' = {}", a, b, a > b) << std::endl;

    // C++ also provides the `compare()` member function on strings that behave like
    // `strcmp()`

    a = "12"; b = "34";

    auto result { a.compare(b) };
    if (result < 0) { std::cout << "less\n"; }
    if (result > 0) { std::cout << "greater\n"; }
    if (result == 0) { std::cout << "equal\n"; }

    // Just as with `strcmp()`, this is also cumbersome considering that someone
    // can forget to the meaning of the returned integer and do this instead:

    if (a.compare(b)) { std::cout << "equal\n"; } // does the opposite

    // With three-way comparison, we can do the above with better type safety.

    auto result1 { a <=> b };

    if (is_gt(result1)) { std::cout << "greater\n"; }
    if (is_lt(result1)) { std::cout << "less\n"; }
    if (is_eq(result1)) { std::cout << "equal\n"; }

    // --- Memory handling
    // C++ string handles memory allocation during creation, resize when needed
    // and deallocation when the string objects go out of scope (the last uses
    // class destructors to achieve this)

    string myString { "hello" };
    myString += ", there";

    string myOtherString { myString };
    if (myString == myOtherString) myOtherString[0] = 'H';

    std::cout << myString << std::endl;
    std::cout << myOtherString << std::endl;

    // For compatibility with C-style strings, the `string` class has the 
    // `c_str()` member function which returns a `const char *` representing 
    // the C-style string. This however, becomes invalid when the `string` object
    // performs memory reallocation or when the `string` class is destroyed. To
    // that effect, you should call this member function just before you use so
    // that it currently reflects the current contents of the string. Consequently,
    // you should never return the result of `c_str()` called on a stack-based string
    // object from a function. Additionally, the `data()` member function returns
    // a `const char *` before C++14 and just `char *` for a non-`const` `string` after
    // C++14.

    // --- Operations on strings
    // The `string` class provides various string operations, with a few demonstrated
    // below:

    string strHello { "Hello!!"  };
    string strWorld { "The World..." };
    auto position { strHello.find("!!") };
    if (position != string::npos)
    {
        // found "||" substring, now replace it
        strHello.replace(position, 2, strWorld.substr(3, 6));
    }

    std::cout << strHello << std::endl;
    
    string toFind { "World" };
    std::cout << std::format("{}", strWorld.contains(toFind)) << std::endl;
    std::cout << std::format("{}", strWorld.contains('.')) << std::endl;
    std::cout << std::format("{}", strWorld.contains("Hello")) << std::endl;

    // Lastly, before C++ 23, it was possible to construct a `string` object
    // which results in undefined behaviour at run time. This results in a
    // compilation error starting from C++23

    // string someString { nullptr };


    return 0;
}