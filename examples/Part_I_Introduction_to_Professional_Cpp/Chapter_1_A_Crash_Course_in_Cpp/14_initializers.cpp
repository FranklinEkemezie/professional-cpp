#include <format>
#include <iostream>

struct CircleStruct
{
    int x, y;
    double radius;
};

class CircleClass
{
    public:
        CircleClass(int x, int y, double radius)
            : m_x { x }, m_y { y }, m_radius { radius } {}
    
    private:
        int m_x, m_y;
        double m_radius;
};


class MyClass
{
    public:
        MyClass()
            : m_array { 0, 1, 2, 3 }    // uniform initialisation of arrays in class constructor initializer
        { }

    private:
        int m_array[4];
};

int main()
{

    // --- Initialisers
    // Before C++ 11, initialisation of types was not always uniform.
    // Then, initialising the class and struct looked different:

    [[maybe_unused]] CircleStruct myCircle1 = { 10, 10, 2.5 };
    [[maybe_unused]] CircleStruct myCircle2(10, 10, 2.5);

    // Now, you can use { ... } syntax for a more uniform initialisation
    [[maybe_unused]] CircleStruct myCircle3  = { 10, 10, 2.5 };
    [[maybe_unused]] CircleClass myCircle4   = { 10, 10, 2.5 };  // automatically calls the constructor

    // The equal sign is even optional
    [[maybe_unused]]
    CircleStruct myCircle5  { 10, 10, 2.5 };
    CircleClass myCircle6   { 10, 10, 2.5 };

    // Uniform initialisation extends to may other types
    [[maybe_unused]]
    int c = { 3 },  // with equal sign
        d { 3 },    // without equal sign
        e { };      // zero-initialisation

    // Zero (uniform initialisation) in structs
    [[maybe_unused]] CircleStruct aCircle1;      // data members of primitive types contain whatever random data is left in memory
    [[maybe_unused]] CircleStruct aCircle2 {  }; // data members are zero initialised

    // Uniform initialisation prevents narrows; throws compiler error
    [[maybe_unused]] int x1 = 3.14;  // implicitly narrows and truncates 3.14 to 3 before assigning, might issue a warning
    // int x { 3.14 }  // generates a compilation error, if you really need narrowing cast, you can use `gsl::narrow_cast()`
    // function from Guidelines Support Library (GSL).

    // Uniform initialisation can be used in class constructor initialiser as shown in
    // the `MyClass` definition, in Standard Library containers such as `std::vector` etc.
    // It is recommended to use uniform initialisation over assignment syntax to initialise variables.


    // --- Designated Initialisers

    // Designated initialiser initialise data members of **aggregates** using their name.
    // An aggregate type is an object of an array type, or an object of a structure or class that has:
    // only `public` data members, no user-declared/inherited constructors, no `virtual` functions, and
    // no `virtual`, `private` or `protected` base classes.
    // - A designated initialiser starts with a dot followed by the name of a data member.
    // - Designated initialisers must be in the same order as the declaration order of the data members.
    // - Mixing designated initialisers and non-designated initialisers is not allowed.
    // - Any data members not initialised in a designated initialization are initialised with their default
    //  values: zero-initialised if the data member does not have an in-class initialiser

    struct Employee
    {
        char firstInitial;
        char lastInitial;
        int employeeNumber;
        int salary { 75'000 };        
    };

    [[maybe_unused]]
    Employee anEmployee1 { 'J', 'D', 42, 80'000 };   // using uniform initialisation

    // using designate initializer
    [[maybe_unused]]
    Employee anEmployee2 {
        .firstInitial   = 'J',
        .lastInitial    = 'D',
        .employeeNumber = 42,
        .salary         = 80'000
    };  // easier to understand what a data member is being initialised to

    // you can skip initialization if you are okay with the default value
    // compilers may warn though depending on warning settings
    Employee anEmployee3 {
        .firstInitial   = 'J',
        .lastInitial    = 'D',
        .salary         = 80'000
    };  // employeeNumber is zero initialised

    std::cout << std::format("Employee Number: {}", anEmployee3.employeeNumber) << std::endl;

    // using uniform initialisation syntax, you have to specify 0 for the employee number:
    [[maybe_unused]]
    Employee anEmployee4 { 'J', 'D', 0, 80'000 };

    // data member with default value takes on that value when skipped
    Employee anEmployee5 { .firstInitial = 'J', .lastInitial = 'D' };

    std::cout << std::format("Salary: {}", anEmployee5.salary) << std::endl;

    // Finally, with designated initialisers, existing code keeps working when members are added
    // to the data structure. The new data members will just be initialised with their default values.



}