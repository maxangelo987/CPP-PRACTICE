/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     11/21/2013
 * Last Modified:    06/23/2014
 * Description:      Demonstrates some of the features required in Programming
 *                   Project 3 of Chapter 17.  Limited demonstration is based
 *                   on project guidelines, not developer preference.  The 
 *                   limited areas are the operator overloads of the 
 *                   polynomialNode class.  These overloads could be useful
 *                   in advanced user input beyond the project requirements.
 *                   For example, if the user enters two nodes with the same
 *                   x-power, a sorting function could combine them into one
 *                   node while making use of the + operator.  Because the
 *                   program guidelines do not include a demonstration of this
 *                   functionality, the operator overload function are not
 *                   included in the test plan either.
 *                   The demonstration prompts the user for a polynomial
 *                   function, confirms the function, prompts for an x-value,
 *                   and solves the function for the value of x in another
 *                   output.
 * Input:            User inputs a polynomial function in the following
 *                   format: ax^n + ax^n-1 + ... a
 *                   User inputs an integer for the x-value
 * Output:           Prompts for input, confirmation of polynomial, and 
 *                   a solution for f(x)
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>   /* For abs() */
#include <cmath>     /* For pow() */

using std::cout;
using std::string;
using std::cin;

/* Based on the IntNode code from Absolute C++, 7th Edition
   The polynomialNode class holds a single node in a linked list that  
   represents a polynomial equation.  Each node represents one part of the  
   equation (e.g., 2x^4 in the equation 2x^4 + 3x^3 - 2x^2.  The 'x' and '^'
   are for demonstration purposes.  The class only holds the values of each
   coefficient, power of 'x', and the pointer value for the next node in the
   list (or NULL).  Operator overloads for addition, subtraction, and 
   multiplication are included to comply with project guidelines; however,
   the project demonstration did not require the use of these overloaded
   operators. The member function calculate() determines f(x) for this
   node */
class polynomialNode{
   public:
      /* Constructors */
      polynomialNode(): coefficient(0), power(0), link(NULL) {}
      polynomialNode(polynomialNode* pointer): coefficient(pointer->getCoeff()),
                                               power(pointer->getPower()), 
                                               link(pointer->getLink()) {}
      polynomialNode(int constant): coefficient(constant), power(0), 
                                    link(NULL) {}
      polynomialNode(int constant, int exponent): coefficient(constant),
                                                  power(exponent),
                                                  link(NULL) {}
      ~polynomialNode() { delete this->link; } //Destructor
      
      /* Accessors */
      int getCoeff() const { return coefficient; }
      int getPower() const { return power; }
      polynomialNode* getLink() const { return link; }
      
      /* Mutators */
      void setCoeff(int coeff) { coefficient = coeff; }
      void setPower(int exponent) { power = exponent; }
      void setLink(polynomialNode* pointer) { link = pointer; }
   
      /* Operator Overloads */
      polynomialNode operator +(const polynomialNode& right);
      polynomialNode operator -(const polynomialNode& right);
      polynomialNode operator *(const polynomialNode& right);
      
      /* Member functions */
      int calculate(int x);      //Calculates this node based on x-value
      
   private:
      int coefficient, power;
      polynomialNode *link;
};

typedef polynomialNode* polynomialNodePtr;

/* Converts string user input into a linked list of polynomial nodes. */
polynomialNodePtr stringToList(string userPoly);

/* Removes all space characters from a string polynomial */
void removeSpaces(string& currentPoly);

/* Outputs a single node of a polynomial */
void outputPoly(polynomialNodePtr& head);

/* Outputs the entire polynomial using a linked list of nodes */
void outputList(polynomialNodePtr& head);

int main(){
    string userPoly;    
    polynomialNodePtr head, next;
    int x = 0, sum = 0;
    
    /* Prompt for polynomial */
    cout << "\n\nPlease enter a polynomial in the following format:";
    cout << "\nax^n + ax^n-1 + ... + a\n";
    cout << "\nPlease enter the entire polynomial on one line and hit enter"
          << " to submit: \n";
    getline(cin, userPoly);
    
    /* Convert input into a linked list of polynomialNodes */
    head = stringToList(userPoly);    
    
    /* Echo polynomial to confirm accurate reading */
    cout << "\nYour polynomial: ";
    outputList(head);
    
    /* Prompt for x */
    cout << "\nEnter an integer x-value: ";
    cin >> x;
    
    /* Solve for x */
    next = head;
    while(next != NULL){
        sum += next->calculate(x);
        next = next->getLink();
    }
    
    /* Output results of function calculation */
    cout << "\nThe sum of ";
    outputList(head);
    cout << " at a value of " << x << " is: " << sum;
    
    cout << "\n\n";      //Extra white space for readability
    
    delete head;
    
    return 0;
}

/* Operator overload for addition.  Two polynomialNodes can only be
    added when they share the same power of x */
polynomialNode polynomialNode::operator +(const polynomialNode& right){
    if(right.getPower() == power)
        return polynomialNode(coefficient + right.getCoeff(), 
                                     power);
    else{
        cout << "\n\nCannot add nodes of different power " 
              << "without first solving for x\n\n";
        exit(1);
    }
}

/* Operator overload for subtraction.  Two polynomialNodes can only be
    subtracted when they share the same power of x */
polynomialNode polynomialNode::operator -(const polynomialNode& right){
    if(right.getPower() == power)
        return polynomialNode(coefficient - right.getCoeff(), 
                                     power);
    else{
        cout << "\n\nCannot subtract nodes of different power " 
              << "without first solving for x\n\n";
        exit(1);
    }
}

/* Operator overload for multiplication. */
polynomialNode polynomialNode::operator *(const polynomialNode& right){
    return polynomialNode(coefficient * right.getCoeff(), 
                                 power + right.getPower());
}

/* Calculates this node based on x-value */
int polynomialNode::calculate(int x){
    int value;
    value = coefficient * (int)(pow((double)x, power));
    return value;
}

/* Converts string user input into a linked list of polynomial nodes. */
polynomialNodePtr stringToList(string userPoly){
    polynomialNodePtr head = new polynomialNode();
    polynomialNodePtr current = head, last = head;
    string currentPoly = userPoly;
    bool power = false;      //For determining constants
    
    removeSpaces(currentPoly);     //Removes spaces from string
    
    int next = 0;  //For handling the crop point in a string
    
    while(currentPoly.length() > 0){
        /* Acquire coefficient */
        for(int i = 0; i < currentPoly.length(); i++){
            if(currentPoly[i] == 'x'){
                power = true;
                next = i;
                if(next == 0)
                    current->setCoeff(1);
                else
                    current->setCoeff(atoi((currentPoly.substr(0, next)).c_str()));
                    
                currentPoly = currentPoly.substr(next + 2);
                i = currentPoly.length();
            }
        }
        /* Acquire power of x (if there is one) */
        if(power){
            power = false;
            for(int i = 1; i < currentPoly.length(); i++)
                if(!(isdigit(currentPoly[i]))){
                    next = i;
                    i = currentPoly.length();
                    current->setPower(atoi((currentPoly.substr(0, next)).c_str()));
                    currentPoly = currentPoly.substr(next);
                }            
        }
        /* Handle constant of polynomial as a node with a power of 0 */
        else{
            current->setCoeff(atoi(currentPoly.c_str()));
            currentPoly = "";
        }
        
        /* Create next node in the list and move down the list */
        if(currentPoly.length() > 0){
            current->setLink(new polynomialNode());
            current = last->getLink();
            last = current;
        }
        
        next = 0;    //Reset next break in the string
    }
    
    return head;
}

/* Removes all space characters from a string polynomial */
void removeSpaces(string& currentPoly){
    for(int i = 0; i < currentPoly.length(); i++)
        if(currentPoly[i] == ' '){
            /* Space in first element */
            if (i < 1)
                currentPoly = currentPoly.substr(1);
            /* Space in middle elements */
            else if(i < currentPoly.length() - 1)
                currentPoly = currentPoly.substr(0, i) + 
                                  currentPoly.substr(i + 1);
            /* Space in final element */
            else
                currentPoly = currentPoly.substr(0, i);
            i--;  //Adjustment for the reduction of string size
        }
}

/* Outputs a single node of a polynomial */
void outputPoly(polynomialNodePtr& head){
    if(head->getCoeff() != 0){
        if(head->getPower() != 0){
            if(head->getCoeff() != 1){
                if(head->getCoeff() == -1)
                    cout << "-";
                else
                    cout << head->getCoeff();
            }
            cout << "x^" << head->getPower();
        }
        else
            cout << head->getCoeff();
    }
        
    return;
}

/* Outputs the entire polynomial using a linked list of nodes */
void outputList(polynomialNodePtr& head){
    polynomialNodePtr next = head;
    
    while(next->getCoeff() == 0){
        outputPoly(next);
        next = next->getLink();
    }
    outputPoly(next);
    next = next->getLink();
    while(next != NULL){
        if(next->getCoeff() < 0){
            cout << " - ";
            next->setCoeff(abs(next->getCoeff()));
            outputPoly(next);
            next->setCoeff(-(next->getCoeff()));
            
        }
        else if(next->getCoeff() > 0){
            cout << " + ";
            outputPoly(next);
        }
        next = next->getLink();
    }
}