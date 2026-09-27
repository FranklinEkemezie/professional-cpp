#include <string>
#include <vector>

// Instead of this:
// void processVector(const std::vector<std::basic_string<char>>& vec);

using string = std::basic_string<char>;

// you do this:
void processVector([[maybe_unused]] const std::vector<string>& vec) {  }


int main()
{

    // --- Type Aliases

    // A type alias provides a new name for an existing type declaration.
    // The syntax: using NewType = type;

    using IntPtr = int *;

    // You can use both the new type name and the definition it aliases interchangeably.
    [[maybe_unused]] int *p1;
    [[maybe_unused]] IntPtr p2;

    // Variables created with the new type name are completely compatible with
    // those created with the original type declaration. They are the same type
    // with just different names
    // Type aliases are commonly used to provide manageable names when the real
    // type declarations become too unwieldy, for example, in templates.
    // An example from the Standard Library itself is `std::basic_string<T>`
    // which is used to represent strings (sequence) of some values. It is a
    // class template where `T` is the type of each item in the string, for
    // example, `char` for a string of characters. Specifying the template type
    // each time you want to refer to such a type can be burdensome, and since a
    // string of characters are common, the Standard Library aliases it:

    // Now, instead of:
    std::vector<std::basic_string<char>> myVector1;
    processVector(myVector1);

    // You can do this:
    std::vector<string> myVector2;
    processVector(myVector2);

    // Before C++11, the verrsion in which type aliases was introduced, you had
    // to use `typedef` to accomplish type aliasing:
    typedef int* IntPtr;    // convoluted, new name comes last, can be confusing

    // While they do the same thing, type aliases and `typedef`s are not
    // entirely equivalent. Type aliases are more powerful when used with templates.
    // You should always use type aliases over `typedef`s for type aliasing

}

