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
        using HR::Title;

        case Title::Manager:
            return "Manager";
        
        case Title::SeniorEngineer:
            return "Senior Engineer";
        
        case Title::Engineer:
            return "Engineer";

        default:
            throw std::invalid_argument { "Unknown title" };
    }
}

int main()
{

    // Create and populate an employee.

    HR::Employee anEmployee {
        .firstInitial = 'J',
        .lastInitial = 'D',
        .employeeNumber = 42,
        .salary = 80'000,
        .title = HR::Title::Manager
    };

    // 
    std::cout << std::format("Employe:  {}{}", anEmployee.firstInitial, anEmployee.lastInitial) << std::endl;
    std::cout << std::format("Number:   {}", anEmployee.employeeNumber) << std::endl;
    std::cout << std::format("Salary:   ${}", anEmployee.salary) << std::endl;
    std::cout << std::format("Title:    {}", getTitleLabel(anEmployee.title)) << std::endl;
}
