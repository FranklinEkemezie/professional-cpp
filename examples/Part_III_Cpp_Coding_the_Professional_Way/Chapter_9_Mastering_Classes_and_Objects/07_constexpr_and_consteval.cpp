#include <print>

// const int getArraySize() { return 32; } // cannot be used as compile time "constant expression"

constexpr int getArraySize() { return 32; } // can be evaluated at compile time

void log(std::string_view message) { std::println("[LOG] {}", message); }

constexpr int computeSomething(bool someFlag)
{
    // `constexpr` functions cannot execute calls that have side effects, or
    // let any exceptions escape the function. You can unconditionally call other
    // `constexpr` function, but non-`constexpr` call only be called if it's
    // guaranteed that section of the code is executed at runtime and is not 
    // reachable during compile time.
    // With C++23, you can now use `goto`, labels (except `case` labels), and
    // `static` and `static constexpr` variables in `constexpr` functions.

    if (someFlag)
    {
        // OK for compile-time computation as long `someFlag` is false
        // and we don't get to execute the non-`constexpr` `log()` function
        // at compile time

        log("someFlag is true")   ;
        return 42;
    }
    else { return 84; }
}

constexpr double inchToMm(double inch) { return inch * 25.4; }

// Functions can be marked with `consteval`
// A `consteval` function is a called an immediate function.
// It must be called during constant evaluation i.e. "inch" parameter
// for example, must a compile-time constant.
consteval double inchToMmConstEval(double inch) { return inchToMm(inch); }

consteval int f(int i) { return i; }

constexpr int g(int i)
{
    // A `constexpr` function which can be called during runtime 
    // (i.e. even when the parameters are not constant/known at compile-time)
    // can call an immediate function as long as they do so only
    // during a constant evaluation. In C++ 23, you can use `consteval` with
    // `if` statement to check if the function is being executed at
    // compile time or run time.

    if consteval    { return f(i); }    // only call during constant evaluation
    else            { return 42; }
}

class Matrix
{
    public:
        Matrix() = default;

        constexpr explicit Matrix(unsigned rows, unsigned columns)
            : rows_ { rows }, columns_ { columns } { }

        constexpr unsigned getSize() const { return rows_ * columns_; }

    private:
        unsigned rows_ { 0 }, columns_ { 0 };
};

int main() 
{

    // The `constexpr` and `consteval` keywords allow us to perform compile-time
    // computations.
    // In many editors such as VSCode, you can hover and see the result of value
    // of compile time constant expressions without running the code.

    std::println("-- `constexpr` keyword");

    int myArray[getArraySize() + 1];
    std::println("Size of array = {}", std::size(myArray));

    constexpr auto value1 { computeSomething(false) };
    std::println("value1: {}", value1); // the value is already known before the code is even executed

    // constexpr auto value2 { computeSomething(true) }; // does not compile: attempt to call non-`constexpr` `log()`
    const auto value2 { computeSomething(true) }; // works! done at run time.

    std::println("value2: {}", value2);
    
    std::println("-- `consteval` keyword");

    // While `constexpr` keyword specifies that a function could be executed at
    // compile time, it does not guarantee that the compiler must always evaluate
    // at compile-time depending on how it's used.

    constexpr double const_inch { 6.0 };
    constexpr double mm1 { inchToMm(const_inch) };  // Computed at compile time. Normal!
    std::println("mm1: {}", mm1);

    double dynamic_inch { 8.0 };
    double mm2 { inchToMm(dynamic_inch) };  // Not computed at compile time, as it is not declared `constexpr`
    std::println("mm2: {}", mm2);

    // double mm3 { inchToMmConstEval(dynamic_inch) }; // won't compile: `dynamic_inch` cannot be used as argument as it is not compile time constant expression
    double mm3 { inchToMmConstEval(const_inch) }; // Ok!
    std::println("mm3: {}", mm3);

    int i1 { g(23) };           // Evaluated at run time: `i1` is not constant expression
    std::println("i2: {}", i1); // Prints "42"

    constexpr int i2 { g(23) }; // Evaluated at compile time
    std::println("i2: {}", i2); // Prints "23"

    std::println("-- `constexpr` and `consteval` Classes");
    // You can mark a constructor as `constexpr` or `consteval` which allows you
    // create constant-expression variables of your user-defined types. As usual,
    // while `constexpr` classes may or may not be evaluated at compile time, 
    // `consteval` classes are guaranteed to be evaluated at compile time.
    // You can also mark member functions as `constexpr` allowing to compute these
    // all at compile time.
    // Compiler-generated (implicitly or explicitly using `= default`) member functions,
    // such as default constructors, destructors, assignment operators, etc are 
    // automatically `constexpr` unless the class contains data members where those
    // member functions (which the compiler is trying to generate) are not `constexpr`.
    // The defintion of `constexpr` and `consteval` member functions must be available
    // for the compiler so they can be evaluated at compile time, meaning they must be
    // defined in the module interface file, not in a module implementation file.
    // Lastly, several classes from the Standard Library (e.g. `vector`, `optional`, 
    // `string`, `unique_ptr`, `bitset`, `variant` etc) are `constexpr` and so can
    // be used within other `constexpr` functions and classes.

    constexpr Matrix matrix { 8, 2 };
    constexpr Matrix matrixDefault {  };

    int linearizedMatrix[matrix.getSize()]; // OK!
    std::println("linearized matrix size: {}", std::size(linearizedMatrix));

    constexpr int matrixDefaultSize { matrixDefault.getSize() };
    std::println("Matrix Default Size: {}", matrixDefaultSize);

}