#include <format>
#include <iostream>
#include <vector>


std::string getString() { return "Hello world!"; }

void addOne(int i) { i++; }     // function "naively" updates its own copy of the variable
void addOneRef(int& i) { i++; } // function actually updates the original variable

void swap(int& first, int& second)
{
    int temp { first };
    first   = second;
    second  = temp;
}

void printString(const std::string& myString) { std::cout << std::format("{}", myString) << std::endl; }


void separateOddsAndEvens(const int arr[], size_t size, int** odds, 
    size_t* numOdds, int** evens, size_t* numEvens)
{
    // Count the number of odds and evens.
    *numOdds = *numEvens = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (arr[i] % 2 == 1) ++(*numOdds);
        else ++(*numEvens);
    }

    // Allocate two new arrays of the appropriate size.
    *odds = new int[*numOdds];
    *evens = new int[*numEvens];

    // Copy the odds and evens to the new arrays.
    size_t oddsPos = 0, evensPos = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (arr[i] % 2 == 1) (*odds)[oddsPos++] = arr[i];
        else (*evens)[evensPos++] = arr[i];
    }
}

void separateOddsAndEvens(const int arr[], size_t size, int*& odds,
    size_t& numOdds, int*& evens, size_t& numEvens)
{
    numOdds = numEvens = 0;
    for (size_t i { 0 }; i < size; ++i)
    {
        if (arr[i] % 2 == 1) ++numOdds;
        else ++numEvens;
    }

    odds = new int[numOdds];
    evens = new int[numEvens];

    size_t oddsPos { 0 }, evensPos { 0 };
    for (size_t i { 0 }; i < size; ++i)
    {
        if (arr[i] % 2 == 1) odds[oddsPos++] = arr[i];
        else evens[evensPos++] = arr[i];
    }
}

void separateOddsAndEvens(const std::vector<int>& arr,
    std::vector<int>& odds, std::vector<int>& evens)
{
    for (int i : arr)
    {
        if (i % 2 == 1) odds.push_back(i);
        else evens.push_back(i);
    }
}

struct OddsAndEvens { std::vector<int> odds, evens; };

OddsAndEvens separateOddsAndEvens(const std::vector<int>& arr)
{
    std::vector<int> odds, evens;
    for (int i : arr)
    {
        if (i % 2 == 1) odds.push_back(i);
        else evens.push_back(i);
    }

    return OddsAndEvens { .odds = odds, .evens = evens };
}

int main()
{

    // --- References

    // A reference in C++ is an alias for another variable.
    // All modifications to the reference change the value of the variable
    // to which it refers. You can think of references as implicit pointers
    // that save you the trouble of taking the address of variables and 
    // dereferencing the pointer. They are like another name for the orignal variables.
    // You can: create stand-alone reference variables, use reference data 
    // members in classes, accept references as parameters to functions, and
    // return references from functions.
    // Attaching & to a type indicates that the variable is a reference

    int x { 3 };
    int& xRef { x };    // a reference variable must always be initialised when created

    xRef = 10;      // used as a normal variable (but still pointer to original variable behind the scenes)

    std::cout << std::format("x: {}; xRef: {}", x, xRef) << std::endl;

    // Notice that references cannot be changed after they are declared: they always refer
    // to the variable.
    // Any assigment to the reference only changes the value of the variable it refers to.

    int y { 4 };
    xRef = y;       // changes value of x to value of y i.e. 4. Doesn't make xRef refer to y
    // xRef = &y;      // does not compile. cannot assign `int *` to a reference to `int`,
    // `xRef` is not a reference to pointer of `int`; only `int` accepted n

    std::cout << std::format("x: {}; xRef: {}; y: {}", x, xRef, x) << std::endl;

    int z { 5 };
    int& zRef { z };
    zRef = xRef;    // assigns reference value (4) to `zRef` thus changing `z` to 4; it does not make z refer to x

    std::cout << std::format("x: {}; xRef: {}; z: {}; zRef: {}", x, xRef, z, zRef) << std::endl;

    // --- References-to-const

    // `const` applied to references is easier than when applied to pointers:
    // - references are `const` by default, you can't change what they refer to. so there's 
    //      no need to explicity mark them `const`.
    // - you can't create a reference to a reference, so there's only one level of indirection
    //      with references. However, you can create a reference to pointer which can introduce
    //      multiple level of indirection.
    // A reference-to-const is declared using one of the two equivalent syntaxes:

    [[maybe_unused]]
    const int& zRef1 { z };     // `zRef` is a reference to int constant
    // zRef1 = 4;                   // does not compile!

    [[maybe_unused]]
    int const& zRef2 { z };      // `zRef` is a refrence to constant int
    // zRef2 = 4;                  // doesn not compile!

    // The original variable can still be modified directly, you just can't do so through the reference

    // You cannot create reference to unnamed value e.g. literals, unless the reference
    // you wish to create is marked `const`.

    [[maybe_unused]]
    // int& unnamedRef1 { 5 };         // does not compile!
    const int& unnamedRef2 { 5 };   // okay

    // The same holds for temporary objects. For example, the `getString()` function
    // returns a string (specifically an `std::string` object) which is not really a variable you
    // can change, just like changing the value of constant 5. 
    // reference-to-const makes sense since you can't change it

    // std::string& string1 { getString() };   // does not compile!
    const std::string& string2 { getString() };  // okay

    // --- References to pointers and pointers to references
    // You can create references to any type, including pointer types:

    int* intP { nullptr };              // pointer to `int`
    int*& ptrRef { intP };              // reference to pointer to `int`
    ptrRef = new int;                   // allocate memory to pointer to `int` via its reference
    *ptrRef = 5;                        // assign value at the memory also via its reference
    delete ptrRef; ptrRef = nullptr;    // delete/deallocate pointer and reset via its reference

    // Taking the address of a reference gives the same result as taking the address of the
    // variable to which the reference refers to.

    int x1 { 3 };
    int& x1Ref { x1 };
    int* x1Ptr { &x1Ref };  // address of a reference is pointer to value, similar to &x1
    *x1Ptr = 100;

    // bool cmp = x1Ptr == x1Ref;  // does not compile: operands are incompatible: `int *` and `int`
    bool cmp1 = x1Ptr == &xRef; // works, here we compare pointers, which all point to `x1`
    bool cmp2 = x1Ptr == &x1;    // works, here we compare `x1Ptr` pointer to int and address of `x1` which are same

    // In both cases, even though `x1Ref` is a reference to `int`, it is used as if it were 
    // a variable of `int` type. So pointers to references in C++ does not really mean we 
    // point to the reference. Instead, we point to the original variable which the reference
    // refers to.

    std::cout << std::format("cmp1: {}; cmp2: {}", cmp1, cmp2) << std::endl;

    // finally, you cannot declare a reference to a reference, for example, `int& &` or
    // a pointer to a reference, for example `int& *`.


    // --- Structured Bindings and References
    // We have seen earlier that structured bindings can be used to decompose an object
    // and assign its data members to variables
    std::pair myPair { "hello", 5 };

    [[maybe_unused]]
    auto [theString, theInt] { myPair };

    // Instead of decomposing to variables, we can decompose to references of the variables:
    [[maybe_unused]]
    auto& [theStringRef, theIntRef] { myPair };

    // We can also mark the reference variables as `const`
    [[maybe_unused]]
    const auto& [theStringRef1, theIntRef1] { myPair };

    // --- Reference Data Members
    // Data members of classes can also be references in which case they must be
    // initialised in the constructor initialiser (and not in the constructor body)
    
    class MyClass
    {
        public:
            MyClass(int& ref) : m_ref { ref } { /* Body of constructor */ }

        private:
            int& m_ref;
    };

    // --- Reference parameters
    // The most common use of references is for function parameters. As we have seen,
    // parameter are passed by value i.e. function receive copies of their arguments
    // so that modifying them leave the original arguments unchanged. In C, pointers
    // to stack variables are passed by the calling function to the function so that
    // can modify them as needed. This, however, introduces pointer complexities and
    // requires manual memory management.
    // C++ allows pass-by-reference where parameters are references to achieve same
    // goal, but with a cleaner, simpler syntax.

    // The two functions `addOne()` defined above are used to illustrate this:

    int myInt { 7 };

    addOne(7);
    std::cout << std::format("myInt: {}", myInt)  << std::endl;

    int& myIntRef { myInt };

    addOneRef(myIntRef);
    std::cout << std::format("myInt: {}", myInt)  << std::endl;

    // Interestingly, the reference can also be used with first function
    // in which case it "acts" (or cast? *anagram*) as just an integer.
    addOne(myIntRef);
    std::cout << std::format("myInt: {}", myInt) << std::endl;

    // And we can just pass the `int`, and a reference to `int` is created
    // and used to modify the value
    addOneRef(myInt);
    std::cout << std::format("myInt: {}", myInt) << std::endl;

    // The pass-by-reference parameter function however does not accept literals
    // because we can't really change them. The solution, similar to what we
    // have discussed before, is to mark the pass-by-reference parameter as `const`
    // addOneRef(3); // fails to compile

    // The `swap()` function used below uses references to swap the values both
    // Here, the `int` variables are passed and used as references to the original
    // variables, allowing the values to be modified.
    x = 5, y = 6;
    std::cout << std::format("[before swap] x: {}, y: {}", x, y) << std::endl;

    swap(x, y);
    std::cout << std::format("[after swap]  x: {}, y: {}", x, y) << std::endl;

    // If we had pointers to the `int` as in below, we can simply dereference
    // and pass to the function. Now the function receives the `int` value but
    // as reference.
    int *xp { &x }, *yp { &y };
    swap(*xp, *yp);

    // Finally, it is not uncommon for functions to accept an output parameter 
    // through which they can use to send output typically for objects of a class 
    // that is expensive to copy which would be the case they were returned by value.
    // However, compilers (even in those days) were usually smart enough to 
    // avoid redundant copies. Therefore, it is recommeded to return objects
    // from function by value, instead of using output parameters.

    // --- Pass-by-reference-to-const
    // Pass-by-reference-to-const is used when we want to pass potentially (large)
    // object by reference (since no copy is made) but we don't also want the function
    // to modify the object

    std::string someString { "Hello World" };
    printString(someString);
    printString("Hello World"); // passing literal works

    // In conclusion, pass-by-reference offer efficiency and can be supported
    // by various C++ data types while some classes may not allow pass-by-value.
    // Pass-by-value is commonly used for simple built-in types such as `int`,
    // `double` where you don't need to modify the value.

    // --- Reference Return Values
    // You can return a reference from a function. The reference must, however, not
    // be locally scoped i.e. is deallocated/deleted when the function completes
    // execution and should continue to exist following the function termination.
    // One of the main reasons to return a reference is if you want to be able to
    // assign to the return value directly as an `lvalue` (left-hand side of an 
    // assignment statement). Several overloaded operators commonly return references.
    // Alternatively, one may return a reference from a function if the intended
    // return type is expensive to copy. This is often used to return objects by
    // reference-to-const from class member functions.

    // --- Deciding between references and pointers
    // Even though you can do almost anything you would do with references with
    // pointers, in most modern C++ code, you'll use references since they are
    // cleaner, safer since it's impossible to have a null reference and you don't
    // worry about dereferencing. Just like pointers, references to objects also 
    // support polymorphism. Pointers can sometimes be the only option in some
    // scenarios. For example, when you really need the pointer to change the
    // location it points to such as when you dynamically allocate memory; when 
    // the pointer is optional; or if you want to store polymorphic types in a container.
    // A way to distinguish pointers and references is by inspecting ownership - who
    // owns the memory. When a code receives a pointer and becomes the owner, it is
    // now responsible for releasing the memory. However, when a code receives a
    // a reference, it is not the owner and is not responsible for freeing the memory.
    // In modern C++, raw pointers should be avoided in favour of smart pointers,
    // which is the recommended way to transfer ownership.
    // In general, prefer references over pointers; i.e. use a pointer only if a reference
    // is not possible.

    // To demonstrate the advantage of references over pointers.
    // Consider a function that:
    // - splits an array of `int`s int two array: one for even numbers and another for odd numbers.
    // - the function does not know how many numbers in the source array will be even or odd (a hint
    // for dynamic memory allocation for destination arrays)
    // - the function also returns the sizes of the two new arrays.
    // Altogether, we have four items to return: pointers to the two new arrays
    // and the sizes of the two new arrays.
    // The functions `separateOddsAndEvens()` defined above use pointers for one implementation
    // and the other pass-by-references for another. You can see that the pass-by-reference version
    // is less messier than the other C-style version with pointer syntax littered everywhere.
    // They are demonstrated below:

    int unSplit[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int *oddNums { nullptr };
    int *evenNums { nullptr };
    size_t numOdds { 0 }, numEvens { 0 };

    separateOddsAndEvens(unSplit, std::size(unSplit), 
        &oddNums, &numOdds, &evenNums, &numEvens);

    std::cout << "v1: Naked Pointer" << std::endl;
    std::cout << "Even: ";
    for (size_t i { 0 }; i < numOdds; i++) { std::cout << std::format("{}, ", oddNums[i]); }
    std::cout << std::endl;

    std::cout << "Odd: ";
    for (size_t i { 0 }; i < numEvens; i++) { std::cout << std::format("{}, ", evenNums[i]); }
    std::cout << std::endl;

    // we own the memory, we must free it after use
    delete[] oddNums; oddNums = nullptr;
    delete[] evenNums; evenNums = nullptr;

    // we now call the pass-by-reference version (thanks to function overloading)
    separateOddsAndEvens(unSplit, std::size(unSplit),
        oddNums, numOdds, evenNums, numEvens);

    std::cout << "v2: Pass-by Reference" << std::endl;
    std::cout << "Even: ";
    for (size_t i { 0 }; i < numOdds; i++) { std::cout << std::format("{}, ", oddNums[i]); }
    std::cout << std::endl;

    std::cout << "Odd: ";
    for (size_t i { 0 }; i < numEvens; i++) { std::cout << std::format("{}, ", evenNums[i]); }
    std::cout << std::endl;

    // again, we own the memory allocated by the function, we must free it
    delete[] oddNums; oddNums = nullptr;
    delete[] evenNums; evenNums = nullptr;

    // the third version, which uses a totally different function signature, employs the
    // `std::vector` container for a safer, shorter, more elegant and much more readable
    // implementation. This is the preferred approach as it is recommended to avoid
    // dynamically allocated arrays as much as possible.

    std::vector<int> vecUnsplit { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> odds, evens;
    separateOddsAndEvens(vecUnsplit, odds, evens);

    std::cout << "v3: Using vectors" << std::endl;
    std::cout << "Even: ";
    for (int num : evens) { std::cout << std::format("{}, ", num); }
    std::cout << std::endl;

    std::cout << "Odd: ";
    for (int num : odds) { std::cout << std::format("{}, ", num); }
    std::cout << std::endl;

    // Here, there is no manual memory allocation and management (at least to us)
    // We do not own the memory and don't need to deallocate it; the `std::vector`
    // class takes of this.

    // We can make this more simpler by following the simple rule we introduced
    // earlier: Avoid output parameters and return it by value if a function needs
    // to return something

    auto [odds1, evens1] { separateOddsAndEvens(vecUnsplit) };

    std::cout << "v4: Returning values" << std::endl;
    std::cout << "Even: ";
    for (int num : evens) { std::cout << std::format("{}, ", num); }
    std::cout << std::endl;

    std::cout << "Odd: ";
    for (int num : odds) { std::cout << std::format("{}, ", num); }
    std::cout << std::endl;


    return 0;

}