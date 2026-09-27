#include <format>
#include <iostream>
#include <string>


// --- Class Definition

// `AirlineTicket` class
class AirlineTicket
{

    public:
        AirlineTicket();
        ~AirlineTicket();

        double calculatePriceInDollars();

        std::string getPassengerName();
        void setPassengerName(std::string name);

        int getNumberOfMiles();
        void setNumberOfMiles(int miles);

        bool hasEliteSuperRewardsStatus();
        void setHasEliteSuperRewardsStatus(bool status);

    private:
        // in-class initialisers
        std::string m_passengerName { "Unknown Passenger" };
        int m_numberOfMiles { 0 };
        bool m_hasEliteSuperRewardsStatus { false };

};

// Implementations:
// These can go directly in the class

// using constructor initialisation
// redudant since we have in-class initialiser in the class definition above
// kept because we need to define it as we have already declared it in the class definition
AirlineTicket::AirlineTicket()
    : m_passengerName { "Unknown Passenger" }
    , m_numberOfMiles { 0 }
    , m_hasEliteSuperRewardsStatus { false }
{}

// you can also initialise in the body
// AirlineTicket::AirlineTicket()
// {
//     m_passengerName = "Unknown Passenger";
//     m_numberOfMiles = 0;
//     m_hasEliteSuperRewardsStatus = false;
// }

AirlineTicket::~AirlineTicket()
{
    // Destructor 
    // Nothing to do in terms of cleanup
    // Can be simply removed from the class; left for demonstration purposes
}

double AirlineTicket::calculatePriceInDollars()
{
    if (hasEliteSuperRewardsStatus()) return 0;
    return getNumberOfMiles() * 0.1;
}

std::string AirlineTicket::getPassengerName() { return m_passengerName; }
void AirlineTicket::setPassengerName(std::string name) { m_passengerName = name; }

int AirlineTicket::getNumberOfMiles() { return m_numberOfMiles; }
void AirlineTicket::setNumberOfMiles(int miles) { m_numberOfMiles = miles;  }

bool AirlineTicket::hasEliteSuperRewardsStatus() { return m_hasEliteSuperRewardsStatus; }
void AirlineTicket::setHasEliteSuperRewardsStatus(bool status) { m_hasEliteSuperRewardsStatus = status; }


// --- Scope resolution

// `Demo` class
class Demo
{
    public:
        int get() { return 5; }
};

// int get() { return 10; }

namespace NS
{
    int get() { return 20; }
}

// anonymous/unnamed namespace
namespace
{
    // this definition causes a compilation error about ambiguous name resolution
    // because of the `get()` defined in the global scope

    // deleting either of them works. Unnamed namespaces are accessed as if they were 
    // global: i.e. without scope resolution operator or using it but without a name
    // Ex: `get()` or `::get()`

    // Same error occurs if we use a named namespace (`using namespace NS`)
    // in a scope where the namespace has a function with a name defined in that scope.

    int get() { return 40; }
}


int main()
{

    // Class usage

    AirlineTicket myTicket;

    std::cout << "Default values: " << std::endl;
    std::cout << std::format("Passenger Name:   {}", myTicket.getPassengerName()) << std::endl;
    std::cout << std::format("Number of Miles:  {}", myTicket.getNumberOfMiles()) << std::endl;
    std::cout << std::format("Price in Dollars: {}", myTicket.calculatePriceInDollars()) << std::endl;
    std::cout << std::endl;


    myTicket.setPassengerName("Sherman T. Socketwrench");
    myTicket.setNumberOfMiles(700);
    double cost { myTicket.calculatePriceInDollars() };

    std::cout << std::format("This ticket will cost ${}\n", cost) << std::endl;


    // Scope resolution

    Demo d;
    std::cout << std::format("{}", d.get()) << std::endl;
    std::cout << std::format("{}", NS::get()) << std::endl;
    std::cout << std::format("{}", ::get()) << std::endl;   // global scope is unamed
    std::cout << std::format("{}", get()) << std::endl;     // still global scope
}

