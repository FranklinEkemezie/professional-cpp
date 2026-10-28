#include <charconv>
#include <format>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')


class SpreadsheetCell
{

    public:


        // constructor: same name as class
        // called "ctor" (pronounced "see tor") for short

        // If your class does not define a constructor, the compiler generates
        // one for you (called the compiler-generated default constructor). It 
        // is a default constructor so it requires no argument and  initialises 
        // object data member but not primitives such as `int`s and `double`s etc.
        // But once you define any constructor yourself, the compiler no longer
        // generates a default constructor for you.
        // The implication is that declaring a variable of the class type (without
        // without initialising it) works when you don't define any constructor 
        // because the compiler uses its default generated constructor. 
        // This will not work if you define a constructor unless you provide a
        // default constructor yourself.
        // If you want the compiler to still generate its default constructor
        // (probably because it is enough and you don't want to write empty 
        // constructors), you can explicitly specify a constructor to be default.
        // You can also explicitly delete a default constructor, to mean that
        // you do not want a default constructor at all. See `MyClass` below


        // SpreadsheetCell(); // default constructor (no arguments)
        SpreadsheetCell() = default; // explicitly defaulted default constructors
        SpreadsheetCell(double initialValue);
        SpreadsheetCell(std::string_view initialValue);

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

    // The ctor-initialisation is different from initialising the data members
    // inside the constructor body. By the time the call constructor is called
    // the object is already created, and you are only modifying the value. With
    // ctor-initialisation, you provide initial values for data members as they
    // are created, which is more efficient than assinging values to them later.
    // You can omit data members which are objects of a class that has a default
    // constructor in the constructor initialising if you are okay with the
    // default constructed object. Otherwise, you should include them as the
    // compiler will not know how to initialise the data member.
    // Sever data types must be initialised in a ctor-initialiser or with an 
    // in-class initialiser:
    // - `const` data members - since you can't assign values to them after they
    //      are created.
    // - `reference` data members - references must refer to something as they are
    //      are created, and you cannot change what they refer to.
    // - object data members with no default constructors.
    // - base classes without default constructors.

    // One very important thing to know about constructor initialisers is that:
    // they initialise data members in the order that they appear in the class
    // definition, and not their order in the ctor-initialiser.
    // See `ctor_initializer.cpp` for demo

    // setValue(initialValue);
}

SpreadsheetCell::SpreadsheetCell(std::string_view initialValue)
{
    setString(initialValue);

    // You should not try to implement one constructor in terms of
    // another as below
    // SpreadsheetCell(stringToDouble(initialValue));
    // This create another object and does not call the constructor
    // for the object and therefore does not initialise its data members
    // C++ supports delegating constructors for this as we'll see later
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

class MyClass
{

    public:
        // If a class has data members that have a deleted default constructor,
        // then the default constructor for the class is automatically deleted as well.
        // This makes sense as there is no way to initialise that data member whose
        // class default constructor has been deleted.
        // MyClass() = delete;

    private:
        std::string name_;
};

int main()
{
    // Objects are created at the point you declare them (on the stack)
    // or you explicity allocate space for them (on the free store, using `new` or `new[]`)
    // The `string` data is also created at the same time the object is
    // created and destroyed as the object is destroyed
    MyClass obj;

    // With constructors, you can initialise objects as you declare them
    // as in:
    int x { 0 };    // declare variable `x` and initialise it
    println("x: {}", x);

    // declare and initialise by passing argument to the constructor
    SpreadsheetCell myCell (5), anotherCell(4);

    // using uniform initialisation
    SpreadsheetCell myCell1 { 5 }, anotherCell1 { 4 };

    // You do not call the constructor explicitly or later
    // SpreadsheetCell myCell2.SpreadsheetCell(5);  // Won't compile
    // myCell1.SpreadsheetCell(5); // Also won't compile

    println("-- constructors for objects on the free store");

    // smart pointer: RECOMMENDED
    auto smartCellp { std::make_unique<SpreadsheetCell>(4) };

    println("smartCellp: {}", smartCellp->getString());

    // raw pointer: remember to free later!
    SpreadsheetCell* myCellp { new SpreadsheetCell { 5 } };

    println("myCellp: {}", myCellp->getValue());

    // raw pointer: initialise with `nullptr`, allocate/create object later
    SpreadsheetCell* anotherCellp { nullptr };
    anotherCellp = new SpreadsheetCell { 4 };

    println("anotherCellp: {}", anotherCellp->getString());

    delete myCellp;         myCellp         = nullptr;
    delete anotherCellp;    anotherCellp    = nullptr;

    // you can overload constructors
    println("-- using constructor overloads");

    SpreadsheetCell aThirdCell { "test" };  // uses string argument ctor
    SpreadsheetCell aFourthCell { 4.4 };    // uses double-argument ctor
    auto aFifthCellp { std::make_unique<SpreadsheetCell>("5.5") }; // uses string argument ctor

    println("aThirdCell:    {}", aThirdCell.getValue());
    println("aFourthCell:   {}", aFourthCell.getValue());
    println("aFifthCellp:   {}", aFifthCellp->getValue());

    println("-- default constructors");
    // Default constructors are zero-argument constructors. The compiler
    // typically uses them to create objects for example when creating an
    // array of objects. After allocating contiguous memory space for all
    // the objects, it needs to call the default constructor on each object
    // to create them. If they don't exist, this fails. Your other option
    // is to initialise the array as you declare it.
    // SpreadsheetCell cells[3]; // fails without default constructor
    // SpreadsheetCell *myCellArrp { new SpreadsheetCell[10] }; // also fail

    // using default constructor
    SpreadsheetCell myCell2; // no parentheses
    myCell2.setValue(6);
    println("cell 2: {}", myCell2.getValue());

    // with parentheses (below) leads to a problem called "most vexing parse".
    // SpreadsheetCell myCell3();  // compiler thinks this is a function declaration
    // myCell3.setValue(6);    // won't compile: you're now using the supposed function as an object
    // println("cell 3: {}", myCell3.getValue());

    // Better yet, use uniform initialisation instead of function-call style parentheses

    SpreadsheetCell myCell4 { };
    println("cell 4: {}", myCell4.getString());

    println("-- using default constructors for free-store based object allocation");

    // smart pointer
    auto smartCellp1 { std::make_unique<SpreadsheetCell>() };

    // raw pointer
    SpreadsheetCell* myCellp5 { new SpreadsheetCell { } };  // OR
    // SpreadsheetCell* myCellp5 { new SpreadsheetCell };   // OR
    // SpreadsheetCell* myCellp5 { new SpreadsheetCell() };

    println("myCellp5: {}", myCellp5->getValue());

    delete myCellp5; myCellp5 = nullptr;













}