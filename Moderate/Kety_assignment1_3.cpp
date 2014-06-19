/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/08/2013
 * Last Modified:    10/09/2013
 * Description:      Calculates and outputs the sum of all the multiples of
 *                   3 or 5 below 1000.
 * Input:            None.
 * Output:           Displays the sum of all multiples of 3 or 5 below 1000.
 * Acknowledgements: None.
 ****************************************************************************/

#include <iostream>

using std::cout;
using std::endl;

/* Returns the sum of all multiples of 3 or 5 below 1000 */
int sumMultiples();

int main(){
   cout << "\nWelcome! The sum of all multiples of 3 or 5 below 1000 is:";
   cout << endl << sumMultiples() << endl << endl;
   
   return 0;
}

/* Returns the sum of all multiples of 3 or 5 below 1000 */
int sumMultiples(){
   int sum = 0;
   
   for(int i = 0; i < 1000; ++i)
      if((!(i % 3)) || (!(i % 5)))
         sum += i;
   
   return sum;
}