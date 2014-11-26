/************************************************************************
 Title         : dictionary.hpp
 Author        : Peter Kamaris
 Created on    : May 2 2013
 Description   : Program is designed to create a spell check Dictionary of words
 Purpose       : Assignment4
 Build with    : g++ dictionary.hpp
 *************************************************************************/
#include <iostream>
#include <vector> //The other libraries are included inorder to use them within this file
#include <string>
//#include <ncurses.h>
#include "Trie.hpp" //Including the ADT to implement it

struct Node{ //Node is created to be used within the Trie

public:
    Node();
    //Pre: Node constructor
    //Post : When constructed the bool variable will be initialzed to false

    Node * findchild(char  x);
    //Pre : This function is expecting there to be nodes within the vector variable for searching
    //Post: If no Nodes are found it will return NULL

    Node * addchild(Node * X){
        words.push_back(X);
    }
    //Pre: Assumes nothing
    //Post : Adds a node into the vector of type node

    void setchar(char x){
       letter = x;
     }
    //Pre: Assumes nothing
    //Post: Sets the char in the parameter to the private variable letter

    void insertword_with_bool(string word){
        full_word = word;
        approval = true;
        }
    //Pre; Assumes nothing
    //Post: Takes the word and inserts it into private variable full word and changes the bool approval from false to true

    void printword(){
     cout << full_word << endl;
     }
    //Pre: Assumes the total word variable has a string within
    //Post: Prints the word to the screen
    bool approved(){
        return approval;
    }
    //Pre:Assumes the word has been inserted
    //Post: Returns the value of the variable approval which is either true or false
    int vsize(){
        return words.size();
    }
    //Pre: Assumes the vector exists
    //Post: Returns the size of the vector of the approriate Node
    string return_word(){
        return full_word;
    }
    //Pre: Assumes the word has been inserted
    //Post: Returns the word
    void addtotal(){
        total++;
    }
    //Pre: Assumes the letter has either been found or is created
    //Post: Increments total so we know how many words have been inserted
    //Each time we pass by a letter we know a word will be inserted so the total gets 1+

    int the_total(){
        return total;
    }
    //Pre: Assuming the total is some number above 0
    //Post: Simply returning the value

    virtual vector<string> getvalidwords(Node * node);
    //Pre: Assumes the vectors have words stored in them
    //Post: Prints out the words for the specificed situation
private:
    bool approval; //To know whether or not it is a full word
    string full_word; //When it is a full word it will be inserted here
    int total; //Total for # of words
    char letter; //Letter representing the node
    vector<Node*> words; //This vector will hold nodes with other letters so can connect the words
};

Node::Node(){ //Should've left inside, stupid of me....future me laughs at old me -__-

    approval = false; //Constructor for node and when constructed we initialize approval to false
    total = 0;
}

class Dictionary: public Trie{

public:

    Dictionary(); //Constructor for Dictionary

    virtual ~Dictionary(); //Destructor for Dictionary

    // This function opens the file named by the argument. This file is in
	// Unix format with one dictionary entry per line. It must return true
	// when the file has been read into memory; false otherwise.
	virtual bool addDictionary (string filename);

    // This function adds a word (the argument) to the dictionary. This
	// must also be written to the dictionary file read in the
	// "addDictionary" function, assuming it has been called. Returns true
	// when the word has been added to the dictionary; false otherwise.
	virtual Trie& operator+(const string & word);

    // This function returns the count of the words starting with the
	// prefix (passed as the argument). In the case of sae-sorted.dic and
	// the prefix "this", the function should return 5. If no dictionary
	// entries start with the prefix, this function should return 0.
	virtual int count (string prefix);

 	// Overloaded version of the above function
	virtual int count (char * prefix);
	// This function provides alternative spellings to the prefix (passed
	// as the argument). If no prefix exists in the data, this function
	// removes the rightmost character and re-attempts this function. The
	// return value of the the empty string is implementation-dependent.
	virtual vector<string> alternatives (string prefix);
	// Overloaded version of the above function
	virtual vector<string> alternatives (char * prefix);
private:

    Node * root; //We are having a node within the Dictionary so we can have a starting point, also why it is titled root
};

Dictionary::Dictionary(){

    root = new Node(); //When the Dictionary is initialized we will have a root be a new node
}
Dictionary::~Dictionary(){

    delete root; //This is the destructor and we are deleting the root which contains everything and
    root = NULL; //then nulling it to be cautious of memory leaks
}

bool Dictionary::addDictionary (string filename){

    Node * current = root; //First create a node and make a copy of root into it

    for(int i = 0; i < filename.length(); i++){ //We will check each letter until we reach the end of the word

        current = current->findchild(filename[i]); //We will be taking each letter and then checking to see if it was inserted or not

            if(current == NULL){ //If at some point NULL is returned that means the word was not inserted
                    cout << filename << " was not inserted" << endl;
            }
    }
}

Trie& Dictionary::operator+(const string & word){ //We will doing a operator overload in which we dictate what happens when using the + sign

    Node * current = root; //Once again we are making a copy of root into current

    if(word.length() == 0){ //If the word's length is equal to 0 that means there is nothing and well we will just leave
        //return; //true; //returning true to satisfy the type of the function
    }

    for(int i = 0; i < word.length(); i++){ //The loop runs once for each letter

        Node * child = current->findchild(word[i]); //We are checking to see if the letter has been inserted in the node or not
        //If something was found it will return the node, if not it will return NULL into child

        if(child != NULL){

            current = child; //If it is not null we will switch from child back to current and continue
            current->addtotal(); //Since we found the letter and we are inserting a word we will increment it
        }
        else{ //If null was returned we will create a node

            Node * temp = new Node(); //Node created
            temp->setchar(word[i]); //Setting the char into the node we created
            temp->addtotal(); //Incrementing the counter within the node we created
            current->addchild(temp); //Adding that node into the vector  of currents node
            current = temp; //Then we make a copy and proceed
        }
        if(i == word.length()-1){
            current->insertword_with_bool(word); //At this stage we are inserted the full word and changing the bool from false to true to indicate it is a complete word
        }

    }

addDictionary(word); //Here are testing to see if the word was properly inserted

}

int Dictionary::count(string prefix){

    Node * current = root; //Yet again making a copy of root

        for(int i = 0; i < prefix.length(); i++){ //Running through each letter
                prefix[i] = tolower(prefix[i]); //Converting all to lowercase just in case
            current = current->findchild(prefix[i]); //Running through the the letters to find the word

            if(current == NULL){
                cout << "Sorry " << prefix << " was not found in the Dictionary." << endl;
                return i; //returning i to comply with the function specifications
                }

        }

        cout << current->the_total(); //Once we found the word we will print it to the screen

}

int Dictionary::count (char * prefix){

    string x = prefix; //Here we are putting prefix into a string to comply with the other function specifications
    Node * current = root; //Another copy
    x[0] = tolower(x[0]); //lowercase just in case
    current = current->findchild(x[0]); //Finding that one child
    cout << current->the_total(); //Printing the total to the screen again

}

vector<string> Dictionary::alternatives (string prefix){

Node * current = root; //Another copy
vector<string> words;

for(int i = 0; i < prefix.length(); i++){

    prefix[i] = tolower(prefix[i]); //lowercase words
    current = current->findchild(prefix[i]); //find letters

    if(current == NULL){
           words.push_back("true"); //returning the size of one if prefix is incorrect or not found
           return words;
    }
}

words = current->getvalidwords(current); //find words and print em
cout << prefix << endl; //print correct prefix
return words; //return size 0
}



vector<string> Dictionary::alternatives (char * prefix){

    vector<string> temp;
    Node * current = root; //Another copy
    string x = prefix; //Changing it to string to comply with the function requirements
    if(isupper(x[0])){
        prefix[0] = tolower(prefix[0]); //lowercase just in case
    }
    current = current->findchild(x[0]); //Finding the child
    temp = current->getvalidwords(current); //Recursively going through each and every node to print them
    return temp;
}


Node * Node::findchild(char x){

    for(int i = 0; i < words.size(); i++){ //Going through the vector of the node looking for the letter

            Node * temp = words.at(i); //Checking each node

            if(temp->letter == x){ //If the letter in the node is equal to the char x we will return temp
                return temp;
            }
    }
return NULL; //if not we will return NULL
}

vector<string> Node::getvalidwords(Node * node){

    Node * temp;
    vector<string> valid; //Creating a vector of type string named valid whose purpose is to hold words

    for(int i = 0; i < node->vsize(); i++){ //Going through each nodes vector size constantly checking

        temp = node->words.at(i); //Returning each node
        getvalidwords(temp); //Recursively running to check if we come across words

            if(temp->approval){ //If we found a word

            valid.push_back(temp->full_word); //It will be inserted into valid

            }
        }

    for(int x = 0; x < valid.size(); x++){
        cout << valid.at(x) << endl; //Printing everything stored in the vector
    }

return valid;
}
