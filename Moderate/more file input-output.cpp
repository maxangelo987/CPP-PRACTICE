/*****************************************************************************
* Author:            Robert Kety
* Date Created:      10/19/2013
* Last Modified:     06/20/2014
* Description:       Retrieves the last and first name and a series of numbers
*                    from input file, computes the average of those numbers,
*                    and outputs the last and first names, the series of 
*                    numbers, and the average of those numbers.  The numbers
*                    are scores for students as described by their first and
*                    last names.  
* Input:             Last name, first name, and NUM_SCORES number of scores
*                    delimited by spaces.  Each record is recorded on a new
*                    line.
* Output:            Outputs all fields in identical format to the input file 
*                    (assuming format is [string] [string] 
*                    [NUM_SCORES integers]) with an additional double-type
*                    number set to the mean of the scores for that line.  
*                    Also outputs confirmation of progress to screen.
* Acknowledgements:  Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>  /* For input/output */
#include <fstream>   /* For input/output */
#include <cstdlib>   /* Necessary for exit() */
#include <string>    /* Necessary for string */

/* Number of test scores for each student in input file */
#define NUM_SCORES 10

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::ios;
using std::string;

/* Retrieve last and first name and test scores from input file, compute the
   mean score, and output in same format with an additional double-type 
   number which is the mean of the scores for that line. */
void scoreFunct(ifstream& listFile, ofstream& meanFile);

int main(){
    /* Declare input/output streams */
    ifstream fin;
    ofstream fout;
    
    cout << "\n\nOpening input file.";
    fin.open("list_scores.txt");
    
    /* Input file opening error handling */
    if(fin.fail()){
        cout << "\n\nInput file opening failed.\n\n";
        exit(1);
    }
    else
        cout << "\nInput file opened successfully!";
    
    cout << "\n\nOpening output file.";
    fout.open("mean_scores.txt");
    
    /* Output file opening error handling */
    if(fout.fail()){
        cout << "\n\nOutput file opening failed.\n\n";
        exit(1);
    }
    else
        cout << "\nOutput file opened successfully!";
    
    cout << "\n\nAveraging scores from input file.";
    scoreFunct(fin, fout);
    cout << "\nScores output successful!";
    
    /* Close input/output files */
    fin.close();
    fout.close();
    
    cout << "\n\nInput and output files closed successfully!";
    cout << "\nProgram ended.\n\n";
    
    return 0;
}

/* Retrieve last and first name and test scores from input file, compute the
    mean score, and output in same format with an additional double-type 
    number which is the mean of the scores for that line. */
void scoreFunct(ifstream& listFile, ofstream& meanFile){
    /* Variable declarations */
    string first, last;
    double next = 0.0, sum = 0.0;
    int elementCount = 0;
    
    /* Format output for whole numbers */
    meanFile.setf(ios::fixed);
    meanFile.precision(0);
    
    /* Loops retrieves input fields, calculates mean score, outputs all fields
        including mean score */
    while(listFile >> last){
        listFile >> first;
        
        /* Output last and first name */
        meanFile << last << " " << first << " ";
        
        /* Reset mean variables for new student */
        elementCount = 0;
        sum = 0;
        
        /* Retrieve and sum scores */
        while(elementCount < NUM_SCORES){
            elementCount++;
            listFile >> next;
            meanFile << next << ' ';
            sum += next;
        }     
        
        /* Format output for double */
        meanFile.setf(ios::showpoint);
        meanFile.precision(2);
        
        /* Output mean score and move to next line of output file */
        meanFile << (sum / NUM_SCORES) << endl;
        
        /* Reset output for whole numbers */
        meanFile.unsetf(ios::showpoint);
        meanFile.precision(0);
    }
    
    return;
}