/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/08/2013
 * Last Modified:    10/09/2013
 * Description:      Creates and populates three two dimensional arrays.  
 *                   The first two arrays are randomly generated.  Each 
 *                   element of the third array is the product of elements
 *                   from the first and second array.
 * Input:            None
 * Output:           Displays the elements of each 2D array.
 *                   The first and second arrays are populated with numbers
 *                   0 - 9 to keep all three arrays in a two-digit format
 *                   for output.
 * Acknowledgements: CS 162 Assignment 5 for related functions
 ****************************************************************************/
 
#include <iostream>	/* Necessary for output */
#include <cstdlib>	/* Necessary for atoi(), rand(), and srand() */
#include <ctime> 	   /* Included to allow time()*/

#define ARRAY_SIZE 10   //A 10 x 10 grid array

using std::cout;
using std::endl;

/* Populates 2D array with random integers 0 - 99 */
void populate_array(int array[ARRAY_SIZE][ARRAY_SIZE]);

/* Stores the product of each element from array1 and array2 in array3 */
void arrayProduct(int array1[ARRAY_SIZE][ARRAY_SIZE], 
                  int array2[ARRAY_SIZE][ARRAY_SIZE], 
                  int array3[ARRAY_SIZE][ARRAY_SIZE]);
                  
/* Outputs 2D array to screen in readable format */
void output_array(int array[ARRAY_SIZE][ARRAY_SIZE]);             

int main(){
   int array1[ARRAY_SIZE][ARRAY_SIZE],
       array2[ARRAY_SIZE][ARRAY_SIZE], 
       array3[ARRAY_SIZE][ARRAY_SIZE];
   
   populate_array(array1);
   populate_array(array2);
   arrayProduct(array1, array2, array3);  //populates array3
   
   output_array(array1);
   output_array(array2);
   output_array(array3);
   
   return 0;
}

/* Populates 2D array with random integers 0 - 99 */
void populate_array(int array[ARRAY_SIZE][ARRAY_SIZE]){
   srand(time(NULL));   	// Seed random number generator
   for(int i = 0; i < ARRAY_SIZE; i++)
      for(int j = 0; j < ARRAY_SIZE; j++)
         array[i][j] = rand() % 10;	//Range is a non-negative integer < 100. 
}

/* Stores the product of each element from array1 and array2 in array3 */
void arrayProduct(int array1[ARRAY_SIZE][ARRAY_SIZE], 
                  int array2[ARRAY_SIZE][ARRAY_SIZE], 
                  int array3[ARRAY_SIZE][ARRAY_SIZE]){
   for(int i = 0; i < ARRAY_SIZE; ++i)
      for(int j = 0; j < ARRAY_SIZE; ++j)
         array3[i][j] = array1[i][j] * array2[i][j];
}

/* Outputs 2D array to screen in readable format */
void output_array(int array[ARRAY_SIZE][ARRAY_SIZE]){
   cout << endl << endl;      //Extra lines for increased readability
   for(int i = 0; i < ARRAY_SIZE; i++){
      for(int j = 0; j < ARRAY_SIZE; j++){
         if(array[i][j] < 10)     //Add "0" to tens position when under 10
            cout << "0" << array[i][j] << " ";
         else
            cout << array[i][j] << " ";
      }
      cout << endl;     //End of row
   }
   cout << endl;
}