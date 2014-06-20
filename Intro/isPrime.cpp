/*****************************************************************************
 * Author:		        Robert Kety
 * Date Created:        07/27/2013
 * Last Modified:       06/19/2014
 * Description:         Determine if a whole number is prime.
 * Input:		        Whole number from user.
 * Output:		        Prompt for user input. Outputs confirmation of whether
 *			            the number is prime.
 * Acknowledgements:	Lab4
 ****************************************************************************/
#include <iostream>

#define PROMPT "\nPlease enter a whole number: "
#define NOT_PRIME "\nThe number is not a prime number.\n\n"
#define PRIME "\nThe number is a prime number.\n\n"
#define DONE 0 /* ends successful program */
#define FIRST_FACTOR 2 /* initial value in for loop */

using std::cout;
using std::cin;
using std::endl;

int main(){
    int i, 		/* loop counter */
    number; 	/* number provided by user */

    cout << PROMPT; /* prompt user */
    cin >> number; 	/* wait for user input */

    /* Prime numbers are defined as any number
     * greater than one that is only divisible
     * by one and itself. */
    for(i = FIRST_FACTOR; i < number; i++){
        if( number % i == 0 ){ /* if divisible */
            cout << NOT_PRIME; /* not prime */
            
            return DONE; /* exit program */
        }
    }

    /* If number is not divisible by any number
     * less than itself then it must be prime */
    cout << PRIME;

    return DONE; /* exit program */
}
