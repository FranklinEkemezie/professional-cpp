#include <print>
#include <string>
#include <memory>

// Where strings are needed as parameters, the functions in this code uses
// `std::string` instead of `std::string_view` to demonstrate how to pass
// `std::string` in a way that is as optimal as the `std::string_view` version.

class Person
{

    public:

        Person() = default;
        Person(std::string firstName, std::string lastName);
        Person(std::string firstName, std::string lastName, std::string initials);

        [[nodiscard]] auto operator<=>(const Person& other) const noexcept = default;

        std::string getFirstName() const;
        void setFirstName(std::string firstName);

        std::string getLastName() const;
        void setLastName(std::string lastName);

        std::string getInitials() const;
        void setInitials(std::string initials);

    private:
        static std::string generateInitials(std::string firstName, std::string lastName);

    private:
        std::string firstName_  { };
        std::string lastName_   { };
        std::string initials_   { };
};

Person::Person(std::string firstName, std::string lastName, std::string initials) 
    : firstName_  { std::move(firstName) }
    , lastName_   { std::move(lastName) }
    , initials_   { std::move(initials) }
{
}

Person::Person(std::string firstName, std::string lastName) 
    : Person { std::move(firstName), std::move(lastName), "" }
{
    initials_ = generateInitials(firstName_, firstName_);
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

std::string Person::getInitials() const
{
    return initials_;
}

void Person::setInitials(std::string initials)
{
    initials_ = std::move(initials);
}

std::string Person::generateInitials(std::string firstName, std::string lastName)
{
    if (! firstName.empty() && ! lastName.empty()) return std::format("{}. {}.", firstName[0], lastName[0]);
    if (! firstName.empty()) return std::format("{}.", firstName[0]);
    if (! lastName.empty()) return std::format("{}.", lastName[0]);

    return "";
}

// Helper function
void printPerson(std::string label, const Person& person)
{
    std::println("{}: {}, {} ({})", 
        std::move(label), 
        person.getFirstName(), 
        person.getLastName(),
        person.getInitials()
    );
}

int main()
{

    Person 
        p1 { "Peter", "Pan" },
        p2 { "John", "Doe" },
        p3 { "Jane", "Doe" },
        p4 { "Cathe", "Leon" };

    printPerson("p1", p1);
    printPerson("p2", p2);
    printPerson("p3", p3);
    printPerson("p4", p4);

    std::println("--- Comparison operators");

    std::println("p1 == p1: {}",    p1 == p1);
    std::println("p3 == p1: {}",    p1 == p3);

    std::println("p3 != p3: {}",    p3 != p3);
    std::println("p4 != p2: {}",    p4 != p2);

    std::println("p2 <  p1: {}",    p2 <  p1);
    std::println("p4 >  p3: {}",    p3 >  p4);

    std::println("p2 >= p2: {}",    p2 >= p2);
    std::println("p2 >= p3: {}",    p2 >= p3);

    std::println("p4 <= p4: {}",    p4 <= p4);
    std::println("p1 <= p4: {}",    p1 <= p4);
}