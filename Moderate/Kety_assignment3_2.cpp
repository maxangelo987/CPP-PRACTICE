/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/13/2013
 * Last Modified:    10/14/2013
 * Description:      Demonstrates the capabilities of the 'overloading' class.  
 *                   The 'overloading' class is used primarily to define char
 *                   elements of an array during declaration while providing
 *                   member support for retrieving and modifying the preset
 *                   element values.  Elements are predefined as '#'.
 *                   The 'overloading' class array has a maximum of 100
 *                   elements; so each instance has less than that number of
 *                   available elements to define.
 *                   The default constructor defines 10 elements to '#'.
 * Input:            Characters for replacing existing values and an integer
 *                   for defining a new class instance of that size. The user
 *                   is also prompted for a string of characters for use in
 *                   the integer and char array constructor.
 * Output:           Prompts for user input.  Introduction and instructions
 *                   that demonstrate proper use of 'overloading' class.
 * Acknowledgements: Absolute C++, Seventh Edition
 ****************************************************************************/

#include <iostream>  /* Necessary for input/output */
#include <cstdlib>
#include <cstring>   /* Necessary for use of strlen */

#define DEFAULT_OVERLOADING_ARRAY_SIZE 100

using std::cout;
using std::cin;
using std::endl;
using std::ostream;

class overloading{
   public:
      /* Default constructor - Initializes first 10 elements to '#' */
      overloading();
      /* Integer argument constructor - Initializes first sz elements to '#' 
         and error checks for sz integers outside the range of 1 to 100 */
      overloading(const int& sz);
      /* Integer and char array argument constructor - Copies the char array
         into an 'overloading' array of the same size */
      overloading(const int& sz, const char oldArray[]);

      /* Array operator overload */
      char& operator[](const int& index);
      
      /* Returns value for private member variable 'size' */
      int get_size();
      
      /* Overloaded operators handling output of overloaded class */
      friend ostream& operator <<(ostream& outputStream, overloading& overload);

   private:
      char array[DEFAULT_OVERLOADING_ARRAY_SIZE];
      int size;
};

int main( ){
   /* Variable declarations */
   overloading a;
   char charArray[DEFAULT_OVERLOADING_ARRAY_SIZE];
   int size = 0;
   
   cout << "\n\nWelcome to the 'overloading' class demonstration!";
   
   cout << "\n\nFirst, a demonstration of 'overloading' initialization.";
   cout << "\n'overloading' class name 'a' (no arguments) has its first\n";
   cout << a.get_size() << " elements initialized as: \n";
   for(int i = 0; i < a.get_size(); i++)
      cout << a[i] << ' ';
   
   cout << "\n\n'overloading' allows manipulations as well.";
   cout << "\na[0] and a[1] are still initialized as: "
        << a[0] << a[1] << endl;   
   cout << "Enter two letters to replace them (no spaces): ";
   cin >> a[0] >> a[1];
   cout << "a[0] and a[1] are now set to: ";
   for(int i = 0; i < 2; i++)
      cout << a[i];
      
   cout << "\n\nNow a demonstration of 'overloading' argument initialization "
        << "to '#'";
   cout << "\nThis will set all elements in the array up to, but not\n";
   cout << "including, the number input.\n"; 
   cout << "The greatest element possible is '99'\n";
   cout << "Please enter the greatest number of elements to initialize "
        << "(0 - 99): ";
   cin >> size;
   overloading b(size);
   cout << "\nElements up to #" << b.get_size()
        << " in 'overloading' array is(are) now initialized:\n";
   for(int i = 0; i <= b.get_size(); i++)
      cout << b[i] << ' ';
   
   cout << "\n\nFinally, let's copy a char array into this class.\n";
   cout << "Please enter a string of 1 - " << DEFAULT_OVERLOADING_ARRAY_SIZE
        << " characters:\n";
   cin.ignore(1000, '\n');    //Reset input stream from getline()
   cin.getline(charArray, DEFAULT_OVERLOADING_ARRAY_SIZE);
   overloading charCopy(strlen(charArray), charArray);
   cout << "\nAn instance of this class called 'charArray' now contains:\n";
   cout << charCopy;
   
   cout << endl << endl;      //Additional whitespace for readability
   
   return 0;
}

/* Default constructor - Initializes first 10 elements to '#' */
overloading::overloading(){
   size = 10;
   for(int i = 0; i < size; i++)
      array[i] = '#';   
}

/* Integer argument constructor - Initializes first sz elements to '#' 
   and error checks for sz integers outside the range of 1 to 100 */
overloading::overloading(const int& sz){
   if((sz < DEFAULT_OVERLOADING_ARRAY_SIZE) && (sz >= 0)){
      size = sz;
      for(int i = 0; i <= sz; i++)
         array[i] = '#';         
   }
   else if(sz < 0){
      cout << "Index value out of range - Too low (below zero).\n";
      exit(1);
   }
   else{   
      cout << "Index value out of range - Too high "
           << "(" << DEFAULT_OVERLOADING_ARRAY_SIZE << " or greater)\n";
      exit(1);
   }
}

/* Integer and char array argument constructor - Copies the char array
   into an 'overloading' array if the sizes are compatible */
overloading::overloading(const int& sz, const char oldArray[]){
   if((sz < DEFAULT_OVERLOADING_ARRAY_SIZE) && (sz >= 0)){
      size = sz;
      for(int i = 0; i <= sz; i++)
         array[i] = oldArray[i];         
   }
   else if(sz < 0){
      cout << "Index value out of range - Too low (below zero).\n";
      exit(1);
   }
   else{   
      cout << "Index value out of range - Too high "
           << "(" << DEFAULT_OVERLOADING_ARRAY_SIZE << " or greater)\n";
      exit(1);
   }
}

/* Array operator overload */
char& overloading::operator[](const int& index){
   if (index >= 0)
      return array[index];
   else{
      cout << "Index value out of range - Too low (below zero).\n";
      exit(1);
   }
}

/* Returns value for private member variable 'size' */
int overloading::get_size(){
   return size;
}

/* Overloaded operators handling output of overloading class */
ostream& operator <<(ostream& outputStream, overloading& overload){
   for(int i = 0; i < overload.get_size(); i++)
      outputStream << overload[i];
   
   return outputStream;
}