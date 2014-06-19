/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     11/8/2013
 * Last Modified:    11/8/2013
 * Description:      Sample code to test the getProductID function.  The 
 *                   getProductID function scans an array of strings for a
 *                   matching string and returns a corresponding number
 *                   associated with that product.  If no there is no match,
 *                   the target string is thrown as an unhandled exception by
 *                   the getProductID function.  The main function catches and
 *                   handles the exception.
 * Input:            An integer array, string array, array size, and target
 *                   string is input via the main function.
 * Output:           Outputs the product ID number for each matching string or
 *                   a string related to an unsuccessful search.
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;

/* The getProductID function scans an array of strings for a matching string 
   and returns a corresponding number associated with that product.  If no 
   there is no match, the target string is thrown as an unhandled exception by
   the getProductID function. */
int getProductID(int ids[], string names[], int numProducts, 
                 string target) throw (string);

int main(){    // Sample code to test the getProductID function
   int productIds[] = {4, 5, 8, 10, 13};
   string products[] = {"computer", "flash drive", "mouse", "printer",
                        "camera"};
   try{
      cout << getProductID(productIds, products, 5, "mouse") << endl;
      cout << getProductID(productIds, products, 5, "camera") << endl;
      cout << getProductID(productIds, products, 5, "laptop") << endl;
   }
   catch(string e){
      cout << "Product \"" << e << "\" not found!\n";
   }
   
   return 0;
}

/* The getProductID function scans an array of strings for a matching string 
   and returns a corresponding number associated with that product.  If no 
   there is no match, the target string is thrown as an unhandled exception by
   the getProductID function. */
int getProductID(int ids[], string names[], int numProducts, 
                 string target) throw(string){
   for(int i = 0; i < numProducts; i++)
      if (names[i] == target)
         return ids[i];
   
   throw target;
}