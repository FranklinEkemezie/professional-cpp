#include <charconv>
#include <print>
#include <string_view>

class SpreadsheetCell
{

    public:
        SpreadsheetCell() = default;
        SpreadsheetCell(double initialValue);

        // Objects on the stack are destroyed when the go out of scope.
        // They are destroyed in the order of their declaration.
        // If you don't declare one, the compiler generates one that recursively
        // destrroys data members.
        ~SpreadsheetCell();

        explicit SpreadsheetCell(std::string_view initialValue);
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

SpreadsheetCell::~SpreadsheetCell()
{
    std::println("Destructor called.");
}

int main()
{
    SpreadsheetCell myCell { 5 };
    if (myCell.getValue() == 5)
    {
        SpreadsheetCell anotherCell { 6 };
    } // destructor is called for `anotherCell` here

    std::println("myCell: {}", myCell.getValue());

    // Remember objects on the free store are not destroyed automatically
    // you must free them yourself. Avoid code such as the one which does not free
    // memory below or use smart pointers which automatically cleanup memory

    SpreadsheetCell* cellPtr1 { new SpreadsheetCell { 5 } };
    SpreadsheetCell* cellPtr2 { new SpreadsheetCell { 6 } };

    std::println("cellPtr1: {}", cellPtr1->getValue());
    delete cellPtr1; cellPtr1 = nullptr;    // destroys `cellPtr1`, `delete` calls destructor (`free()` does not!)

    std::println("cellPtr2: {}", cellPtr2->getValue());

} // `cellPtr2` is NOT destroyed because `delete` was not called on it. Memory leak!!!