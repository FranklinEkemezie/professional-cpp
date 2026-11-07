#include <charconv>
#include <memory>
#include <optional>
#include <print>
#include <string>
#include <vector>

// => refactored to specialised class

/** Spreadsheet Cell */
class SpreadsheetCell
{
    public:
        virtual ~SpreadsheetCell() = default;
        
        // virtual void set(double value);
        virtual void set(std::string_view value) = 0;
        virtual std::string getString() const = 0;

    private:
        // static std::string doubleToString(double value);
        // static double stringToDouble(std::string_view value);

    private:
        // double value_;
};

class DoubleSpreadsheetCell; // forward declare class here

/** StringSpreadsheetCell class */
class StringSpreadsheetCell : public SpreadsheetCell
{
    public:

        StringSpreadsheetCell() = default; // explicitly default constructor since we have defined one
        StringSpreadsheetCell(const DoubleSpreadsheetCell& cell); // converting (or typed) constructor allows us to convert between sibling classes.

        void set(std::string_view value) override;
        std::string getString() const override;

    private:
        std::optional<std::string> value_ { };
};

/** DoubleSpreadsheetCell class */
class DoubleSpreadsheetCell : public SpreadsheetCell
{
    public:
        virtual void set(double value);
        virtual double getValue() const;

        void set(std::string_view value) override;
        std::string getString() const override;

    private:
        static std::string doubleToString(double value);
        static double stringToDouble(std::string_view value);
        std::optional<double> value_;
};


// `StringSpreadsheetCell` implementation

StringSpreadsheetCell::StringSpreadsheetCell(const DoubleSpreadsheetCell& cell) : value_ { cell.getString() } { }
void StringSpreadsheetCell::set(std::string_view value) { value_ = value; }
std::string StringSpreadsheetCell::getString() const { return value_.value_or(""); }

StringSpreadsheetCell operator+(
    const StringSpreadsheetCell& lhs,
    const StringSpreadsheetCell& rhs
)
{
    StringSpreadsheetCell newCell;
    newCell.set(lhs.getString() + rhs.getString());
    return newCell;
}

// `DoubleSpreadsheetCell` implementation

void DoubleSpreadsheetCell::set(double value) { value_ = value; }
double DoubleSpreadsheetCell::getValue() const { return value_.value_or(0); }

void DoubleSpreadsheetCell::set(std::string_view value) { value_ = stringToDouble(value); }
std::string DoubleSpreadsheetCell::getString() const { return value_.has_value() ? doubleToString(value_.value()) : ""; }

std::string DoubleSpreadsheetCell::doubleToString(double value) { return std::to_string(value); }

double DoubleSpreadsheetCell::stringToDouble(std::string_view value)
{
    double number { 0 };
    std::from_chars(value.data(), value.data() + value.size(), number);
    return number;
}

DoubleSpreadsheetCell operator+(
    const DoubleSpreadsheetCell& lhs,
    const DoubleSpreadsheetCell& rhs
)
{
    DoubleSpreadsheetCell newCell;
    newCell.set(lhs.getValue() + rhs.getValue());
    return newCell;
}


// -- Providing implementations for pure virtual member functions

class Base
{
    public:
        virtual void doSomething() = 0;
};

// Implementation for a pure virtual member function must be outside of the class definition
// The class still remains abstract; cannot be instantiated.
void Base::doSomething() { std::println("Base::doSomething()"); }

class Derived : public Base
{
    public:
        void doSomething() override
        {
            // You can call still pure virtual member function in a derived class.
            Base::doSomething();
            std::println("Derived::doSomething()");
        }
};

int main()
{

    std::println("--- Inheritance for Polymorphism");

    // SpreadsheetCell cell; // Error! Attempt to create abstract class instance

    std::println("-- Leveraging polymorphism");

    // While you can't create concrete `SpreadsheetCell` object, you can have a
    // collection of objects that extend the `Spreadsheet` class
    std::vector<std::unique_ptr<SpreadsheetCell>> cellArray { };

    cellArray.push_back(std::make_unique<StringSpreadsheetCell>());
    cellArray.push_back(std::make_unique<StringSpreadsheetCell>());
    cellArray.push_back(std::make_unique<DoubleSpreadsheetCell>());

    // We can treat the different spreadsheet cells uniformly
    // Each one implements it in their own way
    cellArray[0]->set("hello");
    cellArray[1]->set("10");
    cellArray[2]->set("18");

    std::println("Vector: [{}, {}, {}]",
        cellArray[0]->getString(),
        cellArray[1]->getString(),
        cellArray[2]->getString());

    
    std::println("-- Converting across the hierarchy");

    DoubleSpreadsheetCell cell1;
    cell1.set("23");
    std::println("cell1: {}", cell1.getValue());

    StringSpreadsheetCell cell2 { cell1 }; // create "string" spreadsheet cell from "double"
    std::println("cell2: {}", cell2.getString());

    // Another way to cast across the hierarchy is by changing the behaviour of 
    // the cast operator or by using `reinterpret_cast()`

    std::println("-- Overloading operators");

    DoubleSpreadsheetCell doubleCell;
    doubleCell.set(8.4);

    DoubleSpreadsheetCell result { doubleCell + doubleCell };
    std::println("{}", result.getString());

    DoubleSpreadsheetCell stringCell;
    stringCell.set("Hello ");

    StringSpreadsheetCell result1 { stringCell + doubleCell };
    std::println("{}", result1.getString());

    std::println("-- Providing implementations for pure virtual member functions");

    Derived derived;
    Base& base { derived };
    base.doSomething();


}