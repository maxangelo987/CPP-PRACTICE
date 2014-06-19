/***********************************************************************
**	Author:		    Robert Kety
**	Creation Date:	07/08/2013
**	Last Modified:	06/18/2014
**	Description:	Determines the number of bits for integer and
**			        floating-point variables.  This is a demonstration
**                  of the sizeof functionality in C++
**	Input:		    The size of each variable determined by the 
**			        sizeof function and the number of bits in a
**			        byte determined by the macro NUM_BITS_IN_BYTE.
**	Output:		    The value of each variable type and its 
**			        corresponding bits of memory.
**	Acknowledgement:lab2.pdf
***********************************************************************/

#include <iostream>

#define NUM_BITS_IN_BYTE 8

int main() {
	std::cout 	<< "A char takes up " 
			<< sizeof(char) * NUM_BITS_IN_BYTE 
			<< " bits of memory\n";
	std::cout 	<< "An int takes up " 
			<< sizeof(int) * NUM_BITS_IN_BYTE 
			<< " bits of memory\n";
	std::cout 	<< "A float takes up " 
			<< sizeof(float) * NUM_BITS_IN_BYTE 
			<< " bits of memory\n";
	std::cout 	<< "A long takes up " 
			<< sizeof(long) * NUM_BITS_IN_BYTE 
			<< " bits of memory\n";
	std::cout 	<< "A short takes up " 
			<< sizeof(short) * NUM_BITS_IN_BYTE 
			<< " bits of memory\n";
	std::cout 	<< "A double takes up " 
			<< sizeof(double) * NUM_BITS_IN_BYTE 
			<< " bits of memory\n";
	std::cout 	<< "A bool takes up " 
			<< sizeof(bool) * NUM_BITS_IN_BYTE 
			<< " bits of memory\n";
	
	return 0;
}
