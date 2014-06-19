/*****************************************************************************
 *	Author:		Robert Kety
 *	Date Created:	07/10/2013
 *	Last Modified:	07/16/2013
 *	File Name:	Kety_rand_numbers.cpp
 *	Description:	A demonstration of random numbers in a guessing game
 *			format.
 *	Input:		A random integer from the srand function and integer 
 *			guesses from the user.		
 *	Output:		Intructions and feedback for the user.
 *	Acknowledgments:
 *			Eric Anderson for discussing code design
 *			Feng Tian for bringing up the issue of error coding
 ***************************************************************************/

#include <iostream> 	/*included to allow for cout and cin*/
#include <ctime> 	/*included to allow time()*/
#include <cstdlib> 	/*include to allow rand() and srand()*/
#include <limits>	/*included to allow clearing cin*/

using std::cout;
using std::cin;
using std::endl;

int main() {
   int randomInt; 	/* variable to hold our random integer*/
   int bestGuess = 0, guessCount;

   srand(time(NULL)); 	/*seeds random number generator. Do this just once*/
   randomInt = rand() % 50;	//Range is a non-negative integer < 50. 
   
   cout << "Guess a number from 0 to 49.\n";
   cout << "You get 5 attempts.\nGuess my number: " << endl;
   for (guessCount = 1; guessCount < 6; guessCount++){
      if (!(cin >> bestGuess)){		//If cin fails to read an integer
	 cin.clear();		//Clears error flag from non-number entry
	 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	 //Move to next buffer line
	 bestGuess = -1;      
      }
      if ((bestGuess >= 0) && (bestGuess < 50)){
	 if (bestGuess < randomInt){
	    cout << "Too low! " << "That's guess # " << guessCount << endl;
	    if (guessCount < 5)
	       cout << "Guess again: " << endl;
	 } else if (bestGuess > randomInt){
	    cout << "Too high! " << "That's guess # " << guessCount << endl;
	    if (guessCount < 5)
	       cout << "Guess again: " << endl;
	 } else if (bestGuess == randomInt){
	    cout << "Perfect guess on your ";
	    switch (guessCount){
	       case (1):
		  cout << "first";
		  break;
	       case (2):
		  cout << "second";
		  break;
	       case (3):
		  cout << "third";
		  break;
	       case (4):
		  cout << "fourth";
		  break;
	       case (5):
		  cout << "fifth";
		  break;
	       default:
		  cout << "\n\n\nLoop Driver Error!\nTime() to fix some code!\n";
		  guessCount = -1;	//Sets loop driver to error code zero 
		  break;
	    }
	    if (guessCount < 0)
	       break;	//Breaks the for loop in the event of an unpredicted error
	    cout << " attempt!" << endl;
	    break;	//Breaks the for loop in the event of a perfect guess
	 }
      }else{
	 cout << "That's not a number from 0 to 49!" << endl;
	 guessCount--;	//Improper guesses should not count against the user.
	 if (guessCount < 5)
	    cout << "Guess again: " << endl;
      }
   }
   if (guessCount > 5){
      cout << "\nThe number was " << randomInt << "!\n";
      cout << "Better luck next time()!" << endl; 
   }
   else if ((guessCount < 6) && (guessCount > 0))
      cout << endl << "You got me this time()!" << endl;
   cout << " ^Little bit of rand()m humor there." << endl << endl;

   return 0;
}
