/*****************************************************************************
 * Author:              Robert Kety
 * Date Created:        07/31/2013
 * Last Modified:       08/01/2013
 * File Name:           Kety_function_fun.cpp
 * Description:         This program continuously prompts the user for two
 * 			positive integers.  When two positive integers are
 * 			entered, the program outputs a count from zero to 
 * 			the first number and then back down to zero.  Then,
 * 			the program performs a count from the first number
 * 			to the second.
 * Input:		A string response from the user, tested for validity
 * 			and separated into a string for each number.
 * 			A char response for repeating the program.
 * Output:		Prompts for user input.  Output count up from zero
 * 			to first number.  Output count down from first number
 * 			to zero.  Output count from first number to second
 * 			number.  Prompt user for another iteration.
 * Acknowledgements:	Lab5 Instructions
 ****************************************************************************/

#include <iostream>	/* For user input/output */
#include <limits>	/* Necessary for reset of cin error state */
#include <string>	/* Necessary for use of strings */
#include <cstdlib>	/* Necessary for atoi() */

using std::cout;
using std::endl;
using std::cin;
using std::string;

/* Outputs count from zero to argument in a single line */
void countFromZero(int numVar);

/* Outputs count from argument to zero in a single line */
void countToZero(int numVar);

/* Outputs count from first argument to second in a single line */
void countBetween(int numVar1, int numVar2);

/* Prompts user for two positive integers, confirms input is valid, and
 * returns each positive integer in string format to the arguments. */
void get_positive_int(string& numString1, string& numString2);

/* Tests string for the negative sign (i.e., '-'). Returns false if negative
 * sign is present in string. */
bool is_positive_int(string numString);

int main(){
   /* Variable declarations and definition */
   int firstNum = 0, secondNum = 0;
   string numString1, numString2;
   char runAgain = 'y';
   
   /* Loop driven by user response that repeats program until user quits */
   while((runAgain == 'y') || (runAgain == 'Y')){
      
      /* Old Code for Integer-based input. Included as proof of 
       * completion for step 1 of Lab5.
      
      cout << "\nPlease enter two positive integers: ";
      while((!(cin >> firstNum >> secondNum)) || 
	    (firstNum < 0) || 
	    (secondNum < 0)){
   	 
         // Clears error flag from non-number entry 
   	 cin.clear();
   	 
         // Move to next buffer line 
   	 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   	 
         // Prompt user for valid input 
   	 cout << "\nOne of those numbers is invalid.";
   	 cout << "\nPlease enter two positive integers: ";
      }
      */
      
      /* New code for string input */
      /* Loop driven by a test of user input for presence of negative sign
       * (i.e., '-'). */
      do{
	 get_positive_int(numString1, numString2);
      }while((!(is_positive_int(numString1))) ||
  	     (!(is_positive_int(numString2))));
	  
      /* Convert strings to integer type */
      firstNum = atoi(numString1.c_str());
      secondNum = atoi(numString2.c_str());

      /* Output count scenarios */
      countFromZero(firstNum);
      countToZero(firstNum);
      countBetween(firstNum, secondNum);

      /* Confirm user preference for another iteration of program */
      cout << "\n\nDo you want to run this again with 2 different "
	   << "positive integers? (y/n): ";
      cin >> runAgain;
      /* Reset cin to prevent input issues on next iteration */
      // Clears error flag from non-number entry 
      cin.clear();
      // Move to next buffer line 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   }

   return 0;
}

/* Outputs count from zero to argument in a single line */
void countFromZero(int numVar){
   for(int i = 0; i <= numVar; i++){
      cout << i << " ";
   }
   cout << endl;
}

/* Outputs count argument to zero in a single line */
void countToZero(int numVar){
   for(int i = 0; i <= numVar; i++){
      cout << numVar - i << " ";
   }
   cout << endl;
} 

/* Outputs count from first argument to second in a single line */
void countBetween(int numVar1, int numVar2){
   if(numVar1 < numVar2){
      for(int i = numVar1; i <= numVar2; i++){
	 cout << i << " ";
      }      
   }
   else{
      for(int i = 0; i <= (numVar1 - numVar2); i++){
	 cout << numVar1 - i << " ";
      }
   }
   cout << endl;
}

/* Prompts user for two positive integers, confirms input is valid, and
 * returns each positive integer in string format to the arguments. */
void get_positive_int(string& numString1, string& numString2){
   /* Variable declarations and definitions */
   int invalidInput = 0, charValue = 0;
   const int DECIMAL_CHAR_MIN = 48, 	//Decimal value for '0' character
	     DECIMAL_CHAR_MAX = 57, 	//Decimal value for '9' character
	     WHITESPACE_CHAR = 32;	//Decimal value for ' ' character
   string userString;
   
   /* Prompt user for input */
   cout << "\n\nType two positive integers, separated by"
        << " a space, and press enter: ";
   getline(cin, userString);
   
   /* Counts all non-number input and separates userString into two strings 
    * based on placement of ' ' in user input. */
   for(int i = 0; i < userString.size(); i++){
      charValue = userString.at(i);
      
      if((charValue < DECIMAL_CHAR_MIN) ||
         (charValue > DECIMAL_CHAR_MAX)){
	 invalidInput++;
      }

      if((charValue == WHITESPACE_CHAR) && (invalidInput == 1)){
	 numString1 = userString.substr(0, i);
	 numString2 = userString.substr(i + 1, userString.size());
      }
   }
   
   /* Sets both strings to negative if user input has more than one invalid
    * input character */
   if(invalidInput != 1){
      numString1 = "-";
      numString2 = "-";
   } 
   
}

/* Tests string for the negative sign (i.e., '-'). Returns false if negative
 * sign is present in string. */
bool is_positive_int(string numString){
   /* Variable declaration and definition */
   bool isPositive = true;
   
   /* Searches string for '-' character */
   for(int i = 0; i < numString.size(); i++){
      if(numString.at(i) == '-')
	 isPositive = false;
   }

   return isPositive;
}


