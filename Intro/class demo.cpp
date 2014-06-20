/*****************************************************************************
 * Author:              Robert Kety
 * Date Created:        08/27/2013
 * Last Modified:       06/19/2014
 * Description:         Demonstrates the capabilities of the class, Function.  
 *                      The class Function is used primarily to represent a 
 *                      ratio of two integers.  Member functions include a 
 *                      function that returns the ratio in decimal terms (as 
 *                      type double) and a function that outputs the ratio 
 *                      fraction in lowest terms.
 * Input:               Numerator and denominator from user. Input for another
 *                      iteration of the main function.
 * Output:              Prompts for user input.  Display fraction in decimal
 *                      format. Display fraction as ratio in lowest terms.
 * Acknowledgements:    Assignment 6 instructions,
 *                      Absolute C++, Seventh Edition, Chapter 6, Exercise 5.
 ****************************************************************************/
 
#include <iostream>	/* Necessary for output */
#include <cstdlib>  /* Necessary for exit() */
#include <limits>	/* Included to allow clearing cin errors */
#include <string>	/* For use of strings */

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Fraction{
    public:
        /* Initialize numerator and denominator to arguments */
        Fraction(int nValue, int dValue);
        
        /* Initialize numerator and set denominator to 1 */
        Fraction(int nValue);
        
        /* Initialize numerator and denominator to 1 */
        Fraction();
        
        /* Prompt and populate numerator and denominator via user input */
        void input();
        
        /* Set numerator to value of argument */
        void set_numerator(int nValue);
        
        /* Set denominator to value of argument and test for zero */
        void set_denominator(int dValue);
        
        /* Return fraction in decimal format */
        double get_decimal();
        
        /* Determines lowest terms of ratio fraction and outputs to screen */
        void print_lowest_terms();
    
    private:
        int numerator;
        int denominator;      //Cannot be zero.
        
        /* Exits program if denominator is set to zero. */
        void test_denominator();
};

int main(){
    /* Variable Declarations */
    Fraction fract1;
    string runAgain = "y";
    
    /* Continual option to enter another fraction (for testing/grading 
     * purposes). */
    while((runAgain[0] == 'y') || (runAgain[0] == 'Y')){
        /* Prompt user to input numerator and denominator and assign to
         * private variables. */
        fract1.input();
    
        /* Display fraction in decimal format */
        cout << "\nThe result of your fraction is: " 
              << fract1.get_decimal() << ".";
        
        /* Display fraction as ratio in lowest terms */
        fract1.print_lowest_terms();
        
        cin.ignore(1000, '\n');     //Reset input stream for getline()
        /* Prompt for another iteration */
        cout << "\n\nWould you like to enter another ratio?\n";
        getline(cin, runAgain);
    }
    
    cout << endl;      //Extra white space for readability
    
    return 0;
}   //11 Lines of code

/* Initialize numerator and denominator to arguments */
Fraction::Fraction(int nValue, int dValue) : numerator (nValue), 
                                                            denominator (dValue){
    test_denominator();      //Protects against assignment of zero
}   //1 Line of code

/* Initialize numerator and set denominator to 1 */
Fraction::Fraction(int nValue) : numerator (nValue),
                                            denominator (1){
    /* Body intentionally empty */
}

/* Initialize numerator and denominator to 1 */
Fraction::Fraction() : numerator (1),
                              denominator (1){
    /* Body intentionally empty */
}

/* Prompt and populate numerator and denominator via user input */
void Fraction::input(){
    /* Variable declarations */
    int numerValue = 1, denominValue = 1;  //Default is 1
    
    cout << "\n\nEnter a numerator: ";
    
    /* Ensures integer input */
    while(!(cin >> numerValue)){
        // Clears error flag from non-number entry 
        cin.clear();
        
        // Move to next buffer line 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Prompt user for valid input 
        cout << "\nPlease enter an integer for the numerator: ";
    }
    
    set_numerator(numerValue);
    
    cout << "\nEnter a denominator: ";
    
    /* Ensures non-zero integer input */
    while(!(cin >> denominValue) || (denominValue == 0)){
        // Clears error flag from non-number entry 
        cin.clear();
        
        // Move to next buffer line 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Prompt user for valid input 
        cout << "\nPlease enter a non-zero integer for the denominator: ";
    }
    set_denominator(denominValue);
}   //13 Lines of code

/* Set numerator to value of argument */
void Fraction::set_numerator(int nValue){
    numerator = nValue;
}   //1 Line of code

/* Set denominator to value of argument and test for zero */
void Fraction::set_denominator(int dValue){
    denominator = dValue;
    test_denominator();      //Protects against assignment of 0
}   //2 Lines of code

/* Return fraction in decimal format */
double Fraction::get_decimal(){
    double decimalValue = (double) numerator / (double) denominator; 
    
    return decimalValue;
}   //2 Lines of code

/* Determines lowest terms of ratio fraction and outputs to screen */
void Fraction::print_lowest_terms(){
    /* Variable declaration */
    int lowestDivisor = 1;      //Default is 1
    
    /* Determine lowest divisor of numerator and denominator */
    if(abs(numerator) > abs(denominator))
        lowestDivisor = abs(denominator);
    else
        lowestDivisor = abs(numerator);
    
    /* Test all integers from lowest divisor to 1 for common divisor */
    for(int i = lowestDivisor; i > 1; i--)
        /* Divide numerator and denominator by common divisor */
        if(!(numerator % lowestDivisor) && !(denominator % lowestDivisor)){
            numerator /= lowestDivisor;
            denominator /= lowestDivisor;
        }
    
    /* Ensure numerator holds negative sign when only one divisor is
     * negative.  Ensure both divisors are positive when both are input as
     * negative.  This is for readability and consistency purposes.  */
    if(((numerator > 0) && (denominator < 0)) || 
        ((numerator < 0) && (denominator < 0))){
        numerator *= -1;
        denominator *= -1;
    }
    
    /* Output results to screen */
    cout << "\n\nYour fraction in lowest terms is: " << numerator << " / "
          << denominator << ".\n\n";
}   //13 Lines of code

/* Exits program if denominator is set to zero. */
void Fraction::test_denominator(){
    if(denominator == 0){
        cout << "\n\nIllegal denominator value!\n\n";
        exit(1);
    }
}   //3 Lines of code