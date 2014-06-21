/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/18/2013
 * Last Modified:    06/20/2014
 * Description:      Demonstrates the capabilities of the class, Temperature.  
 *                   The class Temperature hold a temperature value in degrees
 *                   Kelvin.  Interface functions allow this temperature to
 *                   modified or returned in Kelvin, Fahrenheit, or Celsius.
 *                   Operator overloads permit boolean direct equivalency (==)
 *                   and input (>>) and output (<<) operations.  The main
 *                   function acts as a demonstration for this class.
 * Input:            Temperatures from the user to demonstrate the
 *                   capabilities of the Temperature class.
 * Output:           Prompts for user input.  Outputs for each type of 
 *                   temperature demonstrating conversion and operator 
 *                   overload properties of the Temperature class.
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>  /* For input/output */
#include <cmath>     /* For floor() */

using std::cout;
using std::cin;
using std::ios;
using std::istream;
using std::ostream;

class Temperature{
    public:
        /* Constructors */
        Temperature(double tempDegrees);
        Temperature();
        
        /* Interface functions */
        void setTempKelvin(double tempKelvin);
        void setTempFahrenheit(double tempFahrenheit);
        void setTempCelsius(double tempCelsius);
        
        double getTempKelvin();
        double getTempFahrenheit();
        double getTempCelsius();
        
        /* Operator overloads */
        friend bool operator ==(const Temperature& temp1, 
                                        const Temperature& temp2);
        friend istream& operator >>(istream& inputStream, 
                                             Temperature& temp);
        friend ostream& operator <<(ostream& outputStream, 
                                             Temperature& temp);
    
    private:
        double kelvin;
        
        /* Generate error output and set default Kelvin temperature */
        void negKelvin();
        /* Outputs error message regarding negative Kelvin temperatures */
        void outNegKelvinError();
        /* Sets private member variable kelvin to absolute zero (0) */
        void setAbsZero();
        /* Tests if tempDegrees is a negative Kelvin temperature */
        bool test_temp(double tempDegrees);
        /* Rounds tempDegrees to the hundreths decimal place */
        double tempRound(double tempDegrees);
};

int main(){
    /* Variable declarations */
    Temperature tempDemo, tempDemo2;
    double temperature;
    
    /* Format number output for cout */
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    /* Introductory message and instructions */
    cout << "\n\nWelcome!\nThis is a demonstration of the Temperature class.";
    cout << "\nThe class initializes the temperature as 0 degrees Kelvin.";
    cout << "\nThe temperature can be stated and defined in three scales -";
    cout << "\nKelvin, Fahrenheit, and Celsius.  All temperatures scales are";
    cout << "\nstored as Kelvin and rounded to the hundreths decimal place.";
    
    cout << "\n\nEnter a temperature in Kelvin degrees to demonstrate: ";
    cin >> temperature;
    
    tempDemo.setTempKelvin(temperature);
    
    cout << "\nKelvin:\t\t" << tempDemo.getTempKelvin() << " K";
    cout << "\nFahrenheit:\t" << tempDemo.getTempFahrenheit() << " F";
    cout << "\nCelsius:\t" << tempDemo.getTempCelsius() << " C";
    
    cout << "\n\nNow enter a temperature in Fahrenheit degrees: ";
    cin >> temperature;
    
    tempDemo.setTempFahrenheit(temperature);
    
    cout << "\nKelvin:\t\t" << tempDemo.getTempKelvin() << " K";
    cout << "\nFahrenheit:\t" << tempDemo.getTempFahrenheit() << " F";
    cout << "\nCelsius:\t" << tempDemo.getTempCelsius() << " C";
    
    cout << "\n\nNow enter a temperature in Celsius degrees: ";
    cin >> temperature;
    
    tempDemo.setTempCelsius(temperature);
    
    cout << "\nKelvin:\t\t" << tempDemo.getTempKelvin() << " K";
    cout << "\nFahrenheit:\t" << tempDemo.getTempFahrenheit() << " F";
    cout << "\nCelsius:\t" << tempDemo.getTempCelsius() << " C";
    
    cout << "\n\nYour current temperature is still set to: "
         << tempDemo;
    cout << "\nFinally, enter a temperature in Fahrenheit degrees: ";
    cin >> tempDemo2;
    
    if(tempDemo == tempDemo2)
        cout << "\n\nThese temperatures are equal!";
    else
        cout << "\n\nThese temperatures are not equal!";
    
    /* End program message */
    cout << "\n\nThis concludes the demonstration.\n\n";
    
    return 0;
}

/* Constructor function */
Temperature::Temperature(double tempDegrees){
    setTempKelvin(tempDegrees);
}

/* Constructor function */
Temperature::Temperature(){
    setAbsZero();
}

/* Confirms tempKelvin is valid kelvin temperature and assigns to kelvin.
    Invalid temperatures are set to absolute zero (0). */
void Temperature::setTempKelvin(double tempKelvin){
    if(test_temp(tempRound(tempKelvin)))
        kelvin = tempRound(tempKelvin);
    else
        negKelvin();
    
    return;
}

/* Translates tempFahrenheit to kelvin and confirms if it is a valid kelvin 
    temperature and assigns to kelvin. Invalid temperatures are set to absolute 
    zero (0). */
void Temperature::setTempFahrenheit(double tempFahrenheit){
    setTempKelvin(tempRound(((5.0 / 9.0) * (tempFahrenheit - 32.0)) + 273.15));
    
    return;
}

/* Translates tempCelsius to kelvin and confirms if it is a valid kelvin 
    temperature and assigns to kelvin. Invalid temperatures are set to absolute 
    zero (0). */
void Temperature::setTempCelsius(double tempCelsius){
    setTempKelvin(tempRound(tempCelsius + 273.15));
    
    return;
}

/* Returns temperature in kelvin degrees */
double Temperature::getTempKelvin(){
    return kelvin;
}

/* Returns temperature in fahrenheit degrees */
double Temperature::getTempFahrenheit(){
    return (((getTempCelsius()) * (9.0 / 5.0)) + 32.0);
}

/* Returns temperature in celsius degrees */
double Temperature::getTempCelsius(){
    return (getTempKelvin() - 273.15);
}

/* Equivalency operator overload for two instance of Temperature class */
bool operator ==(const Temperature& temp1, 
                      const Temperature& temp2){
    return (temp1.kelvin == temp2.kelvin);
}

/* Input overload for accepting Fahrenheit temperature input from istream */
istream& operator >>(istream& inputStream, 
                            Temperature& temp){
    double tempIn = 0;
    
    inputStream >> tempIn;
    temp.setTempFahrenheit(tempIn);
    
    return inputStream;
}

/* Output overload to ostream of temperature in Fahrenheit */
ostream& operator <<(ostream& outputStream, 
                            Temperature& temp){
    outputStream << temp.getTempFahrenheit() << " F";
    
    return outputStream;
}

/* Display error message to user and set temperature to absolute zero (0) */
void Temperature::negKelvin(){
    outNegKelvinError();
    setAbsZero();
}

/* Display error message of temperature definition */
void Temperature::outNegKelvinError(){
    cout << "\n\nError in definition of temperature!";
    cout << "\nTemperature defaulted to 0 degrees Kelvin.\n\n";
    
    return;
}

/* Set temperature to absolute zero (0) */
void Temperature::setAbsZero(){
    kelvin = 0;
    
    return;
}

/* Test if temperature is less than absolute zero (0) */
bool Temperature::test_temp(double tempDegrees){
    if(tempDegrees >= 0)
        return true;
    else
        return false;
}

/* Returns temperature rounded to the hundreths decimal place */
double Temperature::tempRound(double tempDegrees){
    return (floor(((tempDegrees * 100) + 0.5) / 100));
}