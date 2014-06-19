/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     08/26/2013
 * Last Modified:    08/26/2013
 * Description:      Outputs a multiplication and division table of 
 *                   dimensions set by command-line arguments.
 * Input:            Row and column input as command-line arguments.
 * Output:           Multiplication and division tables of specified 
 *                   dimensions in a readable format.
 * Acknowledgements: Lab9 instructions
 ****************************************************************************/
 
#include <iostream>	/* Necessary for output */
#include <cstdlib>	/* Necessary for atoi() */
#include <iomanip>   /* Necessary for setprecision and fixed */

using std::cout;
using std::endl;

struct mult_div_values{
   int mult;
   float div;
};

/* Creates and returns a dynamic 2D array of mult_div_values structs */
mult_div_values** create_table(int m, int n);

/* Populate 2D Array of mult member values to multiplication table.
 * Multiplication table begins at 1. */
void set_mult_values(mult_div_values **table, int m, int n);

/* Populate 2D Array of div member values to division table.
 * Division table begins at 1. */
void set_div_values(mult_div_values **table, int m, int n);

/* Outputs multiplication table from 2D struct array */
void output_mult_table(mult_div_values **table, int m, int n);

/* Outputs division table from 2D struct array */
void output_div_table(mult_div_values **table, int m, int n);

/* Deletes dynamic 2D array of structs */
void delete_table(mult_div_values **table, int m, int n);

int main(int argc, char *argv[]){
   int rows = atoi(argv[1]), cols = atoi(argv[2]);
   
   mult_div_values **dynamicTable = create_table(rows, cols);
   
   set_mult_values(dynamicTable, rows, cols);
   
   set_div_values(dynamicTable, rows, cols);
   
   output_mult_table(dynamicTable, rows, cols);
   
   output_div_table(dynamicTable, rows, cols);
   
   delete_table(dynamicTable, rows, cols);
   
   return 0;
}     //8 Lines of code

/* Creates and returns a dynamic 2D array of mult_div_values structs */
mult_div_values** create_table(int m, int n){
   mult_div_values **table = new mult_div_values*[m];
   
   for(int i = 0; i < m; i++)
      table[i] = new mult_div_values[n];
   
   return table;
}     //4 Lines of code

/* Populate 2D Array of mult member values to multiplication table.
 * Multiplication table begins at 1. */
void set_mult_values(mult_div_values **table, int m, int n){
   for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++)
         table[i][j].mult = (i + 1) * (j + 1);
}     //3 Lines of code

/* Populate 2D Array of div member values to division table.
 * Division table begins at 1. */
void set_div_values(mult_div_values **table, int m, int n){
   for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++)
         table[i][j].div = ((double)i + 1.0) / ((double)j + 1.0);
}     //3 Lines of code

/* Outputs multiplication table from 2D struct array */
void output_mult_table(mult_div_values **table, int m, int n){
   cout << endl;
   
   for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++)
         cout << table[i][j].mult << "\t";
      
      cout << endl;     //End of row
   }
   
   cout << endl;
}     //6 Lines of code

/* Outputs division table from 2D struct array */
void output_div_table(mult_div_values **table, int m, int n){
   cout << endl;
   
   for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++)
         cout << std::setprecision(2) << std::fixed
              << table[i][j].div << "\t";
      
      cout << endl;     //End of row
   }
   
   cout << endl;
}     //6 Lines of code

/* Deletes dynamic 2D array of structs */
void delete_table(mult_div_values **table, int m, int n){
   for(int i = 0; i < m; i++)
      delete [] table[i];
      
   delete [] table;
}     //3 Lines of code