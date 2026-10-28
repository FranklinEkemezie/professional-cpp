#include <print>
#include <string>
#include <memory>

class Person
{

    public:

        Person() = default;
        Person(std::string_view firstName, std::string_view lastName);

        ~Person();

        Person(const Person& src);
        Person& operator=(const Person& rhs);

        std::string getFirstName() const;
        void setFirstName(std::string_view firstName);

        std::string getLastName() const;
        void setLastName(std::string_view lastName);

    private:
        std::string firstName_  { };
        std::string lastName_   { };
};

Person::~Person()
{
    std::println("Destructing Person({}, {})", firstName_, lastName_);
}

Person::Person(const Person& src)
{
    std::println("Copying Person({}, {}) into Person({}, {})",
        src.firstName_, src.lastName_, firstName_, lastName_);

    firstName_  = src.firstName_;
    lastName_   = src.lastName_;
}

Person& Person::operator=(const Person& rhs)
{
    if (this == &rhs)
    {
        std::println("Gotcha! Self-assignment...");
        return *this;
    }

    std::println("Assigning Person({}, {}) to Person({}, {})",
        rhs.firstName_, rhs.lastName_, firstName_, lastName_);
    
    firstName_  = rhs.firstName_;
    lastName_   = rhs.lastName_;

    return *this;
}

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

    Person persons[3]; // needs 'default' constructor

    persons[0] = { "Peter", "Pan" };

    Person somePerson { *freeStorePerson };

    return 0;
}