#include <compare>
#include <format>
#include <iostream>
#include <limits>

int main()
{


    // If statement
    if (int i { 5 }; i % 2 == 0)    // initialised variable available only in if...else if...else statemen
    {
        std::cout << std::format("{} is divisible by 2", i) << std::endl;
    }
    else if (i > 9 && i < 100)
    {
        std::cout << std::format("{} is a 2-digit", i) << std::endl;
    }
    else
    {
        std::cout << std::format("i: {}", i) << std::endl;
    }


    enum class Mode { Default, Custom, Standard };

    int value { 42 };

    switch (Mode mode { Mode::Default }; mode)  // initialisers only available in the switch statement
    {
        // properly scope `using enum` declaration
        using enum Mode;

        case Custom:
            {   // use (optional) braces to scope variables
                int someVariable { 42 };
                value = someVariable * 2;
                [[fallthrough]]; // use attribute to explicitly indicate intended behaviour
            }
        case Standard:
        case Default:
            std::cout << std::format("value: {}", value) << std::endl;
            break;
        // when using switch for enumerations, it is recommended to handle
        // all cases explicitly, rather than using `default` case. This 
        // prevent subtle bugs in the future when a new enumerator is added,
        // the compiler warns about it, instead of being handled silently by a `default` case
    }

    // Ternary operator
    int i;
    std::cin >> i;
    std::cout << std::format("Divisible by 2? {}", i % 2 == 0 ? "yes" : "no") << std::endl;

    // Short-circuit logic
    // C++ uses short-circuit logic when evaluating logical expressions, preventing it
    // from evaluating the whole expression when the final result is certain.
    // For ex, when using logical OR (||), when one of the statement is true, we can conclude
    // that the whole expression results to true since || requires at least one to be true
    // Similarly, when using logical AND (&&), when one of the statement is found to be false,
    // we can stop evaluating the whole expression and conclude the result to be false, since
    // the && requires all operands to be true. This allows us to make less resource intensive
    // comparisons first and short-circuit if there's no need to execute more expensive ones.
    // It is also useful, when we want to check if a value is valid, before making another
    // check with it. E.g. checking if a pointer is valid before dereferencing it.

    // Three-Way Comparisons

    i = 11;
    std::strong_ordering result { i <=> 0 };

    // `strong_ordering` is returned when types have total ordering
    if (result == std::strong_ordering::less)       { std::cout << "less" << std::endl; }
    if (result == std::strong_ordering::greater)    { std::cout << "greater" << std::endl; }
    if (result == std::strong_ordering::equal)      { std::cout << "equal" << std::endl; }

    double myNan { std::numeric_limits<double>::quiet_NaN() };
    double myFloat { 4.56 };
    double p0 { +0.0 }; // "positive zero"
    double n0 { -0.0 }; // "negative zero"

    // `partial_ordering` is used when types may not have total ordering.
    // E.g. NaN floating point are never considered to be <, =, > other floating-point values, hence unordered
    // `equivalent` is used to mean: a != b && ! (a < b) && ! (b > a)
    // `partial_ordering` can still return `less` and `greater` result.
    std::partial_ordering result1 { myNan <=> myFloat };
    std::partial_ordering result2 { p0 <=> n0 };

    if (result1 == std::partial_ordering::unordered)    { std::cout << "unordered" << std::endl; }
    if (result2 == std::partial_ordering::equivalent)   { std::cout << "equivalent" << std::endl; }

    // `weak_ordering` used when there's total ordering but non-equal values
    // can be equivalent. Ex: In case-insensitive comparisons, the two strings: "cat" and "CaT" are
    // equivalent even though they are not equal. Possible values are:
    // `less`, `greater`, `equivalent`.

    // The three different ordering types support implicit conversions:
    // `strong_ordering` -> `weak_ordering` -> `partial_ordering`
    // The three-way comparison operator is especially useful when comparing custom types

    // We can also interpret the result of an ordering using available named comparison functions

    std::cout << std::format("equal? {}",               is_eq(result))      << std::endl;
    std::cout << std::format("not equal? {}",           is_neq(result1))    << std::endl;
    std::cout << std::format("less? {}",                is_lt(result2))     << std::endl;
    std::cout << std::format("less equivalent? {}",     is_lteq(result))    << std::endl;
    std::cout << std::format("greater? {}",             is_gt(result1))     << std::endl;
    std::cout << std::format("greater equivalent? {}",  is_gteq(result2))   << std::endl;


    return 0;
}