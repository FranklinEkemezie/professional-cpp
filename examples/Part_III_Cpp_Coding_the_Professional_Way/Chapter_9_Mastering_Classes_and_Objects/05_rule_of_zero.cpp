#include <print>

int main()
{

    std::println("--- Rule of Zero");

    // Earlier in this chapter, we introduced the "Rule of Five" that states that
    // once you declare any of the five special member functions (destructor, 
    // copy constructor, move constructor, copy assignment operator, and move 
    // assignment operator), you should declare of all them by either implementing,
    // defaulting, or deleting them. This prevents you from thinking about the
    // obviously complicated rule that the compiler uses to decide when to generate
    // those functions automatically.

    // However, in modern C++, you should adopt the "Rule of Zero" which states that
    // you should design your classes in such a way that they do not require any of 
    // those special member functions. You can do so by avoiding old-style dynamically
    // allocated memory and reach for modern constructs such as Standard Library containers
    // and smart pointers.

    // The rule of five should be limited to custom "resource acquisition is initialisation"
    // (RAII) classes. An RAII class takes ownership of a resource and handles it deallocation
    // at the right time. This design technique discussed in Chapter 32, is used by the `vector`
    // class, `unique_ptr` class and other Standard Library classes that need to manage memory.

    std::println("In modern C++, adopt the rule of zero!");
    std::println("Design your classes so they never need any of those five special member functions.");
    std::println("Polymorphic types also require you to follow the rule of five.");
}