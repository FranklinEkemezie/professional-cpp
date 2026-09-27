#include <format>
#include <iostream>
#include <string>
#include <utility>

const std::string message { "Test" };
const std::string& foo() { return message; }

int main()
{

    // --- Type Inference

    // Type inference allows the compiler to automatically deduce the type of
    // expression. There are two keywords for type inference: `auto` and `decltype`

    // --- The `auto` keyword
    // The `auto` keyword has a number of different uses:
    // - to deduce a function's return type
    // - to define structured bindings
    // - to deduece the type of an expression
    // - to deduce the type of non-type template parameters
    // - to use wuth `decltype(auto)`
    // - to write functions using the alternative function syntax
    // - to write generic lambda expressions.
    // We have seen the first two, and will discuss the third usage here.
    // Others will be explained in later chapters (Chapter 12, and 19 for the last one)

    // Suppose you have a function `getFoo()` that has a complicated return type.
    // To assign the result of that function to a variable, you can either spell
    // out the complicated return type, or just use `auto` and let the compiler
    // figure it out. This has the added benefit that you can easily change the 
    // function's return type without having to update all the places in the 
    // code where the function is called.
    // auto result { getFoo() };

    // --- The `auto&` syntax
    // Using `auto` to deduce the type of an expression strips away reference
    // and `const` qualifiers. This is illustrated below:
    // `foo()` is a function that returns a reference-to-`const` string

    auto f1 { foo() };  // `f1` is of type `string`, and thus a copy is made!

    // To prevent making a copy, you using `auto&` to declare the variable as
    // a reference to the deduced type. You can also mark it `const` if need be:

    [[maybe_unused]]
    const auto& f2 { foo() };

    // Similarly, in the following `result` is a string even though `as_const()`
    // returns a reference-to-`const` cast which means a copy is made:

    std::string str { "Hello" };
    [[maybe_unused]] auto result { std::as_const(str) };     // strips away reference and const qualifiers, creates a copy
    [[maybe_unused]] auto& result1 { std::as_const(str) };   // keeps reference and const qualifiers, does not create a copy

    // --- The `auto*` syntax

    // The `auto` keyword can also be used for pointers:
    int i { 123 };
    [[maybe_unused]] auto p { &i };  // not a big deal to make a copy, nothing that expensive

    // Even though the type of `p` is `int *`, you can use `auto*` to clearly
    // state that pointers are involved:

    [[maybe_unused]]
    auto* p1 { &i }; // type is still `int *`

    // However, using `auto *` resolves certain strange behaviour encountered 
    // when using `auto`, `const` and pointers together. In the example below:
    // you would think that `p2` is a `const int *` i.e. a pointer to constant
    // `int`, but the type is actually `int* const` i.e. a constant pointer to
    // an `int`. In other words, the `const` applies to the pointer as a whole
    // rather than what it points to. 

    [[maybe_unused]]
    const auto p2 { &i };   // not `const int*` but `int* const`

    // Putting the `const` after the `auto` does not help either:

    [[maybe_unused]]
    auto const p3 { &i };   // still `int *const`

    // A way to think of this is since the compiler deduced the type to be an
    // `int *`, any qualifier complements this in whole and you can't qualify
    // whatever the pointer points to.

    // By specifying that deduced type involves a pointer type using `auto *`
    // you have granular access of the type when applying qualifier while the
    // compiler still deduces the type.

    [[maybe_unused]]
    const auto* p4 { &i };  // now, its `const int*`

    // Swapping `const and `auto*` gives you the other type as expected:

    [[maybe_unused]]
    auto* const p5 { &i };  // now, its `int *const`

    // With this syntax you can make both the pointer and the integer constant:

    [[maybe_unused]]
    const auto* const p6 { &i }; // you can't do this with just `auto`

    // --- Copy List vs. Direct List Intialisation
    // There are two types of initialisations that use braced initialiser lists:
    // - copy list initialisation: T obj = { arg1, arg2, ... };
    // - direct list initialisation: T obj = { arg1, arg2, ... };

    // In combination with `auto` type deduction, there is an important difference
    // between copy- and direct-list initialisation.

    // Copy initialization
    [[maybe_unused]] auto a = { 11 };            // initializer_list<int>
    [[maybe_unused]] auto b = { 11, 22 };        // initializer_list<int>

    // Direct list initialization
    [[maybe_unused]]
    auto c { 11 };              // int
    // auto d { 11, 22 };          // Compilation error: too many elements

    // For copy initialisation, all elements in the braced initialiser must be
    // of the same type

    // auto e = { 11, 22.33 };     // Error: cannot deduce type


    // --- The `decltype()` keyword

    // The `decltype` keyword takes an expression as argument and computes the
    // type of that expression:

    [[maybe_unused]] int x { 123 };
    [[maybe_unused]] decltype(x) y { 456 };  // deduces y to be the type of x i.e. `int`

    // Unlike `auto`, `decltype` does not strip reference and `const` qualifiers.

    [[maybe_unused]] decltype(foo()) f3 { foo() };   // preserves `const` and reference, thus no copy made.

    // `decltype` becomes even more powerful when used in templates.

    return 0;
}