#include <format>
#include <iostream>
#include <optional>
#include <string>
#include <utility>

// --- Class Definition

// `AirlineTicket` class
class AirlineTicket
{

    public:
    
        double calculatePriceInDollars() const
        {
            if (hasEliteSuperRewardsStatus()) return 0;
            return getNumberOfMiles() * 0.1;
        }

        std::string getPassengerName() const { return m_passengerName; }
        void setPassengerName(const std::string& name) { m_passengerName = name; }

        int getNumberOfMiles() const { return m_numberOfMiles; }
        void setNumberOfMiles(int miles) { m_numberOfMiles = miles; }

        bool hasEliteSuperRewardsStatus() const { return m_hasEliteSuperRewardsStatus; }
        void setHasEliteSuperRewardsStatus(bool status) { m_hasEliteSuperRewardsStatus = status; }

        std::optional<int> getFrequentFlyerNumber() const { return m_frequentFlyerNumber; };
        void setFrequentFlyerNumber(int number) { m_frequentFlyerNumber = number; }

    private:
        // in-class initialisers
        std::string m_passengerName { "Unknown Passenger" };
        int m_numberOfMiles { 0 };
        bool m_hasEliteSuperRewardsStatus { false };
        std::optional<int> m_frequentFlyerNumber { std::nullopt };

};


int main()
{

    AirlineTicket myTicket;

    std::cout << "Default values: " << std::endl;
    std::cout << std::format("Passenger Name:   {}", myTicket.getPassengerName()) << std::endl;
    std::cout << std::format("Number of Miles:  {}", myTicket.getNumberOfMiles()) << std::endl;
    std::cout << std::format("Frequent Flyer:   {}", myTicket.getFrequentFlyerNumber().value_or(-1)) << std::endl;
    std::cout << std::format("Price in Dollars: {}", myTicket.calculatePriceInDollars()) << std::endl;
    std::cout << std::endl;

    myTicket.setPassengerName(std::as_const("John Doe"));
    myTicket.setNumberOfMiles(100);
    myTicket.setHasEliteSuperRewardsStatus(false);
    myTicket.setFrequentFlyerNumber(221);

    std::cout << std::endl;
    std::cout << "After setting new values: " << std::endl;
    std::cout << std::format("Passenger Name:   {}", myTicket.getPassengerName()) << std::endl;
    std::cout << std::format("Number of Miles:  {}", myTicket.getNumberOfMiles()) << std::endl;
    std::cout << std::format("Frequent Flyer:   {}", myTicket.getFrequentFlyerNumber().value_or(-1)) << std::endl;
    std::cout << std::format("Price in Dollars: {}", myTicket.calculatePriceInDollars()) << std::endl;
    std::cout << std::endl;


    return 0;
}