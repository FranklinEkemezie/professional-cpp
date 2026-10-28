#include <charconv>
#include <print>
#include <string_view>

class SpreadsheetCell
{

    public:
        SpreadsheetCell() = default;
        SpreadsheetCell(double initialValue);
        // By default, constructors are converting constructors which allows
        // them to be used to convert the arguments they accept to an object.
        // `explicit` makes this constructor an "explicit constructor" and
        // prevents them from doing so.
        explicit SpreadsheetCell(std::string_view initialValue);
        SpreadsheetCell(const SpreadsheetCell& src);

        void setValue(double value);
        double getValue() const;

        void setString(std::string_view value);
        std::string getString() const;

    private:
        std::string doubleToString(double value) const;
        double stringToDouble(std::string_view value) const;


    private:
        double value_ { 0 };
};

SpreadsheetCell::SpreadsheetCell(double initialValue) 
    : value_ { initialValue } // ctor or constructor initialiser
{

}

SpreadsheetCell::SpreadsheetCell(std::string_view initialValue)
    : SpreadsheetCell { stringToDouble(initialValue) }
{
}


void SpreadsheetCell::setValue(double value)
{
    value_ = value;
}


double SpreadsheetCell::getValue() const
{
    return value_;
}

void SpreadsheetCell::setString(std::string_view value)
{
    value_ = stringToDouble(value);
}

std::string SpreadsheetCell::getString() const
{
    return doubleToString(value_);
}

std::string SpreadsheetCell::doubleToString(double value) const
{
    return std::to_string(value);
}

double SpreadsheetCell::stringToDouble(std::string_view value) const
{
    double number { 0 };
    std::from_chars(value.data(), value.data() + value.size(), number);
    return number;
}

// From C++11, with the introduction of initialiser lists,
// converting constructors can have more than one parameter
class MyClass
{
    public:
        // Mark the constructors as `explicit` to prevent implicit conversions
        MyClass(int) { }
        MyClass(int, int) { }
        // You can pass a Boolean argument. It is the example below it is redundant
        // but we can use it with generic template code to mark certain type convertible
        explicit(true) MyClass(int, int, int) { }
};

void processMyClass(const MyClass& c)
{
    std::println("Processing my class...");
}

int main()
{

    SpreadsheetCell myCell { 4 };
    std::println("{}", myCell.getValue());

    // Compiler implicitly converts `5` to a SpreadsheetCell object 
    // by calling the "double" constructor and then assigns it.
    // This is possible because the constructor (by default) is a converting constructor
    myCell = 5; 
    std::println("{}", myCell.getValue());

    // Compiler implicitly converts the string view to Spreadsheet object
    // by calling the "string view" constructor overload and assigns it.
    // Again, this is possible because the constructor is converting.
    // using namespace std::literals::string_view_literals;
    // myCell = "6"sv; // "string view" constructor marked "explicit", and thus cannot be used to perform implicit conversion
    // std::println("{}", myCell.getValue());

    std::println("--- Converting constructors with more than parameter using list initialisers");

    processMyClass(1);          // converts `1` to temporary `MyClass` object
    processMyClass({ 1 });      // same as previous
    processMyClass({ 1, 2 });   // converts to the other constructor with two parameters
    processMyClass(MyClass { 1, 2, 3 });    // must explicitly convert them yourself
    
    // Recommendation: Mark a constructor that can be called with a single argument as
    // `explicit` to avoid accidental implicit conversion. For constructors with more
    // than one arguments, the caller will intentionally make use of initialiser for implicit
    // conversion. If you really need implicit conversion, state it clearing using
    // `explicit(false)` to make your intention clear.

    std::println("--- Summary of compiler generated constructors");
    std::println("If you don't define a copy constructor explicitly, the compiler generates one for you.");
    std::println("If you define any constructor (copy or non-copy), the compiler does not generate a default (zero-argument) constructor for you.");


}