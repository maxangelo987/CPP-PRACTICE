/******************************************************************************
 * Author:           Robert Kety
 * Date Created:     12/2/2013
 * Last Modified:    12/3/2013
 * Description:      Demonstrates the creation of a maze comprised of doubly
 *                   linked roomNode's.  The user can interact with the list
 *                   by choosing available direction in which they travel.
 *                   The program completes once the user finds the exit to
 *                   the maze.
 * Input:            Directions from the user
 * Output:           Describes initial and conclusion scenarios.  Outputs
 *                   available directions to user.  Prompts user for a 
 *                   direction to travel.
 * Acknowledgements: Absolute C++, Seventh Edition.
******************************************************************************/

#include <iostream>  //For input/output
#include <string>    //For use of string
#include <cctype>    //For use of toupper()

using std::cout;
using std::cin;
using std::string;

/* The roomNode class has a destructor that is customized for use with the 
   custom maze in the maze class.  If you change the maze layout in the maze
   class, be sure to compensate by adjusting the destructor in the roomNode
   class. The destructor will only delete nodes in one lateral and one 
   longitudinal direction (i.e., east and south).  If your maze has any 
   north or west passages when only turning east and south through the maze, 
   you must delete these tail lists separately.  See "junction" in the maze 
   class as an example. */
class roomNode{
   public:
      /* Constructors */
      roomNode(): north(NULL), east(NULL), south(NULL), west(NULL) {}
      roomNode(roomNode* up): north(up), east(NULL), south(NULL), west(NULL) {}
      roomNode(roomNode* up, roomNode* right): north(up), east(right), 
                  south(NULL), west(NULL) {}
      roomNode(roomNode* up, roomNode* right, roomNode* down): north(up), 
                  east(right), south(down), west(NULL) {}
      roomNode(roomNode* up, roomNode* right, roomNode* down, roomNode* left): 
                  north(up), east(right), south(down), west(left) {}
      
      ~roomNode(){
         delete this->east;
         delete this->south;
      }     /*Destructor - Assumes east and south to avoid infinite loop in 
                           doubly linked list */
      
      /* Accessors */
      roomNode* getNorth() const{ return north; }
      roomNode* getEast() const{ return east; }
      roomNode* getSouth() const{ return south; }
      roomNode* getWest() const{ return west; }
      
      /* Mutators */
      void setNorth(roomNode* up){
         north = up;
         if(up->getSouth() == NULL)
            up->setSouth(this);
      }
      
      void setEast(roomNode* right){
         east = right;
         if(right->getWest() == NULL)
            right->setWest(this); 
      }
      
      void setSouth(roomNode* down){
         south = down;
         if(down->getNorth() == NULL)
            down->setNorth(this);
      }
      
      void setWest(roomNode* left){
         west = left;
         if(left->getEast() == NULL)
            left->setEast(this);
      }

      /* Member Functions */
      bool isNorth(){
         if(north == NULL)
            return false;
         return true;
      }
      
      bool isEast(){
         if(east == NULL)
            return false;
         return true;
      }
      
      bool isSouth(){
         if(south == NULL)
            return false;
         return true;
      }
      
      bool isWest(){
         if(west == NULL)
            return false;
         return true;
      }
      
      /* Counts the number of available directions in the room, outputs those 
         directions to the user, and prompts the user for a direction. */
      void describeRoom();
      
   private:
      roomNode *north, *east, *south, *west;
};

/* The roomNode class has a destructor that is customized for use with the 
   custom maze in the maze class.  If you change the maze layout in the maze
   class, be sure to compensate by adjusting the destructor in the roomNode
   class. The destructor will only delete nodes in one lateral and one 
   longitudinal direction (i.e., east and south).  If your maze has any 
   north or west passages when only turning east and south through the maze, 
   you must delete these tail lists separately.  See "junction" in the maze 
   class as an example. */
class maze{
   public:
      /* Constructors */
      /* Creates unique maze as defined in Chapter 17, Programming Project 11 */
      maze(){
         roomNode *current;
         
         //Entrance
         entrance = new roomNode();
         current = entrance;
         current->setEast(new roomNode());
         current->setSouth(new roomNode());
         
         //East Tunnel
         current = current->getEast();
         current->setSouth(new roomNode());
         current = current->getSouth();
         current->setEast(new roomNode());
         current = current->getEast();
         junction = current;
         current->setNorth(new roomNode());
         current->setEast(new roomNode());
         current->setSouth(new roomNode());
   
         //Junction North
         current = current->getNorth();
         current->setEast(new roomNode());
         current = junction;
         
         //Junction East
         current = current->getEast();
         current->setSouth(new roomNode());
         exit = current->getSouth();
         current = junction;
      
         //South Tunnel
         current = entrance;
         current = current->getSouth();
         current->setSouth(new roomNode());
         current = current->getSouth();
         current->setEast(new roomNode());
      }
      ~maze(){ 
         delete junction->getNorth();
         delete entrance; 
      }     /* Destructor - Delete any north or west passages in the doubly 
               linked list first */
      
      roomNode* getEntrance(){ return entrance; }
      roomNode* getExit(){ return exit; }
   private:
      roomNode *entrance, *exit;
      /* Additional junction pointers should be added as necessary for each 
         junction.  A junction is a room where the maze constructor adds a 
         north or west passage. */
      roomNode *junction;
};

typedef roomNode* roomPtr;

int main(){
   char direction;
   maze *labyrinth = new maze();
   roomPtr current = labyrinth->getEntrance();
   
   /* Describe scenario to user */
   cout << "\nYou have entered a dank underground maze!\n";
   cout << "You are standing in a room when the entrance\n"
        << "caves-in behind you!!\n";
   cout << "You must find your way out of this maze!\n";
   
   /* User can continue navigating the maze until they locate the exit */
   while(current != labyrinth->getExit()){
      current->describeRoom();
      cin >> direction;
      
      direction = toupper(direction);
      
      switch(direction){
         case 'N':
            if(current->isNorth())
               current = current->getNorth();
            else
               cout << "There is no tunnel to the north!\n";
            break;
         case 'E':
            if(current->isEast())
               current = current->getEast();
            else
               cout << "There is no tunnel to the east!\n";
            break;
         case 'S':
           if(current->isSouth())
               current = current->getSouth();
            else
               cout << "There is no tunnel to the south!\n";
            break;
         case 'W':
            if(current->isWest())
               current = current->getWest();
            else
               cout << "There is no tunnel to the west!\n";
            break;
         default:
            cout << "That is not a valid direction!\n";
            break;
      }      
   } 
   
   /* Output conclusion and congratulate user on their success */
   cout << "\nAs you walk out of the underground maze, you stop to rub\n" 
        << "your eyes.  The sunlight is warm on your skin and you are\n"
        << "happy to be alive!\n";
   cout << "\nCongratulations! You survived the maze!\n\n";
   
   delete labyrinth;
   
   return 0;
}

/* Counts the number of available directions in the room, outputs those 
   directions to the user, and prompts the user for a direction. */
void roomNode::describeRoom(){
   int paths = 0;
   string directionList[4];
   
   /* Count number of available directions and record corresponding string 
      values */
   if(this->isNorth()){
      directionList[paths] = "north"; 
      paths++;
   }
   if(this->isEast()){
      directionList[paths] = "east";
      paths++;
   }
   if(this->isSouth()){
      directionList[paths] = "south";
      paths++;
   }
   if(this->isWest()){
      directionList[paths] = "west";
      paths++;
   }
   
   /* Output available directions to user */
   cout << "\nThis room has passages to the ";
   for(int i = 0; i < paths; i++){
      if(i > 0)
         cout << " ";
      cout << directionList[i];
      if(paths > 1){
         if(i < paths - 2)
            cout << ",";
         if(i == paths - 2)
            cout << " and";
      }
      if(i > paths - 2)
         cout << ".\n";
   }
   
   /* Prompt user for a direction */
   cout << "Which direction do you wish to travel (";
   for(int i = 0; i < paths; i++){
      if(i > 0)
         cout << " ";
      cout << directionList[i][0];
      if(paths > 1){
         if(i < paths - 2)
            cout << ",";
         if(i == paths - 2)
            cout << " or";
      }
      if(i > paths - 2)
         cout << "): ";
   }
   
   return;
}