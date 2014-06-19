/*****************************************************************************
 * Author:              Robert Kety
 * Date Created:        08/08/2013
 * Last Modified:       08/08/2013
 * File Name:           Kety_assignment4.cpp
 * Description:         Program offers to either reverse a string or determine
 *			if a string is a palindrome.  Based on user
 *			preference, the program will accept a string from the
 *			user and execute a reversal of the string or output
 *			a determination of palindrome for the string.  The
 *			program repeats until user inputs exit option.
 * Input:		User input for function preference and a string to be 
 *			evaluated.
 * Output:		Prompts for user input. Conditional output based on 
 *			function preference; either a reversed string or 
 *			confirmation on whether string is or is not a 
 *			palindrome.
 * Acknowledgements:	Assignment4 Instructions.
 ****************************************************************************/
 
#include <iostream>	/* For user input/output */
#include <limits>	/* Necessary for reset of cin error state */
#include <string>	/* For use of strings */
#include <cctype>	/* For char manipulations */

using std::cout;
using std::cin;
using std::string;
using std::getline;
using std::endl;

/* Returns string with elements in reverse order from parameter string.
 * Preconditions: 	#include <string> and using std::string, and string
 *			parameter. 
 * Post-condition:	Returns transformed string. */
string reverse_string(string forwardString);

/* Determines if a string is a palindrome. Redirects to palindromeTest
 * function to adhere to design document requirements.
 * Preconditions:	#include <string> and using std::string, string
 *					parameter, reverse_string function and palindromeTest
 *					function(and inherited preconditions).
 * Post-condition:	Return true if two string parameters are equal.
 *			Return false otherwise. */
bool is_palindrome(string stringVar);

/* Determines if two strings are equal for the purpose of determining
 * a palindrome.
 * Preconditions:	#include <string> and using std::string, #include 
 *			<iostream> and using std::cout, normal string
 *			parameter, reversed string parameter, lowerString and 
 *			removePunct functions (and inherited preconditions).
 * Post-condition:	Return true if two string parameters are equal.
 *			Return false otherwise. */
bool palindromeTest(string forwardString, string reversedString);

/* Transform all characters in a string to lower case
 * Preconditions:	#include <string> and using std::string, #include 
 *			<cctype>, and pass by reference string parameter. 
 * Post-condition:	Referenced string has all lower case letters. */
void lowerString(string& mixedCaseStr);

/* Remove all punctuation in a string and resize string to new length
 * Preconditions:	#include <string> and using std::string, #include 
 *			<cctype>, and pass by reference string parameter. 
 * Post-condition:	Referenced string has no punctuation and no undefined
 *			elements */
void removePunct(string& punctuatedStr);

int main(){
   /* Variable declarations */
   int functionChoice;
   string userString;
   
   /* Repeats program until user enters quit option */
   do{
      /* Prompt user for function preference or quit */
      cout << "\n\nDo you want to reverse a string, check if it is a "
           << "palindrome, or quit?\n";
      cout << "(Press 1 for reverse, 2 for palindrome, and anything else to"
           << " quit): ";
      if(cin >> functionChoice){
	 /* Move to next line in preparation for getline() input */
         cin.ignore(1000, '\n');
		 
         /* Prompt user for string */
	 cout << "\nEnter your string: ";
	 getline(cin, userString);

         /* Reverse String function */
	 if(functionChoice == 1){
	    cout << "\nReversed String: "
	         << reverse_string(userString)
	         << endl;
         }
	 /* Palindrome function */
	 if(functionChoice == 2){
	    if(is_palindrome(userString))
	       cout << "\nYou have entered a palindrome!!!\n\n";
	    else
	       cout << "\nThis is not a palindrome.\n\n";
         }
      }
      /* Handles non-number input to int variable functionChoice */
      else{
         /* Clears error flag from non-number entry */
         cin.clear();
         /* Move to next buffer line */	 
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	 /* Set functionChoice to end loop condition */
	 functionChoice -= functionChoice;
      } 
   }while((functionChoice == 1) || (functionChoice == 2));
   
   /* Formatting preference for end of program */
   cout << endl << endl;
   
   return 0;
}

/* Returns string with elements in reverse order from parameter string.
 * Preconditions: 	#include <string> and using std::string, and string
 *			parameter. 
 * Post-condition:	Returns transformed string. */
string reverse_string(string forwardString){
   /* Variable declarations */
   string localString;
   int strLength = forwardString.length();
   
   /* Base condition to prevent infinite recursion */
   if(strLength == 1)
      return forwardString;
   else{
      localString = forwardString.at(strLength - 1);
      /* Recursive return statement creates concatenation of multiple one 
       * element strings */
      return (localString + reverse_string(forwardString.substr(0, strLength - 1)));
   }
}

bool is_palindrome(string stringVar){
	return palindromeTest(stringVar, reverse_string(stringVar));
}

/* Determines if two strings are equal for the purpose of determining
 * a palindrome.
 * Preconditions:	#include <string> and using std::string, #include 
 *			<iostream> and using std::cout, normal string
 *			parameter, reversed string parameter, lowerString and 
 *			removePunct functions (and inherited preconditions).
 * Post-condition:	Return true if two string parameters are equal.
 *			Return false otherwise. */
bool palindromeTest(string forwardString, string reversedString){
   /* Variable declarations */
   int forStrLength, backStrLength;
   string strFor = forwardString, 
          strBack = reversedString;
   
   /* Transform strings to lower case */
   lowerString(strFor);
   lowerString(strBack);
   
   /* Transform strings to remove punctuation */
   removePunct(strFor);
   removePunct(strBack);
   
   /* Define string lengths to variables after transformations */
   forStrLength = strFor.length();
   backStrLength = strBack.length();
   
   if(forStrLength == backStrLength){
      /* Base Case 1: When a string has only one element, it is a 
       * palindrome */
      if (forStrLength == 0)
         return true;
      /* Base Case 2: When the first element of a forward and backward string
       * are not equivalent, then the entire string is not a palindrome. */
      else if (strFor.at(forStrLength - 1) != strBack.at(backStrLength - 1))
	 return false;
      /* Recursive return creates intersection of nth booleans to determine 
       * if a string is a palindrome.  One false recursive statement
       * invalidates the entire string */
      else
	 return (true && palindromeTest(strFor.substr(0, forStrLength - 1), 
	                                strBack.substr(0, backStrLength - 1)
				       ));
   }
   /* Error handling for string length inequality */
   else{
      cout << "\n\nError in string reversal length\n\n";
      return 0;
   }
}

/* Transform all characters in a string to lower case
 * Preconditions:	#include <string> and using std::string, #include 
 *			<cctype>, and pass by reference string parameter. 
 * Post-condition:	Referenced string has all lower case letters. */
void lowerString(string& mixedCaseStr){
   /* Transform all elements in string to lower case */
   for(int i = 0; i < mixedCaseStr.length(); i++)
      mixedCaseStr.at(i) = tolower(mixedCaseStr.at(i));
}

/* Remove all punctuation in a string and resize string to new length
 * Preconditions:	#include <string> and using std::string, #include 
 *			<cctype>, and pass by reference string parameter. 
 * Post-condition:	Referenced string has no punctuation and no undefined
 *			elements */
void removePunct(string& punctuatedStr){
   for(int i = 0; i < punctuatedStr.length(); i++){
      /* Determine if char at location i is punctuation and then remove it 
       * from the string */
      if(ispunct(punctuatedStr.at(i))){
	 punctuatedStr = punctuatedStr.substr(0, i) + 
	                 punctuatedStr.substr(i + 1, punctuatedStr.length());
         i--;
      }
   }
}
