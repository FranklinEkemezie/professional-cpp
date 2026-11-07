#include <print>

class Base
{
    public:
        virtual void func1()    { std::println("Base::func1()"); }
        virtual void func2()    { std::println("Base::func2()"); }
        void nonVirtualFunc()   { std::println("Base::nonVirtualFunc()"); }

};

class Derived : public Base
{
    public:
        void func2() override   { std::println("Derived::func2()"); }
        void nonVirtualFunc()   { std::println("Derived::nonVirtualFunc()"); }
};

int main()
{


    std::println("--- The `virtual` Keyword");

    // When you declare a member function as `virtual`, a "virtual table" also
    // called "vtable" is created which maps the virtual member function to its
    // implementation. Since member functions inherit the "virtualness" from their
    // parent classes, the derived class also also has it's own vtable where it
    // maps the function to it's own implementation of those member function. If the
    // virtual member function is not overriden, the entry for the function in the
    // derived class' vtable maps to the base class implementation, otherwise it is
    // mapped to the derived class implementation.
    // Each object created from a class with virtual member functions contains a
    // pointer to the "vtable" which it uses to resolve the correct implementation.
    // This enables pointers and references of a base class which point/refer to 
    // objects of the derived class to call the appropriate version of the member
    // function. At run time, they follow the vtable pointer of the object and 
    // obtain the correct implementation. This is known as dynamic (or late) binding.
    // Note that this is necessary and only applies to pointers or references. When
    // a member function (virtual or not) is called directly on an object, the call
    // is resolved at compile time (static binding).
    // A class without any member function does not have vtable. Without the `virtual` 
    // keyword, calls to derived object stored in a base pointer or reference would 
    // call the base class version.
    // Lastly, the dynamic resolution involves a few level of indirection that incurs
    // a slight performance cost which can be appreciable when such class has large
    // number of references or pointers to its objects. For this reason, C++ allows you
    // to opt-in to `virtual` functions unlike many other languages such as Java or PHP
    // where all member functions are automatically virtual. Similarly, storing the
    // pointer to the vtable in each object also adds a tiny memory usage that can
    // compound at large scale.

    std::println("-- Direct object calls: Static binding");

    Base myBase { };
    Derived myDerived { };

    myBase.func1();         // `Base` version
    myDerived.func1();      // `Base` version: `func1()` is not overriden in `Derived`

    myBase.func2();         // `Base` version
    myDerived.func2();      // `Derived` version

    myBase.nonVirtualFunc();        // `Base` version
    myDerived.nonVirtualFunc();     // `Derived` version: direct object call


    std::println("-- Reference/Pointer calls: Dynamic/late binding");

    Base& ref { myDerived };

    ref.func1();            // `Base` version: `func1()` is not overriden in `Derived`
    ref.func2();            // `Derived` version
    ref.nonVirtualFunc();   // `Base` version even though `Derived` has its own version


}