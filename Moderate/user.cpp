#include "user.h"   //Includes variable and function declarations

using std::cout;
using std::cin;
using std::endl;
using std::string;

namespace{
   /* Returns true if string is 8 letters only */
   bool isValid( ){
      bool validity = false;
      int size = username.size();
      
      if(size == 8)
         validity = true;
         for(int i = 0; i < size; i++)
            if(!(isalpha(username[i])))
               validity = false;
      
      return validity;
   }
}

namespace Authenticate{
   /* Prompts user for username until a valid username is input */   
   void inputUserName( ){
      do{
         cout << "Enter your username (8 letters only)" << endl;
         cin >> username;
      } while(!isValid( ));
   }

   /* Returns username string to calling function */
   string getUserName( ){
      return username;
   }
}