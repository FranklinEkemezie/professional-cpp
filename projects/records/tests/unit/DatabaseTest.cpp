#include <format>
#include <iostream>

#include <Database.cppm>

using namespace Records;

int main()
{
    Database myDB;

    Employee& emp1 { myDB.addEmployee("Greg", "Wallis") };
    emp1.fire();

    Employee& emp2 { myDB.addEmployee("Marc", "White") };
    emp2.setSalary(100'000);

    Employee& emp3 { myDB.addEmployee("John", "Doe") };
    emp3.setSalary(10'000);
    emp3.promote();

    std::cout << "All employees:\n==============" << std::endl;
    myDB.displayAll();

    std::cout << "\nCurrent employees:\n==============" << std::endl;
    myDB.displayCurrent();

    std::cout << "\nFormer employees:\n==============" << std::endl;
    myDB.displayFormer();

    return 0;
}