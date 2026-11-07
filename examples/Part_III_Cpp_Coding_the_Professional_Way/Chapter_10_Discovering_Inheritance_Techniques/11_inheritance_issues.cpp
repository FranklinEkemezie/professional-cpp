#include <print>

// -- Changing the overriden member function's return type

class PowerSource
{
    public:
        virtual void printType() = 0;
};

class GasolinePowerSource : public PowerSource
{
    public:
        void printType() override { std::println("GasolinePowerSource"); }
        virtual void fillTank() { std::println("Gasoline tank filled up."); }
};

class ElectricalPowerSource : public PowerSource
{
    public:
        void printType() override { std::println("ElectricalPowerSource"); }
        virtual void chargeBatteries() { std::println("Batteries charged."); }
};

class Car
{
    virtual PowerSource& getFilledUpPowerSource() = 0;
};

class GasolineCar : public Car
{
    public:
        // You can return a more specific type than the base (virtual) class
        // declares. The return type must be covariant with that of the base class
        // definition i.e. changing it does not require you to change existing code.
        // Subsequently, it must obey Liskov's Substitution Principle (LSP) because
        // an object of a derived class can be used anywhere the base class can be used.
        GasolinePowerSource& getFilledUpPowerSource() override
        {
            engine_.fillTank();
            return engine_;
        }

    private:
        GasolinePowerSource engine_;
};

class ElectricalCar : public Car
{
    public:

        ElectricalPowerSource& getFilledUpPowerSource() override
        {
            engine_.chargeBatteries();
            return engine_;
        }

    private:
        ElectricalPowerSource engine_;
};

// -- Adding overloads of virtual base class member functions to derived classes
// -- Inherited Constructors

class Base
{
    public:
        virtual ~Base() = default;
        Base() = default;
        explicit Base(int i) { std::println("Base constructor called with int: {}", i); }
        
        explicit Base(std::string_view str) : str_ { str } { std::println("Base constructor called string: {}", str); }
        explicit Base(float f) { std::println("Base constructor called with float: {}", f); }

        virtual void someFunction();

        // 

        virtual void overload() { std::println("Base's overload()"); }
        virtual void overload(int i) { std::println("Base's overload(int i: {})", i); }

        virtual void go(int i = 2) { std::println("Base's go with i = {}", i); }

    
        Base(const Base& src) : Base { src.str_ } { }   // copy constructor
        Base& operator=(const Base& rhs);

    private:
        std::string str_ { "" };
};

void Base::someFunction() { std::println("Base::someFunction()"); }

Base& Base::operator=(const Base& rhs)
{
    if (&rhs == this) { return *this; }

    str_ = rhs.str_;

    return *this;
}

class Derived : public Base
{
    public:

        // explicit Derived(int i) : Base { i } { } // Forwards call to `Base`
        using Base::Base; // you can inherit constructor instead. plus, you get to inherit the default (and other) ones too

        // Restrictions with inheriting constructors:
        // - You inherit all of them.
        // - The access specification remains the same, irrespective of which specification
        //      the `using` declaration is under.

        explicit Derived(float f) { std::println("Derived constructor with float: {}", f); } // Hides the inherited float `Base` ctor.

        using Base::someFunction;           // Explicitly inherits the Base version
        virtual void someFunction(int i);   // Adds a new overload of `someFunction()`
        virtual void someOtherFunction();

        // Overriding a member function hides all of its other overloads, if any.
        void overload() override { std::println("Derived's overload"); }
        // Get all other overloads. But remember you get all of them. To prevent
        // weird bugs, you should override all overloads of the member functions as well.
        using Base::overload; 

        // Overrides base class member function, but with different default argument.
        void go(int i = 7) override { std::println("Derived's go with i = {}", i); }

        // NB: Always call the parent copy constructor in the child copy constructor
        // otherwise, the compiler calls the default constructor.
        Derived(const Derived& src) : Base { src } { }
        Derived& operator=(const Derived& rhs);



    private:
        // Always use class-initialiser especially when inherited constructors 
        // may not initialise the derived class data members.
        int int_ { 0 }; 
};

void Derived::someFunction(int i) { std::println("Derived::someFunction({})", i); }
void Derived::someOtherFunction() { std::println("Derived::someOtherFunction()"); }

    Derived& Derived::operator=(const Derived& rhs)
    {
        if (&rhs == this) { return *this; }

        // Call parent copy assignment operator to perform
        // copy assignment for parent portion of the object
        Base::operator=(rhs); 

        // Do the necessary assignments for derived class portion of the object.
        int_ = rhs.int_;

        return *this;
    }

// - Inherited Constructors and Multiple Inheritance

class Base1
{
    public:
        virtual ~Base1() = default;
        Base1() = default;
        explicit Base1(float f) { std::println("Base1 constructor called with float: {}", f); }
};

class Base2
{
    public:
        virtual ~Base2() = default;
        Base2() = default;
        explicit Base2(std::string_view str) { std::println("Base2 constructor called with string: {}", str); }
        explicit Base2(float f) { std::println("Base2 constructor called with float: {}", f); }
};

class ConfusedDerived : public Base1, public Base2
{
    public:
        using Base1::Base1; // Inherits all constructor from `Base1`
        using Base2::Base2; // Tries to inherit the `float` ctor overload again.

        explicit ConfusedDerived(char c) { std::println("ConfusedDerived constructor called with char: {}", c); }

        explicit ConfusedDerived(float f) { std::println("ConfusedDerived constructor called with float: {}", f); }

};

// Overriding member functions when the base class member function is static

class BaseStatic
{
    public:
        static void beStatic() { std::println("BaseStatic being static."); }
};

class DerivedStatic : public BaseStatic
{
    public:
        static void beStatic() { std::println("DerivedStatic keepin' it static."); }
};


// - The base class member function is private

class MilesEstimator
{
    public:
        virtual ~MilesEstimator() = default;

        // Template function
        int getMilesLeft() const { return getMilesPerGallon() * getGallonsLeft(); }

        virtual void setGallonsLeft(int gallons) { gallonsLeft_ = gallons; }
        virtual int getGallonsLeft() const { return gallonsLeft_; }

    private:
        virtual int getMilesPerGallon() const { return 20; }

    private:
        int gallonsLeft_ { 0 };
};

class EfficientCarMilesEstimator : public MilesEstimator
{
    private:
        int getMilesPerGallon() const override { return 35; }
};

// - The base class member function has a different access specification

class Gregarious
{
    public:
        virtual void talk() { std::println("Gregarious says hi!"); }
};

class Shy : public Gregarious
{
    protected:
        void talk() override { std::println("Shy reluctantly says hello."); }
};

class Secret
{
    protected:
        virtual void dontTell() { std::println("I'll never tell."); }
};

class Blabber : public Secret
{
    public:
        virtual void tell() { dontTell(); }

        // Or you can override `dontTell()` to be `public` or explicitly inherit
        // it as `public` with `using Secret::dontTell`
};

int main()
{
    
    std::println("--- Interesting and obscure inheritance issues");

    std::println("-- Changing the overriden member function's return type");

    GasolineCar gc { };
    gc.getFilledUpPowerSource().printType();
    ElectricalCar ev { };
    ev.getFilledUpPowerSource().printType();

    std::println("-- Adding overloads of virtual base class member functions to derived classes");

    Derived myDerived { };
    myDerived.someFunction();       // calls `Base` version
    myDerived.someFunction(42);     // calls `Derived` overload
    myDerived.someOtherFunction(); 

    std::println("-- Inherited Constructors");

    Base base { 1 };            // OK, calls integer `Base` ctor.
    Derived derived1 { 2 };     // OK, calls inherited integer `Base` ctor.
    Derived derived2;           // OK, calls inherited default `Base` ctor.

    std::println("- Hiding inherited constructors");

    Derived derived3 { "Hello" };   // Calls inherited `string_view` `Base` ctor.
    Derived derived4 { 1.23f };     // Calls float `Derived ctor (overloaded version).
    Derived derived5 { };           // Calls inherited default `Base` ctor.
    
    std::println("- Inherited constructors and multiple inheritance");

    // The constructor call below is ambiguous. 
    // You can fix this by declaring the conflicting constructors in the derived
    // class in order to hide the inherited version.
    ConfusedDerived myConfusedDerived { 1.2f }; 

    std::println("- Initialisation of data members");

    // With class initialisation, the data members are appropriately
    // initialised, no matter the constructor that is invoked.

    Derived derived6 { 2 };
    Derived derived7 { "Hello World" };


    std::println("-- Special cases in overriding member functions");

    std::println("- The base class member function is `static`");
    // You cannot override `static` member functions. You can't declare them
    // `virtual` to begin with. This means that a static member function with 
    // in a derived class with the same function signature as another static
    // member function in a base class are unrelated.

    BaseStatic::beStatic();     
    DerivedStatic::beStatic();

    // When a `static` member function is called on an object, the compile time
    // type of the object is used to resolved the particular `static` member function 
    // statically. Remember that `static` member functions can't be virtual anyways,
    // so there is no entry for them in the virtual table to resolve at runtime.

    DerivedStatic myDerivedStatic { };
    BaseStatic& ref { myDerivedStatic };

    myDerivedStatic.beStatic();     // calls `DerivedStatic` version
    ref.beStatic();                 // calls `BaseStatic` version

    std::println("- The base class member function is overloaded");

    // won't work if this overload is overriden in derived class 
    // but not redefined in derived
    myDerived.overload(2); 

    Base& myBaseRef { myDerived };
    myBaseRef.overload(7);  // Access overriden overload.

    //

    std::println("- The base class member function is private");

    // Derived classes can override private member function in C++ even though
    // they cannot access (i.e. call) them. Overriding private member function
    // is commonly used in implementing "template member function" pattern, where
    // the class that can access the private member function calls it in an 
    // implementation to be inherited by derived classes, while other derived classes
    // overrides it (the private member function). When the inherited implementation
    // is invoked for a derived class, the derived class version of the private
    // member function is used. This allows us to change certain features of a class
    // without a major overhaul.
    // In the example, we have a new implementation without having the overriding the 
    // whole implementation, but just the parts that the implementation uses.

    MilesEstimator myMilesEstimator { };
    myMilesEstimator.setGallonsLeft(2);

    std::println("Normal estimator can go {} more miles.", myMilesEstimator.getMilesLeft());

    EfficientCarMilesEstimator myEstimator { };
    myEstimator.setGallonsLeft(2);

    std::println("Efficient estimator can go {} more miles.", myEstimator.getMilesLeft());
    
    std::println("- The base class member function has default arguments");

    // While the function definition may be resolved dynamically during runtime
    // when necessary. Default arguments are bound at compile time.

    Base myBase1 { };
    Derived myDerived1 { };
    Base& myBaseRefToDerived1 { myDerived1 };

    myBase1.go();               // calls `Base` version with default i = 2
    myDerived1.go();            // calls `Derived` version with default i = 7
    myBaseRefToDerived1.go();   // calls `Derived` version but with default i = 2
    

    std::println("- The base class member function has a different access specification");

    // Generally, there is no reasonable way (or good reason) access to a `public`
    // base class member function in the derived class.

    Shy myShy;
    // myShy.talk(); // Error! Attempt to access protected member function.

    // Workaround:
    Gregarious& myShyRef { myShy };
    myShyRef.talk(); // calls the correct overriden "protected" member function.

    // It is much easier (and makes more sense) to lessen access restriction in
    // derived classes.

    Secret mySecret { };
    // mySecret.dontTell(); // Error!

    Blabber myBlabber { };
    myBlabber.tell();   // Ok!

    [[maybe_unused]] Secret& mySecretRef { myBlabber };
    [[maybe_unused]] Secret* mySecretPtr { &myBlabber };

    // mySecretRef.dontTell();     // This member function is "protected" in `Secret`
    // mySecretPtr->dontTell();    // Same Error!

    std::println("-- Copy Constructors and Assignment Operators in Derived Classes");

    // As we saw in Chapter 9, when you have dynamically allocated memory or
    // resource in your class, you should have define (or explicitly default
    // or delete) a copy constructor and copy assignment operator to define
    // what happens to the dynamically allocated memory when the object of
    // such class is copied or assigned. 
    // If the base class inherits from such class, the copy constructor as well
    // as the copy assignment operator should call the corresponding copy
    // constructor and copy assignment operator for the parent class so that the
    // parent portion of the object is copied or copy-assigned properly and completely.
    // For the copy constructor, you have to call the parent copy constructor in
    // constructor initialiser, otherwise the  default constructor is called!
    // For the copy assignment operator, you call the parent copy assignment operator
    // in the body before doing the necessary assigments for the derived portion of
    // the object. The `Base` and `Derived` classes demonstrate this.
    // Later, we will see how to use a polymorphic `clone()` member function to
    // simplify implementing copy functionality in an inheritance hierarchy.

}