/*****************************************************************************
 *	Author:			Robert Kety
 *	Date Created:	07/11/2013
 *	Last Modified:	06/18/2014
 *	Description:	Grade Calculator. For a number of assignments input from 
 *                  the user, sum the points earned and points possible from each 
 *			        assignment.  Calculate percentage of total points 
 *			        earned against total points possible.
 *	Input:		    Number of assignments, points earned for each 
 *			        assignment, and points possible for each assignment.
 *	Ouput:		    Prompts for user input and the total points earned, 
 *			        total points possible, and the percentage of total 
 *			        points earned against total points possible.
 *	Acknowledgements:
 *			Lecture 4 (i.e., "04Lecture.mp4")
 *			Eric Anderson and Feng Tian
 *			For our conversation related to a similar program in 
 *			Lecture 4
 * **************************************************************************/

#include <iostream>
#include <iomanip>	//To use setprecision on percentage
#include <limits>	//To reset cin errors

using std::cout;
using std::cin;
using std::endl;

int main() {
    int numberOfAssignments = 0, 
    pointsEarned, 
    pointsPossible, 
    totalPointsEarned = 0, 
    totalPointsPossible = 0;
    bool validResponse;
    float percentageOfPointsPossible;

    /* Loop preventing non-number and negative input to numberOfAssignments via cin */
    do{
        cout << "How many assignments? " << endl;
        validResponse = (cin >> numberOfAssignments);
        /* If non-number input, clears error state and buffer */
        if(!(validResponse)){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while ((!(validResponse)) || (numberOfAssignments <= 0));
    
    /* Input for possible and earned points for all numberOfAssignments */
    for(int currentAssignment = 1; 
        currentAssignment <= numberOfAssignments; 
        currentAssignment++){
        
        /* Loop preventing non-number, negative, and zero input to pointsPossible via cin */
        do{
            cout 	<< "Points possible for Assignment #" 
            << currentAssignment << " ?\n";
            validResponse = (cin >> pointsPossible);
            /* If non-number input, clears error state and buffer */
            if(!(validResponse)){
                cin.clear();
                cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while ((!(validResponse)) || (pointsPossible < 1));
        
        /* Loop preventing non-number, negative numbers, and numbers greater than pointsPossible */
        do{
            cout 	<< "Points earned for Assignment #" 
            << currentAssignment << " ?\n";
            validResponse = (cin >> pointsEarned);
            /* If non-number input, clears error state and buffer */
            if(!(validResponse)){
                cin.clear();
                cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while((!(validResponse)) || (pointsEarned > pointsPossible) || 
            (pointsEarned < 0));
        
        /* Summary calculations */
        totalPointsPossible += pointsPossible;
        totalPointsEarned += pointsEarned;
    }
    
    /* Calculation to the hundredths and compensating for floating-point precision */
    percentageOfPointsPossible = (float)totalPointsEarned / (float)totalPointsPossible;
    percentageOfPointsPossible = (100000.0 * percentageOfPointsPossible);
    percentageOfPointsPossible /= 10.0;
    
    if((percentageOfPointsPossible + 0.5) >= (((int)(percentageOfPointsPossible)) + 1)){
        percentageOfPointsPossible = (int)((float)percentageOfPointsPossible + 0.5);
    }
    
    percentageOfPointsPossible /= 100.0;
    
    /* Final output */
    cout	<< "Total points are " 
    << totalPointsEarned << " out of "
    << totalPointsPossible << ", or "
    << std::setprecision(2) << std::fixed 
    << percentageOfPointsPossible << "%.\n\n";

    return 0;
}