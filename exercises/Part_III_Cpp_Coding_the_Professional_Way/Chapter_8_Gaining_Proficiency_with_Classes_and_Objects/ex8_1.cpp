#include <print>
#include <string>
#include <memory>

class Person
{

    public:

        Person(std::string_view firstName, std::string_view lastName);

        std::string getFirstName() const;
        void setFirstName(std::string_view firstName);

        std::string getLastName() const;
        void setLastName(std::string_view lastName);

    private:
        std::string firstName_  { };
        std::string lastName_   { };
};

Person::Person(std::string_view firstName, std::string_view lastName)
    : firstName_ { firstName }, lastName_ { lastName }
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

int main()
{

    Person stackPerson { "John", "Doe" };
    std::println("Stack Person: {}, {}", stackPerson.getFirstName(), stackPerson.getLastName());

    auto freeStorePerson { std::make_unique<Person>("Jane", "Doe") };
    std::println("Free Store Person: {}, {}", freeStorePerson->getFirstName(), freeStorePerson->getLastName());

    return 0;
}