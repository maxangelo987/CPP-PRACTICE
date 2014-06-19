/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     11/9/2013
 * Last Modified:    11/9/2013
 * Description:      Demonstrates and times iterative and recursive Fibonacci 
 *                   function.  The recursive Fibonacci sequence has been
 *                   improved to reduce the number of recursive iterations.
 * Output:           Outputs Fibonacci sequence for odd numbers 1 through 15
 *                   and the time it took to calculate.
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>
#include <sys/time.h>      /* Necessary for timing functions */
#include <cmath>
#include <chrono>

#define FIB_ARRAY_SIZE 100
long long int fibArray[FIB_ARRAY_SIZE];      //Holds Fibonacci up to FIB_ARRAY_SIZE

using std::cout;

/* Returns Fibonacci Sequence at n using iteration */
long long int iterFibo(long long int n);

/* Returns Fibonacci Sequence at n using recursion and an array.  The array
   limits the number of recursive calculation to improve performance */
long long int fibonacci(long long int n);

int main(){
   typedef struct timeval time;		
   time stop, start;
   
   cout << "\n";
   
   for(long long int i = 0; i < 1; i++){
      /* Iterative */
      cout << "F" << (int)pow(2.0, i) << " ";
      //gettimeofday(&start, NULL);	//Record start time
      auto start = std::chrono::high_resolution_clock::now();
      cout << iterFibo((int)pow(2.0, i));
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
   for(long long int i = 0; i < 7; i++){
      /* Recursive */
      cout << "F" << (int)pow(2.0, i) << " ";
      //gettimeofday(&start, NULL);	//Record start time
      auto start = std::chrono::high_resolution_clock::now();
      cout << fibonacci((int)pow(2.0, i));
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

/* Returns Fibonacci Sequence at n using iteration*/
long long int iterFibo(long long int n){
   long long int i = 0, iPlus1 = 1, iPlus2 = 1;
   
   for(long long int j = 1; j < n; j++){
      iPlus2 = i + iPlus1;
      i = iPlus1;       //Determine i for next iteration
      iPlus1 = iPlus2;  //Determine iPlus1 for next iteration or Fn
   }
   
   if(n == 0)
      return 0;
   
   return iPlus1;
}


/* Returns Fibonacci Sequence at n using recursion and an array.  The array
   limits the number of recursive calculation to improve performance */
long long int fibonacci(long long int n){
   if(n > (FIB_ARRAY_SIZE - 1)){
      cout << "\n\nArray size exceeded. Array size set to FIB_ARRAY_SIZE.\n\n";
      n = FIB_ARRAY_SIZE - 1;
   }
      
   if(n == 0){
      fibArray[n] = 0;
      return 0;
   }
   
   if(n == 1){
      fibArray[n] = 1;
      fibArray[n + 1] = fibArray[n] + fibonacci(n - 1);
      return 1;
   }
   
   fibArray[n + 1] = fibonacci(n - 1) + fibArray[n];
   
   return (fibArray[n]);
}