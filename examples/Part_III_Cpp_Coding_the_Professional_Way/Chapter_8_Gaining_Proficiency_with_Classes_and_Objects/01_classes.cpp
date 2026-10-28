#include <charconv>
#include <format>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')


struct Point
{
    // Structs in C++ also have access control specifiers, but
    // are "public" by default. However, it's unconventional to do so.
    // Structs are typically used a simple collection of public data
    // members with no member functions

    double x;
    double y;
};

class SpreadsheetCell
{

    // default access specifier for classes is "private"
    // so anything before here is private

    public:
        void setValue(double value);
        double getValue() const;

        void setString(std::string_view value);
        std::string getString() const;


    private:
        std::string doubleToString(double value) const;
        double stringToDouble(std::string_view value) const;

    private:
        double value_ { 0 }; // initialised using in-class initialiser: recommended
};

// Function prototypes

void printCell(const SpreadsheetCell& cell);


void SpreadsheetCell::setValue(double value)
{
    value_ = value;

    // you can also do: this->value_ = value;
    // `this`is a pointer to the object.

    printCell(*this); // pass the object to the function
}

// C++23 introduces explicit object parameter: Like in Python, you receive
// a reference to the object instance as the first argument. The function
// will no longer have the implicitly defined `this`. The usage remains the same.
// They become more useful when you want to:
// - provide a more explicit syntax for writing ref-qualified member function
// - when writing member function templates where the type of the explicit
//      object parameter is a template type parameter.
// - write recursive lambda expressions.
// void SpreadsheetCell::setValue(this SpreadsheetCell& self, double value)
// {
//     self.value_ = value;
//     printCell(self);
// }

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



int main()
{

    println("-- creating objects on the stack");

    SpreadsheetCell myCell, anotherCell;
    myCell.setValue(6);
    anotherCell.setString("3.2");

    println("cell 1: {}", myCell.getValue());
    println("cell 2: {}", anotherCell.getValue());

    println("-- creating objects on the free store");

    SpreadsheetCell* myCellp { new SpreadsheetCell { } };
    (*myCellp).setValue(3.7);

    println("cell 1: {} {}", myCellp->getValue(), myCellp->getString());

    delete myCellp; myCellp = nullptr;

    // for safety and to avoid memory problems, you should smart pointers
    println("-- creating objects on the free store using smart pointers");

    auto myCellSmartp { std::make_unique<SpreadsheetCell>() };
    myCellSmartp->setValue(3.7);
    println("cell 1: {} {}", myCellSmartp->getValue(), myCellSmartp->getString());

}

void printCell(const SpreadsheetCell& cell)
{
    println("{}", cell.getString());
}