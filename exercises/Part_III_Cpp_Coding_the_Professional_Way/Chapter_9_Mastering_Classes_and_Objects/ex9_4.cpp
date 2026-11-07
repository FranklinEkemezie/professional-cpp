#include <print>
#include <string>
#include <memory>

/**
 * Person
 * 
 * Interface file
 */
class Person
{

    private:
        class Impl;

    public:
        Person();
        Person(std::string_view firstName, std::string_view lastName);
        Person(std::string_view firstName, std::string_view lastName, std::string_view initials);

        std::string getFirstName() const;
        void setFirstName(std::string_view firstName);

        std::string getLastName() const;
        void setLastName(std::string_view lastName);

        std::string getInitials() const;
        void setInitials(std::string_view initials);

    private:

        const std::unique_ptr<Impl> impl_;

};


/**
 * Person
 * 
 * Implementation file
 */
class Person::Impl
{

    public:

        Impl() = default;
        Impl(std::string_view firstName, std::string_view lastName);
        Impl(std::string_view firstName, std::string_view lastName, std::string_view initials);

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

/**
 * Person implementation
 */

Person::Impl::Impl(std::string_view firstName, std::string_view lastName)
    : Person::Impl { firstName, lastName, generateInitials(firstName, lastName) }
{

}

Person::Impl::Impl(std::string_view firstName, std::string_view lastName, std::string_view initials)
    : firstName_ { firstName }, lastName_ { lastName}, initials_ { initials }
{

}

std::string Person::Impl::getFirstName() const
{
    return firstName_;
}

void Person::Impl::setFirstName(std::string_view firstName)
{
    firstName_ = firstName;
}

std::string Person::Impl::getLastName() const
{
    return lastName_;
}

void Person::Impl::setLastName(std::string_view lastName)
{
    lastName_ = lastName;
}

std::string Person::Impl::getInitials() const
{
    return initials_;
}

void Person::Impl::setInitials(std::string_view initials)
{
    initials_ = initials;
}

std::string Person::Impl::generateInitials(std::string_view firstName, std::string_view lastName)
{
    if (! firstName.empty() && ! lastName.empty()) return std::format("{}. {}.", firstName[0], lastName[0]);
    if (! firstName.empty()) return std::format("{}.", firstName[0]);
    if (! lastName.empty()) return std::format("{}.", lastName[0]);

    return "";
}

/**
 * Person interface
 */

Person::Person(): impl_ { std::make_unique<Impl>() }
{

}

Person::Person(std::string_view firstName, std::string_view lastName): 
    impl_ { std::make_unique<Impl>(firstName, lastName) }
{

}

Person::Person(std::string_view firstName, std::string_view lastName, std::string_view initials):
    impl_ { std::make_unique<Impl>(firstName, lastName, initials) }
{

}

std::string Person::getFirstName() const
{
    return impl_->getFirstName();
}

void Person::setFirstName(std::string_view firstName)
{
    return impl_->setFirstName(firstName);
}

std::string Person::getLastName() const
{
    return impl_->getLastName();
}

void Person::setLastName(std::string_view lastName)
{
    return impl_->setLastName(lastName);
}

std::string Person::getInitials() const
{
    return impl_->getInitials();
}

void Person::setInitials(std::string_view initials)
{
    return impl_->setInitials(initials);
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

    Person p1 { };
    p1.setFirstName("Peter");
    p1.setLastName("Pan");
    p1.setInitials("P. P.");

    printPerson("p1", p1);

    Person p2 { "John", "Doe" };
    printPerson("p2", p2);

}