#include <iostream> /*included to allow for cout and cin*/
#include <ctime> /*included to allow time()*/
#include <cstdlib> /*include to allow rand() and srand()*/

using std::cout;
using std::endl;

int main() {
	int x; /* variable to hold our random integer*/
	srand(time(NULL)); /*seeds random number generator. Do this just once*/
	
	x = rand();
	cout << "x = " << x << endl;
	
	x = rand();
	cout << "x = " << x << endl;
	
	x = rand();
	cout << "x = " << x << endl;
}
