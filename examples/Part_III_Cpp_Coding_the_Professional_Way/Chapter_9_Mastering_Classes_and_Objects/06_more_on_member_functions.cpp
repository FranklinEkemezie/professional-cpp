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
        // You can mark member functions `static` when they apply to the class
        // as a whole and not to each object. `static` member functions cannot
        // be marked `const` as they do not have access to any object data member
        // to modify. `static` member functions have access to private data of
        // the class that would not have been available if they were defined as
        // stand-alone functions.
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
    nAccess_++; // OK! to modify `mutable` data member in `const` member function
    return value_;
}

void SpreadsheetCell::setString(std::string_view value)
{
    value_ = stringToDouble(value);
}

std::string SpreadsheetCell::getString() const
{
    nAccess_++; // OK! to modify `mutable` data member in `const` member function
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


/** Spreadsheet */
class Spreadsheet
{
    public:
        // constructor with default arguments. This constructor can also function as
        // a default constructor as it has defaults for all its parameters.
        explicit Spreadsheet(std::size_t width = 100, std::size_t height = 100);
        ~Spreadsheet();

        Spreadsheet(const Spreadsheet& src);
        Spreadsheet& operator=(const Spreadsheet& rhs);
        
        void swap(Spreadsheet& other) noexcept;

        Spreadsheet(Spreadsheet&& src) noexcept;
        Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;

        void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell);
        SpreadsheetCell& getCellAt(std::size_t x, std::size_t y);
        const SpreadsheetCell& getCellAt(std::size_t x, std::size_t y) const; // return reference-to-`const` for `const` objects


    private:
        bool inRange(std::size_t value, std::size_t upper) const;
        void verifyCoordinate(std::size_t x, std::size_t y) const;

    private:
        std::size_t width_  { 0 };
        std::size_t height_ { 0 };
        SpreadsheetCell** cells_ { nullptr };
};


void swap(Spreadsheet& first, Spreadsheet& second) noexcept;

Spreadsheet::Spreadsheet(std::size_t width, std::size_t height)
    : width_ { width }, height_ { height }
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
    : Spreadsheet { src.width_, src.height_ }
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
    // Scott Meyer's `const_cast` pattern
    return const_cast<SpreadsheetCell&>(std::as_const(*this).getCellAt(x, y));
}

const SpreadsheetCell& Spreadsheet::getCellAt(std::size_t x, std::size_t y) const
{
    verifyCoordinate(x, y);
    return cells_[x][y];
}


//

class TextHolder
{
    public:
        explicit TextHolder(std::string text) : text_ { std::move(text) }  { }
        const std::string& getText() const & { return text_; }
        std::string&& getText() && 
        { 
            // for temporary objects, move `text_` data member out.
            // `text_` is going to be invalid, but it's ok since the
            // temporary cannot access it again after this call
            return std::move(text_); 
        }

        TextHolder& operator=(const std::string& rhs) &
        { 
            // Only non-temporary objects can a string be assigned
            text_ = rhs; 
            return *this; 
        }
    
    private:
        std::string text_;
};

TextHolder makeTextHolder() { return TextHolder { "Hello World!" }; }

int main()
{

    std::println("--- More About Member Functions");

    std::println("-- `const` Member functions");
    // Marking a member function as `const` guarantees it won't change
    // data members. You can call `const` and non-`const` member functions
    // on a non-`const` object but you can only `const` member functions on
    // a `const` object (which makes sense; calling non-`const` member functions
    // on a `const` object would make the object and its data non-constant)

    SpreadsheetCell myCell { 5 };
    std::println("myCell: {}", myCell.getValue());  // OK
    myCell.setString("6");
    std::println("myCell: {}", myCell.getValue());  // OK

    const SpreadsheetCell& myCellConstRef { myCell };
    std::println("myCellConstRef: {}", myCellConstRef.getValue());  // OK
    // myCellConstRef.setString("6");  // Compilation Error!

    std::println("-- `mutable` Data Members");
    // You can mark a data member as `mutable` to indicate that it is okay
    // to change it in a `const` function. This is common when the data member
    // represents or keeps track of internal data that is not visible to the user.
    // For example, if we had a data member to track how many times a spreadsheet
    // cell has been accessed, we can mark it as `mutable` and modify this counter
    // in `const` member functions like `getString()` and `getValue()`.

    std::println("myCellConstRef: {}", myCellConstRef.getValue());  // mutates internal counter, but still `const`

    std::println("-- Member Function Overloading");
    // We have seen multiple overload for constructors. We can also overload member
    // functions like we overload (non-member) standalone functions. As usual these
    // overload have the same name but with different number and/or types of the parameters.

    myCell.set(12); // "double" overload
    std::println("myCell: {}", myCell.getValue());
    myCell.set("42.34"); // "string" overload
    std::println("myCell: {}", myCell.getValue());

    std::println("- Overloading Based on const");
    // You can also overload based on `const`: two member function with the same
    // name and parameters with one declared `const` and the other is not. The
    // compiler calls the `const` version when you have a `const` object and the other 
    // on a non-`const` object. To prevent code duplication when implementing both
    // overloads (as they're usually identical), you can use:
    // - Scott Meyers' `const_cast()` pattern - where you have the actual implementation
    // in the `const` overload and the non-`const` reuses it by forwarding the call with
    // appropriate casts. One `as_const()` (defined in <utility>) is used to make `this` 
    // a `const` object so that the compiler calls the `const` overload and another 
    // `const_cast()` is used to strip away the `const`-ness from the result
    // - Private helper member function - where you put the common implementation in 
    // a `private const` helper member function but with a non-`const` return type and both
    // of them forward the calls to this helper member function. 
    // The latter is a more general approach which can be applied in overload not based on
    // `const` while the Scott Meyers' pattern is common in `const` based overload.

    Spreadsheet sheet1 { 5, 6 };
    SpreadsheetCell& cell1 { sheet1.getCellAt(1, 1) }; // calls non-`const` overload
    std::println("cell1: {}", cell1.getValue());

    const Spreadsheet sheet2 { 5, 6 };
    const SpreadsheetCell& cell2 { sheet2.getCellAt(1, 1) }; // calls `const` overload
    std::println("cell2: {}", cell2.getValue());

    // You can explicitly delete overloads
    // myCell.setValue(123);   // Won't compile: "integer" overload deleted

    std::println("- Ref-Qualified Member functions");
    // You can specify what kind of instances a member function can be called by
    // adding a ref-qualifier. Use `&` for non-temporary (i.e. `lvalue`) instances
    // and `&&` for temporary (ie. `rvalue`) instances.

    TextHolder textHolder { "Hello world!" };
    std::println("{}", textHolder.getText()); // calls `&` qualified overload

    std::println("{}", TextHolder { "Hello world!" }.getText()); // calls `&&` qualified version

    // makeTextHolder() = "Pointless!"; // Fails. You can't assign to temporary object

    auto text { makeTextHolder() };
    text = "Ok";
    std::println("text: {}", text.getText());


    std::println("-- Inline Member Functions");
    // You can "inline" member functions (as well as standalone functions) so
    // that the compiler does not treat a call to the function as a call to a
    // separate block of code. Instead, the function's body is inserted directly
    // wherever the function is called. A catch is that the function definition
    // should in the same file as the class definition where it belongs so that
    // the compiler can find it for the substitution. Many advanced C++ compilers
    // can do this automatically for functions with small function body even if
    // they're not explicitly marked `inline` or in the same file as the class 
    // definition. Nonetheless, marking a function as `inline` is only a recommendation
    // as the compiler can silently ignore it if it's not cost-effective and can
    // lead to code bloat.

    std::println("SpreadsheetCell::getString() and Spreadsheet::getValue() are marked `inline`");

    std::println("-- Default Arguments");

    Spreadsheet s1;
    Spreadsheet s2 { 5 };
    Spreadsheet s3 { 5, 6 };

    
}