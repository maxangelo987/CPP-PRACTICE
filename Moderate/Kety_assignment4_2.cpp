/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/19/2013
 * Last Modified:    10/20/2013
 * Description:      Retrieves a series of numbers from input file 
 *                   "doubles.txt", computes the average of the numbers, and 
 *                   outputs the mean to an output file "average.txt".
 * Input:            A series of double-type numbers delimited by spaces or
 *                   new-line characters.
 * Output:           Outputs progress of open, read, computation, output, and
 *                   close of both input and output files.  
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>  /* For input/output */
#include <fstream>   /* For input/output */
#include <cstdlib>   /* For exit() */

using std::ostream;  /* Allows use of cout as output stream */
using std::ifstream;
using std::ofstream;
using std::cout;
using std::ios;

/* Reads a series of numbers from input stream, compute the mean of those
   numbers, outputs the mean to the output stream, and outputs the mean
   to the screen. */
void meanFunct(ifstream& doubleFile, ostream& meanFile);

/* Returns mean of double-type elements from input stream */
double meanIn(ifstream& doubleFile);

/* Outputs mean to output stream */
void meanOut(ostream& meanFile, double mean);

int main(){
   /* Declare input/output streams */
   ifstream fin;
   ofstream fout;
   
   cout << "\n\nOpening input file.";
   fin.open("doubles.txt");
   
   /* Input file opening error handling */
   if(fin.fail()){
      cout << "\n\nInput file opening failed.\n\n";
      exit(1);
   }
   else
      cout << "\nInput file opened successfully!";
   
   cout << "\n\nOpening output file.";
   fout.open("average.txt");
   
   /* Output file opening error handling */
   if(fout.fail()){
      cout << "\n\nOutput file opening failed.\n\n";
      exit(1);
   }
   else
      cout << "\nOutput file opened successfully!";
   
   cout << "\n\nAveraging values from input file.";
   meanFunct(fin, fout);
   cout << "\nAverage output successful!";
   
   /* Close input/output files */
   fin.close();
   fout.close();
   
   cout << "\n\nInput and output files closed successfully!";
   cout << "\nProgram ended.\n\n";
   
   return 0;
}

/* Reads a series of numbers from input stream, compute the mean of those
   numbers, outputs the mean to the output stream, and outputs the mean
   to the screen. */
void meanFunct(ifstream& doubleFile, ostream& meanFile){
   /* Variable declaration to mean of input file elements */
   double mean = meanIn(doubleFile);
   
   /* Output mean to output file */
   meanOut(meanFile, mean);
   
   /* Output mean to screen */
   meanOut(cout, mean);
   
   return;
}

/* Returns mean of double-type elements from input stream */
double meanIn(ifstream& doubleFile){
   double sum = 0.0, next = 0.0;
   int elementCount = 0;
   
   /* Input and sum all elements in input file */
   while(doubleFile >> next){
      elementCount++;
      sum += next;
   }
   
   /* Return mean of elements */
   return (sum / elementCount);
}

/* Outputs mean to output stream */
void meanOut(ostream& meanFile, double mean){
   /* Format file output */
   meanFile.setf(ios::fixed);
   meanFile.setf(ios::showpoint);
   meanFile.precision(3);
   
   /* Output mean to output stream */
   meanFile << "Average: " << mean;
   
   return;
}