/*****************************************************************************
 * Author:              Robert Kety
 * Date Created:        07/29/2013
 * Last Modified:       07/30/2013
 * File Name:           Kety_assignment3.cpp
 * Description:         For five different types of functions, calculate the
 *                      area under the curve between two points in the domain
 *                      using either the Rectangle method, Trapezoid method,
 *                      or both.
 * Input:		Selection of function, selection of calculation method, 
 *             		and selection of domain range.
 * Output:		Prompts for user input, including formatted menus. 
 * 			Error handling prompts for unexpected cases, and 
 * 			invalid conditions for domain range.  Outputs result 
 * 			in sentence format that includes relevant descriptors 
 * 			used in its calculation.
 * Acknowledgements:	Assignment3 Instruction,
 * 			Joseph Jess for tips on how to approach x-intercept
 * 			issue.
 ****************************************************************************/
 
#include <iostream>	/* For user input/output */
#include <cmath>	/* For pow function */
#include <limits>	/* Necessary for reset of cin error state */
#include <string>	/* For use of strings in output */

using std::cout;
using std::cin;
using std::endl;
using std::pow;
using std::string;
using std::abs;

/* Returns the y-value for a given x-value for the function: 
 * f(x) = 2x^5 + x^3 - 10x + 2 */
double f1(double xValue);	

/* Returns the y-value for a given x-value for the function: 
 * f(x) = 6x^2 - x + 10 */
double f2(double xValue);	

/* Returns the y-value for a given x-value for the function: 
 * f(x) = 5x + 3 */
double f3(double xValue);	

/* Returns the y-value for a given x-value for the function: 
 * f(x) = 2x^3 + 120 */
double f4(double xValue);	

/* Returns the y-value for a given x-value for the function: 
 * f(x) = 2x^2 */
double f5(double xValue);	

/* Outputs menu for function selection with an option to quit. 
 * Returns integer value from 1 to 5 based on user input. 
 * Call-by-reference string hold description of function choice 
 * and call-by-reference bool allows loop driver in main to 
 * be set to TRUE if the user desires to quit.*/
int getFunction(string& functChoice, bool& quitOption);

/* Outputs menu for calculation method with an option to quit.
 * Return integer value from 1 to 3 based on user input.
 * Call-by-reference bool allows loop driver in main to 
 * be set to TRUE if the user desires to quit.*/
int getCalculation(bool& quitOption);

/* Outputs prompt requesting the number of rectangles.
 * Only accepts and returns positive integers. */
int getNumRectangles();

/* Outputs prompt requesting the number of trapezoids.
 * Only accepts and returns positive integers. */
int getNumTrapezoids();

/* Outputs prompts for starting and ending points.
 * Swaps values if starting point is after ending point.
 * Adds one to ending point if starting point equals ending point.
 * User input is directly recorded to variables via call-by-reference. */
void getDomain(int& domainMin, int& domainMax);

/* Uses relevant boundary variables to determine the height of the left
 * and right boundaries used in area calculation of either rectangles
 * or trapezoids */
void getBoundaryHeights(double& leftHeight, double& rightHeight, 
			double sectionBoundary, double partitionWidth, 
			int functionCase);

/* Returns area under a curve using the Rectangle Method for one of the
 * five functions handled in this program */
double areaRect(int functionCase, int numPolygon, int domainMin, int domainMax);

/* Returns area under a curve using the Trapezoid Method for one of the
 * five functions handled in this program */
double areaTrapezoid(int functionCase, int numPolygon, int domainMin, int domainMax);

int main(){
   /* Declare and define variables */
   int functionType = 1,
      calcType = 1,
      numRectangles = 1,
      numTrapezoids = 1,
      xMin = 0,
      xMax = 1;
   bool stopProgram = false;
   string functString = "";
   
   /* Determine function selection. */
   functionType = getFunction(functString, stopProgram);
   
   if(!(stopProgram))	//Prevents output of second menu if user quits
      /* Determine calculation selection */
      calcType = getCalculation(stopProgram);
   
   /* Program prompts user until receiving quit condition */
   while(!(stopProgram)){
      /* Determine number of polygons */
      switch(calcType){
	 case 1:
	    numRectangles = getNumRectangles();
	    break;
	 case 2:
	    numTrapezoids = getNumTrapezoids();
	    break;
	 case 3:
	    numRectangles = getNumRectangles();
	    numTrapezoids = getNumTrapezoids();
	    break;
	 default:
	    cout << "\n\nError in Calculation Type\n\n";
	    break;
      }
      
      /* Determine floor and ceiling of domain */
      getDomain(xMin, xMax);
      
      /* Calculate and output result */
      cout << "\n\nThe area under "
	   << functString
  	   << " between "
  	   << xMin
  	   << " and "
  	   << xMax;			   
      
      switch (calcType){
	 case 1:
	    cout << ",\nusing "
	         << numRectangles
  		 << " partitions of the Rectangle Method is: " 
  		 << areaRect(functionType, numRectangles, xMin, xMax)
  		 << endl << endl;
	    break;
	 case 2:
	    cout << ",\nusing "
	         << numTrapezoids
  		 << " partitions of the Trapezoid Method is: "
  		 << areaTrapezoid(functionType, numTrapezoids, xMin, xMax)
  		 << endl << endl;
	    break;
	 case 3:
	    cout << ",\nusing "
	         << numRectangles
  		 << " partitions of the Rectangle Method is: "
  		 << areaRect(functionType, numRectangles, xMin, xMax);
	    cout << ",\nand using "
	         << numTrapezoids
  		 << " partitions of the Trapezoid Method is: "
  		 << areaTrapezoid(functionType, numTrapezoids, xMin, xMax)
  		 << endl << endl;
	    break;
	 default:
	    cout << "\n\n Error in Calculation Type Handling\n\n";
	    break;
      }
      
      /* Determine function selection for next iteration of loop. */
      functionType = getFunction(functString, stopProgram);
      if(!(stopProgram))	//Prevents second menu output if user quits
	 /* Determine calculation selection */
	 calcType = getCalculation(stopProgram);
   }	   
   
   return 0;
}


double f1(double xValue){	/* f(x) = 2x^5 + x^3 - 10x + 2 */
   /* Declare and define variable */
   double yValue = 0;
   
   yValue = (2.0 * pow(xValue, 5)) + (pow(xValue, 3)) - (10.0 * xValue) + (2.0);
   
   return yValue;
}

double f2(double xValue){	/* f(x) = 6x^2 - x + 10 */
   /* Declare and define variable */
   double yValue = 0;
   
   yValue = (6.0 * pow(xValue, 2)) - (xValue) + (10.0);
   
   return yValue;
}

double f3(double xValue){	/* f(x) = 5x + 3 */
   /* Declare and define variable */
   double yValue = 0;
   
   yValue = (5.0 * xValue) + (3.0);
   
   return yValue;
}

double f4(double xValue){	/* f(x) = 2x^3 + 120 */
   /* Declare and define variable */
   double yValue = 0;
   
   yValue = (2.0 * pow(xValue, 3)) + (120.0);
   
   return yValue;
}

double f5(double xValue){	/* f(x) = 2x^2 */
   /* Declare and define variable */
   double yValue = 0;
   
   yValue = (2.0 * pow(xValue, 2));

   return yValue;
}

int getFunction(string& functChoice, bool& quitOption){
   /* Declare and define variables */
   int userSelection = 1;
   string funct1 = "2x^5 + x^3 - 10x + 2",
	  funct2 = "6x^2 - x + 10",
	  funct3 = "5x + 3",
	  funct4 = "2x^3 + 120",
	  funct5 = "2x^2";
   
   /* Function Selection Menu */
   cout << "\n\nPlease choose a function to evaluate the area under the following,";
   cout << "\n\t1: f1(x) = 2x^5 + x^3 - 10x + 2";
   cout << "\n\t2: f2(x) = 6x^2 - x + 10";
   cout << "\n\t3: f3(x) = 5x + 3";
   cout << "\n\t4: f4(x) = 2x^3 + 120";
   cout << "\n\t5: f5(x) = 2x^2";
   cout << "\n\tAnything else: quit";
   cout << "\n\nPlease choose an option: ";
   
   /* User input; Non-number and out-of-range initiate program termination */
   if((!(cin >> userSelection)) || (userSelection < 1) || (userSelection > 5)){	
      /* Clears error flag from non-number entry */
      cin.clear();
      /* Move to next buffer line */	 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      /* User has selected to quit the program */
      quitOption = true;
   }
   
   /* Sends string appropriate to user selection back to main() */
   switch(userSelection){
      case 1:
	 functChoice = funct1;
	 break;
      case 2:
	 functChoice = funct2;
	 break;
      case 3:
	 functChoice = funct3;
	 break;
      case 4:
	 functChoice = funct4;
	 break;
      case 5:
	 functChoice = funct5;
	 break;
      default:
	 functChoice = "\n\nUser selected quit option. Error in function selection.\n\n";
	 break;
   }
   
   return userSelection;	//Integer from 1 to 5
}

int getCalculation(bool& quitOption){
   /* Declare and define variable */
   int userSelection = 1;
   
   /* Calculation Type Menu */
   cout << "\n\nYou can calculate the area using:";
   cout << "\n\t1: rectangle method,";
   cout << "\n\t2: trapezoid method,";
   cout << "\n\t3: both rectangle and trapezoid method";
   cout << "\n\tAnything else: quit";
   cout << "\nHow would you like to continue?: ";
   
   /* User input; Non-number and out-of-range initiate program termination */
   if((!(cin >> userSelection)) || (userSelection < 1) || (userSelection > 3)){	
      /* Clears error flag from non-number entry */
      cin.clear();
      /* Move to next buffer line */	 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      /* User has selected to quit the program */
      quitOption = true;
   }
   
   return userSelection;	//Integer from 1 to 3
}

int getNumRectangles(){
   /* Declare and define variable */
   int quantityPolygon = 1;
   
   /* Prompt for user input */
   cout << "\n\nHow many rectangles do you want? ";
   
   /* Ensures input is a positive integer */
   while ((!(cin >> quantityPolygon)) || (quantityPolygon < 1)){
      /* Clears error flag from non-number entry */
      cin.clear();
      /* Move to next buffer line */	 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      /* Prompt for corrected input */
      cout << "\nPlease enter a positive integer: ";
   }
   
   return quantityPolygon;	//Positive integer
}

int getNumTrapezoids(){
   /* Declare and define variable */
   int quantityPolygon = 1;
   
   /* Prompt for user input */
   cout << "\n\nHow many trapezoids do you want? ";
   
   /* Ensures input is a positive integer */
   while ((!(cin >> quantityPolygon)) || (quantityPolygon < 1)){
      /* Clears error flag from non-number entry */
      cin.clear();
      /* Move to next buffer line */	 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      /* Prompt for corrected input */
      cout << "\nPlease enter a positive integer: ";
   }
   
   return quantityPolygon;	//Positive integer
}

void getDomain(int& domainMin, int& domainMax){
   /* Declare and define variable */
   int varSwap;
   
   /* Prompt for domainMin */
   cout << "\n\nPlease select a starting point, a = ";
   
   /* Ensures input is an integer */
   while (!(cin >> domainMin)){
      /* Clears error flag from non-number entry */
      cin.clear();
      /* Move to next buffer line */	 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      /* Prompt for corrected input */
      cout << "\nPlease enter an integer: ";
   }
   
   /* Prompt for domainMax */
   cout << "\n\nPlease select an ending point, b = ";
   
   /* Ensures input is an integer */
   while (!(cin >> domainMax)){
      /* Clears error flag from non-number entry */
      cin.clear();
      /* Move to next buffer line */	 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      /* Prompt for corrected input */
      cout << "\nPlease enter an integer: ";
   }
   
   /* Automatic swapping of reversed domain limits */
   if(domainMin > domainMax){
      cout << "\nYour ending point, "
	   << domainMax
  	   << ", appears to be before your starting point, "
  	   << domainMin
  	   << ".\n";
      cout << "I'll just switch those around.\n";
      
      varSwap = domainMax;
      domainMax = domainMin;
      domainMin = varSwap;
   }
   
   /* Prevents equivalent domain limits */
   if(domainMin == domainMax){
      cout << "\nYour ending point, "
	   << domainMax
  	   << ", appears to be the same as your starting point, "
  	   << domainMin
  	   << ".\n";
      cout << "I'll use "
	   << ++domainMax 
  	   << " as your ending point instead.\n";
   }
   
}

void getBoundaryHeights(double& leftHeight, double& rightHeight, 
                        double sectionBoundary, double partitionWidth, 
			int functionCase){
   double midPointHeight = 0,
	  midPointBoundary = 0,
	  leftBoundary = 0,
	  rightBoundary = 0;
   
   switch(functionCase){
      case 1: 
	 leftHeight = f1(sectionBoundary);	 
	 rightHeight = f1(sectionBoundary + partitionWidth);
	 
	 /* Handles x-intercepts within boundaries of a partition */
	 if((leftHeight > 0) && (rightHeight < 0)){
	    leftBoundary = sectionBoundary;
	    rightBoundary = sectionBoundary + partitionWidth;
	    
	    while(abs(midPointHeight) > 0.00000000001){
	       midPointBoundary = (leftBoundary + rightBoundary) / 2;
	       midPointHeight = f1(midPointBoundary);
	       
	       if(midPointHeight > 0)
	  	  leftBoundary = midPointBoundary;
	       else
		  rightBoundary = midPointBoundary;  
	    }
	    
	    /* Reset rightHeight boundary to ignore area that is
	     * negated on either side of the x-intercept */
	    rightHeight = f1(sectionBoundary + partitionWidth - (2 * abs(midPointBoundary)));		
	 }
	 else if((leftHeight < 0) && (rightHeight > 0)){
	    leftBoundary = sectionBoundary;
	    rightBoundary = sectionBoundary + partitionWidth;
	    
	    while(abs(midPointHeight) > 0.00000000001){
	       midPointBoundary = (leftBoundary + rightBoundary) / 2;
	       midPointHeight = f1(midPointBoundary);
	       
	       if(midPointHeight < 0)
		  leftBoundary = midPointBoundary;
	       else
		  rightBoundary = midPointBoundary;  
	    }
	    
	    /* Reset leftHeight boundary to ignore area that is
	     * negated on either side of the x-intercept */
	    leftHeight = f1(sectionBoundary + (2 * abs(midPointBoundary)));
	 }
	 break;
      case 2:	//Function 2 has no x-intercept or x-intercept is the min.
	 leftHeight = f2(sectionBoundary);
	 rightHeight = f2(sectionBoundary + partitionWidth);
	 break;
      case 3:
	 leftHeight = f3(sectionBoundary);
	 rightHeight = f3(sectionBoundary + partitionWidth);
	 
	 /* Handles x-intercepts within boundaries of a partition */
	 if((leftHeight > 0) && (rightHeight < 0)){
	    leftBoundary = sectionBoundary;
	    rightBoundary = sectionBoundary + partitionWidth;
	    
	    while(abs(midPointHeight) > 0.00000000001){
	       midPointBoundary = (leftBoundary + rightBoundary) / 2;
	       midPointHeight = f3(midPointBoundary);
	       
	       if(midPointHeight > 0)
		  leftBoundary = midPointBoundary;
	       else
		  rightBoundary = midPointBoundary;  
	    }
	    
	    /* Reset rightHeight boundary to ignore area that is
	     * negated on either side of the x-intercept */
	    rightHeight = f3(sectionBoundary + partitionWidth - (2 * abs(midPointBoundary)));
	 }
	 else if((leftHeight < 0) && (rightHeight > 0)){
	    leftBoundary = sectionBoundary;
	    rightBoundary = sectionBoundary + partitionWidth;
	   
	    while(abs(midPointHeight) > 0.00000000001){
	       midPointBoundary = (leftBoundary + rightBoundary) / 2;
	       midPointHeight = f3(midPointBoundary);
	       
	       if(midPointHeight < 0)
		  leftBoundary = midPointBoundary;
	       else
		  rightBoundary = midPointBoundary;  
	    }
	    
	    /* Reset leftHeight boundary to ignore area that is
	     * negated on either side of the x-intercept */
	    leftHeight = f3(sectionBoundary + (2 * abs(midPointBoundary)));
	 }
	 break;
      case 4:
	 leftHeight = f4(sectionBoundary);
	 rightHeight = f4(sectionBoundary + partitionWidth);
	 
	 /* Handles x-intercepts within boundaries of a partition */
	 if((leftHeight > 0) && (rightHeight < 0)){
	    leftBoundary = sectionBoundary;
	    rightBoundary = sectionBoundary + partitionWidth;
	    
	    while(abs(midPointHeight) > 0.00000000001){
	       midPointBoundary = (leftBoundary + rightBoundary) / 2;
	       midPointHeight = f4(midPointBoundary);
	       
	       if(midPointHeight > 0)
		  leftBoundary = midPointBoundary;
	       else
		  rightBoundary = midPointBoundary;  
	    }
	    
	    /* Reset rightHeight boundary to ignore area that is
	     * negated on either side of the x-intercept */
	    rightHeight = f4(sectionBoundary + partitionWidth - (2 * abs(midPointBoundary)));
	 }
	 else if((leftHeight < 0) && (rightHeight > 0)){
	    leftBoundary = sectionBoundary;
	    rightBoundary = sectionBoundary + partitionWidth;
	    
	    while(abs(midPointHeight) > 0.00000000001){
	       midPointBoundary = (leftBoundary + rightBoundary) / 2;
	       midPointHeight = f4(midPointBoundary);
	       
	       if(midPointHeight < 0)
		  leftBoundary = midPointBoundary;
	       else
		  rightBoundary = midPointBoundary;  
	    }
	    
	    /* Reset leftHeight boundary to ignore area that is
	     * negated on either side of the x-intercept */
	    leftHeight = f4(sectionBoundary + (2 * abs(midPointBoundary)));
	 }
	 break;
      case 5:	//Function 5 has no x-intercepts or x-intercept is min.
	 leftHeight = f5(sectionBoundary);
	 rightHeight = f5(sectionBoundary + partitionWidth);
	 break;
      default:
	 cout << "\n\nError in Function Selection in Area Calculation\n\n";
	 break;
   }
}

double areaRect(int functionCase, int numPolygon, int domainMin, int domainMax){
   /* Declare and define variables */
   double totalArea = 0,
   	  domainRange = ((double)domainMax - (double)domainMin),
   	  sectionWidth = domainRange / (double)numPolygon,
   	  sectionCount = (double)domainMin,
   	  sectionHeightLeft = 0,
	  sectionHeightRight = 0;	   
   
   /* Calculate area of numPolygon number of rectangles */
   for(int i = 0; i < numPolygon; i++){
      getBoundaryHeights(sectionHeightLeft, sectionHeightRight, 
	                 sectionCount, sectionWidth, functionCase);
      
      /* Handles calculation of ascending and descending curves
       * even if they drop below the x-axis */
      if(abs(sectionHeightLeft) < abs(sectionHeightRight))
	 totalArea += sectionHeightLeft * sectionWidth;
      else
	 totalArea += sectionHeightRight * sectionWidth;
      
      sectionCount += sectionWidth;
   }
   
   return totalArea;
}

double areaTrapezoid(int functionCase, int numPolygon, int domainMin, int domainMax){
   /* Declare and define variables */
   double totalArea = 0,
   	  domainRange = ((double)domainMax - (double)domainMin),
   	  sectionWidth = domainRange / (double)numPolygon,
   	  sectionCount = (double)domainMin,
   	  sectionHeightLeft = 0,
	  sectionHeightRight = 0;
   
   /* Calculate area of numPolygon number of trapezoids */
   for(int i = 0; i < numPolygon; i++){
      getBoundaryHeights(sectionHeightLeft, sectionHeightRight, 
	                 sectionCount, sectionWidth, functionCase);
      
      totalArea += ((0.5) * (sectionHeightRight + sectionHeightLeft) * sectionWidth);
      
      sectionCount += sectionWidth;
   }   
   return totalArea;
}
