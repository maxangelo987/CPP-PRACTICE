/*****************************************************************************
 * Author:              Robert Kety
 * Date Created:        08/07/2013
 * Last Modified:       08/13/2013
 * File Name:           Kety_lab7.cpp
 * Description:         Demonstrate pointer variable declaration, definition,
 *                      and output.
 * Input:               No input from user, but three variables are defined
 *                      for value and reference throughout program.
 * Output:              Outputs reference locations and values for variables
 *                      and pointer variables.
 * Acknowledgements:	   Lab7 instructions.
 ****************************************************************************/
 
 #include <iostream>    /* Necessary for output */
 
 using std::cout;
 using std::endl;
 
int main(){
   /*Variable declarations */
   double d1 = 7.8,
          d2 = 10.0,
          d3 = 0.009;
   double *d;
   double **dp;
   
   cout << endl;  //Formatting preference for clear output
   
   /* Aim point "d" at each double variable and output to screen. */
   d = &d1;
   cout << "d is at: " << &d << " d1 is at: " << d 
        << " and has a value of: " << *d << endl;
   
   d = &d2;
   cout << "d is at: " << &d << " d2 is at: " << d 
        << " and has a value of: " << *d << endl;

   d = &d3;
   cout << "d is at: " << &d << " d3 is at: " << d 
        << " and has a value of: " << *d << endl;

   
   cout << endl;  //Formatting preference for clear output
   
   /* Aim double point "dp" to pointer variable "d" */
   dp = &d;
   
   /* Aim point "d" at each double variable and output to screen all reference
    * and values associated with double pointer "dp" (i.e., "&dp", "dp",
    * "*dp", and "**dp". */
   d = &d1;
   cout << "dp is at: " << &dp << " and references d at: " << dp
        << " d references d1 at: " << *dp
        << " with a value of: " << **dp << endl;
   d = &d2;
   cout << "dp is at: " << &dp << " and references d at: " << dp
        << " d references d2 at: " << *dp
        << " with a value of: " << **dp << endl;
   d = &d3;
   cout << "dp is at: " << &dp << " and references d at: " << dp
        << " d references d3 at: " << *dp
        << " with a value of: " << **dp << endl;
   
   cout << endl;  //Formatting preference for clear output
   
   return 0;
}
