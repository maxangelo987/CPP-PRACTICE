/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     11/20/2013
 * Last Modified:    11/21/2013
 * Description:      Demonstrates the creation, output, and reversal of a
 *                   linked list of nodes containing integer numbers
 * Output:           Outputs numbers 1 through 9 and the reverse of these 
 *                   numbers, 9 through 1.
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>

using std::cout;

/* The IntNode class is based on code from Absolute C++, 7th Edition 
   (p. 738) 
   The class manages a single node in a linked list and holds an integer
   and an IntNode pointer to the next node in the list (or NULL) */
class IntNode{
   public:
      /* Constructors */
      IntNode() {}
      IntNode(int theData, IntNode* theLink): data(theData), link(theLink) {}
      ~IntNode() { delete this->link; }     //Destructor
      
      /* Accessors */
      int getData() const { return data; }
      IntNode* getLink() const { return link; }
      
      /* Mutators */
      void setData(int theData) { data = theData; }
      void setLink(IntNode* pointer) { link = pointer; }
   
   private:
      int data;
      IntNode *link;
};

typedef IntNode* IntNodePtr;

/* The IntNode class is based on code from Absolute C++, 7th Edition 
   (p. 738) 
   Creates a new node using integer data argument and inserts it before
   the current head of the list (i.e., the "top" of the list) */
void headInsert(IntNodePtr& head, int theData);

/* Outputs all nodes in a CSV linked list */
void outputNodes(IntNodePtr next);

/* Reverse sorts a linked list */
void reverseNodes(IntNodePtr& head);

int main(){
   IntNodePtr head = new IntNode(0, NULL);
   
   /* Create a linked list holding the numbers 1 through 9 */
   for(int i = 1; i < 10; i++)
      headInsert(head, i);
   
   /* Output linked list */
   cout << "\nA linked list of numbers: \t\t";
   outputNodes(head);
   
   /* Reverse linked list if list contains more than one node */
   if(head->getLink() != NULL)
      reverseNodes(head);
   
   /* Output linked list again in new (reversed) order */
   cout << "\nThe same linked list in reverse: \t";
   outputNodes(head);
   
   cout << "\n";     //Extra white space for readability
   
   return 0;
}

/* The IntNode class is based on code from Absolute C++, 7th Edition 
   (p. 738) 
   Creates a new node using integer data argument and inserts it before
   the current head of the list (i.e., the "top" of the list) */
void headInsert(IntNodePtr& head, int theData){
   head = new IntNode(theData, head);
}

/* Outputs all nodes in a CSV linked list */
void outputNodes(IntNodePtr next){
   while(next != NULL){
      cout << next->getData();
      if(next->getLink() != NULL)
         cout << ", ";     //Inserted commas for readability
      next = next->getLink();
   }
   
   cout << "\n";     //Extra white space for readability
}

/* Reverse sorts a linked list */
void reverseNodes(IntNodePtr& head){
   IntNodePtr last = head, next = head->getLink();
   
   head = next;
   last->setLink(NULL);
   do{
      next = next->getLink();
      head->setLink(last);
      last = head;
      head = next;
   }while(next != NULL);
   
   head = last;
   
   return;
}