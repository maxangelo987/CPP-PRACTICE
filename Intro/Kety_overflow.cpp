#include <iostream>

using std::cout;
using std::endl;
using std::cin;

void incrementIfPossible(short int& summaryVar, short int incrementalVar);
void incrementIfPossible(int& summaryVar, int incrementalVar);

int main(){
short int x = 21, y = 2;
cout << "\nEnter summary variable: ";
cin >> x;
cout << "\nEnter incremental variable: ";
cin >> y;
cout << endl << endl << x << endl << y << endl << x + y << endl << endl;
incrementIfPossible(x, y);
cout << x << endl << endl;

return 0;
}

void incrementIfPossible(short int& summaryVar, short int incrementalVar){
if(summaryVar > (summaryVar + incrementalVar))
cout << "\n\nOverflow Error\n\n";
else
summaryVar += incrementalVar;
}

void incrementIfPossible(int& summaryVar, int incrementalVar){
if(summaryVar > (summaryVar + incrementalVar))
cout << "\n\nOverflow Error\n\n";
else
summaryVar += incrementalVar;
}

