/*****************************************************************************
 * Author:              Robert Kety
 * Date Created:        08/07/2013
 * Last Modified:       06/19/2014
 * Description:         Calculates the combination formula for n and r.  Also
 * 			            calculates the time of the calculation.  The
 * 			            calculation can be performed using iterative or
 * 			            recursive functions.
 * Input:		        A number of objects and sets within those objects.
 * 			            User preference for calculation method
 * 			            (recursive/iterative).  Optional command line arguments allow
 *			            user to bypass prompts for input of sets and objects.
 * Output:		        Prompts for user input, output of calculation, and
 * 			            output of time for that calculation.
 * Acknowledgements:	Lab6 instructions, Lab7 instructions,
 * 			            Joseph Jess and Eric Anderson for their forum
 * 			            conversation regarding large numbers.
 ****************************************************************************/
#include <iostream>	    /* Necessary for user input/output */
#include <sys/time.h>	/* Necessary for timing functions */
#include <limits>	    /* Necessary for reset of cin error state */
#include <cstdlib>	    /* Necessary for strtold() */

using std::cout;
using std::cin;
using std::endl;

/* Handles command line arguments */
void cmdArg(int argc, char *argv[], long double& numObjects, long double& numSets);

/* Prompts user for a number of objects and sets for use in a combination
 * formula calculation.  Ensures numbers are non-negative */
void getNAndR(long double& numObjects, long double& numSets);

/* Prompts user for preference regarding calculation method (i.e.,
 * recursive or iterative) */
char solutionPref();

/* Calculates a factorial using recursion */
long double recursiveCalc(long double nVar);

/* Calculates a factorial using iterative loop */
long double iterativeCalc(long double nVar);

/* Performs combination formula calculation using only recursive
 * functions */
long double recursiveCombos(long double objectsN, long double setsR);

/* Performs combination formula calculation using only iterative
 * loops */
long double iterativeCombos(long double objectsN, long double setsR);

int main (int argc, char *argv[]){
    /* Object and variable declaration */
    typedef struct timeval time;
    time stop, start;
    long double nObjects = 0, rSets = 0;
    long double numCombos = 0;
    char userSolution;
 
    if(argc > 1){
        /* Handles Command Line Arguments */
        cmdArg(argc, argv, nObjects, rSets);
     
 	    /* Prompt user for recursive or iterative method of calculation */
        userSolution = solutionPref();
    }
    else{	//When no additional command line arguments are input
        /* Prompt user for objects and sets for combination formula */
        getNAndR(nObjects, rSets);
     
 	    /* Prompt user for recursive or iterative method of calculation */
        userSolution = solutionPref();
    }
 
    if((userSolution == 'r') || (userSolution == 'R')){
        /* Recursive method */
        gettimeofday(&start, NULL);	//Record start time
     
        /* Calculate combination formula */
        numCombos = recursiveCombos(nObjects, rSets);
     
        gettimeofday(&stop, NULL);	//Record stop time
    }
    else{
        /* Iterative method */
        gettimeofday(&start, NULL);	//Record start time
     
        /* Calculate combination formula */
        numCombos = iterativeCombos(nObjects, rSets);
     
        gettimeofday(&stop, NULL);	//Record stop time
    }
 
    /* Output calculation results */
    cout << "\nThe number of possible combinations of "
         << rSets
         << " sets from "
         << nObjects
         << " objects is: "
         << numCombos
         << endl;
 
    /* Output timing for calculation */
    cout << "\nThe time it took to perform this calculation was:\n";
    if(stop.tv_sec > start.tv_sec)
        cout << stop.tv_sec - start.tv_sec << " seconds\n\n";
    else
        cout << stop.tv_usec - start.tv_usec << " microseconds\n\n";

    /* End program */
    return 0;
}

/* Handles command line arguments */
void cmdArg(int argc, char *argv[], long double& numObjects, long double& numSets){
    /* Variable declaration */
    long double tempVar = 0;
 
    /* Scan arguments for first two positive numbers and set to variables */
    for(int i = 1; i < argc; i++){
        if(isdigit(argv[i][0])){
            numSets = strtold(argv[i], NULL);
            for(int j = i + 1; j < argc; j++){
                if(isdigit(argv[j][0])){
                    numObjects = strtold(argv[j], NULL);
                    j = argc;		//Set loop driver to exit condition
                }
            }
            i = argc;		//Set loop driver to exit condition
        }
    }
 
    /* Handles improper command line arguments and terminates program */
    if(numSets == 0){
        cout << "\n\nUsage: ./Kety_lab6_2 "
             << "[<non-negative sets>] [<non-negative objects>]\n\n";
        exit (1);		//Terminate program
    }
    /* Handles insufficient command line arguments */
    else if(numObjects == 0){
        cout << "\n\nI appear to be missing the number of objects.\n";
        cout << "\nPlease enter a non-negative number of objects: ";
        while((!(cin >> numObjects)) || (numObjects < 0)){
            /* Clears error flag from non-number entry */
            cin.clear();
            /* Move to next buffer line */
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            /* Prompt user to re-enter input */
            cout << "\nPlease enter a non-negative number of objects: ";
        }
    }
 
    /* Switches variable assignment to avoid negative factorial
     * calculations */
    if(numObjects < numSets){
        tempVar = numObjects;
        numObjects = numSets;
        numSets = tempVar;
        
        cout << "\n\nYour arguments appear to be reversed.\n";
        cout << "I'll switch them around to avoid negative factorials.\n";
    }
}

/* Prompts user for a number of objects and sets for use in a combination
 * formula calculation.  Ensures numbers are non-negative */
void getNAndR(long double& numObjects, long double& numSets){
    /* Variable declaration */
    long double temp = 0;
 
    cout << "\nPlease enter a non-negative integer of n objects: ";
 
    /* Ensure non-negative number input */
    while(!(cin >> numObjects) || (numObjects < 0)){
        /* Clears error flag from non-number entry */
        cin.clear();
        /* Move to next buffer line */
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        /* Prompt user to reenter input */
        cout << "\nPlease enter a non-negative integer of n objects: ";
    }
 
    cout << "\nPlease enter a non-negative integer of r sets: ";
 
    /* Ensure non-negative number input */
    while(!(cin >> numSets) || (numSets < 0)){
        /* Clears error flag from non-number entry */
        cin.clear();
        /* Move to next buffer line */
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        /* Prompt user to reenter input */
        cout << "\nPlease enter a non-negative integer of r sets: ";
    }
 
    /* Switch values for combination formula variable to prevent negative
     * factorial calculations */
    if(numObjects < numSets){
        /* Prompt user about the change */
        cout << "\nYour set requirements are greater than the number of\n";
        cout << "objects you provided (i.e., n < r).\n";
        cout << "I'll switch those around to avoid negative factorials.\n";
     
        /* Trade values for variables numObjects and numSets */
        temp = numObjects;
        numObjects = numSets;
        numSets = temp;
     
        /* Output new variable values for user */
        cout << "\nI will now be calculating the number of combinations\n";
        cout << "possible of "
             << numSets
             << " sets from "
             << numObjects
             << " objects\n";
    }
}

/* Prompts user for preference regarding calculation method (i.e.,
 * recursive or iterative) */
char solutionPref(){
    /* Variable declaration */
    char userInput = 'i';
 
    /* Prompt user for calculation method */
    cout << "\nBefore I calculate the number of combinations, \n";
    cout << "Would you prefer an iterative or recursive solution?\n";
    cout << "Type r and press enter if you prefer to calculate "
         << "recursively: ";
 
    /* Receive user input and reset for next line */
    cin >> userInput;
    cin.ignore(1000,'\n');
 
    return userInput;
}

/* Calculates a factorial using recursion */
long double recursiveCalc(long double nVar){
    if(nVar < 1)	//Base case. Factorial of zero is one.
        return 1;
    else
        return nVar * recursiveCalc(nVar - 1);	//Recursive call
}

/* Calculates a factorial using iterative loop */
long double iterativeCalc(long double nVar){
    /* Variable declaration */
    long double factorial = 1;	//Default value for factorials of 1 and 0
   
    for(long double i = 0; i < nVar; i++){
        factorial = factorial * (nVar - i);
    }

    return factorial;
}

/* Performs combination formula calculation using only recursive
 * functions */
long double recursiveCombos(long double objectsN, long double setsR){
    /* Variable declaration */
    long double combinations = 0;
    
    /* Perform recursive calculation of combination formula:
     * n! / r! * (n - r)! */
    combinations = recursiveCalc(objectsN - setsR);
    combinations *= recursiveCalc(setsR);
    combinations = recursiveCalc(objectsN) / combinations;
    
    return combinations;
}

/* Performs combination formula calculation using only iterative
 * loops */
long double iterativeCombos(long double objectsN, long double setsR){
    /* Variable declaration */
    long double combinations = 0;
    
    /* Perform iterative calculation of combination formula:
     * n! / r! * (n - r)! */
    combinations = iterativeCalc(objectsN - setsR);
    combinations *= iterativeCalc(setsR);
    combinations = iterativeCalc(objectsN) / combinations;
    
    return combinations;
}
