/*****************************************************************************
 * Author:              Robert Kety
 * Date Created:        08/14/2013
 * Last Modified:       06/19/2014
 * Description:         Creates and populates dynamic two dimensional array from
 *                      command line user input.  For each element in the array,
 *                      it determines the greatest product of four adjacent 
 *                      numbers.  Multiple shape types are used to determine
 *                      adjacency (Line right, line down, left diagonal, etc.).
 * Input:               Command line arguments for array dimensions.
 * Output:              Displays the elements of the 2D array in readable format.
 *                      Outputs details of element with greatest product of four
 *                      adjacent number including the product of those numbers, 
 *                      the location of the element in the array, and the shape
 *                      of adjacency from the origin element.  Assuming the
 *                      standard display can support 80 characters per line, the
 *                      program will output a second display of array elements
 *                      and highlight the four adjacent elements with the 
 *                      greatest product when columns are set to less than 27.
 *                      Invalid or incomplete command line arguments will result
 *                      in descriptive error message and proper usage
 *                      information.
 * Acknowledgements:    Assignment5 Instructions,
 *                      http://www.cplusplus.com/forum for their posts related 
 *                      to creating function pointers.
 *                      Lab6 Materials for introducing me to structs.
 *                      CS225 Text - Discrete Mathematics and Its Applications -
 *                      7th edition for explaining that mathematicians publish
 *                      different recursive formulae and their associated
 *                      sequences.  I was able to search for a formula which
 *                      results in the sequence 0, 1, 2, 2.  This was invaluable
 *                      for determining the row iteration in the L-shaped 
 *                      adjacency function.  I was also able to use the
 *                      Fibonacci sequence in the same manner.
 *                      http://stackoverflow.com/questions for posts related to
 *                      copying arrays using std::copy.
 ****************************************************************************/
#include <iostream>     /* Necessary for output */
#include <cstdlib>	    /* Necessary for atoi(), rand(), and srand() */
#include <string>	    /* For use of strings */
#include <ctime> 	    /*included to allow time()*/
#include <cstring>      /* For strlen() */
#include <cmath>        /* For pow() */
#include <algorithm>    /* For copy() */

using std::cout;
using std::endl;
using std::string;
using std::copy;

/* For int Pointers */
typedef int* IntPtr;

/* All elements that describe a 2D array for this program */
struct ArrayInfo{
    IntPtr* dynArray;                 //2D array
    int rowLimit, colLimit,         //Row/Col limit of 2D array
        maxProd,                        //Greatest product of four numbers in array
        rowVar[4], colVar[4],      //Contains row/col coordinates for maxProd
        origin[2];                     //Contains coordinates for origin element
    string shapeType;                 //Describes shape of maxProd
};

/* For Function Pointers */
typedef void (*FunctionPtr)(ArrayInfo &arrayDetails);

/* FUNCTION DECLARATIONS */

/* Validates and assigns command line arguments variables used to create
 * a 2D dynamic array.  Requires the valid_arguments function. */
void cmd_arg_handler(int argc, char *argv[], int &maxRows, int &maxCols);

/* Validates command line arguments */
bool valid_arguments(int argc, char *argv[]);

/* Outputs error message for incorrect command line arguments */
void error_output(int errorCase, bool &validInput);

/* Creates and populates 2D array 
 * Requires populate_array function. */
IntPtr* create_array(int maxRows, int maxCols);

/* Populates 2D array with random integers 0 - 99 */
void populate_array(IntPtr* array2D, int maxRows, int maxCols);

/* Outputs 2D array to screen in readable format */
void output_array(IntPtr* array2D, int maxRows, int maxCols);

/* Find the greatest product of four adjacent integers within a 2D array 
 * Requires lineRight, lineDown, diagonalLeft, diagonalRight, square,
 * zigZag Right, zigZag Down, zagZig Down, zagZig Right, lShapeDown,
 * lShapeRight, lShapeUp, lShapeLeft, skewDown, skewRight, inverseSkewDown,
 * and inverseSkewRight functions. */
void find_greatest_product(ArrayInfo &arrayDetails);

/* FUNCTION SECTION: Shape Functions */

/* Calculates four adjacent products in Line Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void lineRight(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Line Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void lineDown(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Right Diagonal configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void diagonalRight(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Left Diagonal configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void diagonalLeft(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Down Right Square configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void square(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in ZigZag Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void zigZag_down(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in ZagZig Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type
 *                         string.  */
void zagZig_down(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in ZigZag Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void zigZag_right(ArrayInfo &arrayDetails);
 
/* Calculates four adjacent products in ZigZag Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void zagZig_right(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in L-shape Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.  Requires
 * the use of maleHofstadter and femaleHofstadter functions.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void lShapeDown(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in L-shape Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.  Requires
 * the use of maleHofstadter and femaleHofstadter functions.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void lShapeRight(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in L-shape Left configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.  Requires
 * the use of maleHofstadter and femaleHofstadter functions.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void lShapeLeft(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in L-shape Up configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.  Requires
 * the use of maleHofstadter and femaleHofstadter functions.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void lShapeUp(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Skew Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
 void skewRight(ArrayInfo &arrayDetails);
 
 /* Calculates four adjacent products in Inverse Skew Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void invSkewRight(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Skew Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void skewDown(ArrayInfo &arrayDetails);

/* Calculates four adjacent products in Inverse Skew Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void invSkewDown(ArrayInfo &arrayDetails);

/* FUNCTION SECTION: Functions for reordering and/or copying four products 
 *                         into acceptable output format. */

/* Copies square row/column elements for four products to struct array for
 * use in output_highlighted function. */
 void orderSquare(ArrayInfo &arrayDetails, int rowArray[], int colArray[]);

/* Reorders zigZag_right row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
void orderZigRight(ArrayInfo &arrayDetails, int rowArray[], int colArray[]);

/* Reorders zagZig_right row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
void orderZagRight(ArrayInfo &arrayDetails, int rowArray[], int colArray[]);

/* Reorders lShapeRight row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
void orderLRight(ArrayInfo &arrayDetails, int rowArray[], int colArray[]);
 
/* Reorders lShapeLeft row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
void orderLLeft(ArrayInfo &arrayDetails, int rowArray[], int colArray[]); 

/* Reorders lShapeUp row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
void orderLUp(ArrayInfo &arrayDetails, int rowArray[], int colArray[]);
 
/* Reorders invSkewRight row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
void orderInvSkewRight(ArrayInfo &arrayDetails, int rowArray[], int colArray[]);
 
/* Reorders skewDown row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
void orderSkewDown(ArrayInfo &arrayDetails, int rowArray[], int colArray[]);
 
/* FUNCTION SECTION: Supporting sequence functions */
 
/* Returns Male Hofstadter Sequence  
 * Requires the femaleHofstadter function */
int maleHofstadter(int n);

/* Returns Female Hofstadter Sequence  
 * Requires the maleHofstadter function */
int femaleHofstadter(int n);

/* Returns Fibonnaci Sequence */
int fibonacci(int n);

/* FUNCTION SECTION: Output functions */ 

/* Outputs details of greatest product function */
void output_results(ArrayInfo arrayDetails);

/* Outputs array with highlighted elements if output of array columns 
 * will be less than 80 characters wide. Origin elements determinate upon
 * the use of a reordering function controlled by the placement of a space
 * at the beginning of the shape type string. */
void output_highlighted(ArrayInfo arrayDetails);

/* FUNCTION SECTION: Dynamic memory clearing */

/* Deletes dynamic array */
void delete_array(ArrayInfo &arrayDetails);

int main(int argc, char *argv[]){
    /* Variable declaration */
    ArrayInfo arrayVar;
    
    /* Test command line arguments for validity and assign array limits */
    cmd_arg_handler(argc, argv, arrayVar.rowLimit, arrayVar.colLimit);
    
    /* Create and populate 2D array */
    arrayVar.dynArray = create_array(arrayVar.rowLimit, arrayVar.colLimit);
    
    /* Output array */
    output_array(arrayVar.dynArray, arrayVar.rowLimit, arrayVar.colLimit);
    
    /* Find greatest product of four adjacent numbers in array */
    find_greatest_product(arrayVar);
    
    /* Output Results */
    output_results(arrayVar);
    
    /* Outputs array with highlighted products if display width condition 
     * is met */
    output_highlighted(arrayVar);
    
    /* Deletes dynamic array */
    delete_array(arrayVar);
    
    return 0;
}   // 9 Lines of code

/* Validates and assigns command line arguments variables used to create
 * a 2D dynamic array.  Requires the valid_arguments function. */
void cmd_arg_handler(int argc, char *argv[], int &maxRows, int &maxCols){
    if(valid_arguments(argc, argv))      //Test if arguments are valid
        /* Assign valid row and column arguments */
        for(int i = 1; i < argc; i++){
            if(!(strcmp(argv[i], "-rows")))
                maxRows = atoi(argv[i + 1]);
            else if(!(strcmp(argv[i], "-cols")))
                maxCols = atoi(argv[i + 1]);
        }
    
    else{     // Output proper usage and terminate program
        cout << "\n\nUsage: ./Kety_assignment5 -rows <Number of Rows> "
              << "-cols <Number of Columns>\n\n";
        exit (1);
    }    
}   //9 Lines of code

/* Validates command line arguments */
bool valid_arguments(int argc, char *argv[]){
    /* Variable Declaration */
    bool validArgs = true;
    
    if(argc != 5)      //Must have 5 arguments
        error_output(1, validArgs);
    else if(!((!(strcmp("-rows\0", argv[1])) &&      //Non-number arguments can
                  !(strcmp("-cols\0", argv[3]))) ||     //only be "-rows" or
                 (!(strcmp("-cols\0", argv[1])) &&      //"-cols", but in either
                  !(strcmp("-rows\0", argv[3])))))      //order.
        error_output(2, validArgs);
    else if(isalpha(argv[2][0]) || isalpha(argv[4][0]))    
        error_output(3, validArgs);
    else if((atoi(argv[2]) < 4) || 
              (atoi(argv[4]) < 4))      //At least 4 rows and columns
        error_output(4, validArgs);
    else{
        for(int i = 2; i < argc; i += 2)
            for(int j = 0; j < strlen(argv[i]); j++)
                if(!(isdigit(argv[i][j])))     //Integers only
                    error_output(5, validArgs);
    }

    return validArgs;
}   //15 Lines of code

/* Outputs error message for incorrect command line arguments */
void error_output(int errorCase, bool &validInput){
    validInput = false;
    if(errorCase == 1)    //Not enough arguments, including array dimensions
        cout << "\nMust have four arguments in addition to execution argument.";
    if(errorCase == 2)    //Improper entry of "-rows" or "-cols"
        cout << "\nPlease use \"-rows\" followed by a number and \"-cols\" "
              << "followed by a number.";
    if(errorCase == 3)    //No numeric value for one or both arguments
        cout << "\nPlease use numeric arguments for the number of rows and "
              << "columns.";
    if(errorCase == 4)    //Entered less than 4 rows or columns
        cout << "\nMust use at least four row and columns.";
    if(errorCase == 5)    //Non-integer input
        cout << "\nRows and column must be integers in Arabic numerals"
              << "\n(e.g., 4, 5, 6, etc.).";
}   //11 lines of code

/* Creates and populates 2D array 
 * Requires populate_array function. */
IntPtr* create_array(int maxRows, int maxCols){
    /* Variable Declaration */
    IntPtr *array2D = new IntPtr[maxRows];
    
    for(int i = 0; i < maxRows; i++){
        array2D[i] = new int[maxCols];
    }
    /* Populate array with random numbers 0-99 */
    populate_array(array2D, maxRows, maxCols);
    return array2D;
}   //5 Lines of code

/* Populates 2D array with random integers 0 - 99 */
void populate_array(IntPtr* array2D, int maxRows, int maxCols){
    srand(time(NULL));    	// Seed random number generator
    for(int i = 0; i < maxRows; i++)
        for(int j = 0; j < maxCols; j++)
            array2D[i][j] = rand() % 100;	//Range is a non-negative integer < 100. 
}   //4 Lines of code

/* Outputs 2D array to screen in readable format */
void output_array(IntPtr* array2D, int maxRows, int maxCols){
    cout << endl << endl;        //Extra lines for increased readability
    for(int i = 0; i < maxRows; i++){
        for(int j = 0; j < maxCols; j++){
            if(array2D[i][j] < 10)      //Add "0" to tens position when under 10
                cout << "0" << array2D[i][j] << " ";
            else
                cout << array2D[i][j] << " ";
        }
        cout << endl;      //End of row
    }
    cout << endl;
}   //9 Lines of code

/* Find the greatest product of four adjacent integers within a 2D array 
 * Requires lineRight, lineDown, diagonalLeft, diagonalRight, square,
 * zigZag Right, zigZag Down, zagZig Down, zagZig Right, lShapeDown,
 * lShapeRight, lShapeUp, lShapeLeft, skewDown, skewRight, inverseSkewDown,
 * and inverseSkewRight functions. */
void find_greatest_product(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numFunctions = 17, tempMaxA = 0, tempMaxB = 0;
    FunctionPtr temp[numFunctions], 
                    shapeFunct[] = {lineRight, lineDown, diagonalLeft, 
                                         diagonalRight, square, zigZag_down, 
                                         zagZig_down, zigZag_right, zagZig_right, 
                                         lShapeDown, lShapeRight, lShapeLeft,
                                         lShapeUp, skewRight, invSkewRight,
                                         skewDown, invSkewDown};
        
    /* Determine which shape function has the greatest power of four adjacent
     * elements and assign to a sorted array of function calls */
    for(int i = 0; i < (numFunctions - 1); i++){
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
     * in array to reset associated variables for output */
    shapeFunct[numFunctions - 1](arrayDetails);
}   //12 Lines of code

/* Calculates four adjacent products in Line Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
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
        
    arrayDetails.shapeType = "Line Right";     //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in Line Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
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
    arrayDetails.shapeType = "Line Down";     //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in Left Diagonal configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
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
    arrayDetails.shapeType = "Right Diagonal";    //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in Right Diagonal configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
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
    arrayDetails.shapeType = "Left Diagonal";    //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in Down Right Square configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void square(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in a square line down and to the right of the origin element. */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i + (numProd / 2)) <= (arrayDetails.rowLimit)) && 
                ((j + (numProd / 2)) <= (arrayDetails.colLimit))){
                tempProd = 1;
                for(int k = 0; k < (numProd / 2); k++)
                    for(int m = 0; m < (numProd / 2); m++){
                        rowElements[(k * 2) + m] = i + k;
                        colElements[(k * 2) + m] = j + m;
                        tempProd *= arrayDetails.dynArray[rowElements[(k * 2) + m]][colElements[(k * 2) + m]]; 
                    }
                if(tempProd > arrayDetails.maxProd){
                    arrayDetails.maxProd = tempProd;
                    /* Assign four elements of greatest product to parameter struct */
                    orderSquare(arrayDetails, rowElements, colElements);
                }
            }
        }
    arrayDetails.shapeType = "Square";    //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in ZigZag Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void zigZag_down(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, binaryCol = 0, rowElements[4], 
         colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in a zigzag from the origin element (like a 'Z'). */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i + (numProd)) <= (arrayDetails.rowLimit)) && 
                ((j + (numProd / 2)) <= (arrayDetails.colLimit))){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    rowElements[k] = i + k;
                    colElements[k] = j + (bool)(std::pow(-1.0, k + 1) + 1);
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
    arrayDetails.shapeType = "Zigzag Down";    //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in ZigZag Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void zagZig_down(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, binaryCol = 0, rowElements[4], 
         colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in a zigzag from the origin element (like a 'Z'). */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i + (numProd - 1)) < (arrayDetails.rowLimit)) && 
                ((j - 1) >= 0)){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    rowElements[k] = i + k;
                    colElements[k] = j - (bool)(std::pow(-1.0, k) - 1);
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
    arrayDetails.shapeType = "Zagzig Down";    //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in ZigZag Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements. */
void zigZag_right(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, binaryCol = 0, rowElements[4], 
         colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in a zigzag from the origin element (like a 'Z'). */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i - (numProd / numProd)) >= (0)) && 
                ((j + (numProd)) <= (arrayDetails.colLimit))){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    rowElements[k] = i - (bool)(std::pow(-1.0, k + 1) + 1);
                    colElements[k] = j + k;
                    tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];                
                }
                if(tempProd > arrayDetails.maxProd){
                    arrayDetails.maxProd = tempProd;
                    /* Assign four elements of greatest product to parameter struct */
                    orderZigRight(arrayDetails, rowElements, colElements);
                }
            }
        }
    arrayDetails.shapeType = " Zigzag Right";    //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in ZagZig Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void zagZig_right(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, binaryCol = 0, rowElements[4], 
         colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in a zigzag from the origin element (like a 'Z'). */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i - (numProd / numProd)) >= (0)) && 
                ((j + (numProd)) <= (arrayDetails.colLimit))){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    rowElements[k] = i - (bool)(std::pow(-1.0, k) + 1);
                    colElements[k] = j + k;
                    tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];                
                }
                if(tempProd > arrayDetails.maxProd){
                    arrayDetails.maxProd = tempProd;
                    /* Assign four elements of greatest product to parameter struct */
                    orderZagRight(arrayDetails, rowElements, colElements);
                }
            }
        }
    arrayDetails.shapeType = " Zagzig Right";    //Assign string to parameter struct
}   //14 Lines of code

/* Calculates four adjacent products in L-shape Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.  Requires
 * the use of maleHofstadter and femaleHofstadter functions.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void lShapeDown(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in an L-shape from the origin element. */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i + (numProd - 1)) <= (arrayDetails.rowLimit)) && 
                ((j + (numProd / 2)) <= (arrayDetails.colLimit))){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    rowElements[k] = i + maleHofstadter(k + 1);
                    colElements[k] = j + (k / (numProd - 1));
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
    arrayDetails.shapeType = "L-Shape Down";    //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in L-shape Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.  Requires
 * the use of maleHofstadter and femaleHofstadter functions.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void lShapeRight(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in an L-shape from the origin element. */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i - 1) >= 0) && 
                ((j + (numProd - 1)) <= (arrayDetails.colLimit))){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    colElements[k] = j + maleHofstadter(k + 1);
                    rowElements[k] = i - (k / (numProd - 1));
                    tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];
                }
                if(tempProd > arrayDetails.maxProd){
                    arrayDetails.maxProd = tempProd;
                    /* Assign four elements of greatest product to parameter struct */
                    orderLRight(arrayDetails, rowElements, colElements);
                }
            }
        }
    arrayDetails.shapeType = " L-Shape Right";    //Assign string to parameter struct
}   //14 Lines of code

/* Calculates four adjacent products in L-shape Left configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.  Requires
 * the use of maleHofstadter and femaleHofstadter functions.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void lShapeLeft(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in an L-shape from the origin element. */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i + 1) < (arrayDetails.rowLimit)) && 
                ((j - (numProd / 2)) >= 0)){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    colElements[k] = j - maleHofstadter(k + 1);
                    rowElements[k] = i + (k / (numProd - 1));
                    tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];
                }
                if(tempProd > arrayDetails.maxProd){
                    arrayDetails.maxProd = tempProd;
                    /* Assign four elements of greatest product to parameter struct */
                    orderLLeft(arrayDetails, rowElements, colElements);
                }
            }
        }
    arrayDetails.shapeType = " L-Shape Left";    //Assign string to parameter struct
}   //14 Lines of code

/* Calculates four adjacent products in L-shape Up configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.  Requires
 * the use of maleHofstadter and femaleHofstadter functions.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void lShapeUp(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in an L-shape from the origin element. */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i - (numProd / 2)) >= 0) && 
                ((j - 1) >= 0)){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    rowElements[k] = i - maleHofstadter(k + 1);
                    colElements[k] = j - (k / (numProd - 1));
                    tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];
                }
                if(tempProd > arrayDetails.maxProd){
                    arrayDetails.maxProd = tempProd;
                    /* Assign four elements of greatest product to parameter struct */
                    orderLUp(arrayDetails, rowElements, colElements);
                }
            }
        }
    arrayDetails.shapeType = " L-Shape Up";    //Assign string to parameter struct
}   //14 Lines of code

/* Calculates four adjacent products in Skew Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void skewRight(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in a diagonal line down and to the right of the origin element. */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i + 1) < arrayDetails.rowLimit) && 
                ((j + (numProd / 2)) < arrayDetails.colLimit)){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    rowElements[k] = i + (k / (numProd / 2));
                    colElements[k] = j + fibonacci(k);
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
    arrayDetails.shapeType = "Skew Right";    //Assign string to parameter struct
}   //15 Lines of code

/* Calculates four adjacent products in Inverse Skew Right configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void invSkewRight(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in a diagonal line down and to the right of the origin element. */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i - 1) >= 0) && 
                ((j + (numProd / 2)) < arrayDetails.colLimit)){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    rowElements[k] = i - (k / (numProd / 2));
                    colElements[k] = j + fibonacci(k);
                    tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];
                }
                if(tempProd > arrayDetails.maxProd){
                    arrayDetails.maxProd = tempProd;
                    /* Assign four elements of greatest product to parameter struct */
                    orderInvSkewRight(arrayDetails, rowElements, colElements);
                }
            }
        }
    arrayDetails.shapeType = " Inverse Skew Right";    //Assign string to parameter struct
}   //14 Lines of code

/* Calculates four adjacent products in Skew Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, shape type string,
 *                         and origin elements.  */
void skewDown(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in a diagonal line down and to the right of the origin element. */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i + (numProd / 2)) < arrayDetails.rowLimit) && 
                ((j - 1) >= 0)){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    colElements[k] = j - (k / (numProd / 2));
                    rowElements[k] = i + fibonacci(k);
                    tempProd *= arrayDetails.dynArray[rowElements[k]][colElements[k]];
                }
                if(tempProd > arrayDetails.maxProd){
                    arrayDetails.maxProd = tempProd;
                    /* Assign four elements of greatest product to parameter struct */
                    orderSkewDown(arrayDetails, rowElements, colElements);
                }
            }
        }
    arrayDetails.shapeType = " Skew Down";    //Assign string to parameter struct
}   //14 Lines of code

/* Calculates four adjacent products in Inverse Skew Down configuration for
 * each member of a 2D array to determine the root number with the 
 * greatest product.  Also assigns a string name for the shape type.
 * Preconditions:     Populated 2D array and associated variables from
 *                         the ArrayInfo struct.  
 * Postconditions:    Populated 2D array and associate variables from
 *                         the ArrayInfo struct.  Modified maximum product,
 *                         row variable, column variable, and shape type 
 *                         string.  */
void invSkewDown(ArrayInfo &arrayDetails){
    /* Variable Declarations */
    int numProd = 4, tempProd = 1, rowElements[4], colElements[4];
    arrayDetails.maxProd = 0;
    
    /* Scan array and determine greatest product of four adjacent elements
     * in a diagonal line down and to the right of the origin element. */
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        for(int j = 0; j < arrayDetails.colLimit; j++){
            if(((i + (numProd / 2)) < arrayDetails.rowLimit) && 
                ((j + 1) < arrayDetails.colLimit)){
                tempProd = 1;
                for(int k = 0; k < numProd; k++){
                    colElements[k] = j + (k / (numProd / 2));
                    rowElements[k] = i + fibonacci(k);
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
    arrayDetails.shapeType = "Inverse Skew Down";    //Assign string to parameter struct
}   //15 Lines of code

/* Copies square row/column elements for four products to struct array for
 * use in output_highlighted function. */
 void orderSquare(ArrayInfo &arrayDetails, int rowArray[], int colArray[]){
    /* Variable Declaration */
    int numProd = 4;
    
    copy(rowArray, rowArray + numProd, arrayDetails.rowVar);
    copy(colArray, colArray + numProd, arrayDetails.colVar);
}   //3 Lines of code

/* Reorders zigZag_right row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
 void orderZigRight(ArrayInfo &arrayDetails, int rowArray[], int colArray[]){
    int numProd = 4, tempRows[4], tempCols[4];
    
    arrayDetails.origin[0] = rowArray[0];
    arrayDetails.origin[1] = colArray[0];
    
    tempRows[0] = rowArray[1];
    tempRows[1] = rowArray[3];
    tempRows[2] = rowArray[0];
    tempRows[3] = rowArray[2];
    
    tempCols[0] = colArray[1];
    tempCols[1] = colArray[3];
    tempCols[2] = colArray[0];
    tempCols[3] = colArray[2];
    
    copy(tempRows, tempRows + numProd, arrayDetails.rowVar);
    copy(tempCols, tempCols + numProd, arrayDetails.colVar);
}   //13 Lines of code

/* Reorders zagZig_right row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
 void orderZagRight(ArrayInfo &arrayDetails, int rowArray[], int colArray[]){
    int numProd = 4, tempRows[4], tempCols[4];
    
    arrayDetails.origin[0] = rowArray[0];
    arrayDetails.origin[1] = colArray[0];
    
    tempRows[0] = rowArray[0];
    tempRows[1] = rowArray[2];
    tempRows[2] = rowArray[1];
    tempRows[3] = rowArray[3];
    
    tempCols[0] = colArray[0];
    tempCols[1] = colArray[2];
    tempCols[2] = colArray[1];
    tempCols[3] = colArray[3];
    
    copy(tempRows, tempRows + numProd, arrayDetails.rowVar);
    copy(tempCols, tempCols + numProd, arrayDetails.colVar);
}   //13 Lines of code

/* Reorders lShapeRight row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
 void orderLRight(ArrayInfo &arrayDetails, int rowArray[], int colArray[]){
    int numProd = 4, tempRows[4], tempCols[4];
    
    arrayDetails.origin[0] = rowArray[0];
    arrayDetails.origin[1] = colArray[0];
    
    tempRows[0] = rowArray[3];
    tempRows[1] = rowArray[0];
    tempRows[2] = rowArray[1];
    tempRows[3] = rowArray[2];
    
    tempCols[0] = colArray[3];
    tempCols[1] = colArray[0];
    tempCols[2] = colArray[1];
    tempCols[3] = colArray[2];
    
    copy(tempRows, tempRows + numProd, arrayDetails.rowVar);
    copy(tempCols, tempCols + numProd, arrayDetails.colVar);
}   //13 Lines of code

/* Reorders lShapeLeft row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
 void orderLLeft(ArrayInfo &arrayDetails, int rowArray[], int colArray[]){
    int numProd = 4, tempRows[4], tempCols[4];
    
    arrayDetails.origin[0] = rowArray[0];
    arrayDetails.origin[1] = colArray[0];
    
    tempRows[0] = rowArray[2];
    tempRows[1] = rowArray[1];
    tempRows[2] = rowArray[0];
    tempRows[3] = rowArray[3];
    
    tempCols[0] = colArray[2];
    tempCols[1] = colArray[1];
    tempCols[2] = colArray[0];
    tempCols[3] = colArray[3];
    
    copy(tempRows, tempRows + numProd, arrayDetails.rowVar);
    copy(tempCols, tempCols + numProd, arrayDetails.colVar);
}   //13 Lines of code

/* Reorders lShapeUp row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
 void orderLUp(ArrayInfo &arrayDetails, int rowArray[], int colArray[]){
    int numProd = 4, tempRows[4], tempCols[4];
    
    arrayDetails.origin[0] = rowArray[0];
    arrayDetails.origin[1] = colArray[0];
    
    tempRows[0] = rowArray[3];
    tempRows[1] = rowArray[2];
    tempRows[2] = rowArray[1];
    tempRows[3] = rowArray[0];
    
    tempCols[0] = colArray[3];
    tempCols[1] = colArray[2];
    tempCols[2] = colArray[1];
    tempCols[3] = colArray[0];
    
    copy(tempRows, tempRows + numProd, arrayDetails.rowVar);
    copy(tempCols, tempCols + numProd, arrayDetails.colVar);
}   //13 Lines of code

/* Reorders invSkewRight row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
 void orderInvSkewRight(ArrayInfo &arrayDetails, int rowArray[], int colArray[]){
    int numProd = 4, tempRows[4], tempCols[4];
    
    arrayDetails.origin[0] = rowArray[0];
    arrayDetails.origin[1] = colArray[0];
    
    tempRows[0] = rowArray[2];
    tempRows[1] = rowArray[3];
    tempRows[2] = rowArray[0];
    tempRows[3] = rowArray[1];
    
    tempCols[0] = colArray[2];
    tempCols[1] = colArray[3];
    tempCols[2] = colArray[0];
    tempCols[3] = colArray[1];
    
    copy(tempRows, tempRows + numProd, arrayDetails.rowVar);
    copy(tempCols, tempCols + numProd, arrayDetails.colVar);
}   //13 Lines of code

/* Reorders skewDown row/column elements for four products for use in
 * output_highlighted function.  Copies ordered array to struct array and
 * saves origin element for output. */
 void orderSkewDown(ArrayInfo &arrayDetails, int rowArray[], int colArray[]){
    int numProd = 4, tempRows[4], tempCols[4];
    
    arrayDetails.origin[0] = rowArray[0];
    arrayDetails.origin[1] = colArray[0];
    
    tempRows[0] = rowArray[0];
    tempRows[1] = rowArray[2];
    tempRows[2] = rowArray[1];
    tempRows[3] = rowArray[3];
    
    tempCols[0] = colArray[0];
    tempCols[1] = colArray[2];
    tempCols[2] = colArray[1];
    tempCols[3] = colArray[3];
    
    copy(tempRows, tempRows + numProd, arrayDetails.rowVar);
    copy(tempCols, tempCols + numProd, arrayDetails.colVar);
}   //13 Lines of code

/* Returns Male Hofstadter Sequence 
 * Requires the femaleHofstadter function */
int maleHofstadter(int n){
    if(n == 0)      //Base case
        return 0;
    
    return n - femaleHofstadter(maleHofstadter(n - 1));    //Recursive call
}   //3 Lines of code

/* Returns Female Hofstadter Sequence 
 * Requires the maleHofstadter function */
int femaleHofstadter(int n){
    if(n == 0)      //Base case
        return 1;
        
    return n - maleHofstadter(femaleHofstadter(n - 1));    //Recursive call
}   //3 Lines of code

/* Returns Fibonnaci Sequence */
int fibonacci(int n){
    if(n == 0)
        return 0;
        
    if(n == 1)
        return 1;
        
    return (fibonacci(n - 1) + fibonacci(n - 2));
}   //5 Lines of code

/* Outputs details of greatest product function */
void output_results(ArrayInfo arrayDetails){
    /* Variable Declaration */
    int originElement = 0;
    
    /* Output results */
    cout << "\nMax Prod: " << arrayDetails.maxProd << ",\n";
    if(arrayDetails.shapeType[0] == ' '){
        cout << "Position: " << arrayDetails.origin[0]<< ", " 
             << arrayDetails.origin[1] << ",\n";
        cout << "Shape:" << arrayDetails.shapeType << endl;
    }
    else{
        cout << "Position: " << arrayDetails.rowVar[originElement]<< ", " 
             << arrayDetails.colVar[originElement] << ",\n";
        cout << "Shape: " << arrayDetails.shapeType << endl;
    }
}   //8 Lines of code

/* Outputs array with highlighted elements if output of array columns 
 * will be less than 80 characters wide. Origin elements determinate upon
 * the use of a reordering function controlled by the placement of a space
 * at the beginning of the shape type string. */
void output_highlighted(ArrayInfo arrayDetails){
    /* Variable Declaration */
    int prodElement = 0;
    
    if(arrayDetails.colLimit < 27){  //3 * 27 is greater than 80 characters
        cout << endl << endl;        //Extra lines for readability
        for(int i = 0; i < arrayDetails.rowLimit; i++){
            for(int j = 0; j < arrayDetails.colLimit; j++){
                if((prodElement < 4) && 
                    (i == arrayDetails.rowVar[prodElement]) && 
                    (j == arrayDetails.colVar[prodElement])){
                    cout << "\033[1;31m";    //Change output to bold and red
                    prodElement++;
                }
                if(arrayDetails.dynArray[i][j] < 10)    //Ensure two digit output
                    cout << "0" << arrayDetails.dynArray[i][j] << " ";
                else
                    cout << arrayDetails.dynArray[i][j] << " ";
                cout << "\033[0m";        //Reset output to standard
            }
            cout << endl;      //End of row
        }
        cout << endl;
    }
}   //15 Lines of code

/* Deletes dynamic array */
void delete_array(ArrayInfo &arrayDetails){
    for(int i = 0; i < arrayDetails.rowLimit; i++)
        delete [] arrayDetails.dynArray[i];
        
    delete [] arrayDetails.dynArray;
}   //3 Lines of code