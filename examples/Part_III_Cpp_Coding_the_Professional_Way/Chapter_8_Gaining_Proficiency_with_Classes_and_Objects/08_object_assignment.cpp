#include <charconv>
#include <print>
#include <string_view>

class SpreadsheetCell
{

    public:
        SpreadsheetCell() = default;
        SpreadsheetCell(double initialValue);

        explicit SpreadsheetCell(std::string_view initialValue);
        SpreadsheetCell(const SpreadsheetCell& src) = default;

        // Like "copy constructor", the assignment (also called "copy assignment") operator
        // takes reference-to-const of the object we want to assign to the current object, 
        // but it returns a reference allowing assignment chaining. Technically, you can 
        // return any type or any value, but you would typically return a reference to the object on
        // which it is called which is what clients would expect. 
        // If you don't declare one, the compiler generates one which does simple
        // member-wise assignment of all data members. The compiler does not generate
        // a copy assignment operator if there's a user-declared copy constructor or destructor.
        // Vice versa, it does not generate a copy constructor if you declare a copy assignment operator.
        SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
        // SpreadsheetCell& operator=(const SpreadsheetCell& rhs) = delete; // prevent assignment

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

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
    if (this == &rhs) // handle self-assignment
    {
        return *this;   // just return
    }

    // We do simple assignment of data members which is what the
    // compiler would do if we didn't specify one

    value_ = rhs.value_;

    std::println("done assigning...");

    return *this;
}

int main()
{

    SpreadsheetCell myCell { 5 }, anotherCell;

    // not copying, but assignment; 
    // calls assignment operator on `anotherCell` with `myCell` as argument.
    anotherCell = myCell;   

    SpreadsheetCell aThirdCell { anotherCell }; // construction; calls copy constructor

    // `getString()` creates a temporary `string` object by calling the `string` copy constructor
    // Now, we use it to initialise `s` which also copies it.
    // You can use the "move constructor" or "move assignment operator" to move
    // the string from `getString()` preventing unnecessary copy. (See Chapter 9)
    // Thankfully the compilers can (and are sometimes required to) to implement
    // copy elision to prevent costly copy or move operations when returning values.
    std::string s { aThirdCell.getString() }; 

    std::println("s: {}", s);

    // Lastly, use constructor initialiser to construct objects in constructor
    // which calls the copy constructor instead of assigning them in the body
    // of the constructor which calls the assignment operator

}