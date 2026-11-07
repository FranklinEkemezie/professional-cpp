#include <print>
#include <string>
#include <memory>
#include <utility>

// Where strings are needed as parameters, the functions in this code uses
// `std::string` instead of `std::string_view` to demonstrate how to pass
// `std::string` in a way that is as optimal as the `std::string_view` version.

class Person
{

    public:

        Person() = default;
        Person(std::string firstName, std::string lastName);

        ~Person();

        Person(const Person& src);
        Person& operator=(const Person& rhs);

        Person(Person&& src) noexcept;
        Person& operator=(Person&& rhs) noexcept;

        void swap(Person& other) noexcept;

        std::string getFirstName() const;
        void setFirstName(std::string firstName);

        std::string getLastName() const;
        void setLastName(std::string lastName);

    private:
        std::string firstName_  { };
        std::string lastName_   { };
};

void swap(Person& a, Person& b) noexcept
{
    a.swap(b);
}

Person::Person(std::string firstName, std::string lastName) 
    : firstName_  { std::move(firstName) }
    , lastName_   { std::move(lastName) }
{
    std::println("Main constructor called for {} {}", firstName_, lastName_);
}

Person::~Person()
{
    std::println("Destroying Person({}, {})", firstName_, lastName_);
}

Person::Person(const Person& src)
    : Person { src.firstName_, src.lastName_ } 
{
    std::println("Copying Person({}, {})", src.firstName_, src.lastName_);
}

Person& Person::operator=(const Person& rhs)
{
    std::println("Assigning Person({}, {}) to Person({}, {})",
        rhs.firstName_, rhs.lastName_, firstName_, lastName_);
    
    auto temp { rhs };
    swap(temp);

    return *this;
}

Person::Person(Person&& src) noexcept
{
    std::println("Moving Person({}, {})", src.firstName_, src.lastName_);
    
    swap(src);
}

Person& Person::operator=(Person&& rhs) noexcept
{
    std::println("Move assigning Person({}, {}) into Person({}, {})",
        rhs.firstName_, rhs.lastName_, firstName_, lastName_);

    auto temp { std::move(rhs) };
    swap(temp);

    return *this;
}

void Person::swap(Person& other) noexcept
{
    std::swap(firstName_,   other.firstName_);
    std::swap(lastName_,    other.lastName_);
}

std::string Person::getFirstName() const
{
    return firstName_;
}

void Person::setFirstName(std::string firstName)
{
    firstName_ = std::move(firstName);
}

std::string Person::getLastName() const
{
    return lastName_;
}

void Person::setLastName(std::string lastName)
{
    lastName_ = std::move(lastName);
}

// Helper function

void printPerson(std::string label, const Person& person)
{
    std::println("{}: {}, {}", 
        std::move(label), person.getFirstName(), person.getLastName());
}


int main()
{

    std::println("-- Default constructor");

    Person 
        p1 { "Peter", "Pan" }, 
        p2 { "John", "Doe" },
        p3 { "Jane", "Doe" },
        p4 { "Cathe", "Leon" };

    std::println("-- Copy constructor");
    Person p10 { p1 };
    printPerson("p10", p10);

    std::println("-- Copy assignment");
    p10 = p2;
    printPerson("p10", p10);

    std::println("-- Move constructor");
    Person p11 { std::move(p3) };
    printPerson("p11", p11);

    std::println("-- Move assignment");

    std::print("[Before move assign] ");
    printPerson("p3", p3);

    p3 = std::move(p4);

    std::print("[After move assign] ");
    printPerson("p3", p3);

    std::println("--- `main()` scope ends here");
}