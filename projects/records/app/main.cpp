#include <format>
#include <iostream>

#include <Database.cppm>

using namespace Records;

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);

int main()
{

    Database employeeDB;

    bool done { false };
    while (! done)
    {
    
        switch (int selection { displayMenu() }; selection)
        {
            case 0:
                done = true;
                break;

            case 1:
                doHire(employeeDB);
                break;

            case 2:
                doFire(employeeDB);
                break;

            case 3:
                doPromote(employeeDB);
                break;

            case 4:
                employeeDB.displayAll();
                break;

            case 5:
                employeeDB.displayCurrent();
                break;

            case 6:
                employeeDB.displayFormer();
                break;

            default:
                std::cerr << "Unknown command." << std::endl;
                break;
        }
    }

}

int displayMenu()
{
    std::cout << std::endl;
    std::cout << "Employee Database" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "1) Hire a new employee" << std::endl;
    std::cout << "2) Fire an employee" << std::endl;
    std::cout << "3) Promote an employee" << std::endl;
    std::cout << "4) List all employee" << std::endl;
    std::cout << "5) List all current employees" << std::endl;
    std::cout << "6) List all former employees" << std::endl;
    std::cout << "0) Quit" << std::endl;
    std::cout << std::endl;
    std::cout << "---> ";

    int selection;
    std::cin >> selection;

    return selection;
}

void doHire(Database& db)
{
    std::cout << "First name? ";
    std::string firstName;
    std::cin >> firstName;

    std::cout << "Last Name? ";
    std::string lastName;
    std::cin >> lastName;

    auto& employee { db.addEmployee(firstName, lastName) };
    std::cout << std::format("Hired employee {} {} with employee number {}.",
        firstName, lastName, employee.getEmployeeNumber()) << std::endl;
}

void doFire(Database& db)
{
    std::cout << "Employee number? ";
    int employeeNumber;
    std::cin >> employeeNumber;

    try
    {
        auto& emp { db.getEmployee(employeeNumber) };
        emp.fire();

        std::cout << std::format("Employee {} terminated.", employeeNumber);
    }
    catch (const std::logic_error& exception)
    {
        std::cerr << std::format("Unable to terminate employee: {}", exception.what());
    }
}

void doPromote(Database &db)
{
    std::cout << "Employee number? ";
    int employeeNumber;
    std::cin >> employeeNumber;

    std::cout << "How much of a raise? ";
    int raiseAmount;
    std::cin >> raiseAmount;

    try
    {
        auto& emp { db.getEmployee(employeeNumber) };
        emp.promote(raiseAmount);
    }
    catch(const std::logic_error& exception)
    {
        std::cerr << std::format("Unable to promote employe: {}", exception.what()) << std::endl;
    }
    
}