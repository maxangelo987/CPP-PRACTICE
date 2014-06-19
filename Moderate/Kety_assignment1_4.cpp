/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/08/2013
 * Last Modified:    10/09/2013
 * Description:      Creates and populates two dimensional array from 400
 *                   element string.  For each element in the array,
 *                   it determines the greatest product of four adjacent 
 *                   numbers in a 20 x 20 grid.  Multiple shape types are 
 *                   used to determine adjacency (Line right, line down, left 
 *                   diagonal, and right diagonal)*.
 *                   * - Line left and line up are redundant to right and down.
 * Input:            None.
 * Output:           Displays the elements of the 2D array in readable format
 *                   and highlights the four adjacent elements with the 
 *                   greatest product.
 *                   Outputs greatest product of four adjacent numbers.
 * Acknowledgements: CS 161 Assignment5
 ****************************************************************************/
 
#include <iostream>	/* Necessary for output */
#include <cstdlib>	/* Necessary for atoi(), rand(), and srand() */
#include <string>	   /* For use of strings */
#include <vector>    /* For use of vectors */

using std::cout;
using std::string;
using std::vector;
using std::copy;

/* All elements that describe a 2D array for this program */
struct ArrayInfo{
   int dynArray[20][20];             //2D array
   int rowLimit, colLimit,       //Row/Col limit of 2D array
       maxProd,                  //Greatest product of four numbers in array
       rowVar[4], colVar[4],     //Contains row/col coordinates for maxProd
       origin[2];                //Contains coordinates for origin element
};

/* For Function Pointers */
typedef void (*FunctionPtr)(ArrayInfo &arrayDetails);

/* Find the greatest product of four adjacent integers within a 2D array 
 * Requires lineRight, lineDown, diagonalLeft, diagonalRight functions. */ 
int maxProduct(int array[20][20]);

/* Calculates four adjacent products in Line Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:    Populated 2D array and associated variables from
 *                   the ArrayInfo struct.  
 * Postconditions:   Populated 2D array and associate variables from
 *                   the ArrayInfo struct.  Modified maximum product,
 *                   row variable, column variable, and shape type 
 *                   string.  */
void lineRight(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Line Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:    Populated 2D array and associated variables from
 *                   the ArrayInfo struct.  
 * Postconditions:   Populated 2D array and associate variables from
 *                   the ArrayInfo struct.  Modified maximum product,
 *                   row variable, column variable, and shape type 
 *                   string.  */
void lineDown(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Left Diagonal configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:    Populated 2D array and associated variables from
 *                   the ArrayInfo struct.  
 * Postconditions:   Populated 2D array and associate variables from
 *                   the ArrayInfo struct.  Modified maximum product,
 *                   row variable, column variable, and shape type 
 *                   string.  */
void diagonalRight(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Right Diagonal configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:    Populated 2D array and associated variables from
 *                   the ArrayInfo struct.  
 * Postconditions:   Populated 2D array and associate variables from
 *                   the ArrayInfo struct.  Modified maximum product,
 *                   row variable, column variable, and shape type 
 *                   string.  */
void diagonalLeft(ArrayInfo &arrayDetails);

/* Outputs array with highlighted elements. */
void output_highlighted(ArrayInfo arrayDetails);

int main(){
   /* Variable Declarations */
   int array[20][20], k = 0;
   vector<int> v;
   string dataStream = string("08 02 22 97 38 15 00 40 00 75 ") +
                              "04 05 07 78 52 12 50 77 91 08 " +
                              "49 49 99 40 17 81 18 57 60 87 " +
                              "17 40 98 43 69 48 04 56 62 00 " +
                              "81 49 31 73 55 79 14 29 93 71 " +
                              "40 67 53 88 30 03 49 13 36 65 " +
                              "52 70 95 23 04 60 11 42 69 24 " +
                              "68 56 01 32 56 71 37 02 36 91 " +
                              "22 31 16 71 51 67 63 89 41 92 " +
                              "36 54 22 40 40 28 66 33 13 80 " +
                              "24 47 32 60 99 03 45 02 44 75 " +
                              "33 53 78 36 84 20 35 17 12 50 " +
                              "32 98 81 28 64 23 67 10 26 38 " +
                              "40 67 59 54 70 66 18 38 64 70 " +
                              "67 26 20 68 02 62 12 20 95 63 " +
                              "94 39 63 08 40 91 66 49 94 21 " +
                              "24 55 58 05 66 73 99 26 97 17 " +
                              "78 78 96 83 14 88 34 89 63 72 " +
                              "21 36 23 09 75 00 76 44 20 45 " +
                              "35 14 00 61 33 97 34 31 33 95 " +
                              "78 17 53 28 22 75 31 67 15 94 " +
                              "03 80 04 62 16 14 09 53 56 92 " +
                              "16 39 05 42 96 35 31 47 55 58 " +
                              "88 24 00 17 54 24 36 29 85 57 " +
                              "86 56 00 48 35 71 89 07 05 44 " +
                              "44 37 44 60 21 58 51 54 17 58 " +
                              "19 80 81 68 05 94 47 69 28 73 " +
                              "92 13 86 52 17 77 04 89 55 40 " +
                              "04 52 08 83 97 35 99 16 07 97 " +
                              "57 32 16 26 26 79 33 27 98 66 " +
                              "88 36 68 87 57 62 20 72 03 46 " +
                              "33 67 46 55 12 32 63 93 53 69 " +
                              "04 42 16 73 38 25 39 11 24 94 " +
                              "72 18 08 46 29 32 40 62 76 36 " +
                              "20 69 36 41 72 30 23 88 34 62 " +
                              "99 69 82 67 59 85 74 04 36 16 " +
                              "20 73 35 29 78 31 90 01 74 31 " +
                              "49 71 48 86 81 16 23 57 05 54 " +
                              "01 70 54 71 83 51 54 69 16 92 " +
                              "33 48 61 43 52 01 89 19 67 48";
   
   //Convert string to vector
   for(int q = 0; q < 400; ++q)
      v.push_back(((dataStream[q*3] - '0') * 10) + (dataStream[q*3 + 1] - '0'));
   
   //Convert vector to 2D array per assignment requirements
   for(int i = 0; i < 20; i++)
      for(int j = 0; j < 20; ++j)
         array[i][j] = v[((i*20)+j)];
   
   //Output max product of array
   cout << "\n\nMax product of array: " << maxProduct(array) << "\n\n";
   
   return 0;
}

/* Find the greatest product of four adjacent integers within a 2D array 
 * Requires lineRight, lineDown, diagonalLeft, diagonalRight functions. */ 
int maxProduct(int array[20][20]){
   /* Variable Declarations */
   int numFunctions = 4, tempMaxA = 0, tempMaxB = 0;
   ArrayInfo arrayDetails;
   FunctionPtr temp[numFunctions], 
               shapeFunct[] = {lineRight, lineDown, diagonalLeft, 
                               diagonalRight};
   
   //Copy 2D array into 2D array of struct
   for(int q = 0; q < 20; ++q)
      copy(array[q], array[q] + 20, arrayDetails.dynArray[q]);
      
   //Define relevant details of 2D array in struct arrayDetails
   arrayDetails.rowLimit = 20;
   arrayDetails.colLimit = 20;
   
   /* Determine which shape function has the greatest power of four adjacent
    * elements and assign to a sorted array of function calls */
   for(int i = 0; i < (numFunctions - 1); ++i){
      shapeFunct[i](arrayDetails);
      tempMaxA = arrayDetails.maxProd;
      shapeFunct[i + 1](arrayDetails);
      tempMaxB = arrayDetails.maxProd;
      if(tempMaxA > tempMaxB){
         temp[i] = shapeFunct[i];
         shapeFunct[i] = shapeFunct[i + 1];
         shapeFunct[i + 1] = temp[i];
      }      
   }
   
   /* Run function with the greatest product of four adjacent elements
    * in array to reset associated variables for return */
   shapeFunct[numFunctions - 1](arrayDetails);
   
   /* Outputs array with highlighted products */
   output_highlighted(arrayDetails);
   
   return arrayDetails.maxProd;
}

/* Calculates four adjacent products in Line Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:    Populated 2D array and associated variables from
 *                   the ArrayInfo struct.  
 * Postconditions:   Populated 2D array and associate variables from
 *                   the ArrayInfo struct.  Modified maximum product,
 *                   row variable, column variable, and shape type 
 *                   string.  */
void lineRight(ArrayInfo &arrayDetails){
   /* Variable Declarations */
   int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
   arrayDetails.maxProd = 0;
   
   /* Scan all array elements and determine greatest product of four adjacent
    * elements in a line to the right of the origin element.  */
   for(int i = 0; i < arrayDetails.rowLimit; i++)
      for(int j = 0; j < arrayDetails.colLimit; j++){
         if((j + numProd) <= arrayDetails.colLimit){
            tempProd = 1;
            for(int k = 0; k < numProd; k++){
               rowElements[k] = i;
               colElements[k] = j + k;
               tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];
            }
            if(tempProd > arrayDetails.maxProd){
               arrayDetails.maxProd = tempProd;
               /* Assign four elements of greatest product to parameter struct */
               copy(rowElements, rowElements + numProd, arrayDetails.rowVar);
               copy(colElements, colElements + numProd, arrayDetails.colVar);
            }
         }
      }
}

/* Calculates four adjacent products in Line Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:    Populated 2D array and associated variables from
 *                   the ArrayInfo struct.  
 * Postconditions:   Populated 2D array and associate variables from
 *                   the ArrayInfo struct.  Modified maximum product,
 *                   row variable, column variable, and shape type 
 *                   string.  */
void lineDown(ArrayInfo &arrayDetails){
   /* Variable Declarations */
   int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
   arrayDetails.maxProd = 0;
   
   /* Scan all array elements and determine greatest product of four adjacent
    * elements in a line below the origin element.  */
   for(int i = 0; i < arrayDetails.rowLimit; i++)
      for(int j = 0; j < arrayDetails.colLimit; j++){
         if((i + numProd) <= arrayDetails.rowLimit){
            tempProd = 1;
            for(int k = 0; k < numProd; k++){
               rowElements[k] = i + k;
               colElements[k] = j;
               tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];
            }
            if(tempProd > arrayDetails.maxProd){
               arrayDetails.maxProd = tempProd;
               /* Assign four elements of greatest product to parameter struct */
               copy(rowElements, rowElements + numProd, arrayDetails.rowVar);
               copy(colElements, colElements + numProd, arrayDetails.colVar);
            }
         }
      }
}

/* Calculates four adjacent products in Left Diagonal configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:    Populated 2D array and associated variables from
 *                   the ArrayInfo struct.  
 * Postconditions:   Populated 2D array and associate variables from
 *                   the ArrayInfo struct.  Modified maximum product,
 *                   row variable, column variable, and shape type 
 *                   string.  */
void diagonalRight(ArrayInfo &arrayDetails){
   /* Variable Declarations */
   int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
   arrayDetails.maxProd = 0;
   
   /* Scan array and determine greatest product of four adjacent elements
    * in a diagonal line down and to the right of the origin element. */
   for(int i = 0; i < arrayDetails.rowLimit; i++)
      for(int j = 0; j < arrayDetails.colLimit; j++){
         if(((i + numProd) <= arrayDetails.rowLimit) && 
            ((j + numProd) <= arrayDetails.colLimit)){
            tempProd = 1;
            for(int k = 0; k < numProd; k++){
               rowElements[k] = i + k;
               colElements[k] = j + k;
               tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];
            }
            if(tempProd > arrayDetails.maxProd){
               arrayDetails.maxProd = tempProd;
               /* Assign four elements of greatest product to parameter struct */
               copy(rowElements, rowElements + numProd, arrayDetails.rowVar);
               copy(colElements, colElements + numProd, arrayDetails.colVar);
            }
         }
      }
}

/* Calculates four adjacent products in Right Diagonal configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:    Populated 2D array and associated variables from
 *                   the ArrayInfo struct.  
 * Postconditions:   Populated 2D array and associate variables from
 *                   the ArrayInfo struct.  Modified maximum product,
 *                   row variable, column variable, and shape type 
 *                   string.  */
void diagonalLeft(ArrayInfo &arrayDetails){
   /* Variable Declarations */
   int numProd = 4, tempProd = 1, colMin = 0, rowElements[4], colElements[4];
   arrayDetails.maxProd = 0;
   
   /* Scan array and determine greatest product of four adjacent elements
    * in a diagonal line down and to the left of the origin element. */
   for(int i = 0; i < arrayDetails.rowLimit; i++)
      for(int j = 0; j < arrayDetails.colLimit; j++){
         if(((i + numProd) <= arrayDetails.rowLimit) && 
            ((j - numProd) >= (colMin - 1))){
            tempProd = 1;
            for(int k = 0; k < numProd; k++){
               rowElements[k] = i + k;
               colElements[k] = j - k;
               tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];
            }
            if(tempProd > arrayDetails.maxProd){
               arrayDetails.maxProd = tempProd;
               /* Assign four elements of greatest product to parameter struct */
               copy(rowElements, rowElements + numProd, arrayDetails.rowVar);
               copy(colElements, colElements + numProd, arrayDetails.colVar);
            }            
         }
      }
}

/* Outputs array with highlighted elements. */
void output_highlighted(ArrayInfo arrayDetails){
   /* Variable Declaration */
   int prodElement = 0;
      
   cout << "\n\n";      //Extra lines for readability
   
   for(int i = 0; i < arrayDetails.rowLimit; i++){
      for(int j = 0; j < arrayDetails.colLimit; j++){
         if((prodElement < 4) && 
            (i == arrayDetails.rowVar[prodElement]) && 
            (j == arrayDetails.colVar[prodElement])){
            cout << "\033[1;31m";   //Change output to bold and red
            prodElement++;
         }
         if(arrayDetails.dynArray[i][j] < 10)   //Ensure two digit output
            cout << "0" << arrayDetails.dynArray[i][j] << " ";
         else
            cout << arrayDetails.dynArray[i][j] << " ";
         cout << "\033[0m";      //Reset output to standard
      }
      cout << "\n";     //End of row
   }
   
   cout << "\n";
}