/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     11/10/2013
 * Last Modified:    06/22/2014
 * Description:      Demonstrates the isMoney algorithm - a series of 
 *                   recursive functions that returns a boolean determination
 *                   if a string meets a standard money format (i.e., 
 *                   "$###,###,###").
 * Output:           Outputs a series of test strings and the isMoney result.
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>
#include <string>
#include <cctype>    //For isdigit

#define NUM_STRINGS 41  //Number of test strings in stringArray (main function)

using std::cout;
using std::string;

/* The isMoney algorithm - a series of recursive functions that returns a 
   boolean determination if a string meets a standard money format (i.e., 
   "$###,###,###"). */
bool isMoney(string s);
bool state0(string s);
bool state1(string s);
bool state2(string s);
bool state3(string s);
bool state4(string s);
bool state5(string s);
bool state6(string s);
bool state7(string s);

int main(){
    string stringArray[NUM_STRINGS];
    
    /* String Array Initialization in lieu of C++11 initialization list */
    stringArray[0] = "$1";
    stringArray[1] = "$10";
    stringArray[2] = "$100";
    stringArray[3] = "$1,000";
    stringArray[4] = "$10,000";
    stringArray[5] = "$100,000";
    stringArray[6] = "$1,000,000";
    stringArray[7] = "$10,000,000";
    stringArray[8] = "$100,000,000";
    stringArray[9] = "$1,000,000,000";
    stringArray[10] = "100,000";
    stringArray[11] = "100";
    stringArray[12] = "10";
    stringArray[13] = "1";
    stringArray[14] = "0";
    stringArray[15] = "$";
    stringArray[16] = "$000,000";
    stringArray[17] = "$000";
    stringArray[18] = "$00";
    stringArray[19] = "$0";
    stringArray[20] = "100000";
    stringArray[21] = "-$100,000";
    stringArray[22] = "-$100";
    stringArray[23] = "-$10";
    stringArray[24] = "-$1";
    stringArray[25] = "$-100,000";
    stringArray[26] = "$-100";
    stringArray[27] = "$-10";
    stringArray[28] = "$-1";
    stringArray[29] = "$100,000.00";
    stringArray[30] = "$100.00";
    stringArray[31] = "$10.00";
    stringArray[32] = "$1.00";
    stringArray[33] = "$1,";
    stringArray[34] = "$1,0";
    stringArray[35] = "$1,00";
    stringArray[36] = "$1,000,";
    stringArray[37] = "$1,000,0";
    stringArray[38] = "$1,000,00";
    stringArray[39] = "1000,000";
    stringArray[40] = "1,000000";
    
    for(int i = 0; i < NUM_STRINGS; i++){
        cout << "\nString " << i << " (\"" << stringArray[i] << "\"): ";
        if(isMoney(stringArray[i]))
            cout << "Valid money string.";
        else
            cout << "Invalid money string.";
    }
    
    cout << "\n\n";        //Extra white space for readability
    
    return 0;
}

/* The isMoney algorithm - a series of recursive functions that returns a 
    boolean determination if a string meets a standard money format (i.e., 
    "$###,###,###"). */
bool isMoney(string s){
    if((s[0]=='$') && (s.length() > 1))
            return state0(s.substr(1));
    
    return false;
}

bool state0(string s){
    if(isdigit(s[0]) && (s[0] != '0'))  //"$0" is not valid according to DFA
            return state1(s.substr(1));
    
    return false;
}

bool state1(string s){
    if(isdigit(s[0]))
        return state2(s.substr(1));
    if(s[0] == ',')
        return state4(s.substr(1));
    if(s.length() > 2)    //Prevents floating point input from returning true
        return false;
    
    return true;
}

bool state2(string s){
    if(isdigit(s[0]))
        return state3(s.substr(1));
    if(s[0] == ',')
        return state4(s.substr(1));
    if(s.length() > 2)    //Prevents floating point input from returning true
        return false;
    
    return true;
}

bool state3(string s){
    if(s[0] == ',')
        return state4(s.substr(1));
    if(s.length() > 2)    //Prevents floating point input from returning true
        return false;
    
    return true;
}

bool state4(string s){
    if(isdigit(s[0]))
        return state5(s.substr(1));
    
    return false;
}

bool state5(string s){
    if(isdigit(s[0]))
        return state6(s.substr(1));
        
    return false;
}

bool state6(string s){
    if(isdigit(s[0]))
        return state7(s.substr(1));
    
    return false;
}

bool state7(string s){
    if(s[0] == ',')
        return state4(s.substr(1));
    if(s.length() > 2)    //Prevents floating point input from returning true
        return false;
    
    return true;
}