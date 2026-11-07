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

int main()
{

    std::println("--- Building Stable Interfaces");
    // Stable interfaces do not require clients using the interface class to
    // recompiler when they make changes which are not visible to them e.g.
    // adding a new non-`public` member functions or data members. They also
    // significantly reduce compile times.

    std::println("-- Private implementation (pimpl) idiom");
    // One way to achieve this is using the private implementation (or "pimpl")
    // idiom, also known as the bridge pattern. The basic idea is to define two
    // classes for every class you want to write: the interface class which the
    // the clients can use and the implementation class which is the class in
    // which you have the implementation (the same implementation if you didn't
    // follow this pattern) and it stays hidden from the user. The interface class
    // contains a pointer to the implementation and forwards calls to it the
    // hidden implementation file, thus acting as a bridge between the implementation
    // and the client. The interface remains the same as the implementation changes.

    std::println("-- Using abstract interface");
    // Another way to do this is by using an abstract interface i.e. an interface
    // with only pure virtual member functions and then an implementation class that
    // implements that interface. This is discussed in the next chapter.

}