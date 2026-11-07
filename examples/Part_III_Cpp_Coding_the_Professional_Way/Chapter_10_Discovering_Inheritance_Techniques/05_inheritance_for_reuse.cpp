#include <cmath>
#include <format>
#include <print>
#include <string>


/**
 * "Weather Prediction" library
 * 
 * Interface
 */

namespace weather_prediction
{
    // Predicts the weather using proven new- age techniques given the current
    // temperature and the distance from Jupiter to Mars. If these values are
    // not provided, a guess is still given but it's only 99% accurate.
    class WeatherPrediction
    {
        public:
            // Virtual destructor
            virtual ~WeatherPrediction();
            // Sets the current temperature in Fahrenheit
            virtual void setCurrentTempFahrenheit(int temp);
            // Sets the current distance between Jupiter and Mars
            virtual void setPositionOfJupiter(int distanceFromMars);
            // Gets the prediction for tomorrow's temperature
            virtual int getTomorrowTempFahrenheit() const;
            // Gets the probability of rain tomorrow. 1 means
            // definite rain. 0 means no chance of rain.
            virtual double getChanceOfRain() const;
            // Displays the result to the user in this format:
            // Result: x.xx chance. Temp. xx
            virtual void showResult() const;
            // Returns a string representation of the temperature
            virtual std::string getTemperature() const;
        private:
            int m_currentTempFahrenheit { 0 };
            int m_distanceFromMars { 0 };
    };
}

/** Implementation */

namespace weather_prediction
{
    WeatherPrediction::~WeatherPrediction() { }

    void WeatherPrediction::setCurrentTempFahrenheit(int temp)
    {
        m_currentTempFahrenheit = temp;
    }

    void WeatherPrediction::setPositionOfJupiter(int distanceFromMars)
    {
        m_distanceFromMars = distanceFromMars;
    }

    int WeatherPrediction::getTomorrowTempFahrenheit() const
    {

        time_t t;
        time(&t);
        srand(t);

        const double randNum { (double) rand() / RAND_MAX * 100.0 };
        const double addPart { randNum * m_currentTempFahrenheit };

        return static_cast<int>(randNum + addPart / 2);
    }

    double WeatherPrediction::getChanceOfRain() const
    {
        const int nearestTens { static_cast<int>(pow(10, ceil(log10(m_distanceFromMars)))) };
        time_t t;
        time(&t);
        srand(t);

        const double randNum { rand() / (RAND_MAX * 1.0) };

        return 1 - (m_distanceFromMars * 1.0 / nearestTens) * randNum;
    }

    void WeatherPrediction::showResult() const
    {
        std::println("Result: {:0.4f}% chance. Temp. {}°F", 
            getChanceOfRain() * 100, getTomorrowTempFahrenheit());
    }

    std::string WeatherPrediction::getTemperature() const
    {
        return std::format("{}°F", m_currentTempFahrenheit);
    }
}


/**
 * Custom Weather Prediction class with custom functionality
 */

class MyWeatherPrediction : public weather_prediction::WeatherPrediction
{

    public:
        virtual void setCurrentTempCelsius(int temp);
        virtual int getTomorrowTempCelsius() const;
        void showResult() const override;

    private:
        static int convertCelsiusToFahrenheit(int celsius);
        static int convertFahrenheitToCelsius(int fahrenheit);

};

void MyWeatherPrediction::setCurrentTempCelsius(int temp)
{
    int fahrenheitTemp { convertCelsiusToFahrenheit(temp) };
    setCurrentTempFahrenheit(fahrenheitTemp);
}

int MyWeatherPrediction::getTomorrowTempCelsius() const
{
    int fahrenheitTemp { getTomorrowTempFahrenheit() };
    return convertFahrenheitToCelsius(fahrenheitTemp);
}

int MyWeatherPrediction::convertCelsiusToFahrenheit(int celsius)
{
    return static_cast<int>(static_cast<double>(celsius) * 9 / 5 + 32);
}

int MyWeatherPrediction::convertFahrenheitToCelsius(int fahrenheit)
{
    return static_cast<int>(static_cast<double>(fahrenheit - 32) * 5 / 9);
}

void MyWeatherPrediction::showResult() const
{
    std::println("Tomorrow will be {} degrees Celsius ({} degrees Fahrenheit)",
        getTomorrowTempCelsius(), getTomorrowTempFahrenheit());
    std::println("Chance of rain is {}%", getChanceOfRain() * 100);
    if (getChanceOfRain() > 0.5) { std::println("Bring an umbrella.!"); }
}

int main()
{

    
    using namespace weather_prediction;

    WeatherPrediction wp { };

    wp.setPositionOfJupiter(12345);

    wp.showResult();
    wp.showResult();
    wp.showResult();

    MyWeatherPrediction myWp { };

    myWp.setPositionOfJupiter(12345);

    myWp.showResult();
    
}