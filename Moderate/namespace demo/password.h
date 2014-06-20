/*
    Contributor:    Robert Kety and unknown
    Description:    This is based off of skeleton code I received from an unknown author.
                    It is included as part of a larger multi-file program and not intended
                    for distribution.
*/
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