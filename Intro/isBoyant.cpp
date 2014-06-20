/******************************************************************************
 * Author:		        Robert Kety
 * Date Created:        07/27/2013
 * Last Modified:       06/19/2014
 * Description:         Determine if a sphere will sink or float based on user
 *			            input of sphere radius in feet and weight in pounds.
 * Input:		        Sphere weight in pounds and radius in feet.
 * Output:		        Prompts for user input. Outputs confirmation of whether
 *			            the sphere will sink or float
 * Acknowledgements:	Lab4
 *****************************************************************************/
#include <iostream>
#include <cmath>

#define WATER_WEIGHT 62.4   //Defines the specific weight of water
#define PI 3.14159265359    //Defines the circumference to diameter ratio

using std::cout;
using std::cin;

int main(){
    //Variables needed to calculate buoyancy
    float radius, bforce, volume, weight;

    //Prompt user for weight and radius of sphere
    cout << "\nPlease enter the weight (lbs): ";
    cin >> weight;
    cout << "\nPlease enter the radius (feet): ";
    cin >> radius;

    //Calculate the volume and buoyancy force
    volume = 4.0 / 3.0 * PI * pow(radius, 3);
    bforce = volume * WATER_WEIGHT;

    //Determine if the sphere will sink or float
    if(bforce >= weight)
        cout << "\nThe sphere will float!\n";
    else
        cout << "\nThe sphere will sink!\n";

    return 0;
}