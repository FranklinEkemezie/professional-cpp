#include <print>

class Base
{
    public:
        // Mark a member function as `virtual` to be able to override it properly.
        // This
        virtual void someFunction() { std::println("someFunction() defined in Base"); }

        virtual void someFunction(double d) 
        { 
            std::println("someFunction() defined in Base prints: {}", d);
        }

    protected:
        int protectedInt_ { 0 };
    private:
        int privateInt_ { 0 };
};

class Derived : public Base
{
    public:

        // Use the `override` keyword to override a virtual member function.
        // Declaring it `virtual` is redundant as `virtual` applies on all overrides.
        void someFunction() override { std::println("someFunction() defined in Derived"); }
        virtual void someOtherFunction() { std::println("someFunction() defined in Derived"); }
        virtual void someOtherFunction1()
        {
            std::println("I can access base class data member `protectedInt_`.");
            std::println("It's value is {}", protectedInt_);
            std::println("I can't access base class data member `privateInt_`.");
            // std::println("The value of `privateInt_` is {}", privateInt_); // Error!
        }

        // Overrides `Base::someFunction(double d)` properly but does use
        // `override` keyword. Okay, as long as you override to intended overload
        // otherwise you end up with a new function that hides the member function from
        // the base class.
        virtual void someFunction(double d)
        {
            std::println("someFunction defined Derived prints {}", d);
        }

        // If we had this function instead of the "double" overload above, this would
        // be regarded as an override and the `Base` version will always be called.
        // This could happen when you override a base method and then forget to update
        // the functions overriding it. These functions technically becomes a new
        // virtual function and calls to "overriden" version will miss and go straight
        // to the base version. By adding the `override` keyword, the compiler generates
        // an error since you're trying to override the wrong (non-existent) function overload.
        // You should always use the `override` keyword to override member functions.
        virtual void someFunction(int i)
        {
            std::println("someFunction defined Derived prints {}", i);
        }

};

int main()
{

    std::println("--- Overriding Member Functions");

    std::println("-- A Client's View of Overriden Member Functions");

    Base myBase { };
    myBase.someFunction();

    Derived myDerived { };
    myDerived.someFunction();
    myDerived.someOtherFunction();

    Base& ref { myDerived };
    // Even though `ref` can only access `Base` method, it still refers to a 
    // `Derived` object and forwards any call to it to `Derived` version
    ref.someFunction();
    // ref.someOtherFunction(); // Error!

    std::println("-- The `override` keyword");

    ref.someFunction(1.1);
   
}