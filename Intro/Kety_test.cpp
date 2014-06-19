/************************************************************************
 *	Author:		Robert Kety
 *	Date Created:	07/10/2013
 *	Last Modified:	07/11/2013
 *	File Name:	Kety_test.cpp
 *	Description:	Simple program to demonstrate input/output.
 *	Input:		Integer response from user.
 *	Output:		Prompt for input and output based on input.
 *	Acknowledgements:
 *			Lab3.pdf
 * ********************************************************************/
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {

   int loveVi = 0;

   cout << "Do you love vi? (1 = true, 2 = false) " << endl;
   cin >> loveVi;

   switch (loveVi){
      case(2):
	 cout << "You hate vi?!" << endl << endl;
	 break;
      case(1):
	 cout << "You love vi!" << endl << endl;
	 break;
      default:
	 cout << "That is not a correct response! EJECT!!" << endl << endl;
   }

   return 0;
}
