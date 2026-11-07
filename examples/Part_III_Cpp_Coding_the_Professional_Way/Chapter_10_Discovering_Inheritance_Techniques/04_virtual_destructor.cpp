#include <print>

class Base
{
    public:
        Base() = default;
        ~Base() = default;
        // virtual ~Base() = default; // uncomment to ensure child classes' destructors are resolved properly.

        virtual void someFunction() { std::println("Base::someFunction()"); }
};

class Derived : public Base
{
    public:
        Derived()
        {
            string_ = new char[30];
            std::println("`string_` allocated");
        }

        // You can ensure the parent's (i.e. `Base`) class destructor is virtual
        // by marking the `Derived` constructor as `override`. This generates a 
        // compilation error if the `Base` destructor is not declared `virtual`.
        // You can combine `virtual` (which is redundant), `override`, and `default`
        // as shown below:
        // virtual ~Derived()  override = default;
        ~Derived()
        {
            delete[] string_;
            std::println("`string_ deallocated");
        }

        virtual void someFunction() override final { std::println("Derived::someFunction()"); }

    private:
        char* string_;
};

class DerivedDerived : public Derived
{
    public:
        // void someFunction() override;   // Error! The parent class marked this member function as `final`
};


int main()
{

    std::println("-- Make destructors `virtual`");

    // Knowing the role of the `virtual` keyword, you should always make your destructors
    // to be `virtual` so that the right destructor is called. This is particularly
    // useful when the derived class uses dynamically allocated memory and must be
    // destroyed in the destructor. If the destructor is not resolved appropriately
    // the memory is not freed. The same is true when the derived class contains members
    // that need to perform automatic cleanup when the destructor is called such as
    // smart pointers e.g. `std::unique_ptr`. If the destructor is not called, they
    // cannot know when to free the memory they manage resulting in a memory leak.
    
    Base* ptr { new Derived {} };   // `string_` is allocated here.

    // The code below produces an undefined behaviour according to the C++ standard.
    // In such undefined situations, the compiler could do whatever it wants. Most
    // compilers, however, simply call the destructor of the base class.
    // GCC compiler emits a warning:
    // warning: deleting object of polymorphic class type ‘Base’ which has non-virtual 
    // destructor might cause undefined behavior [-Wdelete-non-virtual-dtor]
    delete ptr; // non-virtual `~Base()` is called, but `~Derived()` and so allocated string is not freed

    // `final` classes do not need `virtual` member functions as they cannot be extended.
    // You can also mark individual member functions as `final` to prevent them from
    // being overriden.
}