#include "password.h"   //Includes variable and function declarations

using std::cout;
using std::cin;
using std::endl;
using std::string;

namespace{
   /* Returns true if string is at least 8 characters with at least one
      non-letter. */
   bool isValid( ){
      bool validity = false;
      int size = password.size();
      
      if(size >= 8){
         for(int i = 0; i < size; i++)
            if(!(isalpha(password[i])))
               validity = true;
      }
      
      return validity;
   }
}

namespace Authenticate{
   /* Prompt user for a password until a valid password is input */
   void inputPassword( ){
      do{
         cout << "Enter your password (at least 8 characters "
              << "and at least one non-letter)" << endl;
         cin >> password;
      } while(!isValid( ));
   }

   /* Returns password string to calling function */
   string getPassword( ){
      return password;
   }
}