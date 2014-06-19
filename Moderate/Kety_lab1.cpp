/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/08/2013
 * Last Modified:    10/08/2013
 * Description:      Computes the mean and standard deviation of a number set
 *                   using one of three methods determined by the user -
 *                   an array on the stack, an array on the heap, or a vector.
 * Input:            User preference for calculation method and number set.
 * Output:           Prompts for user input.  Display mean and standard
 *                   deviation of number set.
 * Acknowledgements: Absolute C++, Seventh Edition, Chapter 6, Exercise 5.
 ****************************************************************************/

#include <iostream>  /* Necessary for input/output */
#include <vector>    /* Necessary for vectors */
#include <cmath>     /* Necessary for pow() and sqrt() */
#include <cstdlib>   /* Necessary for exit() */

#define ARRAY_SIZE 100  //Array size for arrays in this program

using std::cout;
using std::cin;
using std::endl;
using std::vector;

/* Outputs menu for user preference of array or vector */
void prefMenu();

/* Get user response for array or vector preference and return to calling
   function. */
int getPref();

/* Execute function of user's choice */
void runInput(const int& inputType);

/* Computes the mean and standard deviation of a number set input by user.
   Number set is handled with an array on the stack.  */
void stackArray();

/* Computes the mean and standard deviation of a number set input by user.
   Number set is handled with an array on the heap.  */
void heapArray();

/* Computes the mean and standard deviation of a number set input by user.
   Number set is handled with vectors.  */
void withVectors();

/* Outputs instructions for user input of number set */
void outputInstruct();

/* Place user input in an array and return the number of elements in set */
int arrayInput(double* array);

/* Place user input in a vector */
void vectInput(vector<double>& vect);

/* Compute the mean of number set stored in an array and return to calling
   function */
double mean(const double* array, const int& elementNum);

/* Compute the mean of number set stored in a vector and return to calling
   function */
double mean(const vector<double>& vect);

/* Compute the standard deviation of number set stored in an array and 
   return to calling function */
double stdDev(const double* array, const int& elementNum, const double& mean);

/* Compute the standard deviation of number set stored in a vector and 
   return to calling function */
double stdDev(const vector<double>& vect, const double& mean);

/* Output results of mean and standard deviation calculations */
void outputResults(const double& mean, const double& stdDev);

int main(int argc, char *argv[]){
   /* Variable Declarations */
   int inputPref = 0;
   char runAgain = 'y';
   
   while((runAgain == 'y') || (runAgain == 'Y')){
      //Output menu for user preference of array or vector
      prefMenu();
   
      //Get user input regarding array or vector preference
      inputPref = getPref();
   
      //Execute functions based on user preference
      runInput(inputPref);
            
      //Clear input stream
      cin.clear();
      cin.ignore(1000, '\n');
      
      //Prompt for another iteration of program
      cout << "\n\nRun again? (y/n): ";
      
      cin >> runAgain;
   }

   //Additional whitespace for increased readability
   cout << endl << endl;   
   
   return 0;
}

/* Outputs menu for user preference of array or vector */
void prefMenu(){
   cout << "\nWelcome to the mean and standard deviation calculator!"
        << "\nHow should I store your input?"
        << "\n\t1. With arrays on the stack"
        << "\n\t2. With arrays on the heap"
        << "\n\t3. With vectors"
        << "\nInvalid options will terminate program";
   cout << "\n\nPlease enter your preference (1, 2, or 3): ";
   
   return;
}

/* Get user response for array or vector preference and return to calling
   function. */
int getPref(){
   int userSelect = 0;
   
   cin >> userSelect;
   
   if((userSelect > 3) || (userSelect < 1)){
      cout << "\n\nYou have entered an invalid option.  Goodbye!\n";
      exit(1);
   }
   
   return userSelect;
}

/* Execute function of user's choice */
void runInput(const int& inputType){
   switch(inputType){
      case 1:
         stackArray();
         break;
      case 2:
         heapArray();
         break;
      case 3:
         withVectors();
         break;
      default:
         cout << "\n\nError handling inputType in "
              << "runInput(const int& inputType)!\n";
         exit(1);
         break;
   }
   
   return;
}

/* Computes the mean and standard deviation of a number set input by user.
   Number set is handled with an array on the stack.  */
void stackArray(){
   double array[ARRAY_SIZE];    //Creates the array
   int inputCount = 0;
   double stackMean = 0.0, stackStdDev = 0.0;
   
   //Prompt for input
   outputInstruct();
   
   //Populate the array
   inputCount = arrayInput(array);
   
   //Calculate the mean
   stackMean = mean(array, inputCount);
   
   //Calculate the standard deviation
   stackStdDev = stdDev(array, inputCount, stackMean);
   
   //Output results
   outputResults(stackMean, stackStdDev);
   
   return;
}

/* Computes the mean and standard deviation of a number set input by user.
   Number set is handled with an array on the heap.  */
void heapArray(){
   double* array = new double[ARRAY_SIZE];    //Creates the array pointer
   int inputCount = 0;
   double heapMean = 0.0, heapStdDev = 0.0;
   
   //Prompt for input
   outputInstruct();
   
   //Populate the array
   inputCount = arrayInput(array);
   
   //Calculate the mean
   heapMean = mean(array, inputCount);
   
   //Calculate the standard deviation
   heapStdDev = stdDev(array, inputCount, heapMean);
   
   //Output results
   outputResults(heapMean, heapStdDev);
   
   //Delete array
   delete [] array;
   
   return;
}

/* Computes the mean and standard deviation of a number set input by user.
   Number set is handled with vectors.  */
void withVectors(){
   vector<double> vect;
   double vectMean = 0.0, vectStdDev = 0.0;
   
   //Prompt for input
   outputInstruct();
   
   //Populate the array
   vectInput(vect);
   
   //Calculate the mean
   vectMean = mean(vect);
   
   //Calculate the standard deviation
   vectStdDev = stdDev(vect, vectMean);
   
   //Output results
   outputResults(vectMean, vectStdDev);
   
   return;
}

/* Outputs instructions for user input of number set */
void outputInstruct(){
   cout << "\n\nEnter up to " << ARRAY_SIZE << " and at least 2 numbers.";
   cout << "\nSeparate each entry with the spacebar or the enter key.";
   cout << "\nEnter a letter to finish input and begin calculation.\n";
   
   return;
}

/* Place user input in a vector */
void vectInput(vector<double>& vect){
   double temp = 0.0;
   
   while((cin >> temp))
      vect.push_back(temp);
   
   if(vect.size() <= 1){
      cout << "\n\nTwo numbers are required for a standard deviation "
           << "calculation.  Goodbye!\n\n";
      exit(1);
   }
   
   return;
}

/* Place user input in an array and return the number of elements in set */
int arrayInput(double* array){
   int i = 0;
   
   while((cin >> array[i]) && (i < (ARRAY_SIZE)))
      ++i;
   if(i <= 1){
      cout << "\n\nTwo numbers are required for a standard deviation "
           << "calculation.  Goodbye!\n\n";
      exit(1);
   }
   
   return i;
}

/* Compute the mean of number set stored in an array and return to calling
   function */
double mean(const double* array, const int& elementNum){
   double sum = 0;
   
   if((elementNum < 1) || (elementNum >= ARRAY_SIZE)){
      cout << "\n\nNumber of elements recorded in array is "
           << "out of bounds at mean()!\n\n";
      exit(1);
   }
   
   for(int i = 0; i < elementNum; ++i){
      sum += array[i];
   }
      
   return (sum / static_cast<double> (elementNum));
}

/* Compute the mean of number set stored in a vector and return to calling
   function */
double mean(const vector<double>& vect){
   double sum = 0;
   unsigned int elementNum = vect.size();
   
   for(unsigned int i = 0; i < elementNum; ++i){
      sum += vect[i];
   }
      
   return (sum / static_cast<double> (elementNum));
}

/* Compute the standard deviation of number set stored in an array and 
   return to calling function */
double stdDev(const double* array, const int& elementNum, const double& mean){
   double sum = 0;
   
   if((elementNum <= 1) || (elementNum >= ARRAY_SIZE)){
      cout << "\n\nNumber of elements recorded in array is "
           << "out of bounds at mean()!\n\n";
      exit(1);
   }
   
   for(int i = 0; i < elementNum; ++i){
      sum += std::pow(array[i] - mean, 2);
   }
      
   return (std::sqrt(sum / static_cast<double> (elementNum - 1)));
}

/* Compute the standard deviation of number set stored in a vector and 
   return to calling function */
double stdDev(const vector<double>& vect, const double& mean){
   double sum = 0;
   unsigned int elementNum = vect.size();
   
   for(unsigned int i = 0; i < elementNum; ++i){
      sum += std::pow(vect[i] - mean, 2);
   }
      
   return (std::sqrt(sum / static_cast<double> (elementNum - 1)));
}

/* Output results of mean and standard deviation calculations */
void outputResults(const double& mean, const double& stdDev){
   cout << "\n\nThe mean is: " << mean;
   cout << "\n\nThe standard deviation is: " << stdDev;
}