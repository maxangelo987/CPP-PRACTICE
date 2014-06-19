/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     11/8/2013
 * Last Modified:    11/8/2013
 * Description:      Demonstrates and times iterative and recursive fibonacci 
 *                   function.
 * Output:           Outputs fibonacci sequence for odd numbers 1 through 15
 *                   and the time it took to calculate.
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>
#include <sys/time.h>	/* Necessary for timing functions */
#include <cmath>
#include <chrono>

using std::cout;

/* Returns Fibonnaci Sequence at n using iteration */
long long int iterFibo(long long int n);

/* Returns Fibonnaci Sequence at n using recursion */
long long int fibonacci(long long int n);

int main(){
   typedef struct timeval time;		
   time stop, start;
   
   cout << "\n";
   
   for(long long int i = 0; i < 32; i++){
      /* Iterative */
      cout << "F" << i << " ";
      //gettimeofday(&start, NULL);	//Record start time
      auto start = std::chrono::high_resolution_clock::now();
      cout << iterFibo(i);
      auto finish = std::chrono::high_resolution_clock::now();
      //gettimeofday(&stop, NULL);	   //Record stop time
      
      /* Output timing for calculation */		
      cout << " Time for iterative calculation:\t\t"; 
      /*if(stop.tv_sec > start.tv_sec)
         cout << stop.tv_sec - start.tv_sec << " s\n";
      else
         cout << stop.tv_usec - start.tv_usec << " ms\n";*/
      cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";
   }
   cout << "\n";
   for(long long int i = 0; i < 16; i++){
      /* Recursive */
      cout << "F" << i+16 << " ";
      //gettimeofday(&start, NULL);	//Record start time
      auto start = std::chrono::high_resolution_clock::now();
      cout << fibonacci(i+16);
      auto finish = std::chrono::high_resolution_clock::now();
      //gettimeofday(&stop, NULL);	   //Record stop time
      
      /* Output timing for calculation */		
      cout << " Time for recursive calculation:\t\t"; 
      /*if(stop.tv_sec > start.tv_sec)
         cout << stop.tv_sec - start.tv_sec << " s\n";
      else
         cout << stop.tv_usec - start.tv_usec << " ms\n";*/
      cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";
   }
   
   cout << "\n";
   
   return 0;
}

/* Returns Fibonnaci Sequence at n using iteration*/
long long int iterFibo(long long int n){
   long long int i = 0, iPlus1 = 1, iPlus2 = 1;
   
   for(int j = 1; j < n; j++){
      iPlus2 = i + iPlus1;
      i = iPlus1;       //Determine i for next iteration
      iPlus1 = iPlus2;  //Determine iPlus1 for next iteration or Fn
   }
   
   if(n == 0)
      return 0;
   
   return iPlus1;
}

/* Returns Fibonnaci Sequence at n using recursion */
long long int fibonacci(long long int n){
   if(n == 0)
      return 0;
   
   if(n == 1)
      return 1;
      
   return (fibonacci(n - 1) + fibonacci(n - 2));
}