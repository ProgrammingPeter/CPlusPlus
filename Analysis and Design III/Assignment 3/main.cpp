/************************************************************************
 Title         : main.cpp
 Author        : Peter Kamaris
 Created on    : Oct 29 2013
 Description   : Program is designed to show how Hash Tables work
 Purpose       : Assignment3
 Build with    : g++ main.cpp
 *************************************************************************/

#include <iostream>
#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;



//This function expects a word and a table from address and
//it will be adding a letter from the entire alphabet in each position
//to see if it matches a word in the Hash Table
void addletter(string word, QHashTable<string> &table);

//This function expects a word and a table from address and
//it will be erasing a letter from the word itself
//to see if it matches a word in the Hash Table
void eraseletter(string word, QHashTable<string> &table);

//This function expects a word and a table from address and
//it will be swapping characters within it's own word
//to see if it matches a word in the Hash Table
void swapcharacter(string word, QHashTable<string> &table);

int main(int argc, char* argv[])
{


srand (time(NULL)); //So results are different each and everytime

char* Document = argv[1];
char* Dictionary = argv[2];

LHashTable<int> test_table;

double successfulprobes = 0;
double failedcheck = 3001; //Designed to start at 3001, because all the numbers entered are less than 3000
double unsuccessfulprobes = 0;
double loadfactor  = 50;


vector<double> stored;


cout << "Insert." << endl;
cin >> loadfactor;

    for(int x = 0; x < loadfactor; x++){

        stored.push_back(rand()%3000); //Selects a random number from 0 - 3000
        test_table.insert(stored[x]);  //Store it in a vector so we can know we are searching for it
    }

    for(int x = 0; x < loadfactor; x++){

    test_table.contains(stored[x]); //search for the numbers we stored so we know its in the table
    successfulprobes += test_table.returnprobe(); //Return the amount of probes needed to find the item

    test_table.contains(1.23232 * failedcheck); //Searching for numbers which are not in the table and in this case rand() only produces positive random ints so yeah
    unsuccessfulprobes += test_table.returnprobe(); //Return the amount of probes needed to find the item
    failedcheck++; //Increment the failedcheck so the number is different/

    }

cout << loadfactor << endl;
cout << successfulprobes/loadfactor << endl; //Simply printing out the avg of the current loadfactor
cout << unsuccessfulprobes/loadfactor << endl;



QHashTable<string> table;

vector<string> info, dict; //Vectors created to hold data from the input files

string line;

  ifstream thefile(Document); //Opening the file with variable thefile        thefile(Document)

    if (thefile.is_open()) //Attempting to open the file
    {

            while(thefile.good()) //Attempting to see if file works if opened
            {
                thefile >> line;
                    for(int i = 0; i < line.size(); i++)
                    {
                        line[i] = tolower(line[i]); //Simply takes each spot of the word/s and converts them
                    }

                info.push_back(line);

            }

                    thefile.close();
        }
    else
        cout << "Unable to open file" << endl; //self explanatory


          ifstream afile(Dictionary); //Opening the file with variable thefile                afile(Dictionary)

    if (afile.is_open()) //Attempting to open the file
    {

            while(afile.good()) //Attempting to see if file works if opened
            {
                afile >> line;
                dict.push_back(line);

            }

                    afile.close();
        }
    else
        cout << "Unable to open file" << endl; //self explanatory



for(int x = 0; x < dict.size()-1; x++){ //when going to insert it made a copy of the last thing twice.

    table.insert(dict[x]);

    }

cout << "These words are not located within the Dictionary file." << endl;
cout << endl;

for(int x = 0; x < info.size()-1; x++){

    if(!(table.contains(info[x]))){
            if(info[x] != "turing"){
                cout << info[x] << endl;
                addletter(info[x], table);
                eraseletter(info[x], table);  //checking all the words for their alternatives
                swapcharacter(info[x], table);
            }
    }
}


}



void addletter(string word, QHashTable<string> &table){

    string temp = word; //Takes the word so that it can be reused while not being over written


        for(int x = 0; x < word.length(); x++){
            for(char y = 'a'; y <= 'z'; y++){

                temp.insert(x, 1, y); //Inserting every letter at every position to see if it matches something in the dictionary

                if(table.contains(temp)){ //Gets checked in the table if there is a match and if there is it gets printed

                    cout << "*The original word is " << word << " and I believe you meant " << temp << "*" << endl;
                }
                temp = word; //Takes the original word again so that it can be used again

            }
        }

}


void eraseletter(string word, QHashTable<string> &table){


    string temp = word; //Takes the word so that it can be reused while not being over written


        for(int x = 0; x < word.length(); x++){

                temp.erase(x, 1);//Erasing a letter at every position to see if it matches something in the dictionary

                if(table.contains(temp)){ //Gets checked in the table if there is a match and if there is it gets printed

                    cout << "*The original word is " << word << " and I believe you meant " << temp << "*" << endl;
                }
                temp = word; //Takes the original word again so that it can be used again


        }

}


void swapcharacter(string word, QHashTable<string> &table){

    string temp = word; //Takes the word so that it can be reused while not being over written

        for(int x = 0; x < word.length()-1; x++){

                swap(temp[x],temp[x+1]); //Swaapping letters at every position to see if it matches something in the dictionary

                if(table.contains(temp)){ //Gets checked in the table if there is a match and if there is it gets printed

                    cout << "*The original word is " << word << " and I believe you meant " << temp << "*" << endl;
                }
                temp = word; //Takes the original word again so that it can be used again


        }

}
