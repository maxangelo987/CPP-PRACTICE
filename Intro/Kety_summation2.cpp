/******************************************************************************
 * Author:              Robert Kety
 * Date Created:        07/27/2013
 * Last Modified:       07/27/2013
 * File Name:           Kety_summation2.cpp
 * Description:         Calculate the summation of f(x) = x^5 + 10 for all
 *                      values of x from 1 to n, where n is input from the
 *                      user and less than 73. Use a function to calculate
 *                      using each loop type.
 * Input:		Selection of for- or while-loop calculation (1 or 2,
 * 			respectively). Definition of the summation limit in a
 * 			range between 1 and 73. Response for running the
 * 			program again (i.e., 'n' or 'N' to stop).
 * Output:		Prompts for user input. Error handling prompts for
 * 			nonnumber and out-of-range input. Description of 
 * 			calculation performed and the result.
 * Acknowledgements:	Lab4
 * ***************************************************************************/

#include <iostream>	/* For user input/output */
#include <cmath>	/* For pow function */
#include <limits>	/* Necessary for reset of cin error state */

/* The power of x in the function f(x) = x^5 + 10 */ 
#define FUNCTION_POWER 5
/* The addition of 10 in the function f(x) = x^5 + 10 */
#define FUNCTION_INCREASE 10

using std::cout;
using std::cin;
using std::endl;
using std::pow;

long long int forLoopCalc(int summationLimitVariable);
long long int whileLoopCalc(int summationLimitVariable);

int main(){
   char		/* Initialize at valid loop driver value */
   		runAgain = 'y';	
   int		/* Controls if calculation will be for- or while-loop, 
		   based on user input, initialized to 1 (for-loop) */	
		forOrWhile = 1,
		/* Initializes value for n in summation notation where 
		   1 <= n <= 73. n cannot exceed 73 due to overflow.  
		   This variable is controlled by user input */
		summationLimit = 1;
   long long int	/* Variable for the sum of f(x) = x^5 + 10 for all
			   values of x where 1 <= x <= summationLimit */ 
      			summationTotal = 0;	
   
   while(!(runAgain == 'n') && !(runAgain == 'N')){
      /* Reset variables to default definitions */
      forOrWhile = 1;	
      summationLimit = 1;	

      /* Prompt user for initial input of loop type (i.e., for or while) */
      cout << "\n\nWelcome to the summation calculator for the function f(x) ="
	   << " x^5 + 10\n";
      cout << "Would you like to calculate using a for-loop or while-loop?\n";
      cout << "Enter 1 for for-loop or 2 for while-loop: ";
      /* Prevents non-number input and input out-of-range */
      while((!(cin >> forOrWhile)) || (forOrWhile > 2) || (forOrWhile < 1)){
         /* Clears error flag from non-number entry */
	 cin.clear();
	 /* Move to next buffer line */	 
	 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	 /* Prompt for corrected input */
         cout << "\nThat's not a 1 or a 2.\n";
	 cout << "Please enter 1 for a for-loop or 2 for a while-loop: ";
      }
      
      /* Prompt user for summationLimit for summary calculation */
      cout << "\nPlease enter the limit for this summation calculation.\n";
      cout << "Where Sigma of 1 <= x <= n, and n cannot be greater than 73, "
	   << "please enter the value for n: ";
      /* Prevents non-number input and input out-of-range */
      while(
	    (!(cin >> summationLimit)) || 
	    (summationLimit < 1) || 
	    (summationLimit > 73)){	
         /* Clears error flag from non-number entry */
         cin.clear();
	 /* Move to next buffer line */	 
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	 /* Prompt for corrected input */
         cout << "\nThat's not a number from 1 to 73.\n";
	 cout << "Where Sigma of 1 <= x <= n, and n cannot be greater than 73,"
	      << " please enter the value for n: ";
      }
      /* Conditionals controlling if calculation is executed through for- or
         while-loop */
      if(forOrWhile == 1)
	 summationTotal = forLoopCalc(summationLimit);
      else if(forOrWhile == 2)
	 summationTotal = whileLoopCalc(summationLimit);
      else	//Output for unexpected result in forOrWhile variable
	 cout << "\nError in input for choice of for- or while-loop\n\n";
      
      /* Output calculation results */
      cout << "According to my calculations, where Sigma of 1 <= x <= "
	   << summationLimit
	   << ", x^"
	   << FUNCTION_POWER
	   << " + "
	   << FUNCTION_INCREASE
	   << " = "
	   << summationTotal
	   << endl << endl;
      
      /* Prompt user to calculate a different summation limit */
      cout << "That was fun! I'd be happy to calculate another.\n";
      cout << "Type anything to continue or n to stop: ";
      cin >> runAgain;
   }

   return 0;
}

long long int forLoopCalc(int summationLimitVariable){
   /* Initializes total */
   long long int summationTotal = 0;
   
   /* for-loop method of calculation */
   for(
     	 int forLoopDriver = 1; 
	 forLoopDriver <= summationLimitVariable; 
	 forLoopDriver++){
      summationTotal += (int)pow((float)forLoopDriver, FUNCTION_POWER);
      summationTotal += FUNCTION_INCREASE;
   }
  
   return (summationTotal);
}

long long int whileLoopCalc(int summationLimitVariable){
   /* Initializes totsl */
   long long int summationTotal = 0;
   /* Initializes loop driver */
   int whileLoopDriver = 1;

   /* while-loop method of calculation */
   while(whileLoopDriver <= summationLimitVariable){
      summationTotal += (int)pow((float)whileLoopDriver, FUNCTION_POWER);
      summationTotal += FUNCTION_INCREASE;
      whileLoopDriver++; //Iteration of loop driver
   }

   return (summationTotal);
}
