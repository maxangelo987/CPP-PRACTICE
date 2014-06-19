/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/09/2013
 * Last Modified:    10/09/2013
 * Description:      Collect a username and password that meets format
 *                   requirements and output to screen.
 * Input:            An 8 letter username and 8 character password. The
 *                   password must have at least one non-letter.
 * Output:           Prompts for input and outputs the valid username and
 *                   password.
 * Acknowledgements: Absolute C++ textbook
 ****************************************************************************/

#include <iostream>     //Necessary for input/output
#include "user.h"       //Necessary for username-related functions
#include "password.h"   //Necessary for password-related functions

using std::cout;
using std::endl;
using Authenticate::inputUserName;
using Authenticate::getUserName;
using Authenticate::inputPassword;
using Authenticate::getPassword;

int main(){
   /* Prompt user for valid username and password */
   inputUserName( );
   inputPassword( );

   /* Echo username and password to user */
   cout << "Your username is " << getUserName( )
        << " and your password is: "
        << getPassword( ) << endl;

   return 0;
}