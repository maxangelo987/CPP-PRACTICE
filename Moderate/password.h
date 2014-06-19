#ifndef KETY_PASSWORD_H
#define KETY_PASSWORD_H

#include <iostream>     //Necessary for input/output
#include <string>       //Necessary for string

using std::string;

namespace{
   string password;
   
   /* Returns true if string is at least 8 characters with at least one
      non-letter. */   
   bool isValid(string passwordVar);
}

namespace Authenticate{
   /* Prompt user for a password until a valid password is input */
   void inputPassword( );

   /* Returns password string to calling function */
   string getPassword( );
}

#endif