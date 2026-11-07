#include <print>

class Something
{
    public:
        Something() { std::println("2) Something"); }
        virtual ~Something() { std::println("2) Something"); }
};

class Base
{
    public:
        Base() { std::println("1) Base"); }
        virtual ~Base() { std::println("1) Base"); }
};

class Derived : public Base
{
    public:
        Derived() { std::println("3) Derived"); }
        virtual ~Derived() override { std::println("3) Derived"); }
    private:
        Something dataMember_;
};


int main()
{

    std::println("Respect Your Parents");

    std::println("-- Order of construction: ");
    // When the constructor of a class is called, the follow happens in that order:
    // - If the class derives from a base class, the default constructor of the base
    //      class is called. If the class calls the base class's constructor in its
    //      ctor-initialiser, then that base class constructor is called instead of
    //      the default one.
    // - Next, non-`static` data members of the class are constructed in the order in
    //      which they are declared.
    // - Finally, the body of the class's constructor is executed.
    // This happens recursively.

    Derived myDerived { };

    std::println("Order of destruction: ");
    // -- Order of destruction
    // This happens in the reverse order:
    // - The body of the class's destructor is called.
    // - Data members are destroyed in the reverse order of their construction.
    // - The parent class, if any, is destructed.
    // Remeber to mark your destructors as virtual, so that the appropriate destructors
    // can be called.

}