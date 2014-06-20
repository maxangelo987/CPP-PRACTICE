/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     08/16/2013
 * Last Modified:    06/19/2014
 * Description:      Translates command line arguments including strings into
 *                   Pig Latin.
 * Input:            Verbatim- or string-style command line arguments.
 * Output:           The combined verbatim- or string-style command line
 *                   arguments translated into pig latin.
 * Acknowledgements: Lab8 instructions.
 *                   Feng Tian for mentioning the possibility of additional
 *                   spaces in a string-style command line argument.
 ****************************************************************************/
#include <iostream>     /* For output */
#include <cstring>      /* For strlen() */
#include <cctype>       /* For tolower() */

using std::cout;
using std::endl;

typedef char* charPtr;


/* Transforms every character in command line arguments to lower case. */
void lower_case(int argc, char *argv[]);

/* Tests if char array is a string with more than one word. */
bool is_string(char argument[]);

/* Tests if character is a vowel */
bool is_vowel(char letter);

/* Extracts each word in a char array and returns it as an array of char
 * arrays. Also, modifies the number of words through the pass by
 * reference parameter "wordCount". */
charPtr *extract_string(char argument[], int &wordCount);

/* Extracts a word argument and returns as a char array. */
charPtr extract_word(char argument[]);

/* Transforms char array into pig latin if argument is not a space. */
void pigLatin(char argument[]);

/* Outputs char array to screen and adds a space if argument is not a 
 * space. */
void outputWord(char argument[]);

int main(int argc, char *argv[]){
    /*Variable Declaration */
    int numOfWords = 1;
    
    cout << endl;     //Additional whitespace for output readability
    
    for(int i = 1; i < argc; i++){
        lower_case(argc, argv);    //All characters to lower case
        
        if(is_string(argv[i])){    //Handles string command line arguments
            charPtr *sentence = extract_string(argv[i], numOfWords);
            
            for(int j = 0; j < numOfWords; j++){
                pigLatin(sentence[j]);     //Translate word into pig latin
                outputWord(sentence[j]);      //Output word to screen
            }
            numOfWords = 1;
        }
        else{    //Handles single word command line arguments
            charPtr word = extract_word(argv[i]);
            pigLatin(word);      //Translate word into pig latin
            outputWord(word);    //Output word to screen
        }
    }
    
    cout << endl << endl;      //Additional whitespace for output readability
    
    return 0;
}

/* Transforms every character in command line arguments to lower case. */
void lower_case(int argc, char *argv[]){
    for(int i = 1; i < argc; i++)
        for(int j = 0; j < strlen(argv[i]); j++)
            argv[i][j] = tolower(argv[i][j]);
}

/* Tests if char array is a string with more than one word. */
bool is_string(char argument[]){
    bool stringTest = false;
    
    for(int i = 0; i < strlen(argument); i++)
        if(argument[i] == ' ')
            stringTest = true;

    return stringTest;
}

/* Tests if character is a vowel */
bool is_vowel(char letter){
    switch(letter){
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
            break;
        default:
            return false;
            break;
    }
}

/* Extracts each word in a char array and returns it as an array of char
 * arrays. Also, modifies the number of words through the pass by
 * reference parameter "wordCount". */
charPtr *extract_string(char argument[], int &wordCount){
    /* Variable Declarations */
    int argLength = strlen(argument), currentWord = 0, spacePlace = 0,
        suffixLength = 2;
    char suffixHolder = '0';   //A placeholder for adding pig latin suffix
    
    /* Count the number of words by incrementing the word counter for each 
     * space in the char array. */
    for(int i = 0; i < argLength; i++)
        if((argument[i] == ' '))
            wordCount++;
    
    charPtr *stringArray = new charPtr[wordCount];
    
    if(is_vowel(argument[0]))
        suffixLength = 3;
    
    /* For n number of words, assign 1 through n - 1 to array of char arrays. */
    for(int k = 0; k < argLength; k++){
        if(argument[k] == ' '){
            stringArray[currentWord] = new char[k - spacePlace + suffixLength];
            
            for(int m = 0; m < (k - spacePlace + suffixLength); m++)
                if(m < (k - spacePlace))
                    stringArray[currentWord][m] = argument[m + spacePlace];
                else if (argument[spacePlace + 1] != ' ')
                    stringArray[currentWord][m] = suffixHolder;
            
            spacePlace = k;
            currentWord++;
            
            if(is_vowel(argument[k + 1]))
                suffixLength = 3;
            else
                suffixLength = 2;
        }
    }
    
    /* For n number of words, assign the nth word to array of char arrays. */
    stringArray[currentWord] = new char[argLength - spacePlace - 1 +
                                        suffixLength];
    
    for(int j = 0; j < (argLength - spacePlace - 1 + suffixLength); j++)
        if(j < (argLength - spacePlace - 1))
            stringArray[currentWord][j] = argument[j + spacePlace + 1];
        else if (argument[spacePlace + 1] != ' ')
            stringArray[currentWord][j] = suffixHolder;  
    
    return stringArray;
}

/* Extracts a word argument and returns as a char array. */
charPtr extract_word(char argument[]){
    /* Variable Declarations */
    int argLength = strlen(argument), suffixLength = 2;
    char suffixHolder = '0';   //A placeholder for adding pig latin suffix
    
    if(is_vowel(argument[0]))
        suffixLength = 3;
       
    charPtr word = new char[argLength + suffixLength];
    
    for(int i = 0; i < argLength; i++)
        word[i] = argument[i];
    
    /* Assign suffix placeholders to end of char array */
    for(int j = 0; j < suffixLength; j++)
        word[argLength + j] = suffixHolder;
    
    return word;
}

/* Transforms char array into pig latin if argument is not a space. */
void pigLatin(char argument[]){
    /* Variable Declarations */
    int argLength = strlen(argument), suffixPlace = argLength;
    char tempChar = '\0';
    
    if(argument[0] != ' '){    //Add suffix when argument is not a space
        argument[--suffixPlace] = 'y';
        argument[--suffixPlace] = 'a';
    }
    
    if(is_vowel(argument[0]))
        argument[--suffixPlace] = 'w';
    else{
        tempChar = argument[0];
        for(int i = 0; i < suffixPlace; i++)
            argument[i] = argument[i + 1];
        argument[suffixPlace - 1] = tempChar;
    }
}

/* Outputs char array to screen and adds a space if argument is not a 
 * space. */
void outputWord(char argument[]){
    for(int i = 0; i < strlen(argument); i++)
        cout << argument[i];
    
    if(argument[0] != ' ')  //Add space when argument is not already a space.
        cout << " ";
}