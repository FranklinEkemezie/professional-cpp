#include <format>
#include <iostream>
#include <utility>


void thirdPartyLibraryFunction(char *str);

void f(const char *str)
{
    thirdPartyLibraryFunction(const_cast<char *>(str));
}

int main()
{

    // --- `const_cast()`
    // C++ provides five types of casts: `const_cast()`, `static_cast()`,
    // `reinterpret_cast()`, `dynamic_cast()`, and `std::bit_cast()`. We have
    // seen `static_cast()` earlier. `const_cast()` is used to add `const`-ness
    // or cast away `const`-ness of a variable. It is the only cast of the five
    // that can cast away `const`-ness. Theoretically, there should be no need
    // for a `const` cast as a `const` variable is expected to stay `const`. 
    // However, there are situation where a function parameters requires a
    // `const` argument or we need to supply a `const` variable to a funciton
    // that requires non-`const` argument. In this case, we can add `const`-ness
    // to the argument to the `const` parameter as we passing it to make the
    // function happy. In the other case, we can cast away `const`-ness of a
    // `const` variable so that a function that requires a non-`const` argument
    // accept it, but we must be sure the function does not modify the value.
    // Technically, in such situation, the "correct" thing to do is to make
    // `const` consistent instead of using `const` as workaround. But it might
    // be the case that the function is from a third-party library. However, you
    // should not cast away `const` and pass it to a function that modifies the
    // variable instead you have to restructure your program, for ex. pass a 
    // non-`const` copy.

    // In the example below, `f()` receives a `const char *` and casts away its
    // `const`-ness so that a third party library function can accept it.

    f("Hello, World!");

    // The Standard Library also provides a helper function `std::as_const()`
    // defined in <utility> which returns a reference-to-`const` of its parameter.
    // Basically this function is equivalent to `const_cast<const T&>(obj)`,
    // where `T` is the type of `obj`.

    std::string str { "C++" };
    const std::string& constStr { std::as_const(str) };

    // Now, we have `constStr` to be a reference to constant `std::string` which
    // makes the underlying C-string obtained using the `c_str()` member function
    // automatically a `const char *` that we can pass to our `f()` function.
    f(constStr.c_str());


}

void thirdPartyLibraryFunction(char *str)
{
    std::cout << std::format("third party lib func prints: {}", str) << std::endl;
}