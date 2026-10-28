#include <charconv>
#include <initializer_list>
#include <print>
#include <string>
#include <vector>


class SpreadsheetCell
{

    public:

        SpreadsheetCell() = default;
        SpreadsheetCell(double initialValue);
        SpreadsheetCell(std::string_view initialValue);

        SpreadsheetCell(const SpreadsheetCell& src) = default;

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
    : value_ { initialValue }
{

}

// Delegate to the "double" constructor
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

// You should avoid constructor recursion while using delegating constructors

// class MyClass
// {
//     public:
//         MyClass(char c)     : MyClass { 1.2 } { }
//         MyClass(double d)   : MyClass { 'm' } { } // recursive delegation
// };

int main()
{

    SpreadsheetCell cell { "5.2" };
    std::println("{}", cell.getValue());

    // compiles but behaviour is undefined; can result in segfault
    // MyClass myClass { 'X' }; 

}