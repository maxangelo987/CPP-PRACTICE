/*****************************************************************************
 *	Author:		Robert Kety
 *	Date Created:	07/12/2013
 *	Last Modified:	07/14/2013
 *	File Name:	Kety_rand_numbers2.cpp
 *	Description:	The program attempts to guess a number from 0 to 50.  
 *			The user has the option to verify the accuracy of 
 *			guesses made by the program.  The guessing strategy 
 *			for the program is to guess the midpoint for each 
 *			range of remaining options.  The fifth guess is a 
 *			random selection of the remaining options.  Program 
 *			also controls the fairness of guess verification made 
 *			by the user.
 *	Input:		A random number provided by the user from 0 to 50. 
 *			confirmation of verification, playing again, and guess
 *			accuracy (conditions permitting). 
 *	Output:		Prompts for input of random number, prompts for user
 *			preference to verify accuracy, each guess, 
 *			verification of guess accuracy (conditions permitting), 
 *			success/failure	confirmation, early termination 
 *			messages, and prompts for playing again.
 *	Acknowledgments:
 *			Sharon Davis 
 *				For providing feedback during my design	phase.
 *				Specifically, for allowing me to enhance my 
 *				program	beyond the assignment guidelines.
 *			Eric Anderson and Jennifer Wolfe
 *				For being the first to mention the low accuracy
 *				of the midpoint strategy in five guesses.  This 
 *				simple realization inspired me to code the 
 *				random element that increases accuracy to the 
 *				point where the program can actually respond 
 *				for all numbers 0 to 50.
 *			Notepad++
 *				For being much easier to use than vim for the 
 *				initial	drafting of code :^)
 ****************************************************************************/

#include <iostream> 	/* Included for cout and cin */
#include <ctime> 	/* Included for time() */
#include <cstdlib> 	/* Included for rand() and srand() */
#include <limits>	/* Included to allow clearing cin errors */
#include <cmath>	/* Included for pow function */

using std::cout;
using std::cin;

int main() {
   int 	firstGuess = 25,
	nextGuess, 
	currentGuess, 
	lastGuess, 
	guessCeiling = 50,	/* Highest possible guess in range */
	guessFloor = 0,		/* Lowest possible guess in range */
	fourthGuessCeiling = 46,/* Highest possible guess in four guesses */
	fourthGuessFloor = 4,	/* Lowest possible guess in four guesses */
	guessLow = 1,		/* Value for a guess that is too low */
	guessPerfect = 2,	/* Value for a perfect guess */
	guessHigh = 3,		/* Value for a guess that is too high */
	guessCount, 		/* Loop drive for 5 guess for loop */
	exitGuessCountLoop = 6,	/* This value will stop the guessCount loop */
	guessVariance, 		/* Control variable for high/low/perfect */
	randomGuess,		/* Random number for modifying guess */
	randomInt = -1, 	/* User's random integer input. Default is -1 */
	strikes = 3;		/* Number of inaccurate responses allowed by user */
   const int 	inaccurateResponse = 1,	/* Each inaccurate response is equivalent
					   to 1 strike */
   		fairGame = 0;	/* Number of inaccurate responses in a fair 
				   game */
   char runAgain = 'y', userVerifies = 'y';
   bool validResponse;

   srand(time(NULL)); 	/*seeds random number generator. Do this just once */

   while(runAgain == 'y'){
      /* Reset User's random integer */
      randomInt = -1;
      /* Reset first guess for new game */
      currentGuess = firstGuess;
      lastGuess = guessCeiling;
      /* Retrieve the random number from the user */
      do{
	 cout << "Enter a number from 0 to 50:\n";
	 validResponse = (cin >> randomInt);
	 /* Clears error and buffer */
	 if (!(validResponse)){
	    cin.clear();
	    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	 }
	 if ((randomInt < guessFloor) || (randomInt > guessCeiling))
	    cout << "That's not a number from 0 to 50!\n";
      } while (
	    (!(validResponse)) || 
	    (randomInt < guessFloor) || 
	    (randomInt > guessCeiling)
	    );
      /* Prompt user if they want the option to verify high/low/perfect */
      cout << "Will you be verifying my guesses? (y/n)\n";
      cin >> userVerifies;
      /* Initial guess output will always be 25 */
      cout << "My first guess is 25.\n";
      /* Loop for a maximum of 5 guesses */
      for (guessCount = 1; guessCount < 6; guessCount++){
	 /* Computer controlled guess verification */
	 if (!(userVerifies == 'y')){	
	    if (currentGuess < randomInt)
	       guessVariance = guessLow;	//Guess is low
	    else if (currentGuess == randomInt)
	       guessVariance = guessPerfect;	//Guess is perfect
	    else if (currentGuess > randomInt)
	       guessVariance = guessHigh;	//Guess is high
	 }
	 else {		
	    /* Prompt user for valid guess verification */
	    do{
	       cout << "Enter 1 for too low, 2 for perfect, "
		    << "3 for too high.\n";
	       validResponse = (cin >> guessVariance);
	       /* Clears error and buffer */
	       if (!(validResponse)){
		  cin.clear();
		  cin.ignore(
			std::numeric_limits<std::streamsize>::max(), '\n'
			);
	       }
	       if ((guessVariance < guessLow) && (guessVariance > guessHigh))
		  cout << "That's not a valid response!\n";
	       /* Inaccurate user input tracked to fairGame variable */
	       else if ((guessVariance == guessLow) && 
		     (!(currentGuess < randomInt))){
		  strikes -= inaccurateResponse;
		  if (currentGuess == randomInt)
		     strikes -= exitGuessCountLoop;		//Ensures strikes < fairGame
	       }
	       else if ((guessVariance == guessPerfect) && 
		     (!(currentGuess == randomInt)))
		  strikes -= exitGuessCountLoop;		//Ensures strikes < fairGame
	       else if ((guessVariance == guessHigh) && 
		     (!(currentGuess > randomInt))){
		  strikes -= inaccurateResponse;
		  if (currentGuess == randomInt)
		     strikes -= exitGuessCountLoop;		//Ensures fairGame is negative
	       }
	    } while (!(validResponse) || 
		  (guessVariance < guessLow) || 
		  (guessVariance > guessHigh));
	 }
	 /* Conditional controlling response to high/low/perfect */
	 switch (guessVariance){
	    case(1):		//Guess is too low
	       nextGuess = std::abs((float)(lastGuess - currentGuess));
	       nextGuess /= 2;
	       nextGuess += currentGuess;
	       /* 5th guess random adjustment ensures that any number 0 to 
		  50 is a possible guess */
	       if (guessCount == 4){
		  /* Adds capability of guesses 47 through 50 */
		  if (currentGuess == fourthGuessCeiling){
		     randomGuess = (rand() % 4);
		     nextGuess += randomGuess;
		  } 
		  /* Adds capability of every guess between 4 and 46 */
		  else{
		     randomGuess = (rand() % 2);
		     nextGuess += randomGuess;
		  }
	       }
	       /* Redefines guess variables for next loop iteration */
	       lastGuess = currentGuess;
	       currentGuess = nextGuess;
	       /* Informs user of computer controlled guess verification */
	       if (!(userVerifies == 'y'))
		  cout << lastGuess << " is too low!\n";
	       /* Ends program if user guess verification is inaccurate */
	       else if (strikes <= fairGame){
		  cout << "If you're not going to play fair, "
		       << "I don't want to play.\n\n";
		  guessCount = exitGuessCountLoop;
		  runAgain = 'n';
	       }
	       break;
	    case(2):		//Guess is perfect
	       /* Informs user of computer controlled guess verification */
	       if (!(userVerifies == 'y'))
	       cout << currentGuess << "? ";
	       /* Ends program if user guess verification is inaccurate */
	       if (strikes <= fairGame){
		  cout << "If you're not going to play fair, "
		       << "I don't want to play.\n\n";
		  guessCount = exitGuessCountLoop;
		  runAgain = 'n';
	       } else{	//Confirms success and prompts to reiterate game
		  cout << "I knew it!\n\n";					 
		  guessCount = exitGuessCountLoop;
		  cout << "Want to play again?i (y/n)\n";
		  cin >> runAgain;
	       }
	       break;
	    case(3):		//Guess is too high
	       nextGuess = std::abs((float)(currentGuess - lastGuess));
	       nextGuess = (int)(nextGuess / 2);
	       nextGuess = currentGuess - nextGuess;
	       /* A 5th guess random adjustment ensures that any number  
		  0 to 50 is a possible guess */
	       if (guessCount == 4){
		  /* Adds capability of guesses 0 through 3 */
		  if (currentGuess == fourthGuessFloor){
		     randomGuess = (rand() % 4);
		     nextGuess -= randomGuess;
		  } 
		  /* Adds capability of every guess between 4 and 46 */
		  else{
		     randomGuess = (rand() % 2);
		     nextGuess -= randomGuess;
		  }
	       }
	       /* Redefines guess variables for next loop iteration */
	       lastGuess = currentGuess;
	       currentGuess = nextGuess;
	       /* Informs user of computer controlled guess verification */
	       if (!(userVerifies == 'y'))
		  cout << lastGuess << " is too high!\n";
	       /* Ends program if user guess verification is inaccurate */
	       else if (strikes <= fairGame){
		  cout << "If you're not going to play fair, "
		       << "I don't want to play.\n\n";
		  guessCount = exitGuessCountLoop;	
		  runAgain = 'n';
	       }
	       break;
	    default:
	       /* Unexpected error handling guessVariance */
	       cout << "Error in variance determination!\n\n";
	       break;
	 }
	 /* Conditional to output computer guesses or prompt to play again */
	 switch (guessCount){
	    case (1):
	       cout << "My second guess is " << nextGuess << ".\n";
	       break;
	    case (2):
	       cout << "My third guess is " << nextGuess << ".\n";
	       break;
	    case (3):
	       cout << "My fourth guess is " << nextGuess << ".\n";
	       break;
	    case (4):
	       cout << "My fifth guess is " << nextGuess << ".\n";
	       break;
	    case (5):
	       cout << "\nYou got me this time.  Want to play again? (y/n)\n";
	       cin >> runAgain;
	       break;
	    default:
	       /* Unexpected error handling when the loop driver encounters
		  a case of guessCount outside of its 1 - 6 range. */
	       if (!(guessCount == exitGuessCountLoop))	 
		  cout << "\n\n\nLoop Driver Error!\n"
		       << "Time to fix some code!\n";
	       break;
	 }
      }
   }

   return 0;
}
