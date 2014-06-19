/*****************************************************************************
 *	Author:		    Robert Kety
 *	Date Created:	07/12/2013
 *	Last Modified:	06/18/2014
 *	Description:	Buoyancy calculator.  Calculates if a sphere will float 
 *                  depending on the radius and weight of the sphere.
 *	Input:		    Weight in pounds and radius in feet of a sphere. Opt 
 *			        to run another calculation.
 *	Output:		    Prompt for inputs of weight and radius, confirmation 
 *			        that the sphere will sink or float, prompt to run 
 *			        another	calculation.
 *	Acknowledgements:
 *			    Absolute C++ 5th edition
 *				    For providing me with the reference material
 *				    necessary to solve an issue with type casting.
 * **************************************************************************/

#include <iostream>		//Included for cin and cout
#include <limits>		//Included to allow reset cin errors
#include <cmath>		//Included for pow function

#define PI 3.14159265359	//Constant for circumference to diameter ratio

using std::cout;
using std::cin;
using std::endl;

int main(){
    int sphereWeight, sphereRadius;
    bool validResponse;
    char runAgain = 'y';
    const float weightOfWater = 62.4;
    float buoyantForce, sphereVolume;

    /* Permits continual calculations */
    while(runAgain == 'y'){
        cout << endl;
        
        /* Ensures valid number input for weight */
        do{
            cout << "Weight of sphere in pounds?\n";
            validResponse = (cin >> sphereWeight);
            if (!(validResponse)){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (!(validResponse) || (sphereWeight < 1));
        
        /* Ensures valid number input for radius */
        do{
            cout << "Radius of sphere in feet?\n";
            validResponse = (cin >> sphereRadius);
            if (!(validResponse)){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (!(validResponse) || (sphereRadius < 1));
        
        /* sphereVolume calculation separate per assignment instructions */
        sphereVolume = (4.0 / 3.0) * PI * (std::pow((float)sphereRadius, 3));
        buoyantForce = sphereVolume * weightOfWater;
        
        /* Sink/Float output */
        if (buoyantForce >= sphereWeight)
            cout << "This sphere will float\n";
        else
            cout << "This sphere will sink\n";
        
        /* Prompt to begin another calculation */
        cout << "Would you like to run another calculation?\n";
        cin >> runAgain;
    }
    
    cout << "\n\n";
    
    return 0;
}
