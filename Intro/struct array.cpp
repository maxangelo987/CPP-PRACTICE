/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     08/26/2013
 * Last Modified:    06/19/2014
 * Description:      Creates and populates array of structs composed of movie
 *                   titles, descriptions, genre, rating, and quantity.  The 
 *                   program prompts the user for a display filter (i.e., by 
 *                   title, by genre, or by rating) and outputs the ordered 
 *                   list to the screen.  The program then prompts the user 
 *                   for a specific title, outputs detailed information on 
 *                   that title, and prompts the user if they wish to rent 
 *                   the title (provided copies are available).  A positive 
 *                   response results in a decrease of quantity for that 
 *                   title.  Program will continually ask if user want to know
 *                   more about another title and will allow multiple rentals.
 * Input:            User input of video library, display filter, title 
 *                   selection, and rental confirmation.
 * Output:           Prompts for user input, ordered inventory output, 
 *                   and detailed description of a movie.
 * Acknowledgements: Lab9 instructions,
 *                   http://publib.boulder.ibm.com/ For help with member name
 *                   pointers.
 ****************************************************************************/
 
#include <iostream>	 /* Necessary for output */
#include <string>    /* For use of string class */
#include <cctype>    /* Necessary for tolower() */
#include <limits>	 /* Included to allow clearing cin errors */

#define NUM_MOVIES 5    //Number of movie titles in library

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct movie_record{
    string title, rating, description, genre;
    int copies;
};

/* Creates pointer to member name */
typedef string movie_record::*memberPtr;

/* Prompts user to populate movie_record struct */
void set_movies(movie_record &currentMovie);

/* Prompts user to populate undefined array elements of movie_record 
 * structs. Default undefined array elements is NUM_MOVIES. */
void set_movies(movie_record catalog[], int undefinedMovies = NUM_MOVIES);

/* Prompts user for a display filter to view catalog of movies.
 * Returns user selection in all lower case and without punctuation
 * if the string is a valid selection. */
string which_movies_to_view(movie_record catalog[]);

/* Tests user input to confirm if string will parse against the three
 * display filter options (i.e., "title", "genre", and "rating") */
bool test_selection(string &displayFilter);

/* Sorts catalog by display filter option and outputs to screen */
void get_movies(movie_record catalog[], string displayFilter);

/* Outputs catalog to screen */
void output_movies(movie_record catalog[]);

/* Prompts user for title, outputs title and description, and prompts
 * for rental if copies are available. */
void get_movie_info(movie_record catalog[]);

/* Outputs title and description of movie selection. */
void get_movie_info(movie_record catalog[], int movieSelection);

/* Prompts user for rental preference if copies are available. */
void rent_movie(movie_record catalog[], int movieSelection);

int main(){
    /* Variable declarations */
    int remainingMovies = NUM_MOVIES;
    string runAgain = "y";
    movie_record library[NUM_MOVIES], rushHour = {"Rush Hour", "R", 
        "Do you understand the strings that are coming out of my iostream?",
        "Comedy", 100};
    
    /* Demonstrates direct array population vs. user input */
    library[0] = rushHour;
    remainingMovies--;
    
    set_movies(library, remainingMovies);    //Populate remaining library
    
    get_movies(library, which_movies_to_view(library));
    
    while((runAgain[0] == 'y') || (runAgain[0] == 'Y')){
        get_movie_info(library);
        cout << "\nWould you like to know more about another movie?\n";
        getline(cin, runAgain);
    }   //Continually prompts for another movie to allow multiple rentals
    
    return 0;
}   //12 Lines of code

/* Prompts user to populate movie_record struct */
void set_movies(movie_record &currentMovie){
    cout << "\n\nTitle:\n";
    getline(cin, currentMovie.title);
       
    cout << "\nRating:\n";
    getline(cin, currentMovie.rating);
       
    cout << "\nDescription:\n";
    getline(cin, currentMovie.description);
       
    cout << "\nGenre:\n";
    getline(cin, currentMovie.genre);
       
    cout << "\nCopies:\n";
    while (!(cin >> currentMovie.copies) || (currentMovie.copies < 0)){
        // Clears error flag from non-number entry 
        cin.clear();
        
        // Move to next buffer line 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Prompt user for valid input 
        cout << "\n\nPlease enter a non-negative number of copies:\n";
    }
    
    cin.ignore(1000, '\n');    //Clears line from cin of int
}   //14 Lines of code

/* Prompts user to populate array of movie_record structs */
void set_movies(movie_record catalog[], int undefinedMovies){
    for(int i = NUM_MOVIES - undefinedMovies; i < NUM_MOVIES; i++){
        cout << "\n\nEnter movie number " 
             << i + 1 << " of " << NUM_MOVIES;
        set_movies(catalog[i]);      
    }
}   //3 Lines of code

/* Prompts user for a display filter to view catalog of movies.
 * Returns user selection in all lower case and without punctuation
 * if the string is a valid selection. */
string which_movies_to_view(movie_record catalog[]){
    /* Variable declaration */
    string displaySelection("title");   //Default is a valid selection
    
    do{
        if(!(test_selection(displaySelection)))
            cout << "\nThat does not appear to be a valid selection.\n";
        cout << "\nType 'Title' to see every movie title in alphabetical order.\n";
        cout << "Type 'Genre' to see every movie title in order by genre.\n";
        cout << "Type 'Rating' to see every movie title in order by rating.\n";
        cout << "\n\nHow would you like to review your library?\n";
        
        getline(cin, displaySelection);
    }while(!(test_selection(displaySelection)));
    
    return displaySelection;
}   //11 Lines of code

/* Tests user input to confirm if string will parse against the three
 * display filter options (i.e., "title", "genre", and "rating") */
bool test_selection(string &displayFilter){
    /* Formats string to lower case and removes punctuation. */
    for(int i = 0; i < displayFilter.length(); i++){
        displayFilter[i] = tolower(displayFilter[i]);
        if(ispunct(displayFilter[i])){
            displayFilter.erase(i, 1);
            i--;
        }      
    }
    /* Tests formatted string for valid selection */
    if((displayFilter == "title") || (displayFilter == "genre") ||
       (displayFilter == "rating"))
        return true;
    else
        return false;
}   //9 Lines of code

/* Sorts catalog by display filter option and outputs to screen */
void get_movies(movie_record catalog[], string displayFilter){
    movie_record tempStruct;
    memberPtr orderType[3] = {&movie_record::title, &movie_record::genre,
                              &movie_record::rating};
    int orderSelection = 0;    //Assumes "title"
    
    if(displayFilter == "genre")
        orderSelection = 1;
    
    if(displayFilter == "rating")
        orderSelection = 2;
    
    for(int h = 1; h < NUM_MOVIES; h++)
        for(int i = 1; i < NUM_MOVIES; i++)
            /* Bubble sort catalog in lexicographic order by member name */
            if(catalog[i].*orderType[orderSelection] < 
                catalog[i - 1].*orderType[orderSelection]){
                tempStruct = catalog[i - 1];
                catalog[i - 1] = catalog[i];
                catalog[i] = tempStruct;
            }
    output_movies(catalog);   
}   //14 Lines of code

/* Outputs catalog to screen */
void output_movies(movie_record catalog[]){
    cout << endl;    //Additional white space for readability
    
    for(int j = 0; j < NUM_MOVIES; j++)
        cout << "\n" << catalog[j].title
             << "\n\tGenre: " << catalog[j].genre
             << "\tRated: " << catalog[j].rating;
    
    cout << endl << endl;    //Additional white space for readability
}   //4 Lines of code

/* Prompts user for title, outputs title and description, and prompts
 * for rental if copies are available. */
void get_movie_info(movie_record catalog[]){
    bool validSelection = false;
    string selection = "";
    
    do{
        cout << "\n\nWhich movie are you interested in?\n"
             << "(Selection is case- and punctuation-sensitive)\n"
             << "Type 'list' to see our selection\n";  
        getline(cin, selection);
        if(selection == "list")
            output_movies(catalog);    //Output list in current order
        for(int i = 0; i < NUM_MOVIES; i++)
            if(catalog[i].title == selection){
                get_movie_info(catalog, i);   //Output title and description
                rent_movie(catalog, i);    //Prompt for rental if there are copies
                validSelection = true;
            }
        if(!(validSelection) && (selection != "list"))
            cout << "\n\nI have no movie matching that title.\n";         
    }while(!(validSelection));
}   //15 Lines of code

/* Outputs title and description of movie selection. */
void get_movie_info(movie_record catalog[], int movieSelection){
    cout << "\n\nTitle:\t" << catalog[movieSelection].title << endl;
    cout << "Description: " << "\n\t"
         << catalog[movieSelection].description << endl;
    cout << "Genre:\t" << catalog[movieSelection].genre
         << "\nRating:\t" << catalog[movieSelection].rating;
    cout << "\nCopies:\t" << catalog[movieSelection].copies << endl;
}   //4 Lines of code
   
/* Prompts user for rental preference if copies are available. */
void rent_movie(movie_record catalog[], int movieSelection){
    string rentPref = "";
    
    if(catalog[movieSelection].copies > 0){
        cout << "\n\nWould you like to rent that movie?\n";
        getline(cin, rentPref);
        if((rentPref[0] == 'Y') || (rentPref[0] == 'y')){
            catalog[movieSelection].copies--;
            cout << "\nIt's all yours! It's due back Thursday by noon!\n";
        }
    }
    else
        cout << "\n\nSorry! No copies of that movie in stock.\n\n";
}   //9 Lines of code