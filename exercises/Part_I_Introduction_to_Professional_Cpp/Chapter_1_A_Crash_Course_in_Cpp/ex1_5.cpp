#include <format>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

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
        string firstName;
        string lastName;
        int employeeNumber;
        int salary;
        Title title;
    };

}


const string getTitleLabel(HR::Title title)
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
            throw invalid_argument { "Unknown title" };
    }
}

int main()
{

    using namespace HR;

    // Create and populate an employee.

    vector<Employee> employees;

    employees.push_back(Employee { "John", "Doe", 42, 80'000,  Title::Manager });
    employees.push_back(Employee { "Kate", "Boar", 123, 75'000, Title::Engineer });
    employees.push_back(Employee { "Alan", "Quejor", 77,  61'250, Title::SeniorEngineer });

    for (Employee employee : employees)
    {
    // 
        cout << format("Employee: {} {}", employee.firstName, employee.lastName) << endl;
        cout << format("Number:   {}", employee.employeeNumber) << endl;
        cout << format("Salary:   ${}", employee.salary) << endl;
        cout << format("Title:    {}", getTitleLabel(employee.title)) << endl;
        cout << endl;
    }

    return 0;
}
