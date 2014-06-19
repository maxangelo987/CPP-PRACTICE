/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/13/2013
 * Last Modified:    10/14/2013
 * Description:      Demonstrates the capabilities of the 'prime' class.  
 *                   The 'prime' class is used primarily to define hold an
 *                   unsigned integer that is a prime number.  Overloaded
 *                   increment and decrement operators allow class instance 
 *                   to increase or decrease to the next prime number.  The 
 *                   range of primes is constrained to the range of 1 to 
 *                   UINT_MAX.  Default prime number is 1.
 * Input:            User inputs a prime number (error checked).
 * Output:           Prompts for user input.  A demonstration of prefix and
 *                   postfix increment/decrement operations on the 'prime'
 *                   class.
 * Acknowledgements: Absolute C++, Seventh Edition
 ****************************************************************************/

#include <iostream>  /* Necessary for input/output */
#include <climits>   /* Necessary for UINT_MAX */
#include <cstdlib>   /* Necessary for abs() */

using std::cout;
using std::cin;
using std::ostream;
using std::istream;
using std::string;
using std::endl;

class prime{
   public:
      /* Default constructor sets prime to 1 */
      prime();
      /* Tests validity of userPrime and sets prime (invalid defaults to 1) */
      prime(unsigned int userPrime);
      
      /* Postfix Increment Operator Overload */
      friend const prime operator ++(prime& primeNum, int ignore);
      /* Postfix Decrement Operator Overload */
      friend const prime operator --(prime& primeNum, int ignore);
      /* Prefix Increment Operator Overload */
      friend const prime& operator ++(prime& primeNum);
      /* Prefix Decrement Operator Overload */
      friend const prime& operator --(prime& primeNum);
      
      /* Returns current value of prime stored in private variable 'current' */
      unsigned int get_prime() const;
      /* Tests validity of userPrime and sets prime (invalid defaults to 
         no change in private variable 'current') */
      void set_prime(unsigned int userPrime);      
      
      /* Overloaded operator handling output of overloaded class */
      friend ostream& operator <<(ostream& outputStream, const prime& primeNum);
      /* Overloaded operator handling input of prime class */
      friend istream& operator >>(istream& inputStream, prime& primeNum);
   private:
      unsigned int current;
      /* Verifies if testValue is a prime number */
      bool test_prime(unsigned int testValue);
};

int main(){
   prime userPrime;
   
   /* Prompt user for a prime number */
   cout << "\n\nPlease enter your prime number: ";
   cin >> userPrime;
   
   /* Demonstrate prefix/postfix increment/decrement of 'prime' class */
   cout << "\n\nPrefix Increment\nNext higher prime: " << ++userPrime
        << "\n'current' set to: " << userPrime;
   cout << "\n\nPrefix Decrement\nNext lower prime: " << --userPrime
        << "\n'current' set to: " << userPrime;
   cout << "\n\nPostfix Increment\n'current' set to: " << userPrime--
        << "\nNext lower prime: " << userPrime;
   cout << "\n\nPostfix Decrement\n'current' set to: " << userPrime++
        << "\nNext higher prime: " << userPrime;   
   
   cout << endl << endl;      //Additional whitespace for readability
   
   return 0;
}

/* Default constructor sets prime to 1 */
prime::prime():current(1){
   /* Intentionally Blank */
}

/* Tests validity of userPrime and sets prime (invalid defaults to 1) */
prime::prime(unsigned int userPrime){
   if(!(test_prime(userPrime))){
      cout << "\n\nNumber is not prime!\nDefaulting to 1.\n\n";
      current = 1;
   }
   else
      current = userPrime;
}

/* Postfix Increment Operator Overload */
const prime operator ++(prime& primeNum, int ignore){
   unsigned int tempPrime = primeNum.current;
   for(unsigned int i = primeNum.current + 1; i < UINT_MAX; i++)
      if(primeNum.test_prime(i)){
         primeNum.current = i;
         break;
      }
         
   return prime(tempPrime);
}

/* Postfix Decrement Operator Overload */
const prime operator --(prime& primeNum, int ignore){
   unsigned int tempPrime = primeNum.current;
   for(unsigned int i = primeNum.current - 1; i > 0; i--)
      if(primeNum.test_prime(i)){
         primeNum.current = i;
         break;
      }
   
   return prime(tempPrime);
}

/* Prefix Increment Operator Overload */
const prime& operator ++(prime& primeNum){
   for(unsigned int i = primeNum.current + 1; i < UINT_MAX; i++)
      if(primeNum.test_prime(i)){
         primeNum.set_prime(i);
         break;
      }
         
   return primeNum;
}

/* Prefix Decrement Operator Overload */
const prime& operator --(prime& primeNum){
   for(unsigned int i = primeNum.current - 1; i > 0; i--)
      if(primeNum.test_prime(i)){
         primeNum.set_prime(i);
         break;
      }
   
   return primeNum;
}

/* Returns current value of prime stored in private variable 'current' */
unsigned int prime::get_prime() const{
   return current;
}

/* Tests validity of userPrime and sets prime (invalid defaults to 
   no change in private variable 'current') */
void prime::set_prime(unsigned int userPrime){
   if(test_prime(userPrime))
      current = userPrime;
   else{
      cout << "\n\nNumber is not prime!\nDefaulting to 1.\n\n";
      current = 1;
   }
   return;
}

/* Verifies if testValue is a prime number */
bool prime::test_prime(unsigned int testValue){
   bool validPrime = true;
   
   for(unsigned int j = 2; j < testValue; j++)
      if(testValue % j == 0){
         validPrime = false;
         break;
      }
   
   return validPrime;
}

/* Overloaded operator handling output of prime class */
ostream& operator <<(ostream& outputStream, const prime& primeNum){
   outputStream << primeNum.get_prime();
   
   return outputStream;
}

/* Overloaded operator handling input of prime class */
istream& operator >>(istream& inputStream, prime& primeNum){
   string stringIn;
   unsigned int userInput = 1;
   
   inputStream >> stringIn;
   
   for(int i = 0; i < (int)stringIn.length(); i++)
      if(!(isdigit(stringIn[i])) && (stringIn[i] == '-')){
         cout << "\n\nNon-number input!\n\n";
         exit(1);
      }
   
   userInput = abs(atoi(stringIn.c_str()));
   
   primeNum.set_prime(userInput);
   
   return inputStream;
}