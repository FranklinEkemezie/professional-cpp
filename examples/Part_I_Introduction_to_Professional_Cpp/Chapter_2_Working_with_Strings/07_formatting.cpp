#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

enum class Language { English, Dutch };

string_view GetLocalizedFormat(Language language)
{
    switch (language)
    {
        case Language::English: return "Numbers: {0} and {1}.";
        case Language::Dutch:   return "Getallen: {0} en {1}.";
        default: throw invalid_argument { "Unknown language" };
    }
}

int main()
{

    // --- Formatting and Printing Strings

    // C++20 introduced `std::format()` defined in <format> to format strings.
    // Before then, C-style functions like `printf()` and C++ I/O streams like
    // `std::cout` were used. While C-style functions were easier to read than
    // C++ I/O streams, they are not type safe and not extensible to support 
    // your custom types.
    // `std::format()` combines the advantages of both C-style functions and
    // C++ I/O streams, being type-safe and extensible.
    
    int x { 3 }, y { 4 };

    cout << format("x has value {} and y has value {}", x, y) << endl;

    // C++23 introduces `std::print()` and `std::println()` functions which
    // makes it easier. These functions have better support for writing
    // UTF-8 Unicode text to Unicode-compliant consoles allowing you to
    // unconventional characters such as those found in Japanese or Chinese
    // languagues, as well as emojis. To compile source code containing
    // Unicode characters, you might need to pass a compiler switch. E.g.,
    // GCC accespts the option `-finput-charset=UTF-8`

    // --- Format strings

    // Formatting functions such as `std::format()`, `print()`, and `println()`
    // accepts a format string as the first parameter to specify how the given 
    // arguments must be formatted in the output string. 

    // 1. Curly braces, {} represent a replacement field. Subsequent arguments
    // are used to fill in those replacement field. Add an extra brace to escape
    // the curly brace, e.g. {{ or }}.

    // 2. Inside the replacement field, we can enter a string in the form:
    // [index][:specifier] i.e. an optional argument index and optional format
    // specifier which stipulates how a value must be formatted in the output.
    
    // 3. You must pass a format string to these formatting functions. That is,
    // instead of println(x), you would do println("{}", x) and to print a newline
    // you would do println("") instead of println().

    // --- Argument indices

    // You can omit the `index` from all replacement fields or specify for all
    // of them. An index of 0 refers to the second argument . You may use an
    // index multiple time if you want to output that value multiple times.

    int n { 42 };

    cout << format("Read {} bytes from {}", n, "file1.txt") << endl;
    cout << format("Read {0} bytes from {1}", n, "file1.txt") << endl;

    // Specifying the index can be useful when we want to switch the ordering of
    // values without have to switch the arguments each time, for example in 
    // translation.

    cout << format("From {1} read {0} bytes", n, "file1.txt") << endl; // same argument order
    cout << format("Read from {1} {0} bytes", n, "file1.txt") << endl;

    // We can print to a different destination from `cout`. For`print()` and
    // `println()` functions, you pass the destination output stream as the the
    // first argument, and continue with format strings and arguments.

    cerr << format("x has value {} and y has value {}.", x, y) << endl; // print to standard error

    // Ad of C++23, the format string for these formatting functions must be a
    // compile-time constant so that the compiler can check for syntax errors

    string s { "Hello World!" };
    // cout << format(s) << endl;  // Does not compile: s is not a constant expression
    cout << format("{}", s) << endl; // Works

    constexpr auto formatString { "Value: {}" };
    cout << format(formatString, 11) << endl;   // Works

    // If you want non-compile-time constant format strings, for example, to
    // localise/translate format strings for different language, you may use
    // `std::vprint_unicode()` or `std::vprint_nonunicode()` instead of `print()`
    // though they are more cumbersome since you need to use `std::make_format_args()`
    // to parse the arguments for the format strings.
    // This, however, like `print()` and `println()` are available in C++23.
    // Syntax:
    // vprintf(GetLocalizedFormat(Language::English), make_format_args(1, 2));
    // Non-compile-time constant format strings are verified at run time, and
    // therefore throw `std::format_error` exceptions for any format string error.


    // --- Format specifiers
    // The general form of a format specifier is:
    // [[fill]align][sign][#][0][width][.precision][L][type]
    // where  all parts between square brackets are optional

    // 1. width - minimum width of the field into which the given value should
    // be formatted. You can specify an integer or another set of curly braces
    // for dynamic widths in which case, the width value is obtained from the
    // index in the curly braces, or the next argument if index is not specified.

    int i { 42 };

    cout << endl << "--- width" << endl;
    cout << format("|{:5}|", i) << endl;        // width is 5
    cout << format("|{:{}}|", i, 7) << endl;    // width is 7 (after argument for the value)
    cout << format("|{1:{0}}|", 7, i) << endl;  // width is 7 (based on the index specified in dynamic width curly braces)

    // 2. [fill]align - what character to use to fill up the specified with and optionally
    // how to align the value. Use <, >, ^ for left, right or centre alignment.
    // Integers and floating-point numbers are right aligned by default, while others
    // are left aligned by default. If no width is specified, fill and align does
    // not have any effect. For centre alignment, an extra fill character is added on
    // the right if the total number of fill characters is odd

    cout << endl << "--- [fill]align" << endl;
    cout << format("|{:7}|", i) << endl;    // width = 7, default aligned
    cout << format("|{:<7}|", i) << endl;   // width = 7, left aligned
    cout << format("|{:_>7}|", i) << endl;  // width = 7, fill with '_', right aligned
    cout << format("|{:_^7}|", i) << endl;  // width = 7, fill with '_', centre aligned

    // print equal sign (=) 16 times
    cout << format("|{:=>16}|", "") << endl;    // width = 16, fill with =, right align

    // 3. sign - when formatting numbers: Use '-', '+', or ' ' to display sign
    // for only -ve numbers (default), for both +ve and -ve, or display minus
    // for -ve but space for +ve numbers

    cout << endl << "--- sign" << endl;
    cout << format("|{:<5}|", i) << endl;
    cout << format("|{:<+5}|", i) << endl;
    cout << format("|{:< 5}|", i) << endl;
    cout << format("|{:< 5}|", -i) << endl;

    // 4. # - enable alternate formatting rules. With formatting type (see next
    // section, no. 5) specified, it inserts a 0x or 0X, 0b or 0B, or 0 for
    // integral types to be formatted as hexadecimal, binary or octal respectively.
    // For floating-points, the alternate format will always output a decimal
    // operator, even if no digits follow it.

    // 5. type - the type a given value must be formatted in:
    // - integers - b or B, d, o, x or X to output the value as binary, decimal, 
    // octal, or hexadecimal. Using uppercase B or X makes all the characters to
    // be in uppercase, including the characters appended when # is enabled. By
    // default, d is used for integer types and outputs the decimal values.
    // - floating-point: e or E for scientific notation using e or E as exponent; 
    // f or F for fixed notation; - g or G for general chooses from either 
    // scientifc or exponential as previously discussed for `std::chars_format`;
    // - a or A for hexadecimal using lower (a) or uppercase (A) letters.
    // g is the default if unspecified for floating-point types.
    // - booleans: s (default) outputs true or false text, while b or B, c, d, d,
    // o, x or X outputs 1 or 0.
    // - characters: c (default) (or ?) so actual (or escaped) character is copied 
    // to output; b or B, d, o, x or X so the integer representation is used.
    // - strings: s (default) (or ?) so actual (or escaped) string is copied to output;
    // - pointers: p (default; hexadecimal notation of the pointer prefixed with 0x)
    // only pointers of type `void*` can be formatted. other pointer types must
    // first be cast to `void *` for example using `static_cast<void *>(myPtr)`

    cout << endl << "--- type" << endl;
    cout << format("|{:10d}|", i) << endl;
    cout << format("|{:10b}|", i) << endl;
    cout << format("|{:#10b}|", i) << endl;
    cout << format("|{:10X}|", i) << endl;
    cout << format("|{:#10X}|", i) << endl;

    s = "ProCpp";
    cout << format("|{:_^10}|", s) << endl;

    // Examples on floating-point types are givein in the next section under 'precision'

    // 6. precision - applies to only floating-point and string types. it is 
    // specified as dot followed by the number of decimal digits (including
    // before decimal separator, except fiexd notation is used`f` or `F`) 
    // to output for floating-point types, or the number of characters to 
    // output for strings. This can also be dynamic like width, and the
    // precision is taken from the next arguement in the list of arguments
    // or from the argument with given index

    double d { 3.1415 / 2.3 };

    cout << endl << "--- precision" << endl;
    cout << format("|{:12g}|", d) << endl;
    cout << format("|{:12.2g}|", d) << endl;
    cout << format("|{:12e}|", d) << endl;

    int width { 12 }, precision { 3 };
    cout << format("|{2:{0}.{1}f}|", width, precision, d) << endl;
    cout << format("|{2:{0}.{1}}|", width, precision, d) << endl;


    // 7. 0 - For numerical values, zeros sare used to obtain the desired minimum
    // width. The number of zeros factor in signs and any of the binary or hexadecimal
    // prefixes.

    cout << endl << "--- 0" << endl;
    cout << format("|{:06d}|", i) << endl;
    cout << format("|{:+06d}|", i) << endl;
    cout << format("|{:06X}|", i) << endl;
    cout << format("|{:#06X}|", i) << endl;

    // 8. L - enables locale-specific formatting. This option is valid only for
    // arithmetic types e.g. integers, floating-point types and Booleans. For 
    // integers, it specifies that the local-specific digit group separator character
    // must be used, for floating-point types, locale-specific group and decimal
    // separator must must be use, and for booleans in textual form, the 
    // locale-specific representation of `true` and `false` must be used.
    // This works only with `format()` not `print()` and `println()` and you must
    // pass a `std::locale` instance as the first parameter instead.

    float f { 1.2f };
    cout << endl << "--- L" << endl;
    cout << format("|{:g}|\n", f);
    // cout << format(locale{ "nl" }, "|{:Lg}|\n", f);

    // --- Formatting Escaped Characters and Strings
    // By using the `?` type specifier, you can output escaped characters as
    // they are. This is typically useful in logging and debugging purposes.
    // For unprintable characters, the escaped output is `\u{hex-code-point}`

    cout << endl << "--- format escaped characters and strings" << endl;
    // cout << format("|{:?}|", "Hello\tWorld!\n") << endl;
    // cout << format("|{:?}|", "\"") << endl;
    // cout << format("|{:?}|", '\'') << endl;
    // cout << format("|{:?}|", '"') << endl;


    // --- Formating Ranges
    // "Standard Library Containers" such as `std::vector`, `array`, `pair` etc
    // can be directly formatted from C++23. For ranges such as `vector`s and `array`s, 
    // the output is surrounded by square brackets with inidividual elements
    // separated by commas, by default. The underling elements are formatted
    // recursively. When the elements are strings, they are escaped.
    // The format specifier is in the form:
    // [[fill]align][width][n][range-type][:range-underlying-spec]
    // `fill`, `align` and `width` retain their usual mean. 
    // - When `n` is specfied, the output does not contain opening and closing brackets. 
    // - `range-type` can be:
    //      >> `m` - for `pair`s and `tuple` with only two elements; the brackets
    //      are removed, and are separated by ": "  rather than the default commas
    //      >> `s` (or ?s) - formats the range as a (escpaed) string (cannot be 
    //      combined with `n` or `range-underlying-spec`)
    // - `range-underlying-spec` - optional format specifier for the individual
    //      elements of the range. This can be nested multiple levels deep. If the
    //      elements are again ranges, then this should be another range format specifier
    // Examples are commented out as they are only available on C++23


    vector values { 11, 22, 33 };

    cout << endl << "--- formatting ranges" << endl;
    cout << format("{}", values) << endl;
    // cout << format("{:n}", values) << endl;

    // To replace the surrounding brackets, combine it with the `n` specifier
    // cout << format("{[:n]}", values) << endl;
    // cout << format("{{{:n}}}", values) << endl;  // Escape curly braces if you want to use them {{ and }}

    // You can do many other things:

    cout << format("{:*^16}", values) << endl;  // the range output has a min width of 16, fill with *, centre aligned
    cout << format("{:*^16n}", values) << endl; // same but the default square brackets are not included

    cout << format("{::*^6}", values) << endl; // the formatting is specified for individual elements.
    cout << format("{:n:*^6}", values) << endl; // surrounding brackets removed; format individual item

    vector strings { "Hello"s, "World!\t2023"s };

    cout << format("{}", strings) << endl; // square brackets for range, string items formatted default and escaped
    cout << format("{:}", strings) << endl; // same as before, no format specified for individual string items
    cout << format("{::}", strings) << endl; // default used for range, string, characters (characters not escaped by default)
    cout << format("{:n:}", strings) << endl; // remove square bracket for range, others same as previous

    vector chars { 'W', 'o', 'r', 'l', 'd', '\t', '!' };

    cout << format("{}", chars) << endl; // format as range of chars, with square brackets, characters escaped
    cout << format("{::#x}", chars) << endl; // format individual characters as hexadecimal values
    cout << format("{:s}", chars) << endl; // format individual characters as strings (not escaped)
    cout << format("{:?s}", chars) << endl; // format individual characters as strings (escaped)

    pair p { 11, 22 };
    cout << format("{}", p) << endl;    // surrounded by parentheses (default)
    cout << format("{:n}", p) << endl;  // remove surrounding parentheses
    cout << format("{:m}", p) << endl;  // remove surronding parentheses, separate using ": "

    vector<vector<int>> vv { { 11, 22 }, { 33, 44, 55 } };

    cout << format("{}", vv) << endl;       // default, outer and inner range with surrounding square brackets
    cout << format("{:n}", vv) << endl;     // remove surrounding square brackets for outer range
    cout << format("{:n:n}", vv) << endl;   // remove surrounding square brackets for both ranges
    cout << format("{:n:n:*^4}", vv) << endl;// same as previous, individual integer item now formatted


    return 0;
    

}