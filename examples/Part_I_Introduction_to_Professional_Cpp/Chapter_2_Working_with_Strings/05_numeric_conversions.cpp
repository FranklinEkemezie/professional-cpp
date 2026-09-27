#include <charconv>
#include <format>
#include <iostream>
#include <string>


using std::string;

int main()
{
    // --- Numeric Conversion
    // The C++ standard library provides both high-level and low-level numeric
    // conversion functions

    // --- High-level numeric conversion (defined in <string>)
    // 

    // Converting to strings
    long double d { 3.14L };
    string s { std::to_string(d) };

    std::cout << std::format("{}\n", s);
    std::cout << std::format("{}, {}, {}, {}\n",  // supports various integer/float/double types
        std::to_string(static_cast<unsigned int>(d)),
        std::to_string(static_cast<float>(d)),
        std::to_string(static_cast<long long>(d)),
        std::to_string(static_cast<unsigned short>(d))
    );

    // Converting from strings
    // These can be done using the functions: `stoi()`, `stol()`, `stoul()`,
    // `stoul()`, `stoll()`, `stof()`, `stod()` and `stold()` which as expected
    // convert a string to `int`, `long`, `unsigned long`, `long long`, `float`,
    // `double` and `long double` respectively. These functions accept as
    // parameters a reference-to-`const` string to be converted, optional pointer
    // (defaulting to `nullptr`) which receives position/index of the first
    // unconverted character, and a mathematical base (default is 10) (for string
    // -to-integer conversion functions like `stoi()`) to be used during conversion. 
    // These functions also ignore leading whitespace, and throw `invalid_argument` 
    // exception if no conversion could be performed, and `out_of_range` if the
    // converted value is outside of the range which its return type can represent.

    const string toParse { "   123USD" };
    size_t index { 0 };
    int value { std::stoi(toParse, &index) };

    std::cout << std::format("Parsed value: {}\n", value);
    std::cout << std::format("First non-parsed character: '{}'\n", toParse[index]);

    // For the base, the default is 10, where decimal numbers 0-9 are expected,
    // and hexadecimal numbers for base of 16, etc. If the base is set to 0, the
    // function automatically figures out the base as hexadecimal if it starts
    // with 0x or 0X, octal if it starts with 0, or decimal.

    // --- Low-Level Numeric Conversions (defined in <charconv>)
    // Unlike the previous functions, these functions do not perform any memory
    // allocations and do not work directly with `std::string`s, but instead use
    // raw buffers provided by caller. They are turned for high-performance, are
    // locale-independent and designed for perfect round-tripping, this means 
    // serialising a numerical value to a string representation followed by
    // deserialising the resulting string back to a numerical value results in 
    // exact same value as the original one making them useful in serialising/
    // deserialising data to/from human-readable formats such as JSON, XML, etc.

    // --- Converting to strings
    // The `to_chars()` function is used to convert integers to characters. It
    // accepts as its parameters pointers to the first and last character of
    // the pre-allocated string buffer, the integer (any integer type) value
    // to be converted and optional base (defaulting to 10). The result is a
    // `to_chars_result` struct containing the `char * ptr` pointer and `errc ec`
    // enumeration. The `ptr` is either equal to one-past-the-end of pointer 
    // of written characters if successful or equal to pointer to the `last`
    // character if the conversion failed (in which case `ec` equals 
    // `errc::value_too_large`). When successful, `ec` is equal to a the default
    // constructed `errc`.
    // In the example we use `out.size()` because it gives the number of
    // characters in the string (null-termination not included), which exactly
    // makes the `out.data() + out.size()` fall exactly on the null-termination
    // which is the desired last character since strings, like arrays are zero-indexed.

    const size_t BufferSize { 50 };
    string out(BufferSize, ' '); // a string of BufferSize space characters
    auto result { std::to_chars(out.data(), out.data() + out.size(), 12345) }; 
    if (result.ec == std::errc{}) { std::cout << std::format("{}\n", out); }

    // WIth structured bindings, you can easily destructure the result:
    auto [ptr, error] { result };
    if (error == std::errc{}) { std::cout << std::format("{}\n", out); }

    // A similar set of functions is available for floating-point types except
    // that they do not accept the last optional base like the integer versions.
    // Instead, different overloads of the function allows you to specify a
    // format and optional integer to specify a precision. The format is a 
    // `chars_format` enum class with enumerations:
    // - `scientific`   - (-)d.ddde±dd
    // - `fixed`        - (-)ddd.ddd
    // - `hex`          - (-)h.hhhhp±d (Note: no 0x!)
    // - `general`      - `fixed` | `scientific` (default)

    // When `general` is used as format, the result is one of `fixed` or `scientific`
    // either of which results in a shorter representation with at least one digit before
    // the decimal point (if present). When no precision is specified, the 
    // precision for the shortest possible representation for the given format is used,
    // with a maximum of six digits.

    double value1 { 0.314 };
    string out1(BufferSize, ' ');
    auto [ptr1, error1] { std::to_chars(out1.data(), out1.data() + out1.size(), value1) };
    if (error1 == std::errc{}) { std::cout << std::format("{}\n", out1); }

    // --- Converting from strings
    // For the opposite conversion, a similar set of functions `from_chars()`
    // provided. It accepts pointers to the first and last characters of the
    // strings to convert from, a value (reference to integer or floating-point
    // types), and optional base integer for string-to-integer conversions 
    // (defaulting to 10), or optional `chars_format` enum format (defaulting
    // to `general` as discussed before) for string-to-floating-point 
    // conversions. It returns a `from_chars` struct with `const char* ptr` and
    // `errc ec` enumeration data members. The `ptr` member is a pointer to the
    // first character that was not converted or to the last character if all 
    // characters were successfully converted. If no characters could be converted,
    // `ptr` equals `first`, and the error code `ec` will be `errc::invalid_argument`.
    // If the parsed value is too large to be representable by the return type,
    // then `ec` will be `errc::result_out_of_range`.
    // NB: `from_chars()` does not skip any leading whitespaces.
    // In the next example, we demonstrate `from_chars()` usage, as well the
    // perfect round-tripping feature of `to_chars()` and `from_chars()`:

    double value2 { 0.314 };
    string out2(BufferSize, ' ');
    auto [ptr2, error2] { std::to_chars(out2.data(), out2.data() + out2.size(), value1) };
    if (error2 == std::errc{}) { std::cout << std::format("{}\n", out2); }

    // Now `out2` contains the resulting string from the last conversion
    // Let's do the opposite, storing the result in another `double` variable

    double value3;
    auto [ptr3, error3] { std::from_chars(out2.data(), out2.data() + out2.size(), value3) };
    if (error3 == std::errc{})
    {
        if (value2 == value3) std::cout << "Perfect roundtrip\n";
        else std::cout << "No perfect roundtrip?!?\n";
    }

}