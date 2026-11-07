#include <print>

class Base 
{
    public:

        virtual void someFunction() { std::println("Base::someFunction()"); }
};

class Derived : public Base
{

    public:
        void someFunction() override { std::println("Derived::someFunction()"); }

        virtual void someOtherFunction() { std::println("Derived::someOtherFunction()"); }
};

void presumptuous(Base* base)
{

    // Presumes `base` will always be `Derived`
    Derived* myDerived { static_cast<Derived*>(base) };

    myDerived->someFunction();  // OK, if `base` is really a valid pointer. `someFunction()` belongs to `Base`
    myDerived->someOtherFunction(); // Dangerious, if `base` is not a pointer to `Derived`
    std::println(">>>>");
}

void lessPresumptuous(Base *base)
{

    // use `dynamic_cast` instead of `static_cast` for runtime casting.
    Derived* myDerived { dynamic_cast<Derived*>(base) };

    // Checks if `base` is really a pointer to `Derived`.
    // Screams bad design!
    if (myDerived != nullptr)
    {
        myDerived->someFunction();
        myDerived->someOtherFunction();
        std::println(">>>>");
    }
}

int main()
{
    Derived myDerived { };

    std::println("--- Casting Up and Down");

    std::println("-- Upcasting");

    // You can assign derived class object to its parent. The end result is an
    // object of the type of the base/parent class.
    // This is called upcasting (casting up the hierarchy).
    // You cannot call member functions specific to the derived class.
    // The derived object is said to have been sliced.
    Base myBase1 { myDerived };     // Slicing!
    myBase1.someFunction();         // OK: Calls `Base` version.
    // myBase1.someOtherFunction();    // `myBase1` does not have this function.

    // When you assign a derived class object to its a reference or pointer of the
    // parent, the end result is still a reference or pointer to the parent type, but
    // you can access the derived class version of the member functions.
    // You cannot call member function specific to the derived class though, but when
    // you call member functions available to the base class, the derived version is called.
    // This type of upcasting (using pointers and references) does not slice
    // the derived object. You should use instead when upcasting
    Base& myBase2 { myDerived };    // No slicing!
    myBase2.someFunction();         // OK: Calls `Derived` version.
    // myBase2.someOtherFunction();    // Ok!

    // 
    std::println("-- Downcasting");

    presumptuous(&myDerived);   // Ok
    presumptuous(&myBase2);     // Ok
    // presumptuous(&myBase1);     // Dangerous: `myBase1` has been sliced. Possible segfault.
    lessPresumptuous(&myBase1); // Safer






}