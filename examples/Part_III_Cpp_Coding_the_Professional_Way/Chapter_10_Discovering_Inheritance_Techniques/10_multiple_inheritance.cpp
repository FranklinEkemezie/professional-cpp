#include <print>


class Foo { };
class Bar { };
class Baz : public Foo, public Bar { };

class Animal
{
    public:
        // virtual void sleep() { std::println("The animal sleeps."); }
        // Multiple inheritance can lead to "diamond shaped hierarchies", where
        // a class inherits from two or more classes which themselves inherit from
        // a common class. This can cause ambiguous base classes
        // The top class in such "diamond shaped class hierarches" should be made
        // abstract by declaring all its member functions as "pure virtual".
        // A more refined solution for this is introduced later.
        virtual void eat() = 0;
};

class Dog : Animal
{
    public:
        virtual void bark() { std::println("Woof!"); }
        virtual void eat() { std::println("The dog ate."); }
};

class Bird : Animal
{
    public:
        virtual void chirp() { std::println("Chirp!"); }
        virtual void eat() { std::println("The bird ate."); }
};

class DogBird : public Dog, public Bird
{

    public:
        // void eat() override { Dog::eat(); } // Override to prevent ambiguity
        using Dog::eat; // Explicitly inherit the version you want

};

int main()
{


    std::println("--- Multiple inheritance");

    // `Baz` inherits from both `Foo` and `Bar`
    [[maybe_unused]] Baz baz { };
    [[maybe_unused]] Foo foo { baz };
    [[maybe_unused]] Bar bar { baz };

    // Same here
    DogBird myConfusedAnimal { };
    myConfusedAnimal.bark();
    myConfusedAnimal.chirp();

    std::println("-- Name Ambiguity");

    // myConfusedAnimal.eat(); // Error! Ambiguous call to member function `eat()`
    dynamic_cast<Dog&>(myConfusedAnimal).eat(); // Upcast to hide the undesired version
    myConfusedAnimal.Bird::eat();    // Use the "disambiguation syntax" to call the desired version

    // You can prevent this ambiguity in the class by either override the ambiguous
    // member function to call the desired version, or explicitly inheriting the desired
    // version with the `using` keyword. See the `DogBird` class for usage

    std::println("-- Ambiguous Base Classes");

    // The `DogBird` class inherits the `sleep()` method from `Dog` and `Bird`.
    // When this member function is called, the compiler cannot know which version
    // it should invoke.
    // myConfusedAnimal.sleep(); // Error! Ambiguous call.


}