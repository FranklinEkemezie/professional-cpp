#include <print>

class Base
{
    public:
        void someFunction() { std::println("someFunction() defined in Base"); }
    protected:
        int protectedInt_ { 0 };
    private:
        int privateInt_ { 0 };
};

// Use `:` to extend a class. The `public` keyword will be explained later
class Derived : public Base
{
    public:
        void someOtherFunction() { std::println("someFunction() defined in Derived"); }
        void someOtherFunction1()
        {
            std::println("I can access base class data member `protectedInt_`.");
            std::println("It's value is {}", protectedInt_);
            std::println("I can't access base class data member `privateInt_`.");
            // std::println("The value of `privateInt_` is {}", privateInt_); // Error!
        }
};

int main()
{

    std::println("--- Extending Classes");

    std::println("-- A Client's View of Inheritance");

    Derived myDerived { };
    myDerived.someFunction();
    myDerived.someOtherFunction();

    Base myBase { };
    // myBase.someOtherFunction(); // Error! Base doesn't have someOtherFunction()

    // A pointer or reference to a class type can refer to an object of the
    // declared class type or any of its derived class

    Base* base { new Derived { } }; // `Base` pointer pointing to `Derived` object. OK!
    base->someFunction(); // OK!
    // base->someOtherFunction(); // To the compiler `Base` does not have the function, even though we know it's pointing to `Derived` which does

    std::println("-- A Derived Class's View of Inheritance");

    myDerived.someOtherFunction1();

}