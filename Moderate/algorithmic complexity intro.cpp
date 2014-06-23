/*
    Author:       Robert Kety
    Modified:     06/23/2014
    Descriptions: This is a simple program for timing different operations - an
                  introductory examination of algorithmic complexity.
*/
#include <iostream>
#include <cmath>         /* For use of pow() */
#include <sys/time.h>      /* Necessary for timing functions */

using std::cout;

void partA(unsigned long long int n);
void partB(unsigned long long int n);
void partC(unsigned long long int n);
void partD(unsigned long long int n);
void partE(unsigned long long int n);
void partF(unsigned long long int n);

int main(){
   unsigned long long int sum = 0, n = 0; 
  
   

   //Part A
   cout << "\n";
   for(int q = 1; q < 5; q++){
      n =  (int)pow(10.0, q);
      
      cout << "Time to perform part a at n = " << n << ":\t\t"; 
       partA(n);
      
       
   }
   
   //Part B
   cout << "\n";
   for(int q = 1; q < 5; q++){
      n =  (int)pow(10.0, q);
      
      cout << "Time to perform part b at n = " << n << ":\t\t"; 
       partB(n);
      
       
   }
   
   //Part C
   cout << "\n";
   for(int q = 1; q < 5; q++){
      n =  (int)pow(10.0, q);
      
      cout << "Time to perform part c at n = " << n << ":\t\t"; 
       partC(n);
      
       
   }
   
   //Part D
   cout << "\n";
   for(int q = 1; q < 5; q++){
      n =  (int)pow(10.0, q);
      
      cout << "Time to perform part d at n = " << n << ":\t\t"; 
       partD(n);
      
       
   }
   
   //Part E
   cout << "\n";
   for(int q = 1; q < 5; q++){
      n =  (int)pow(10.0, q);
      
      cout << "Time to perform part e at n = " << n << ":\t\t"; 
       partE(n);
      
       
   }
   
   //Part F
   cout << "\n";
   for(int q = 1; q < 5; q++){
      n =  (int)pow(10.0, q);
      
      cout << "Time to perform part f at n = " << n << ":\t\t"; 
       partF(n);
      
       
   }
   
   cout << "\n\n";
   
   return 0;
}

void partA(unsigned long long int n){
   typedef struct timeval time;
   time start, stop;
   unsigned long long int sum, i;
   
   gettimeofday(&start, NULL);	//Record start time
   sum = 0;
      for(i = 0; i < n; i++)
         sum = sum + 1;
   gettimeofday(&stop, NULL);	   //Record stop time
   
   if(stop.tv_sec > start.tv_sec)
      cout << stop.tv_sec - start.tv_sec << " seconds\n";
   else
      cout << stop.tv_usec - start.tv_usec << " microseconds\n";
}

void partB(unsigned long long int n){
   typedef struct timeval time;
   time start, stop;
   unsigned long long int sum, i, j;
   
   gettimeofday(&start, NULL);	//Record start time
   sum = 0;
   for(i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         sum = sum + 1;
   gettimeofday(&stop, NULL);	   //Record stop time
   
   if(stop.tv_sec > start.tv_sec)
      cout << stop.tv_sec - start.tv_sec << " seconds\n";
   else
      cout << stop.tv_usec - start.tv_usec << " microseconds\n";
}

void partC(unsigned long long int n){
   typedef struct timeval time;
   time start, stop;
   unsigned long long int sum, i, j;
   
   gettimeofday(&start, NULL);	//Record start time
   sum = 0;
      for(i = 0; i < n; i++)
         for(j = 0; j < i; j++)
            sum = sum + 1;
   gettimeofday(&stop, NULL);	   //Record stop time
   
   if(stop.tv_sec > start.tv_sec)
      cout << stop.tv_sec - start.tv_sec << " seconds\n";
   else
      cout << stop.tv_usec - start.tv_usec << " microseconds\n";
}

void partD(unsigned long long int n){
   typedef struct timeval time;
   time start, stop;
   unsigned long long int sum, i, j;
   
   gettimeofday(&start, NULL);	//Record start time
   sum = 0;
   for (i = 0; i < n; i++)
      for (j = 0; j < (n * n); j++)
         sum = sum + 1;
   gettimeofday(&stop, NULL);	   //Record stop time
   
   if(stop.tv_sec > start.tv_sec)
      cout << stop.tv_sec - start.tv_sec << " seconds\n";
   else
      cout << stop.tv_usec - start.tv_usec << " microseconds\n";
}

void partE(unsigned long long int n){
   typedef struct timeval time;
   time start, stop;
   unsigned long long int sum, x, i, j;
   
   gettimeofday(&start, NULL);	//Record start time
   sum = 0;
   x = n;
   for(i = 0; i < n; i++)
      for(j = 0; j < x; j++){
         sum = sum + 1;
         x = x / 2;
      }
   gettimeofday(&stop, NULL);	   //Record stop time
   
   if(stop.tv_sec > start.tv_sec)
      cout << stop.tv_sec - start.tv_sec << " seconds\n";
   else
      cout << stop.tv_usec - start.tv_usec << " microseconds\n";
}

void partF(unsigned long long int n){
   typedef struct timeval time;
   time start, stop;
   unsigned long long int sum, i, j, k;
   
   gettimeofday(&start, NULL);	//Record start time
   sum = 0;
   for(i = 0; i < n; i++)
      for(j = 0; j <= i; j++)
         for(k = 0; k < n; k++)
            sum = sum + 1;
   gettimeofday(&stop, NULL);	   //Record stop time
   
   if(stop.tv_sec > start.tv_sec)
      cout << stop.tv_sec - start.tv_sec << " seconds\n";
   else
      cout << stop.tv_usec - start.tv_usec << " microseconds\n";
}