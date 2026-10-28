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

        // Copy constructor
        SpreadsheetCell(const SpreadsheetCell& src);
        // SpreadsheetCell(const SpreadsheetCell& src) = default;   // Tell the compiler to generate a default copy constructor which copies the data members
        // SpreadsheetCell(const SpreadsheetCell& src) = delete;    // Delete the copy constructor, meaning the object cannot be copied

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

// SpreadsheetCell::SpreadsheetCell() // no define a default constructor if it's explicitly defaulted
// {
//     // the statement below is already done in the in-class initialiser
//     // so can be left out, leaving the default constructor empty.
//     value_ = 0; 
// }

SpreadsheetCell::SpreadsheetCell(double initialValue) 
    : value_ { initialValue } // ctor or constructor initialiser
{

}

SpreadsheetCell::SpreadsheetCell(std::string_view initialValue)
{
    setString(initialValue);
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

// Typically, in a copy constructor, you initialise the data member
// of the copy constructor to be the same as the object being copied from
// C++ generates a default constructor that is used if you do not specify one
// So, our constructor is just for demonstration as it is no different from the 
// default compiler-generated one
SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src)
    : value_ { src.value_ }
{
    std::println("SpreadsheetCell ({}) copy constructor called!", src.getValue());
}

// In C++, the default semantics for passing arguments is pass-by value.
// This means, the function below receives a copy of the `std::string` object
// passed. To do this, the compiler calls the copy constructor.
void printString(std::string value)
{
    std::println("{}", value);
}

void printCellValue(SpreadsheetCell cell)
{
    std::println("Cell => [{}]", cell.getString());
}

void printCellRefValue(SpreadsheetCell& cell)
{
    std::println("Cell => [{}]", cell.getString());
}

// --- Initialiser-List constructors

class EvenSequence
{

    public:

        // Constructor accept an initialiser list followed by no other arguments
        // or by arguments with default values
        EvenSequence(std::initializer_list<double> values)
        {
            if (values.size() % 2 != 0)
            {
                throw std::invalid_argument { "initializer_list should"
                    " contain even number of elements." };
            }

            // sequence_.reserve(values.size());
            // for (const auto& value : values)
            // {
            //     sequence_.push_back(value);
            // }
            // The above lines (creating enough space to prevent frequent reallocation, and copying)
            // can all be done in one line
            sequence_.assign(values);
        }

        void print() const
        {
            for (const auto& value : sequence_)
            {
                std::print("{}, ", value);
            }
            std::println("");
        }

    private:
        std::vector<double> sequence_;
};

int main()
{

    SpreadsheetCell myCell { 4 };
    SpreadsheetCell myCell2 { myCell }; // triggers the copy constructor to copy `myCell` into `myCell2`
    printCellValue(myCell); // passing by value triggers copy

    // Recommended: prevent copying by accepting reference (use `const` to prevent modification)
    // For primitive types, you can pass by value.
    printCellRefValue(myCell);    


    // Using classes with initialiser list constructor
    try
    {

        EvenSequence p1 { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
        p1.print();

        EvenSequence p2 { 1.0, 2.0, 3.0 };
    }
    catch (const std::invalid_argument& e)
    {
        std::println("{}", e.what());
    }

    // The Standard Library also uses initialiser list constructors. For ex:
    std::vector<std::string> myVec { "String 1", "String 2", "String 3" };
    std::println("{}", myVec);
    // However, initialiser list must not be confused with constructos with single arguments
    // Use parentheses for the constructor arguments and braces for initialiser list
    std::vector<int> v1 { 6 };  // vector with a single element, 6.
    std::vector<int> v2 (6);    // vector with 6 default-initialised `int` elements

    std::println("{}", v1);
    std::println("{}", v2);


}