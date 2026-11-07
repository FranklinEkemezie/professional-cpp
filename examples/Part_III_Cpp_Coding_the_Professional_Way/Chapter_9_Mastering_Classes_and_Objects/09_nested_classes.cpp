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

        explicit SpreadsheetCell(std::string_view initialValue);
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

    std::println("--- Nested Classes");
    // Class defintions can contain nested classes, structs, type alias, and
    // enumerations. These also obey the access control semantics like
    // data members and member functions. As an example, instead of having a
    // separate `SpreadsheetCell` class, we can nest it in a `Cell` class 
    // in the `Spreadsheet` class.

    Spreadsheet::Cell cell1 { 34 };
    std::println("Spreadsheet::Cell cell1 = {}", cell1.getValue());

    const SpreadsheetApplication app { };
    Spreadsheet s1 { app };
    s1.setCellAt(10, 10, 100);

    auto cell2 { s1.getMyCellAt(10, 10) };

    std::println("Spreadsheet::MyCell cell2 = {}", cell2.getValue());

    std::println("--- Enumerations inside Classes");
    // You can also have enumeration inside classes

    SpreadsheetCell myCell { 5 };
    std::println("myCell colour: {}", static_cast<unsigned int>(myCell.getColor()));

    myCell.setColor(SpreadsheetCell::Color::Green);
    auto color { myCell.getColor() };
    std::println("myCell colour: {}", static_cast<unsigned int>(color));


}