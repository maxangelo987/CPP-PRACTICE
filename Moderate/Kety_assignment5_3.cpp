/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/27/2013
 * Last Modified:    10/27/2013
 * Description:      Demonstrates the capabilities of the 'Creature' class
 *                   and its children and grandchildren, specifically the
 *                   getDamage() accessor.  Each class has its mutator and
 *                   accessor functions for private variables.  The main
 *                   driver frames the demonstration in a pseudo-combat
 *                   scenario.
 * Input:            No inputs from user.  Creature(and sub-Creatures) are
 *                   defined in the main driver.
 * Output:           Introduction and output demonstration of pseudo-combat
 *                   scenario.
 * Acknowledgements: Absolute C++, Seventh Edition
 ****************************************************************************/

#include <iostream>  /* For input/output */
#include <cstdlib>   /* For rand() */
#include <string>    /* For strings */

using std::cout;
using std::string;
using std::endl;

/* Every creature has strength, hitpoints, and a species */
class Creature{
   public:
      /* Constructors */
      Creature();
      Creature(int newStrength, int newHit);
      
      /* Accessors */
      int getDamage() const;  // Returns damage inflicted in one combat round
      int getStrength() const;
      int getHitpoints() const;
      string getSpecies() const; // Returns name of species
      
      /* Mutators */
      void setStrength(int newStrength);
      void setHitpoints(int newHit);
      void setSpecies(string newSpecies);
   private:
      /* Variable declarations */
      int strength;     /* How much damage we can inflict */
      int hitpoints;    /* How much damage we can sustain */
      string species;   /* Name of species */
};

/* Every Demon is a Creature */
class Demon : public Creature{
   public:
      /* Constructors */
      Demon();
      Demon(int newStrength, int newHit);
      
      /* Accessors */
      int getDamage() const;
};

/* Every Elf is a Creature */
class Elf : public Creature{
   public:
      /* Constructors */
      Elf();
      Elf(int newStrength, int newHit);
      
      /* Accessors */
      int getDamage() const;
};

/* Every Human is a Creature */
class Human : public Creature{
   public:
      /* Constructors */
      Human();
      Human(int newStrength, int newHit);
};

/* Every Balrog is a Demon */
class Balrog : public Demon{
   public:
      /* Constructors */
      Balrog();
      Balrog(int newStrength, int newHit);
      
      /* Accessors */
      int getDamage() const;
};

/* Every Cyberdemon is a Demon */
class Cyberdemon : public Demon{
   public:
      /* Constructors */
      Cyberdemon();
      Cyberdemon(int newStrength, int newHit);
};

int main(){
   /* Variable declarations */
   int damage = 0;
   Human aragorn(15, 15);
   Cyberdemon doomThrowback(20, 10);
   Balrog balor(15, 9);
   Elf legolas(12, 12);
   
   /* Introduction statements */
   cout << "\n\nImmortal Kombat!";
   cout << "\nFight!!";
   
   /* Cyberdemon attacks Aragorn */
   cout << "\n\nA cyberdemon appears and attacks Aragorn!";
   damage = aragorn.getHitpoints() - doomThrowback.getDamage();
   aragorn.setHitpoints(damage);
   if(aragorn.getHitpoints() < 0)
      cout << "\nAragorn dies!!";
   else{    //Aragorn attacks Cyberdemon
      cout << "\n\nAragorn strikes back!";
      damage = doomThrowback.getHitpoints() - aragorn.getDamage();
      doomThrowback.setHitpoints(damage);
   }
   
   /* Legolas attacks Cyberdemon */
   cout << "\n\nLegolas looses arrows at the cyberdemon!";
   damage = doomThrowback.getHitpoints() - legolas.getDamage();
   doomThrowback.setHitpoints(damage);
   if(doomThrowback.getHitpoints() < 0)
      cout << "\nThat Doom throwback is toast!";
   
   /* Balrog attacks Legolas */
   cout << "\n\nA cranky Balrog attacks Legolas to avenge his cyber-cousin!";
   damage = legolas.getHitpoints() - balor.getDamage();
   legolas.setHitpoints(damage);
   if(legolas.getHitpoints() < 0)
      cout << "\nLegolas falls!";
   
   cout << endl << endl;   //Additional white space for readability
   
   return 0;
}

/* Constructors for Creature class */
Creature::Creature(){
   strength = 0;
   hitpoints = 0;
   species = "Creature";
}

Creature::Creature(int newStrength, int newHit){
   strength = newStrength;
   hitpoints = newHit;
   species = "Creature";
}

/* Accessors for Creature class */
/* Returns amount of damage this creature
   inflicts in one round of combat */
int Creature::getDamage() const{
   /* All creatures inflict damage, which is a
      random number up to their strength */
   int damage;
   
   /* initialize random seed: */
   srand (time(NULL));
   
   damage = (rand() % getStrength()) + 1;
   cout << endl << getSpecies() << " attacks for " << damage << " points!";
   
   return damage;
}

int Creature::getStrength() const{
   return strength;
}

int Creature::getHitpoints() const{
   return hitpoints;
}

/* Returns name of species */
string Creature::getSpecies() const{
   return species;
}

/* Mutators for Creature class */
void Creature::setStrength(int newStrength){
   this->strength = newStrength;
   return;
}

void Creature::setHitpoints(int newHit){
   this->hitpoints = newHit;
   return;
}

void Creature::setSpecies(string newSpecies){
   this->species = newSpecies;
   return;
}

/* Constructors for Demon class */
Demon::Demon() : Creature(){
   setSpecies("Demon");
}

Demon::Demon(int newStrength, int newHit) : Creature(newStrength, newHit){
   setSpecies("Demon");
}

/* Accessors for Demon class */
int Demon::getDamage() const{
   /* All creatures inflict damage, which is a
      random number up to their strength */
   int damage;
   Creature demon(getStrength(), getHitpoints());
   
   /* initialize random seed: */
   srand (time(NULL));
   
   demon.setSpecies(getSpecies());
   
   damage = demon.getDamage();
   
   /* Demons can inflict damage of 50 with a 5% chance */
   if ((rand() % 100) < 5){
      damage = damage + 50;
      cout << "\nDemonic attack inflicts 50 " 
           << "additional damage points!";
   }
   
   return damage;
}

/* Constructors for Elf class */
Elf::Elf() : Creature(){
   setSpecies("Elf");
}

Elf::Elf(int newStrength, int newHit) : Creature(newStrength, newHit){
   setSpecies("Elf");
}

/* Accessors for Elf class */
int Elf::getDamage() const{
   /* All creatures inflict damage, which is a
      random number up to their strength */
   int damage;
   Creature elf(getStrength(), getHitpoints());
   
   /* initialize random seed: */
   srand (time(NULL));
   
   elf.setSpecies(getSpecies());
   damage = elf.getDamage();
   
   /* Elves inflict double magical damage with a 10% chance */
   if ((rand() % 10) == 0){
      cout << "\nMagical attack inflicts " << damage 
           << " additional damage points!";
      damage = damage * 2;
   }
   
   return damage;
}

/* Constructors for Human class */
Human::Human() : Creature(){
   setStrength(10);
   setHitpoints(10);
   setSpecies("Human");
}

Human::Human(int newStrength, int newHit) : Creature(newStrength, newHit){
   setStrength(newStrength);
   setHitpoints(newHit);
   setSpecies("Human");
}   

/* Constructors for Balrog class */
Balrog::Balrog() : Demon(){
   setSpecies("Balrog");
}

Balrog::Balrog(int newStrength, int newHit) : Demon(newStrength, newHit){
   setSpecies("Balrog");
}

/* Accessors for Balrog class */
int Balrog::getDamage() const{
   /* All creatures inflict damage, which is a
      random number up to their strength */
   int damage;
   Demon balrog(getStrength(), getHitpoints());
   
   /* initialize random seed: */
   srand (time(NULL));
   
   balrog.setSpecies(getSpecies());
   
   damage = balrog.getDamage();
   
   /* Balrogs are so fast they get to attack twice */
   int damage2 = (rand() % getStrength()) + 1;
   cout << "\nBalrog speed attack inflicts " << damage2 
        << " additional damage points!";
   damage = damage + damage2;
   
   return damage;
}

/* Constructors for Cyberdemon class */
Cyberdemon::Cyberdemon() : Demon(){
   setSpecies("Cyberdemon");
}

Cyberdemon::Cyberdemon(int newStrength, int newHit) : Demon(newStrength, newHit){
   setSpecies("Cyberdemon");
}