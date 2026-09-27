#include <format>
#include <iostream>

#include <Employee.cppm>

using namespace Records;

int main()
{
    std::cout << "Testing the Employee class." << std::endl;
    
    Employee emp { "Jane", "Doe" };

    emp.setFirstName("John");
    emp.setLastName("Doe");
    emp.setEmployeeNumber(71);
    emp.setSalary(50'000);
    emp.promote();
    emp.promote(50);
    emp.hire();
    emp.display();

    return 0;
}