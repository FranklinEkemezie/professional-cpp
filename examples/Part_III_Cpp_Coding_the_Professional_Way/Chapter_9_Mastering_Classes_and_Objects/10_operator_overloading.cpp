#include <charconv>
#include <print>
#include <string>
#include <utility>
#include <vector>


/** Spreadsheet Cell */
class SpreadsheetCell
{

    public:
        enum class Color { Red = 1, Green, Blue, Yellow };

    public:

        SpreadsheetCell() = default;
        SpreadsheetCell(double initialValue);

        SpreadsheetCell(std::string_view initialValue);
        SpreadsheetCell(const SpreadsheetCell& src) = default;

        void setValue(double value);
        void setValue(int) = delete;
        inline double getValue() const;

        void set(double value);
        void set(std::string_view value);

        void setString(std::string_view value);
        inline std::string getString() const;

        void setColor(Color color);
        Color getColor() const;

        SpreadsheetCell add(const SpreadsheetCell& cell) const;

        // Operator overloading
        // SpreadsheetCell operator+(const SpreadsheetCell& cell) const;
        SpreadsheetCell operator+(double rhs) const;
        SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
        SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);

        // Comparison operator overloading since C++20
        [[nodiscard]] std::partial_ordering operator<=>(const SpreadsheetCell& rhs) const;
        [[nodiscard]] bool operator==(double rhs) const;
        [[nodiscard]] std::partial_ordering operator<=>(double rhs) const;
        // You can explicitly default the `operator<=>` and the compiler generates
        // one for you along with `operator==` overload. The compiler generated version
        // as you may have guessed performs member-wise lexicographical comparison (which
        // is what we need in our case). If you specify a comparison operator overload
        // after defaulting the `operator<=>` the compiler will not generate the
        // `operator==` for you and you will need to default it separately.
        // Also, if any member does not support `operator<=>`, it falls back to the
        // `operator<` and `operator==` in which case return type deduction won't work
        // and you need to specify the return type as one of `strong_ordering`,
        // `partial_ordering` or `weak_ordering`. If it also does not support the 
        // fallback `operator<` and `operator==`, then the default `operator<=>` is 
        // implicitly deleted. You can mark the return type as `auto` to let the 
        // compiler deduce the appropriate return type.
        // [[nodiscard]] auto operator<=>(const SpreadsheetCell& rhs) const = default;

    private:
        static std::string doubleToString(double value);
        static double stringToDouble(std::string_view value);


    private:
        double value_ { 0 };
        Color colour_ { Color::Blue };

        mutable unsigned nAccess_ { 0 };
};

SpreadsheetCell::SpreadsheetCell(double initialValue) 
    : value_ { initialValue }
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
    nAccess_++;
    return value_;
}

void SpreadsheetCell::setString(std::string_view value)
{
    value_ = stringToDouble(value);
}

std::string SpreadsheetCell::getString() const
{
    nAccess_++;
    return doubleToString(value_);
}

void SpreadsheetCell::set(double value) { setValue(value); }
void SpreadsheetCell::set(std::string_view value) { setString(value); }

std::string SpreadsheetCell::doubleToString(double value)
{
    return std::to_string(value);
}

double SpreadsheetCell::stringToDouble(std::string_view value)
{
    double number { 0 };
    std::from_chars(value.data(), value.data() + value.size(), number);
    return number;
}

void SpreadsheetCell::setColor(Color color) { colour_ = color; }
SpreadsheetCell::Color SpreadsheetCell::getColor() const { return colour_; }



// Operator overloading implementations

// First attempt
SpreadsheetCell SpreadsheetCell::add(const SpreadsheetCell& cell) const
{
    return SpreadsheetCell { getValue() + cell.getValue() };
}

// Having both overload member function would result in ambiguous definition.
// The compiler does not know which overload to call.
// SpreadsheetCell SpreadsheetCell::operator+(const SpreadsheetCell& cell) const
// {
//     return SpreadsheetCell { getValue() + cell.getValue() };
// }

SpreadsheetCell SpreadsheetCell::operator+(double rhs) const
{
    return SpreadsheetCell { getValue() + rhs };
}

// Global operator+
SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return SpreadsheetCell { lhs.getValue() + rhs.getValue() };
}

SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell &rhs)
{
    if (rhs.getValue() == 0)
    {
        throw std::invalid_argument { "Divide by zero." };
    }

    return SpreadsheetCell { lhs.getValue() / rhs.getValue() };
}

SpreadsheetCell& SpreadsheetCell::operator+=(const SpreadsheetCell& rhs)
{
    set(getValue() + rhs.getValue());
    return *this;
}

SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    // You can now implement the basic operator- in terms of the shorthand operator:
    return SpreadsheetCell { lhs.getValue() } -= rhs;
}

SpreadsheetCell& SpreadsheetCell::operator-=(const SpreadsheetCell& rhs)
{
    set(getValue() - rhs.getValue());
    return *this;
}

bool operator==(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    // Not a good idea to perform (in)equality on floating-point values
    // directly; you can use the epsilon test. But, ok! whatever, anyhoo:
    return (lhs.getValue() == rhs.getValue());
}

bool operator<(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return lhs.getValue() < rhs.getValue();
}

bool operator>(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return rhs < lhs;
}

bool operator>=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return ! (lhs < rhs);
}

std::partial_ordering SpreadsheetCell::operator<=>(const SpreadsheetCell& rhs) const
{
    return getValue() <=> rhs.getValue();
}

bool SpreadsheetCell::operator==(double rhs) const { return getValue() == rhs; }
std::partial_ordering SpreadsheetCell::operator<=>(double rhs) const { return getValue() <=> rhs; }


class SpreadsheetApplication { };

/** Spreadsheet */
class Spreadsheet
{

    public:
        // You can forward declare to prevent bloated code:
        class MyCell;

        // Or define the whole class
        class Cell
        {
            public:
                Cell() = default;
                Cell(double initialValue);

                double getValue() const;

            private:
                double value_ { };
        };

    public:

        explicit Spreadsheet(
            const SpreadsheetApplication& theApp,
            std::size_t width = MaxWidth, 
            std::size_t height = MaxHeight
        );
        ~Spreadsheet();

        Spreadsheet(const Spreadsheet& src);
        Spreadsheet& operator=(const Spreadsheet& rhs);
        
        std::size_t getId() const;

        void swap(Spreadsheet& other) noexcept;

        Spreadsheet(Spreadsheet&& src) noexcept;
        Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;

        void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell);
        SpreadsheetCell& getCellAt(std::size_t x, std::size_t y);
        const SpreadsheetCell& getCellAt(std::size_t x, std::size_t y) const;

        const Spreadsheet::MyCell getMyCellAt(std::size_t x, std::size_t y) const;


    private:
        bool inRange(std::size_t value, std::size_t upper) const;
        void verifyCoordinate(std::size_t x, std::size_t y) const;

    public:
        static constexpr std::size_t MaxHeight  { 100 };
        static constexpr std::size_t MaxWidth   { 100 };

    private:
        const std::size_t id_ { 0 }; // prevent copying ID, instead make a new one
        std::size_t width_  { 0 };
        std::size_t height_ { 0 };
        SpreadsheetCell** cells_ { nullptr };
        const SpreadsheetApplication& theApp;

        inline static std::size_t counter_;

};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;

Spreadsheet::Spreadsheet(
    const SpreadsheetApplication& theApp,
    std::size_t width, 
    std::size_t height
) : 
    id_     { counter_++ },
    width_  { std::min(width,   MaxWidth)   }, 
    height_ { std::min(height,  MaxHeight)  },
    theApp  { theApp }
{
    cells_ = new SpreadsheetCell *[width_];
    for (std::size_t i { 0 }; i < width_; i++)
    {
        cells_[i] = new SpreadsheetCell[height_];
    }
}

Spreadsheet::~Spreadsheet()
{
    for (std::size_t i { 0 }; i < width_; delete[] cells_[i], i++);
    delete[] cells_; cells_ = nullptr;
}

Spreadsheet::Spreadsheet(const Spreadsheet& src)
    : Spreadsheet { src.theApp, src.width_, src.height_ }
{
    for (std::size_t i { 0 }; i < width_; i++)
    {
        for (std::size_t j { 0 }; j < height_; j++)
        {
            cells_[i][j] = src.cells_[i][j];
        }
    }
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
    Spreadsheet temp { rhs };
    swap(temp);

    return *this;
}

void Spreadsheet::swap(Spreadsheet& other) noexcept
{
    std::swap(width_,   other.width_);
    std::swap(height_,  other.height_);
    std::swap(cells_,   other.cells_);
}

void swap(Spreadsheet& first, Spreadsheet& second) noexcept
{
    first.swap(second);
}

Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
    : theApp { std::move(src.theApp) }
{
    swap(src);
}

Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept
{
    auto moved { std::move(rhs) };
    swap(moved);
    
    return *this;
}
bool Spreadsheet::inRange(std::size_t value, std::size_t upper) const
{
    return value < upper;
}

void Spreadsheet::verifyCoordinate(std::size_t x, std::size_t y) const
{
    if (! inRange(x, width_))
    {
        throw std::out_of_range {
            std::format("x ({}) must be less than width ({}).", x, width_)
        };
    }

    if (! inRange(y, height_))
    {
        throw std::out_of_range {
            std::format("y ({}) must be less than height ({}).", y, height_)
        };
    }
}

void Spreadsheet::setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell)
{
    verifyCoordinate(x, y);
    cells_[x][y] = cell;
}

SpreadsheetCell& Spreadsheet::getCellAt(std::size_t x, std::size_t y)
{
    return const_cast<SpreadsheetCell&>(std::as_const(*this).getCellAt(x, y));
}

const SpreadsheetCell& Spreadsheet::getCellAt(std::size_t x, std::size_t y) const
{
    verifyCoordinate(x, y);
    return cells_[x][y];
}

// Get to the correct inner score: `Spreadsheet::Cell::Cell`
Spreadsheet::Cell::Cell(double initialValue) : value_ { initialValue } { }

double Spreadsheet::Cell::getValue() const { return value_; }

// Define the `Cell` separately for the forward declaration
class Spreadsheet::MyCell
{

    public:
        MyCell() = default;
        MyCell(double initialValue): value_ { initialValue } { }
        
        double getValue() const { return value_; }

    private:
        double value_ { 0 };
    
};

// Specify fully qualified name in return type, but not in parameter (as always)
const Spreadsheet::MyCell Spreadsheet::getMyCellAt(std::size_t x, std::size_t y) const
{
    return Spreadsheet::MyCell { getCellAt(x, y).getValue() };
}

// Helper function
void printCell(std::string_view label, const SpreadsheetCell& cell)
{
    std::println("{}: {}", label, cell.getValue());
}

int main()
{

    std::println("--- Operator Overloading");

    std::println("-- Implementing Addition for Spreadsheet Cells");

    std::println("- Using `add()` member function");

    SpreadsheetCell myCell { 4 }, anotherCell { 5 };

    printCell("myCell", myCell);
    printCell("anotherCell", anotherCell);

    SpreadsheetCell aThirdCell { myCell.add(anotherCell) };
    printCell("thirdCell", aThirdCell);

    auto aFourthCell { aThirdCell.add(anotherCell) };
    printCell("fourthCell", aFourthCell);

    std::println("- Overloaded operator+ as member function");

    SpreadsheetCell myCell3 { myCell + anotherCell };
    printCell("myCell3", myCell3);

    auto myCell4 { aThirdCell + anotherCell };
    printCell("myCell4", aFourthCell);

    std::println("- Implicit Conversions");

    std::string str { "hello" };

    // If the constructor accepting string view allow implicit conversion
    // the compiler can use to create a temporary object and perform the operation.
    // To prevent implicit construction (as it can be inefficient due to the
    // creation of the temporary object), you can mark the class as `explicit`
    // or define an overload for the operator
    aThirdCell = myCell + std::string_view { str }; printCell("thirdCell", aThirdCell);
    aThirdCell = myCell + 5.6;  printCell("thirdCell", aThirdCell); // uses "double" operator+ overload
    aThirdCell = myCell + 4;    printCell("thirdCell", aThirdCell);

    std::println("- Global operator+");
    // When the operator is overloaded in the class definition, it is only
    // called when the left operand is the object of the class type. To make
    // it work for any operand, we can define a global one. The compiler finds
    // the operator overload (applying implicit conversion if possible) and uses
    // it to evaluate the operation.

    aThirdCell = myCell + 5.6;  printCell("thirdCell", aThirdCell);
    aThirdCell = myCell + 4;    printCell("thirdCell", aThirdCell);
    aThirdCell = 5.6 + myCell;  printCell("thirdCell", aThirdCell);
    aThirdCell = 4 + myCell;    printCell("thirdCell", aThirdCell);
    // The example below works but does not invoke the operator+ overload.
    // Since none of them a `SpreadsheetCell` object, it performs normal
    // double addition and the result is then assigned to `aThirdCell`. The
    // assignment works if the copy assignment allows implicit conversion.
    aThirdCell = 4.5 + 5.5;     printCell("thirdCell", aThirdCell);

    std::println("-- Overloading Arithmetic Operators");
    // Overloading other arithmetic operators is similar to the operator+
    // addition. You can do whatever you want in those operator implementation
    // and can return whatever you want, but it is recommended and best to
    // do what is expected for the operator and return what clients would
    // expect

    aThirdCell = myCell / 2; printCell("thirdCell", aThirdCell);

    std::println("-- Overloading Arithmetic Shorthand Operators");
    // These operators include +=, -= etc. Unlike the basic arithmetic operators,
    // they actually modify the left hand side operand, and return a reference to
    // the modified object (or at least this is what most people would expect the
    // operators to do). To avoid code duplication when you have a normal and 
    // shorthand version of an operator, you should implement the normal one in terms
    // of the shorthand version. They should be implemented as member functions, and not
    // global functions to prevent weird usages.

    aThirdCell -= myCell;   printCell("thirdCell", aThirdCell);
    aThirdCell += 5.4;      printCell("thirdCell", aThirdCell);
    // 5.4 += aThirdCell;      // you can't do this weird thing since += is defined as member function

    std::println("-- Overloading Comparison Operators");
    // These should be global functions like the basic arithmetic operators.
    // Once you have implemented the == and < overloads, you can implement other
    // comparison operators in terms of those two. For ex:
    // x >= y is same as ! (x < y)

    if (myCell > aThirdCell || myCell < 10) printCell("myCell", myCell);
    std::println("fourthCell >= fourthCell: {}", aFourthCell >= aFourthCell);

    // Before C++20, you had to implement the six separate functions to support
    // the six comparison operators. You would need 6 more to support comparison
    // between the type and another type to avoid the inefficient implicit
    // conversion. With the introduction of the spaceship operator in C++20, you
    // only need to implement an overload for `operator=` and `<=>` and the
    // compiler will provide support for all six comparison operators by rewriting
    // their usage in terms of `<=>`. For ex: x < y is automatically rewritten to
    // something equivalent to `std::is_lt(x < y)`

    std::println("myCell != thirdCell: {}", myCell != aThirdCell);
    std::println("10 == myCell: {}", 10 <= myCell);








}