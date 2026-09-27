#include <format>
#include <iostream>
#include <stdexcept>

namespace HR
{

    enum class Title
    {
        Manager,
        SeniorEngineer,
        Engineer
    };

    struct Employee
    {
        char firstInitial;
        char lastInitial;
        int employeeNumber;
        int salary;
        Title title;
    };

}


const std::string getTitleLabel(HR::Title title)
{
    switch (title)
    {
        using enum HR::Title;

        case Manager:
            return "Manager";
        
        case SeniorEngineer:
            return "Senior Engineer";
        
        case Engineer:
            return "Engineer";

        default:
            throw std::invalid_argument { "Unknown title" };
    }
}

int main()
{

    using namespace HR;

    // Create and populate an employee.

    std::array employees {
        Employee { 'J', 'D', 42, 80'000,  Title::Manager },
        Employee { 'K', 'B', 123, 75'000, Title::Engineer },
        Employee { 'A', 'Q', 77,  61'250, Title::SeniorEngineer }
    };


    for (Employee employee : employees)
    {
    // 
        std::cout << std::format("Employe:  {}{}", employee.firstInitial, employee.lastInitial) << std::endl;
        std::cout << std::format("Number:   {}", employee.employeeNumber) << std::endl;
        std::cout << std::format("Salary:   ${}", employee.salary) << std::endl;
        std::cout << std::format("Title:    {}", getTitleLabel(employee.title)) << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
