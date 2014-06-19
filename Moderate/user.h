#ifndef KETY_USER_H
#define KETY_USER_H

#include <iostream>     //Necessary for input/output
#include <string>       //Necessary for string

using std::string;

namespace{
   string username;
   
   /* Returns true if string is 8 letters only */
   bool isValid(/*string usernameVar*/);
}

namespace Authenticate{
   /* Prompts user for username until a valid username is input */   
   void inputUserName( );
   
   /* Returns username string to calling function */
   string getUserName( );
}

#endif