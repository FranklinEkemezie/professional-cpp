

class Bar
{
};

class Foo
{
    // Make `Bar` a friend of `Foo`. 
    // This gives `Bar` access to private and protected data members and
    // member functions of `Foo`.
    friend class Bar; 

    // You can also make a member function or stand-alone function as friend of class
    // which allows them access private and protected data members and member
    // functions of `Foo`.
    // Use them carefully as they allow you violate the principle of encapsulation
    // since they have access to the internals of your class.
    friend void printFoo(const Foo&);
};

void printFoo(const Foo&)
{

}



int main()
{

}