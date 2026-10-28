#include <print>
#include <string>
#include <memory>

class Person
{

    public:

        Person() = default;
        Person(std::string_view firstName, std::string_view lastName);
        Person(std::string_view firstName, std::string_view lastName, std::string_view initials);

        std::string getFirstName() const;
        void setFirstName(std::string_view firstName);

        std::string getLastName() const;
        void setLastName(std::string_view lastName);

        std::string getInitials() const;
        void setInitials(std::string_view initials);

    private:
        static std::string generateInitials(std::string_view firstName, std::string_view lastName);

    private:
        std::string firstName_  { };
        std::string lastName_   { };
        std::string initials_   { };
};

Person::Person(std::string_view firstName, std::string_view lastName)
    : Person { firstName, lastName, generateInitials(firstName, lastName) }
{

}

Person::Person(std::string_view firstName, std::string_view lastName, std::string_view initials)
    : firstName_ { firstName }, lastName_ { lastName}, initials_ { initials }
{

}

std::string Person::getFirstName() const
{
    return firstName_;
}

void Person::setFirstName(std::string_view firstName)
{
    firstName_ = firstName;
}

std::string Person::getLastName() const
{
    return lastName_;
}

void Person::setLastName(std::string_view lastName)
{
    lastName_ = lastName;
}

std::string Person::getInitials() const
{
    return initials_;
}

void Person::setInitials(std::string_view initials)
{
    initials_ = initials;
}

std::string Person::generateInitials(std::string_view firstName, std::string_view lastName)
{
    if (! firstName.empty() && ! lastName.empty()) return std::format("{}. {}.", firstName[0], lastName[0]);
    if (! firstName.empty()) return std::format("{}.", firstName[0]);
    if (! lastName.empty()) return std::format("{}.", lastName[0]);

    return "";
}

int main()
{

    Person stackPerson { "John", "Doe" };
    std::println("Stack Person: {}, {}", stackPerson.getFirstName(), stackPerson.getLastName());

    auto freeStorePerson { std::make_unique<Person>("Jane", "Doe") };
    std::println("Free Store Person: {}, {}", freeStorePerson->getFirstName(), freeStorePerson->getLastName());

    Person persons[3]; // needs 'default' constructor

    persons[0] = { "Peter", "Pan" };

    Person somePerson { *freeStorePerson }; // copy constructor

    std::println("Some Person (Initials): {}", somePerson.getInitials());

    return 0;
}