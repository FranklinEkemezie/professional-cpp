
#include <charconv>
#include <memory>
#include <print>
#include <string>
#include <string_view>

class Foo
{
    public:
        Foo(double value);

    private:
        double value_ { 0 };
};

Foo::Foo(double value): value_ { value }
{
    std::println("Foo::value_ = {}", value_);
}

class MyClass
{
    public:
        MyClass(double value);

    private:
        double value_ { 0 };
        Foo foo_;

        // problematic, if the order of definition of data members
        // does not match the order in ctor initialisation
        // Foo foo_;
        // double value_ { 0 };
};

MyClass::MyClass(double value) : 
    // order of ctor initialiser should match order of the definition
    // because they are initialised in that order (and as you'll see later
    // popped off the stack in reverse order). Mismatch may lead to unexpected
    // result. In this case, if `foo_` is defined before `value_`, it's initialised
    // with `value_` which is unintialised at the time resulting in garbage value.
    // Technically, you can fix this by using `value` directly but you should
    // ensure that the order matches.
    value_ { value }, foo_ { value_ }
{
    std::println("MyClass::value_ = {}", value_);
}

int main()
{
    MyClass instance { 1.2 };
}