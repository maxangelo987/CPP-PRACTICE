/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     10/26/2013
 * Last Modified:    06/20/2014
 * Description:      Demonstrates the capabilities of the 'Document' class  
 *                   and its children classes 'Email' and 'File'.  The main
 *                   driver demonstrates the capabilities of these classes
 *                   by searching the text of each 'Email' or 'File' for a
 *                   keyword and outputs the result.
 * Input:            No input from user or file, but instances of 'Document'
 *                   classes (and sub-classes) are defined in the main.
 * Output:           Introduction and output results of boolean search for
 *                   keyword to screen.
 * Acknowledgements: Absolute C++, Seventh Edition
 *                   stackoverflow.com forum for inspiration with sting::erase
 ****************************************************************************/

#include <iostream>
#include <string>

using std::cout;
using std::string;

/* Every document has text */
class Document{
    public:
        /* Constructors */
        Document();
        Document(string text);
        
        /* Accessors */
        string getText() const;
        
        /* Mutators */
        void setText(string newText);
        
        /* Operator overloads */
        Document& operator =(const Document& rtSide);
    protected:
        /* Variable declarations */
        string text;
};

/* Every email is a document with a sender, receiver, and a title */
class Email : public Document{
    public:
        /* Constructors */
        Email();
        Email(string sender, string recipient);
        Email(string sender, string recipient, string title);
        Email(string sender, string recipient, string title, string text);
        
        /* Accessors */
        string getSender() const;
        string getRecipient() const;
        string getTitle() const;
        
        /* Mutators */
        void setSender(string sender);
        void setRecipient(string recipient);
        void setTitle(string title);
        
        /* Operator overloads */
        Email& operator =(const Email& rtSide);
    private:
        /* Variable declarations */
        string sender, recipient, title;
};

/* Every file is a document with a pathname */
class File : public Document{
    public:
        /* Constructors */
        File();
        File(string pathname);
        File(string pathname, string text);
        
        /* Accessors */
        string getPath() const;
        
        /* Mutators */
        void setPath(string pathname);
        
        /* Operator overloads */
        File& operator =(const File& rtSide);
    private:
        /* Variable declarations */
        string pathname;
};

/* Searches text in Document argument for an instance of string argument */
bool ContainsKeyword(const Document& docObject, string keyword);

/* Standardizes text in Document argument, searches for keyword, and outputs 
    result */
void testDocument(const Document& docObject, string keyword);

/* Standardizes string to all lower case letters and removes punctuation */
string toLower(string mixedCaseStr);

int main(){
    /* Variable declarations */
    Email email1("Sam",
                 "Frodo",
                 "RE: What are we holding onto, Sam?", 
                 "That there's some good in this world, Mr. Frodo, and it's worth fighting for."),
          email2("Gandalf",
                 "Saruman",
                 "RE: Sauron",
                 "There is only one Lord of the Ring, only one who can bend it to his will. And he does not share power."),
          email3("Gollum",
                 "Frodo",
                 "RE: Filthy Hobbitses",
                 "We swears, to serve the master of the Precious. We will swear on… on the Precious!");
    File file1("C:\\DOS\\",
               "There are 10 types of people in the world: those who understand binary, and those who don't."),
          file2("C:\\DOS\\RUN\\",
                "I would love to change the world, but they won't give me the source code."),
          file3("%\\RUN\\DOS\\RUN\\",
                "My software never has bugs. It just develops random features.");
    string keyword1("ring"), keyword2("world");
    
    /* Output email demonstration */
    cout << "\n\nThree emails from Middle Earth have been recovered!";
    cout << "\nSearching emails for keyword: \"" << keyword1 << "\"";
    cout << "\nEmail 1:\t";
    testDocument(email1, keyword1);
    cout << "\nEmail 2:\t";
    testDocument(email2, keyword1);
    cout << "\nEmail 3:\t";
    testDocument(email3, keyword1);
    
    /* Output file demonstration */
    cout << "\n\nThree files from an old x86 computer have been recovered!";
    cout << "\nSearching files for keyword: \"" << keyword2 << "\"";
    cout << "\nFile 1:\t\t";
    testDocument(file1, keyword2);
    cout << "\nFile 2:\t\t";
    testDocument(file2, keyword2);
    cout << "\nFile 3:\t\t";
    testDocument(file3, keyword2);
    
    cout << "\n\n";    //Additional white space for readability
    
    return 0;
}

/* Constructors for Document class */
Document::Document(){
    text = "";
}

Document::Document(string text){
    this->text = text;
}

/* Accessors for Document class */
string Document::getText() const{
    return text;
}

/* Mutators for Document class */
void Document::setText(string newText){
    this->text = newText;
    
    return;
}

/* Operator overloads for Document class */
Document& Document::operator =(const Document& rtSide){
    text = rtSide.text;
    
    return *this;
}

/* Constructors for Email class */
Email::Email():Document(){
    this->sender = "";
    this->recipient = "";
    this->title = "";
}

Email::Email(string sender, string recipient):Document(){
    this->sender = sender;
    this->recipient = recipient;
    this->title = title;
}

Email::Email(string sender, string recipient, string title):Document(){
    this->sender = sender;
    this->recipient = recipient;
    this->title = title;
}

Email::Email(string sender, string recipient, string title, string text):Document(text){
    this->sender = sender;
    this->recipient = recipient;
    this->title = title;
}

/* Accessors for Email class */
string Email::getSender() const{
    return sender;
}

string Email::getRecipient() const{
    return recipient;
}

string Email::getTitle() const{
    return title;
}

/* Mutators for Email class */
void Email::setSender(string sender){
    this->sender = sender;
    
    return;
}

void Email::setRecipient(string recipient){
    this->recipient = recipient;
    
    return;
}

void Email::setTitle(string title){
    this->title = title;
    
    return;
}

/* Operator overloads for Email class */
Email& Email::operator =(const Email& rtSide){
    sender = rtSide.sender;
    recipient = rtSide.recipient;
    title = rtSide.recipient;
    text = rtSide.text;
    
    return *this;
}

/* Constructors for File class */
File::File():Document(){
    this->pathname = "";
}

File::File(string pathname):Document(){
    this->pathname = pathname;
}

File::File(string pathname, string text):Document(text){
    this->pathname = pathname;
}

/* Accessors for File class */
string File::getPath() const{
    return pathname;
}

/* Mutators for File class */
void File::setPath(string pathname){
    this->pathname = pathname;
    
    return;
}

/* Operator overloads for File class */
File& File::operator =(const File& rtSide){
    this->text = rtSide.text;
    this->pathname = rtSide.pathname;
    
    return *this;
}

/* Searches text in Document argument for an instance of string argument */
bool ContainsKeyword(const Document& docObject, string keyword){
    if (docObject.getText().find(keyword) != string::npos)
        return true;
    
    return false;
}

/* Standardizes text in Document argument, searches for keyword, and outputs 
    result */
void testDocument(const Document& docObject, string keyword){
    string loweredString(toLower(keyword));
    Document testDoc(toLower(docObject.getText()));
    
    if(ContainsKeyword(testDoc, loweredString))
        cout << "Found keyword!";
    else
        cout << "No keyword found.";
}

/* Standardizes string to all lower case letters and removes punctuation */
string toLower(string mixedCaseStr){
    string returnString = mixedCaseStr;
    
    for(int i = 0; i < returnString.length(); i++){
        /* Changes all characters to lower case */
        returnString[i] = tolower(returnString[i]);
        /* Removes punctuation */
        if(ispunct(returnString[i])) 
            returnString.erase(returnString.find_first_of(returnString[i]));
    }
    
    return returnString;
}