/*******************************************************************************
**	Author:		Robert Kety
**	Date Created:	07/08/2013
**	Last Modified:	07/08/2013
**	File Name:	Kety_functions.cpp
**	Description:	A demonstration of various functions available in the
**			cmath library
**	Input:		Equations stated in step 14 of lab2.pdf. Entered 
**			directly into code.
**	Output:		Description of equation and solution to equation in 
**			correct integer- of floating-point-type format.
**	Acknowledgement:http://www.cplusplus.com/reference/cmath/
*******************************************************************************/


#include <iostream>
#include <cmath>

#define PI 3.14159265		//Global constant for PI

int main() {
	long long int 	powerFunction1, powerFunction5;	//To prevent overflow
	short 		powerFunction2, powerFunction3, absAndRoundFunction;
	float 		powerFunction4, roundFunction, trigFunction, 
			expFunction1, expFunction2, expFunction3;

	powerFunction1		= (long long int)(std::pow(((float)2), 32)) - 1;
	powerFunction2		= std::pow(5.0, 3);
	powerFunction3 		= std::sqrt((float)25);
	powerFunction4	 	= std::sqrt((float)96);
	roundFunction 		= std::fmod(34.0, 5);
	trigFunction 		= (std::sin(90 * PI / 180) - std::cos(30 * PI / 180)) * 180 / PI;	//Output is in degrees because input is in degrees
	expFunction1 		= std::log((float)5);
	expFunction2	 	= std::log10((float)100);
	expFunction3 		= std::exp(5.0);
	powerFunction5 		= std::sqrt(std::pow(((float)2), 64));
	absAndRoundFunction 	= std::ceil(std::abs(-2.5));

	std::cout << "(2^32) - 1 = \t\t\t\t" << powerFunction1 << std::endl;
	std::cout << "5.0^3 = \t\t\t\t" << powerFunction2 << std::endl;
	std::cout << "sqrt(25) = \t\t\t\t" << powerFunction3 << std::endl;
	std::cout << "sqrt(96) = \t\t\t\t" << powerFunction4 << std::endl;
	std::cout << "34.0 mod 5 = \t\t\t\t" << roundFunction << std::endl;
	std::cout << "sin(90 degrees) - cos (30 degrees) = \t" << trigFunction << " degrees\n";		//Output is in degrees because input is in degrees
	std::cout << "ln(5) = \t\t\t\t" << expFunction1 << std::endl;
	std::cout << "Common logarithm of 100 = \t\t" << expFunction2 << std::endl;
	std::cout << "e^5.0 = \t\t\t\t" << expFunction3 << std::endl;
	std::cout << "sqrt(2^64) = \t\t\t\t" << powerFunction5 << std::endl;
	std::cout << "Ceiling of the absolute value of -2.5 = " << absAndRoundFunction << std::endl;
	std::cout  << std::endl;
	
	return 0;
}
