#include <print>


// -- Order of creation and destruction


// -- Referring to Parent class name

class Book
{
    public:
        virtual ~Book() = default;
        virtual std::string getDescription() const { return "Book"; }
        virtual int getHeight() const { return 120; }
};

class Paperback : public Book
{
    public:
        std::string getDescription() const override
        {
            return "Paperback " + Book::getDescription();
        }
};

class Romance : public Paperback
{
    public:
        std::string getDescription() const override
        {
            return "Romance " + Paperback::getDescription();
        }

        int getHeight() const override { return Paperback::getHeight() / 2; }
};

class Technical : public Book
{
    public:
        std::string getDescription() const override
        {
            return "Technical " + Book::getDescription();
        }
};

// -- Casting Up and Down

int main()
{

    std::println("-- virtual Member function calls within constructors and destructor");
    // When you call a `virtual` member function within a constructor or destructor,
    // the base class version is called i.e. it is resolved statically. This is because
    // in the constructor, the object is not fully initialised, but the base has been
    // fully initialised, and it would be dangerous to call a method on the yet-to-be
    // fully initialised object. Similarly, since the destructor of the base class is
    // called first, it would be dangerous to call the derived class version on an object
    // being destroyed, but the base class destructor is yet to called, so the base class
    // version of the `virtual` function is called.
    // If you need to polymorphic behaviour in the constructor or destructor - though
    // you will rarely need to do so and it's not recommended - you can define `virtual`
    // member functions `initialise()` that the client call after the object is completely
    // constructed and `shutdown()` before the object is destroyed.

    std::println("-- Referring to Parent Names");
    // Function calls in a class are resolved from the local scope outwards. If you want
    // to call the parent version, you should prefix the member function with the name of 
    // the parent class to specifically tell the compiler to do so. C++ does not have a
    // standard `super` or `parent` name alias for the parent class.

    Romance novel { };
    Book book { };
    Technical manual { };

    std::println("{}", novel.getDescription());
    std::println("{}", book.getDescription());
    std::println("{}", manual.getDescription());
    std::println("{}", novel.getHeight());
    std::println("{}", book.getHeight());
    std::println("{}", manual.getHeight());

    std::println("Casting Up and Down");



}
