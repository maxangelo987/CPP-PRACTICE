/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/13/2013
 * Last Modified:    10/14/2013
 * Description:      Demonstrates the capabilities of the 'Vehicle' class and  
 *                   its child, 'Truck'.  Every instance of 'Vehicle' has an
 *                   owner of class 'Person'.  The main driver demonstrates
 *                   these capabilities in the form of a humorous rhyme.
 * Input:            No input from user or file.  Classes are defined in main.
 * Output:           Introduction and outputs related to humorous rhyme.
 * Acknowledgements: Absolute C++, Seventh Edition
 ****************************************************************************/
 
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
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
   /* Variable declaration */
   Person owner("John");
   Truck johnsTruck("Ford", 8, owner, 2, 1500);
   
   /* Output humours rhyme */
   cout << "\n\nThere once was a man named " << johnsTruck.owner.getName() << ".";
   cout << "\nHe was interested in an " 
        << johnsTruck.getNumCylinders() << " cylinder "
        << johnsTruck.getManufacturer() << " truck.";
   cout << "\nIt could carry " << johnsTruck.getLoadCapacity() << " tons "
        << "and tow " 
        << johnsTruck.getTowCapacity()
        << " lbs.,";
   cout << "\nbut he preferred to drive it through muck!\n\n";
   
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