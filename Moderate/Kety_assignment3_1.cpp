/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/11/2013
 * Last Modified:    10/14/2013
 * Description:      Demonstrates the capabilities of the rational class.  
 *                   The rational class is used primarily to represent a 
 *                   ratio of two integers.  Private member functions ensures  
 *                   each ratio has a valid denominator, proper negative 
 *                   number assignment, and states the ratio in lowest terms.
 *                   Public members include default, single, and double 
 *                   argument constructors; overloaded operators, including 
 *                   boolean operators; and set/get functions for modifying
 *                   the numerator and denominator of each instance of the
 *                   rational function.
 * Input:            Numerator and denominator from user. Input for another
 *                   iteration of the main function.
 * Output:           Prompts for user input.  
 * Acknowledgements: CS 161, Assignment6,
 *                   Absolute C++, Seventh Edition
 ****************************************************************************/
 
#include <iostream>	/* Necessary for output */
#include <cstdlib>   /* Necessary for exit() */
#include <limits>	   /* Included to allow clearing cin errors */
#include <string>	   /* For use of strings */

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::istream;

class rational{
   public:
      /* Initialize numerator and denominator to arguments */
      rational(int nValue, int dValue);
      
      /* Initialize numerator and set denominator to 1 */
      rational(int wholeNumber);
      
      /* Initialize numerator to 0 and denominator to 1 */
      rational();
      
      /* Set numerator to value of argument */
      void set_numerator(int nValue);
      
      /* Set denominator to value of argument and test for zero */
      void set_denominator(int dValue);
      
      /* Return numerator */
      int getNumerator() const;
      
      /* Return denominator */
      int getDenominator() const;
      
      /* Overloaded operators including boolean operators for rational class */
      friend const rational operator +(const rational& ratio1, 
                                       const rational& ratio2);
      friend const rational operator -(const rational& ratio1, 
                                       const rational& ratio2);
      friend const rational operator *(const rational& ratio1, 
                                       const rational& ratio2);
      friend const rational operator /(const rational& ratio1, 
                                       const rational& ratio2);
      friend const rational operator -(const rational& ratio);
      friend const rational operator ++(rational& ratio);
      friend const rational operator --(rational& ratio);
      friend const rational operator ++(rational& ratio, int ignore);
      friend const rational operator --(rational& ratio, int ignore);
      friend bool operator ==(const rational& ratio1, const rational& ratio2);
      friend bool operator >(const rational& ratio1, const rational& ratio2);
      friend bool operator <(const rational& ratio1, const rational& ratio2);
      friend bool operator >=(const rational& ratio1, const rational& ratio2);
      friend bool operator <=(const rational& ratio1, const rational& ratio2);
      
      /* Overloaded operators handling input/output of rational class */
      friend istream& operator >>(istream& inputStream, rational& ratio);
      friend ostream& operator <<(ostream& outputStream, const rational& ratio);

   private:
      int numerator;
      int denominator;     //Cannot be zero.
      
      /* Determines lowest terms of rational */
      void lowest_terms();
      
      /* Manages negative numerators and denominators */
      void negative_ratio();
      
      /* Exits program if denominator is set to zero. */
      void test_denominator();
};

int main(){
   /* Variable Declarations */
   rational fract1, fract2(-20, 100), fract3(-16, -40);  //fract3 != 0
   string runAgain = "y";
   
   /* Continual option to enter another fraction (for testing/grading 
    * purposes). */
   while((runAgain[0] == 'y') || (runAgain[0] == 'Y')){
      /* Prompt user to input numerator and denominator and assign to
       * private variables. */
      cout << "\nPlease enter ratio as two integers separated by '/' : ";
      cin >> fract1;
      
      cout << "\n\nConfirmation of initialization:\n";
      cout << "Ratio 1\tRatio2\tRatio3\n";
      cout << fract1 << '\t' 
           << fract2 << '\t' 
           << fract3 << endl;
      
      cout << "\nRatio 2 + Ratio 3 =\n";
      cout << fract2 + fract3 << endl;
      cout << "Ratio 2 - Ratio 3 =\n";
      cout << fract2 - fract3 << endl;
      cout << "Ratio 2 * Ratio 3 =\n";
      cout << fract2 * fract3 << endl;
      cout << "Ratio 2 / Ratio 3 =\n";
      cout << fract2 / fract3 << endl;
      
      cout << "\nNegation of Ratio 1\n";
      cout << -fract1 << endl;
      
      cout << "\nPrefix increment of Ratio 1:\n";
      cout << ++fract1 << '\t' << fract1 << '\n'; 
      cout << "Prefix decrement of Ratio 1:\n";
      cout << --fract1 << '\t' << fract1 << '\n';
      cout << "Postfix decrement of Ratio 1:\n";
      cout << fract1-- << '\t' << fract1 << '\n';
      cout << "Postfix increment of Ratio 1:\n";
      cout << fract1++ << '\t' << fract1 << '\n';
      
      cout << "\nRatio 2 > Ratio 3:\n";
      cout << (fract2 > fract3) << endl;
      cout << "Ratio 2 < Ratio 3:\n";
      cout << (fract2 < fract3) << endl;
      cout << "Ratio 2 >= Ratio 3:\n";
      cout << (fract2 >= fract3) << endl;
      cout << "Ratio 2 <= Ratio 3:\n";
      cout << (fract2 <= fract3) << endl;
      cout << "Ratio 2 == Ratio 3:\n";
      cout << (fract2 == fract3) << endl;
      
      cin.ignore(1000, '\n');    //Reset input stream for getline()
      /* Prompt for another iteration */
      cout << "\n\nWould you like to enter another ratio?\n";
      getline(cin, runAgain);
   }
   
   cout << endl;     //Extra white space for readability
   
   return 0;
}

/* Initialize numerator and denominator to arguments */
rational::rational(int nValue, int dValue){
   numerator = nValue;
   denominator = dValue;
   test_denominator();     //Protects against assignment of zero
   negative_ratio();       //Manages negative ratios
   lowest_terms();         //Ensures ratio is stated in lowest terms
}

/* Initialize numerator and set denominator to 1 */
rational::rational(int wholeNumber) : numerator (wholeNumber),
                                 denominator (1){
   /* Body intentionally empty */
}

/* Initialize numerator and denominator to 1 */
rational::rational() : numerator (0),
                       denominator (1){
   /* Body intentionally empty */
}

/* Set numerator to value of argument */
void rational::set_numerator(int nValue){
   numerator = nValue;
}

/* Set denominator to value of argument and test for zero */
void rational::set_denominator(int dValue){
   denominator = dValue;
   test_denominator();     //Protects against assignment of 0
}

/* Return numerator */
int rational::getNumerator() const{
   return numerator;
}
      
/* Return denominator */
int rational::getDenominator() const{
   return denominator;
}

/* Determines lowest terms of rational */
void rational::lowest_terms(){
   /* Variable declaration */
   int lowestDivisor = 1;     //Default is 1
   /* Determine lowest divisor of numerator and denominator */
   if(abs(numerator) > abs(denominator))
      lowestDivisor = abs(denominator);
   else
      lowestDivisor = abs(numerator);
   
   /* Test all integers from lowest divisor to 1 for common divisor */
   for(int i = lowestDivisor; i > 1; i--)
      /* Divide numerator and denominator by common divisor */
      if(!(numerator % i) && !(denominator % i)){
         numerator /= i;
         denominator /= i;
      }
}

/* Manages negative numerators and denominators */
void rational::negative_ratio(){
   if(((numerator <= 0) && (denominator <= 0)) ||
      ((numerator >= 0) && (denominator <= 0))){
      numerator = numerator * -1;
      denominator = denominator * -1;
   }  
}

/* Exits program if denominator is set to zero. */
void rational::test_denominator(){
   if(denominator == 0){
      cout << "\n\nIllegal denominator value!\n\n";
      exit(1);
   }
}

/* Overloaded operators including boolean operators for rational class */
const rational operator +(const rational& ratio1, const rational& ratio2){
   int commonDenom = ratio1.getDenominator() * ratio2.getDenominator();
   int numerator1 = ratio1.getNumerator() * ratio2.getDenominator();
   int numerator2 = ratio2.getNumerator() * ratio1.getDenominator();
   rational commonTermRatio((numerator1 + numerator2), commonDenom);
   
   return commonTermRatio;
}

const rational operator -(const rational& ratio1, const rational& ratio2){
   int commonDenom = ratio1.getDenominator() * ratio2.getDenominator();
   int numerator1 = ratio1.getNumerator() * ratio2.getDenominator();
   int numerator2 = ratio2.getNumerator() * ratio1.getDenominator();
   int nValue = 0;
   
   if(numerator1 > numerator2)
      nValue = numerator1 - numerator2;
   else
      nValue = numerator2 - numerator1;

   rational commonTermRatio(nValue, commonDenom);
   
   return commonTermRatio;
}

const rational operator *(const rational& ratio1, const rational& ratio2){
   int nValue = ratio1.getNumerator() * ratio2.getNumerator();
   int dValue = ratio1.getDenominator() * ratio2.getDenominator();
   rational ratioProduct(nValue, dValue);
   
   return ratioProduct;
}

const rational operator /(const rational& ratio1, const rational& ratio2){
   int nValue = ratio1.getNumerator() * ratio2.getDenominator();
   int dValue = ratio2.getNumerator() * ratio1.getDenominator();
   rational ratioDivision(nValue, dValue);
   
   return ratioDivision;
}

const rational operator -(const rational& ratio){
   return rational((ratio.getNumerator() * -1), ratio.getDenominator());
}

const rational operator ++(rational& ratio){
   ratio.numerator += ratio.denominator;
   
   return ratio;
}

const rational operator --(rational& ratio){
   ratio.numerator -= ratio.denominator;
   
   return ratio;
}

const rational operator ++(rational& ratio, int ignore){
   int tempNumerator = ratio.numerator;
   int tempDenominator = ratio.denominator;
   
   ratio.numerator += ratio.denominator;
   
   return rational(tempNumerator, tempDenominator);
}

const rational operator --(rational& ratio, int ignore){
   int tempNumerator = ratio.numerator;
   int tempDenominator = ratio.denominator;
   
   ratio.numerator -= ratio.denominator;
   
   return rational(tempNumerator, tempDenominator);
}

bool operator ==(const rational& ratio1, const rational& ratio2){
   return ((ratio1.getNumerator() * ratio2.getDenominator()) ==
           (ratio2.getNumerator() * ratio1.getDenominator()));
}

bool operator >(const rational& ratio1, const rational& ratio2){
   bool greaterThan = false;
   
   if((ratio1.getNumerator() * ratio2.getDenominator()) > 
      (ratio1.getDenominator() * ratio2.getNumerator()))
      greaterThan = true;
   
   return greaterThan;
}

bool operator <(const rational& ratio1, const rational& ratio2){
   return (ratio2 > ratio1);
}

bool operator >=(const rational& ratio1, const rational& ratio2){
   return ((ratio1 > ratio2) || (ratio1 == ratio2));
}

bool operator <=(const rational& ratio1, const rational& ratio2){
   return (ratio2 >= ratio1);
}

/* Overloaded operators handling input of rational class 
   Protects against non-number input (besides '-' and '/') */
istream& operator >>(istream& inputStream, rational& ratio){
   string stringIn, nString, dString;
   int divLocation = -1, nValue = 0, dValue = 1;
   
   inputStream >> stringIn;
   
   for(int i = 0; i < (int)stringIn.length(); i++){
      if(stringIn[i] == '/'){
         divLocation = i;
         break;
      }
      if((!(isdigit(stringIn[i]))) && 
         ((stringIn[i] != '-') && 
          (stringIn[i] != '/'))){
         cout << "\n\nNon-number input!\n\n";
         exit(1);
      }
   }
   
   if(divLocation < 0)
      nString = stringIn.c_str();
   else{
      nString = stringIn.substr(0, divLocation);
      dString = stringIn.substr(divLocation + 1);
      dValue = atoi(dString.c_str());
   }
   
   nValue = atoi(nString.c_str());
   
   rational tempRatio(nValue, dValue);
   ratio = tempRatio;
   
   return inputStream;
}

/* Overloaded operators handling output of rational class */
ostream& operator <<(ostream& outputStream, const rational& ratio){
   outputStream << ratio.getNumerator() << '/' << ratio.getDenominator();
   
   return outputStream;
}