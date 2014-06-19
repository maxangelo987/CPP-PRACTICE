/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/13/2013
 * Last Modified:    11/15/2013
 * Description:      Demonstrates the capabilities of the 'Vehicle' class and  
 *                   its child, 'Truck'.  Every instance of 'Vehicle' has an
 *                   owner of class 'Person'.  The main driver demonstrates
 *                   test cases from a test plan.
 * Input:            No input from user or file.  Classes are defined in main.
 * Output:           Introduction and outputs related to humorous rhyme.
 * Acknowledgements: Absolute C++, Seventh Edition
 ****************************************************************************/
 
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::istream;
using std::ostream;

/* Every person has a name */
class Person{
   public:
      /* Constructors */
      Person();
      Person(string theName);
      Person(const Person& theObject);
      
      /* Accessor */
      string getName() const;
      
      /* Operator overloads */
      Person& operator =(const Person& rtSide);
      friend istream& operator >>(istream& inStream, Person& personObject);
      friend ostream& operator <<(ostream& outStream, 
                                  const Person& personObject);
   private:
      /* Variable declaration */
      string name;
};

/* Every vehicle has an owner, manufacturer, and a quantity of cylinders */
class Vehicle{
   public:
      /* Constructors */
      Vehicle();
      Vehicle(string manufacturer);
      Vehicle(string manufacturer, int numCylinders);
      Vehicle(string manufacturer, int numCylinders, Person owner);
      Vehicle(const Vehicle& theObject);
      
      /* Accessors */
      string getManufacturer() const;
      int getNumCylinders() const;
      string getOwner() const;
      
      /* Operator overloads */
      Vehicle& operator =(const Vehicle& rtSide);
      
      /* Variable declaration */
      Person owner;
   protected:
      /* Variable declaration */
      string manufacturer;
      int numCylinders;
};

/* Every truck is a vehicle and has a tow and load capacity */
class Truck : public Vehicle{
   public:
      /* Constructors */
      Truck();
      Truck(string manufacturer);
      Truck(string manufacturer, int numCylinders);
      Truck(string manufacturer, int numCylinders, Person owner);
      Truck(string manufacturer, int numCylinders, Person owner, 
            double loadCapacity);
      Truck(string manufacturer, int numCylinders, Person owner, 
            double loadCapacity, int towCapacity);
      Truck(const Truck& theObject);
      
      /* Accessors */
      double getLoadCapacity() const;
      int getTowCapacity() const;
      
      /* Operator overloads */
      Truck& operator =(const Truck& rtSide);
   protected:
      /* Variable declaration */
      double loadCapacity;
      int towCapacity;
};

int main(){
   /* Test Code for Person class */
   Person owner1;
   Person owner2("John");
   Person owner3(owner2);
   
   cout << owner1.getName() << ".\n";
   cout << owner2.getName() << ".\n";
   cout << owner3.getName() << ".\n";

   owner1 = owner2;
   cout << owner1.getName() << ".\n";
   cout << owner1 << ".\n";
   
   cout << "\nEnter a name: ";
   cin >> owner3;
   cout << owner3 << ".\n\n";
   
   /* cout << owner3.name << "\n\n";  //Should cause compile error */

   /* Test Code for Vehicle class */
   Vehicle vehicle1;
   Vehicle vehicle2("Ford");
   Vehicle vehicle3("Ford", 8);
   Vehicle vehicle4("Ford", 8, owner2);
   Vehicle vehicle5(vehicle4);
   
   cout << vehicle1.getManufacturer() << ", " << vehicle1.getNumCylinders() 
        << ", " << vehicle1.getOwner() << ".\n";
   cout << vehicle2.getManufacturer() << ", " << vehicle2.getNumCylinders() 
        << ", " << vehicle2.getOwner() << ".\n";
   cout << vehicle3.getManufacturer() << ", " << vehicle3.getNumCylinders() 
        << ", " << vehicle3.getOwner() << ".\n";
   cout << vehicle4.getManufacturer() << ", " << vehicle4.getNumCylinders() 
        << ", " << vehicle4.getOwner() << ".\n";
   cout << vehicle5.getManufacturer() << ", " << vehicle5.getNumCylinders() 
        << ", " << vehicle5.getOwner() << ".\n";
   
   vehicle1 = vehicle4;
   cout << vehicle1.getManufacturer() << ", " << vehicle1.getNumCylinders() 
        << ", " << vehicle1.getOwner() << ".\n\n";
   
   /* cout << vehicle1.manufacturer << ", " << vehicle1.numCylinders << ", " 
        << vehicle1.name << ".\n\n";  //Should cause compile error */
   
   /* Test Code for Truck class */
   Truck truck1;
   Truck truck2("Ford");
   Truck truck3("Ford", 8);
   Truck truck4("Ford", 8, owner2);
   Truck truck5("Ford", 8, owner2, 2000.5);
   Truck truck6("Ford", 8, owner2, 2000.5, 1500);
   Truck truck7(truck6);

   cout << truck1.getManufacturer() << ", " << truck1.getNumCylinders() 
        << ", " << truck1.getOwner() << ", " << truck1.getLoadCapacity() << ", " 
        << truck1.getTowCapacity() << ".\n";
   cout << truck2.getManufacturer() << ", " << truck2.getNumCylinders() 
        << ", " << truck2.getOwner() << ", " << truck2.getLoadCapacity() << ", " 
        << truck2.getTowCapacity() << ".\n";
   cout << truck3.getManufacturer() << ", " << truck3.getNumCylinders() 
        << ", " << truck3.getOwner() << ", " << truck3.getLoadCapacity() << ", " 
        << truck3.getTowCapacity() << ".\n";
   cout << truck4.getManufacturer() << ", " << truck4.getNumCylinders() 
        << ", " << truck4.getOwner() << ", " << truck4.getLoadCapacity() << ", " 
        << truck4.getTowCapacity() << ".\n";
   cout << truck5.getManufacturer() << ", " << truck5.getNumCylinders() 
        << ", " << truck5.getOwner() << ", " << truck5.getLoadCapacity() << ", " 
        << truck5.getTowCapacity() << ".\n";
   cout << truck6.getManufacturer() << ", " << truck6.getNumCylinders() 
        << ", " << truck6.getOwner() << ", " << truck6.getLoadCapacity() << ", " 
        << truck6.getTowCapacity() << ".\n";
   cout << truck7.getManufacturer() << ", " << truck7.getNumCylinders() 
        << ", " << truck7.getOwner() << ", " << truck7.getLoadCapacity() << ", " 
        << truck7.getTowCapacity() << ".\n";
   
 
   truck1 = truck6;  
   cout << truck1.getManufacturer() << ", " << truck1.getNumCylinders() << ", " 
        << truck1.getOwner() << ", " << truck1.getLoadCapacity() << ", " 
        << truck1.getTowCapacity() << ".\n\n";

   /* cout << truck1.manufacturer << ", " << truck1.numCylinders << ", " 
        << truck1.name << ", " << truck1.loadCapacity << ", " 
        << truck1.towCapacity << ".\n\n"; //Should cause compile error */
   
   return 0;
}

/* Constructors for Person class */
/* Default person has no name */
Person::Person(){
   name = "";
}

Person::Person(string theName){
   name = theName;
}

Person::Person(const Person& theObject){
   this->name = theObject.getName();
}

/* Accessors for Person class */
string Person::getName() const{
   return name;
}

/* Operator overloads for Person class */
Person& Person::operator =(const Person& rtSide){
   name = rtSide.getName();
   return *this;
}

istream& operator >>(istream& inStream, Person& personObject){
   string inputString;
   
   inStream >> inputString;
   
   personObject.name = inputString;
   
   return inStream;
}

ostream& operator <<(ostream& outStream, const Person& personObject){
   outStream << personObject.getName();
   
   return outStream;
}

/* Constructors for Vehicle class */
Vehicle::Vehicle(){
   Person defaultOwner("");
   
   this->manufacturer = "";
   this->numCylinders = 0;
   this->owner = defaultOwner;
}

Vehicle::Vehicle(string manufacturer){
   Person defaultOwner("");
   
   this->manufacturer = manufacturer;
   this->numCylinders = 0;
   this->owner = defaultOwner;
}

Vehicle::Vehicle(string manufacturer, int numCylinders){
   Person defaultOwner("");
   
   this->manufacturer = manufacturer;
   this->numCylinders = numCylinders;
   this->owner = defaultOwner;
}

Vehicle::Vehicle(string manufacturer, int numCylinders, Person owner){
   this->manufacturer = manufacturer;
   this->numCylinders = numCylinders;
   this->owner = owner;
}

Vehicle::Vehicle(const Vehicle& theObject){
   this->manufacturer = theObject.manufacturer;
   this->numCylinders = theObject.numCylinders;
   this->owner = theObject.owner;
}

/* Accessors for Vehicle class */
string Vehicle::getManufacturer() const{
   return manufacturer;
}

int Vehicle::getNumCylinders() const{
   return numCylinders;
}

string Vehicle::getOwner() const{
   return owner.getName();
}

/* Operator overloads for Vehicle class */
Vehicle& Vehicle::operator =(const Vehicle& rtSide){
   manufacturer = rtSide.manufacturer;
   numCylinders = rtSide.numCylinders;
   owner = rtSide.owner;
   
   return *this;
}

/* Constructors for Truck class */
Truck::Truck():Vehicle(){
   loadCapacity = 0.0;
   towCapacity = 0;
}

Truck::Truck(string manufacturer) : Vehicle(manufacturer){
   loadCapacity = 0.0;
   towCapacity = 0;
}

Truck::Truck(string manufacturer, 
             int numCylinders) : Vehicle(manufacturer, numCylinders){
   loadCapacity = 0.0;
   towCapacity = 0;
}

Truck::Truck(string manufacturer, 
             int numCylinders, 
             Person owner) : Vehicle(manufacturer, numCylinders, owner){
   loadCapacity = 0.0;
   towCapacity = 0;
}

Truck::Truck(string manufacturer, 
             int numCylinders, 
             Person owner,
             double loadCapacity) : Vehicle(manufacturer, 
                                            numCylinders, 
                                            owner){
   this->loadCapacity = loadCapacity;
   towCapacity = 0;
}

Truck::Truck(string manufacturer, 
             int numCylinders, 
             Person owner, 
             double loadCapacity, 
             int towCapacity) : Vehicle(manufacturer, 
                                            numCylinders, 
                                            owner){
   this->loadCapacity = loadCapacity;
   this->towCapacity = towCapacity;
}
Truck::Truck(const Truck& theObject){
   this->manufacturer = theObject.manufacturer;
   this->numCylinders = theObject.numCylinders;
   this->owner = theObject.owner;
   this->loadCapacity = theObject.loadCapacity;
   this->towCapacity = theObject.towCapacity;
}

/* Accessors for Truck class */
double Truck::getLoadCapacity() const{
   return loadCapacity;
}

int Truck::getTowCapacity() const{
   return towCapacity;
}

/* Operator overloads for Truck class */
Truck& Truck::operator =(const Truck& rtSide){
   manufacturer = rtSide.manufacturer;
   numCylinders = rtSide.numCylinders;
   owner = rtSide.owner;
   loadCapacity = rtSide.loadCapacity;
   towCapacity = rtSide.towCapacity;
   
   return *this;
}