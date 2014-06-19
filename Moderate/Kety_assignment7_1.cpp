/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     11/8/2013
 * Last Modified:    11/8/2013
 * Description:      Demonstration of the recursive fibonacci function.
 * Output:           Outputs fibonacci sequence from F0 to Fn, where n is set
 *                   by the integer variable nthNum.
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>

using std::cout;

/* Returns Fibonnaci Sequence at n */
int fibonacci(int n);

int main(){
   int nthNum = 16;
   
   cout << "\n\n";
   
   for(int i = 0; i < nthNum; i++){
      cout << fibonacci(i);
      if((i + 1) < nthNum)
         cout << ", ";
   }
   
   cout << "\n\n";
   
   return 0;
}

/* Returns Fibonnaci Sequence */
int fibonacci(int n){
   if(n == 0)
      return 0;
   
   if(n == 1)
      return 1;
      
   return (fibonacci(n - 1) + fibonacci(n - 2));
}