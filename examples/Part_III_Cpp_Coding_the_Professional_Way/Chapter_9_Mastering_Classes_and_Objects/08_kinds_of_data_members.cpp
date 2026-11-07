#include <charconv>
#include <print>
#include <string>
#include <utility>
#include <vector>


/** Spreadsheet Cell */
class SpreadsheetCell
{

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

    private:
        static std::string doubleToString(double value);
        static double stringToDouble(std::string_view value);

    private:
        double value_ { 0 };
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


class SpreadsheetApplication { };

/** Spreadsheet */
class Spreadsheet
{
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


    private:
        bool inRange(std::size_t value, std::size_t upper) const;
        void verifyCoordinate(std::size_t x, std::size_t y) const;

    public:
        // Use `static constexpr` for class-level class constants
        static constexpr std::size_t MaxHeight  { 100 };
        static constexpr std::size_t MaxWidth   { 100 };

    private:
        // `const` or `constexpr` data member cannot be changed after they are
        // created (and initialised). Like other constants, they must be initialised
        // as they are declared and this is typically done in the constructor.
        const std::size_t id_ { 0 }; // prevent copying ID, instead make a new one
        std::size_t width_  { 0 };
        std::size_t height_ { 0 };
        SpreadsheetCell** cells_ { nullptr };
        const SpreadsheetApplication& theApp_;

        // Can't use in-class initialiser. You have to allocate space
        // for them by declaring them in a source. You can initialise
        // them at the same time, though they are zero-initialsed by
        // default. Access control specifiers apply too.
        // You can also declare your static data members as `inline`,
        // in which case you initialise them in-class, thus eliminating
        // the need to allocate space and/or initialise them in the 
        // source file.
        inline static std::size_t counter_;

};

// Static data members are zero-initialised by default.
// You can explicitly initialise them.
// std::size_t Spreadsheet::counter_ { 0 }; // `inline` declares them in class, you can't "redeclare" again here

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;

Spreadsheet::Spreadsheet(
    const SpreadsheetApplication& theApp, 
    std::size_t width, 
    std::size_t height
) : 
    id_ { counter_++ }, // use `static` data member like normal data member
    width_ { std::min(width, MaxWidth) }, 
    height_ { std::min(height, MaxHeight) },
    theApp_ { theApp }
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
    : Spreadsheet { src.theApp_, src.width_, src.height_ }
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
    std::swap(cells_,   other.cells_);}

void swap(Spreadsheet& first, Spreadsheet& second) noexcept
{
    first.swap(second);
}

Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
    : theApp_ { std::move(src.theApp_) }
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

int main()
{

    std::println("--- Different Kinds of Data Members");
    std::println();

    std::println("-- `static` Data Members");
    // Like static member functions, by marking a data member as `static`,
    // you can make a data member apply to to the class as a whole instead 
    // of each object instance. For example, the `Spreadsheet` class use a
    // static data member to keep a class-level counter.

    std::println("-- `constexpr` `static` Data Members");
    // When constants apply only the class, you can make them class constants
    // by declaring them `static` as well as `constexpr`

    std::println("Maximum height is: {}", Spreadsheet::MaxHeight);

    std::println("-- Reference Data Members");
    // Data members can also be references. In that case, the reference must
    // be initialised in ctor initiliaser list as references must always refer
    // to something. You can also mark them `const` to obtain reference-to-`const`
    // data members and whatever they refer to cannot be changed after initialisation.
    // The `Spreadsheet` class is updated to store a reference to the spreadsheet
    // application in which it is created.


}