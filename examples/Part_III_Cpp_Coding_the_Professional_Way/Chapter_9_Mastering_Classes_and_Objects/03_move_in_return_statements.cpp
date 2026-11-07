#include <print>

int main()
{

    std::println("--- Using `std::move()` in Return statements");

    // A) In return statements of the form `return object` where `object` is a:
    // - nameless temporary - the compiler is not allowed to perform any copying or moving
    //      thus incurring no performance penalty by returning by value. This is called
    //      "mandatory elision of copy/move operations".
    // - local variable that is not a function parameter - the compiler may use an
    //      optimisation known as "named return value optimisation (NRVO)" to prevent copying
    //      or moving. This is known as "non-mandatory elision of copy/move operations". This,
    //      however, is not guaranteed and some compiler may do so only for release builds but
    //      not for debug builds.
    // With these features, compilers can implement zero-copy pass-by-value semantics.
    // B) For statements in the form `return std::move(object)`, copy/move elision cannot be used,
    // rather the compiler attempts to use move semantics if `object` supports it or fall back
    // to copy semantics. 
    // => You should use `return object` instead of `return std::move()` to return local or nameless temporary
    // => You may use `std::move()` if you want to move a class data member out instead of copying 
    //      if you wish too. Note that the data member (and the class object as a whole) 
    //      enters an indeterminate state and should not be used further.
    // => Beware that copy/move elision do not apply to ternary expressoin i.e. return statements
    //      of the form: `return condition ? obj1 : obj2;`. The result is an `lvalue` ie. one of
    //      objects and incurs a copy. You could trigger move semantics using:
    //      `return condition ? std::move(obj) : std::move(obj2);` or `return std::move(condition ? obj1 : obj2)`.
    //      However, `if (condition) { return obj1; } else { return obj2; }` would be clearer and with the
    //      benefit that the compiler can automatically use move semantics without expliciting `std::move()`.

    std::println("=> `return object` uses copy/move elision for nameless temporary `object`");
    std::println("=> `return object` may (not guaranted) perform copy/move elision using NRVO for local variables that are not funciton parameters");
    std::println("=> `return std::move(object)` uses move semantics if supported, or fall back to copy");
    std::println("=> You should be fine using `return object` instead of `std::move(object)`");
    std::println("=> You may use `std::move()` to move a data member in a return statement; but don't use it later on");
    std::println("=> `return condition ? obj1 : obj2` does not use copy/move elision. Use `std::move()` or if-else statements");
}