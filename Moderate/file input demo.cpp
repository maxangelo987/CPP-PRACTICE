/*****************************************************************************
* Author:            Robert Kety
* Date Created:      10/19/2013
* Last Modified:     06/20/2014
* Description:       Scans a list of words to determine the longest word that
*                    has only a single vowel.  Longest word is output to
*                    the screen.  In the event of multiple words of equal
*                    length (and only one vowel), only one of the words needs
*                    to be output to the screen.
* Input:             A series of words containing different case letters and
*                    delimited by new-line characters.
* Output:            Outputs the longest word with a single vowel to the
*                    screen.
* Acknowledgements:  Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>  /* For input/output */
#include <fstream>   /* For input/output */
#include <string>    /* For use of strings */
#include <cstdlib>   /* For use of exit() */

using std::ifstream;
using std::cout;
using std::string;

/* Returns longest word in input file that has only one vowel */
string findLongWord(ifstream& wordsFile);

/* Determines if character is a vowel. */
bool isVowel(const char& testChar);

int main(){
    /* Input and variable declaration */
    ifstream fin;
    string longWord;
    
    cout << "\n\nOpening input file.";
    fin.open("words.txt");
    
    /* Input file opening error handling */
    if(fin.fail()){
        cout << "\n\nInput file opening failed.\n\n";
        exit(1);
    }
    else
        cout << "\nInput file opened successfully!";
    
    cout << "\n\nDetermining largest word with one vowel from input file.";
    longWord = findLongWord(fin);
    cout << "\nLongest word with one vowel found!";
    
    /* Output longest word with one vowel to screen */
    cout << "\nLongest word with one vowel is: " << longWord;
    
    /* Close input file */
    fin.close();
    
    cout << "\n\nInput file closed successfully!";
    cout << "\nProgram ended.\n\n";
    
    return 0;
}

/* Returns longest word in input file that has only one vowel */
string findLongWord(ifstream& wordsFile){
    /* Variable declarations */
    string currentLong, tempLong;
    int currentLength = 0, tempLength = 0, vowelCount = 0;
    
    /* Scan input file for all words and determine longest word containing
        only one vowel. */
    while(wordsFile >> tempLong){
        /* Determine length of the current word */
        tempLength = tempLong.length();
        
        /* Reset number of vowels to zero */
        vowelCount = 0;
        
        /* Test each character of current word and count the vowels */
        for(int i = 0; i < tempLength; i++)
            if(isVowel(tempLong[i]))
                vowelCount++;
        
        /* If word has only one vowel, compare it to the longest word
            in currentLong and replace if current word is longer than
            currentLong.  */
        if(vowelCount == 1)
            if(tempLength > currentLength){
                currentLength = tempLength;
                currentLong = tempLong;
            }
    }
    
    return currentLong;
}

/* Determines if character is a vowel. */
bool isVowel(const char& testChar){
    /* Variable declaration */
    bool containsVowel = false;    //Assume false
    char tempChar = tolower(testChar);  //Convert to lower case 
    
    return ((tempChar == 'a') || (tempChar == 'e') || (tempChar == 'i') ||
              (tempChar == 'o') || (tempChar == 'u'));
}