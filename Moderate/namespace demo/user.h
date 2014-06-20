/*
    Contributor:    Robert Kety and unknown
    Description:    This is based off of skeleton code I received from an unknown author.
                    It is included as part of a larger multi-file program and not intended
                    for distribution.
*/
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