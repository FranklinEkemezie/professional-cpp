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

        std::string getFirstName() const &;
        std::string getFirstName() const &&;
        void setFirstName(std::string firstName);

        std::string getLastName() const &;
        std::string getLastName() const &&;
        void setLastName(std::string lastName);

        std::string getInitials() const &;
        std::string getInitials() const &&;
        void setInitials(std::string initials);

    private:
        static std::string generateInitials(std::string firstName, std::string lastName);

    private:
        std::string firstName_  { };
        std::string lastName_   { };
        std::string initials_   { };
};

Person::Person(std::string firstName, std::string lastName, std::string initials): 
    firstName_  { std::move(firstName) }, 
    lastName_   { std::move(lastName) }, 
    initials_   { std::move(initials) }
{

}

Person::Person(std::string firstName, std::string lastName)
    : Person { std::move(firstName), std::move(lastName), "" }
{
    initials_ = generateInitials(firstName_, lastName_);
}

std::string Person::getFirstName() const & { return firstName_; }
std::string Person::getFirstName() const && { return std::move(firstName_); }
void Person::setFirstName(std::string firstName)
{
    firstName_ = std::move(firstName);
}

std::string Person::getLastName() const & { return lastName_; }
std::string Person::getLastName() const && { return std::move(lastName_);  }
void Person::setLastName(std::string lastName)
{
    lastName_ = std::move(lastName);
}

std::string Person::getInitials() const & { return initials_; }
std::string Person::getInitials() const && { return std::move(initials_); }
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

    Person p { "John", "Doe", "JD." };
    printPerson("p", p);

    std::println("tmp initials: {}", Person { "Jane", "Doe" }.getInitials());
    

}