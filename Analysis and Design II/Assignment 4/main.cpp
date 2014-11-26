/************************************************************************
 Title         : main.cpp
 Author        : Peter Kamaris
 Created on    : May 2 2013
 Description   : Program is designed to create a spell check Dictionary of words
 Purpose       : Assignment4
 Build with    : g++ main.cpp
 *************************************************************************/
#include <iostream>
#include <cstdlib>
#include <fstream> //included to open and read lines from the file
#include <string>//included for the strings
#include <vector> //included for the vector
//#include <ncurses.h>
#include "Trie.hpp" //included because well..we need them to work
#include "dictionary.hpp" //same as above

using namespace std;

int main()
{


//initscr();			// Start curses mode
//raw();				// Line buffering disabled
//noecho();
int intake;
string word_intake; //Each 3 will be used for the menu
char * char_intake = new char[5]; //created to use in the function parameter
vector<string> temp; //Will be used for alternatives function
string words; //Creating this string to take each line from the text file
ifstream myfile; //ifstream variable to open the file
Dictionary Dict; //Creating a Dictionary

myfile.open("sae-sorted.dic"); //Trying to open the file

  if(myfile.is_open())//If the file opened then we will go to the while loop
  {
    while(myfile.good())//while the file open is good we will keep taking lines from the file
    {
      getline(myfile, words); //Taking the line and inserting it into temp
      Dict + words; //Adding words to the dictionary using the += function
    }
    myfile.close(); //Once done we will close it securely
  }

  else{ //If the text file never opened we will print that it was unable to open
    //printw("Unable to open file");
    //refresh();
  }

//printw("Welcome to the Menu");
//refresh();


cout << "Welcome to the Menu" << endl;
cout << "If you would like to add a word enter 1" << endl;
cout << "To count enter 2" << endl;
cout << "To check alternatives enter 3" << endl;
cin >> intake;

switch(intake){ //Simple menu with options of what to do
    case 1:
		cout << "Please enter the word" << endl;
		cin >> word_intake;
		cout << endl;
		Dict + word_intake;
		cout << word_intake << " has been inserted unless stated otherwise" << endl;
        break;

    case 2:
        cout << "If you would like to count a word press 1, for character press 2" << endl;
        cin >> intake;
        cout << endl;

            switch(intake){ //Switch within a switch for other options
                case 1:
                    cout << "Please enter the word" << endl;
                    cin >> word_intake;
                    cout << endl;
                    Dict.count(word_intake); //Takes word and looks for the count
                    break;

                case 2:
                    cout << "Please enter the char" << endl;
                    cin >> char_intake;
                    cout << endl;
                    Dict.count(char_intake); //Takes car and looks for count
                    break;
            }
        break;
    case 3: //Everything else is self explanatory they are just switches in switches for options
        cout << "If you would like to check alternatives of a word press 1" << endl;
        cout << "For character press 2" << endl;
        cin >> intake;

        switch(intake){
            case 1:
                cout << "Please enter a word" << endl;
                cin >> word_intake;
                cout << endl;

                    if(temp.size() == 0){ //To start with the temp size is 0 because it has nothing in it

                        temp = Dict.alternatives(word_intake); //This function was never specified to take correct spelling or incorrect spelling so either way it responds to both
                        //Temp will take vector from the function, within the function if the word is spelled wrong it will return a vector of size 0

                            while(temp.size() == 1){ //While it is one we will keep trying and making the word smaller and smaller
                                    word_intake = word_intake.substr(0, word_intake.size()-1); //If not we will try again with the word minus the last letter
                                    temp = Dict.alternatives(word_intake); //Try try and try again
                                }

                            }
                            break;
            case 2:
                cout << "Please enter the character" << endl;
                cin >> char_intake;
                cout << endl;
                temp = Dict.alternatives(char_intake); //same as above
                break;
            }
    }
delete char_intake;//deleting for precaution
char_intake = NULL;//nulling for memory leak

}


