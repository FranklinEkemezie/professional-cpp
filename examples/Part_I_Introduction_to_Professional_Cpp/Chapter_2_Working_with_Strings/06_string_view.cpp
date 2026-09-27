#include <format>
#include <iostream>
#include <string>
#include <string_view>

std::string extractExtension(std::string_view filename)
{
    // Return a copy of the extension.
    return std::string { filename.substr(filename.rfind('.')) };
}

int main()
{

    // -- The `std::string_view` class
    // Before C++17, when you wanted to choose the parameter type for a function
    // that accepted a read-only string, you have a few (sub-optimal) options:
    // - make the parameter a `const char*` - you loose type-safety, object-
    //      oriented goodies and `string` class nice helper member functions.
    // - make the parameter a `const string&` - Here, you will always need a 
    //      `string` object. When a `string` is passed, a `const` reference to
    //      it is used. But when a string literal is passed, the compiler 
    //      silently creates a temporary `string` object, copy your string
    //      literal and then pass a reference to that object to your function,
    //      thus adding some overhead.
    // - choose both world - write overloads that accept both `const char*` and
    //      `const string &` which is not so elegant.

    // Problems such as these were solved with introduction of `string_view`s.
    // The `std::string_view` class, an instantiation of the `std::basic_string_view`
    // class template (defined in <string_view>), is used to provide a readonly
    // view of a string. It is basically a drop-in replacement for `const string&
    // ` without the overhead as it never copies strings. It supports similar 
    // interface to `string` including the `contains()` member function introduced
    // in C++23, except the absence of `c_str()`, though `data()` is available.
    // Included are additional member functions `remove_prefix(size_t)` and 
    // `remove_suffix(size_t)` which shrink a string by advancing the starting/
    // end pointer by a given offset forward/backward respectively. As with 
    // strings, any construction with `nullptr` fails from C++23.
    // As rules of thumbs:
    // - Use an `std::string_view` insteaf of `const string&` or `const char*`
    //      whenever a function requires a read-only string as a parameter.
    // - Functions returning a string should return a `const string&` or a 
    //      `string` but not a `string_view`. Returning a `string_view` would
    //      risk being invalid when the returned `string_view` needs to 
    //      be reallocated.
    // - Storing a `const string&` or a `string_view` as a data member of a class
    //      requires you to make sure the string to which they refer to stays
    //      alive for the duration of the object's lifetime since they are not
    //      copied. It is strongly recommended to store an `std::string` instead.

    // Below shows the usage of a function using `string_view`:
    // In all of these, not a single copy is made to resolve the parameter.

    std::string filename { R"(c:\temp\my file.ext)" };
    std::cout << std::format("C++ string: {}\n", extractExtension(filename));

    const char* cString { R"(c:\temp\my file.ext)" };
    std::cout << std::format("C string: {}\n", extractExtension(cString));

    std::cout << std::format("Literal: {}\n", extractExtension(R"(c:\temp\my file.ext)"));

    // There is also a `std::string_view` constructor that accepts any raw buffer
    // and a length which constructs a string view from a string buffer that is not
    // necessarily NUL (\0) terminated. Providing the (optional) length prevents
    // the constructor from counting the number of characters again.

    const char* raw { R"(c:\temp\my file.ext)" };
    size_t length { 20 };
    std::cout << std::format("Raw: {}\n", extractExtension(std::string_view { raw, length }));

    // You can also construct one from a common range (a range based on iterators)
    // and since C++23 from a modern range. Iterators, common ranges, and modern
    // ranges are discussed later.

    // You cannot implicitly construct a `string` from a `string_view`. This is 
    // prevent accidental copying of the string in `string_view` as constructing
    // a `string` from `string_view` always involves copying the data. That way,
    // you are forced to explicitly indicate that you wish to construct this
    // `string`, and okay with copying it. This is exactly what the function used
    // above does.
    // For the same reason, you cannot concatenate a `string` and `string_view`:

    std::string str { "Hello" };
    std::string_view sv { " world" };

    // auto result { str + sv }; // Error, does not compile!
    auto result { str + std::string { sv } }; // construct a string and then concatenate

    std::cout << std::format("result: {}\n", result);

    // or use append(), specifically the overload the accepts 
    // `const char *` and its length
    std::cout << std::format("result: {}\n", result.append(sv.data(), sv.size()));


    // --- `std::string_view` and temporary strings
    // A `std::string_view` should never be used to store a view of a temporary
    // string. For example, the code snippet below has undefined behaviour. The
    // result of the concatentation is stored in a temporary pointer which is
    // destroyed on moving to the next line. Since the a string view never
    // copies its string content, it still points to that temporary dangling 
    // pointer which is no longer valid (destroyed)
    
    std::string s { "Hello" };
    std::string_view sv1 { s + " World!" };
    std::cout << std::format("{}\n", sv1);  // might work? might crash? weird results? 

    // --- `std::string_view` literals
    // You can use the standard literal `sv` to interpret a string literal as
    // `std::string_view`. The standard literal `sv` requires one of the
    // following `using` directives:    
    // using namespace std;
    // using namespace std::literals;
    // using namespace std::string_view_literals:
    using namespace std::literals::string_view_literals;

    [[maybe_unused]] auto sv2 { "My string_view"sv };

    // --- Nonstandard Strings
    // Some frameworks and operating systems tend to have their own way of
    // representing strings typically for backward compatibility or to address
    // legacy issues. When doing so, it is helpful to leverage the capabilites
    // of `std::string` class and `std::string_view` class
    

    return 0;
}