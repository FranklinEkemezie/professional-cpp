#include <iostream>

namespace my_code
{
    void foo()
    {
        std::cout << "foo() called in the mycode namespace" << std::endl;
    }
}

// Nested Namespace

namespace MyLibraries::Networking::FTP
{
    /**  */

    void connect()
    {
        std::cout << "connecting to network using FTP..." << std::endl;
    }
}


using namespace my_code;
// using my_code::foo; // just use the function you need

namespace MyFTP = MyLibraries::Networking::FTP; // alias a namespace


int main()
{

    my_code::foo();
    foo();

    MyFTP::connect();

    return 0;
}