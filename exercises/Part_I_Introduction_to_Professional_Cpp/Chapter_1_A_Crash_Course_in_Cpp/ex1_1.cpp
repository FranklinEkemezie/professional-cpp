#include <format>
#include <iostream>

namespace HR
{
    struct Employee
    {
        char firstInitial;
        char lastInitial;
        int employeeNumber;
        int salary;
    };

}

int main()
{

    // Create and populate an employee.

    HR::Employee anEmployee {
        .firstInitial = 'J',
        .lastInitial = 'D',
        .employeeNumber = 42,
        .salary = 80'000
    };

    // 
    std::cout << std::format("Employe: {}{}", anEmployee.firstInitial, anEmployee.lastInitial) << std::endl;
    std::cout << std::format("Number: {}", anEmployee.employeeNumber) << std::endl;
    std::cout << std::format("Salary: ${}", anEmployee.salary) << std::endl;
}
