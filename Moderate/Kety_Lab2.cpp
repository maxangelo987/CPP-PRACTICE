/*****************************************************************************
* Author:            Robert Kety
* Date Created:      10/21/2013
* Last Modified:     10/21/2013
* Description:       Scans a list of words to determine the word with the
*                    longest consecutive vowels.  That word is output to
*                    the screen.  In the event of multiple words of equal
*                    length, only one of the words needs to be output to the 
*                    screen.
* Input:             A series of words containing different case letters and
*                    delimited by new-line characters.
* Output:            Outputs the word with the longest consecutive vowels to 
*                    the screen.
* Acknowledgements:  Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>  /* For input/output */
#include <fstream>   /* For input/output */
#include <string>    /* For use of strings */
#include <cstdlib>   /* For use of exit() */

using std::ifstream;
using std::cout;
using std::string;

/* Returns word with longest consecutive vowels in input file */
string findLongestVowels(ifstream& wordsFile);

/* Determines if character is a vowel. */
bool isVowel(const char& testChar);

/* Determines the longest consecutive length of vowels in a string */
int consecVowels(const string& word);

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
   
   cout << "\n\nDetermining word with longest consecutive vowels from input file.";
   longWord = findLongestVowels(fin);
   cout << "\nWord with longest consecutive vowels found!";
   
   /* Output longest word with one vowel to screen */
   cout << "\nWord with longest consecutive vowels is: " << longWord;
   
   /* Close input file */
   fin.close();
   
   cout << "\n\nInput file closed successfully!";
   cout << "\nProgram ended.\n\n";
   
   return 0;
}

/* Returns word with longest consecutive vowels in input file */
string findLongestVowels(ifstream& wordsFile){
   /* Variable declarations */
   string currentLong, tempLong;
   int currentLongest = 0, tempLongest = 0;
   
   /* Scan input file for all words and determine word with longest 
      consecutive vowels */
   while(wordsFile >> tempLong){
      /* Determine longest length of consecutive vowels in word */
      tempLongest = consecVowels(tempLong);
      
      /* Store word with longest consecutive vowels and the length of
         consecutive vowels */
      if(tempLongest >= currentLongest){
            currentLongest = tempLongest;
            currentLong = tempLong;
         }
      
   }
   
   return currentLong;
}

/* Determines if character is a vowel. */
bool isVowel(const char& testChar){
   /* Variable declaration */
   bool containsVowel = false;   //Assume false
   char tempChar = tolower(testChar);  //Convert to lower case 
   
   return ((tempChar == 'a') || (tempChar == 'e') || (tempChar == 'i') ||
           (tempChar == 'o') || (tempChar == 'u'));
}

/* Determines the longest consecutive length of vowels in a string */
int consecVowels(const string& word){
   /* Variable declarations */
   int vowelCount = 0, tempCount = 0, currentLetter = 0;
   
   /* Inspects each letter of the word */
   do{
      /* Counts longest consecutive vowels in the word */
      if(!(isVowel(word[currentLetter]))){
         if(tempCount > vowelCount)
            vowelCount = tempCount;
         tempCount = 0;
      }
      else
         tempCount++;
      
      currentLetter++;  //Loop driver increment
   }while(currentLetter < word.length());
   
   /* In the event the word ends with consecutive vowels */
   if(tempCount > vowelCount)
      vowelCount = tempCount;
   
   return vowelCount;
}