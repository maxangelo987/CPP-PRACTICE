#include <iostream> /*included to allow for cout and cin*/
#include <ctime> /*included to allow time()*/
#include <cstdlib> /*include to allow rand() and srand()*/
using std::cout;
using std::cin;
using std::endl;
int main() {
int x; /* variable to hold our random integer*/
int guessNum;

srand(time(NULL)); /*seeds random number generator. Do this just once*/
x = rand() % 50;
cout << "x = " << x << endl;
cout << "Choose a # between 0 and 50: " << endl;
cin >> guessNum;
for (int guessCount = 0; guessCount < 5; guessCount++){
	if (guessNum >= 00 && guessNum <= 50){
		if (guessNum < x){
			cout << "Too low!" << endl;
			cin >> guessNum;
		} else if (guessNum > x){
			cout << "Too high!" << endl;
			cin >> guessNum;
		} else if (guessNum == x){
			cout << "Perfect guess!" << endl << endl;
			break;
		}
	} else
		cout << "That's not between 0 and 50!!" << endl << endl;
		break;
}
	return 0;
}