/************************************************************************
 Title         : main.cpp
 Author        : Peter Kamaris
 Created on    : Nov 29 2013
 Description   : Program is designed to show how Heaps work
 Purpose       : Assignment
 Build with    : g++ main.cpp
 *************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <limits>
#include "QuadraticProbing.h"
#include "QuadraticProbing.cpp"
#include "BinaryHeap.h"
#include "dsexceptions.h"
using namespace std;

int main(int argc, char* argv[])
{

char * users_input = argv[1];

int flag;

cout << "If you would like to enter numbers, enter 1." << endl;
cout << "If you would like to enter numbers through a file, enter 2" << endl;
cin >> flag;


if(flag == 1){

BinaryHeap<int> Heap;
QHashTable<int> table;
int inputs;
string test;  //Initializing all the variables to be used
string test_2 ; //Another temp
int inputs_2;
int counter = 1;
int temp;

    while(test != "end"){

        cout << "Please enter a number to insert. If not enter 'end'." << endl;
        cin >> test;
            if(test == "end"){
                cout << "Onto the next step." << endl;
            }
                else{
                    istringstream ( test ) >> inputs; //First we take it as a string and store the int version in another variable
                    Heap.insert(inputs); //inserting into heap
                    table.alt_insert(inputs);//inserting into table
                    counter++;
                    for(int j = 1; j < counter; j++){
                        temp = Heap.returnval(j);
                        table.adjustments(temp, j);
                    }
                }

    }

    while(test_2 != "quit"){

        Heap.printHeap();
        cout << endl;
        cout << "Please enter a number to delete. If not enter 'quit'." << endl;
        cin >> test_2;
        cout << endl;

            if(test_2 == "quit"){
            }
            else{
                istringstream ( test_2 ) >> inputs_2; //First we take it as a string and store the int version in another variable
                Heap.remove(inputs_2);
                table.alt_remove(inputs_2);
                counter--;
                for(int x = 1; x < counter; x++){
                        temp = Heap.returnval(x);
                        table.adjustments(temp, x);
                }
                cout << endl;
                }
    }


    for(int x = 2; counter > x;){
            Heap.deleteMin();
            table.removemin();
            for(int j = 1; j < counter; j++){
                temp = Heap.returnval(j);
                table.adjustments(temp, j);
            }
            counter--;

            cout << "After removing the min this is the new min in the Heap " << Heap.retmin() << endl;
            cout << endl;
            Heap.printsorted();
            cout << endl;
    }

}

if(flag == 2){

    BinaryHeap<int> Heap;
    QHashTable<int> table;
    vector<string> holder;
    string line;
    int input;
    int endspot;
    int x = 0;
    int counter = 1;
    int temp;


    ifstream thefile(users_input); //Opening the file with variable thefile

    if (thefile.is_open()) //Attempting to open the file
    {
            while(thefile.good()) //Attempting to see if file works if opened
            {
                getline(thefile, line);
                holder.push_back(line);
                if(line == "end"){
                    endspot = x;
                }
                    x++;
            }
                    thefile.close();
        }
    else
        cout << "Unable to open file" << endl; //self explanatory


        for(int x = 0; x < endspot; x++ ){
            istringstream ( holder[x] ) >> input;
            Heap.insert(input); ///inserts numbers instead of words, no proof checking for words and other symbols
            table.insert(input);
            Heap.printHeap();
            counter++;
            for(int j = 1; j < counter; j++){
                temp = Heap.returnval(j);
                table.adjustments(temp, j);
            }
            cout << holder[x] << " was inserted." << endl;
            cout << endl;
}

        for(; endspot+1 < holder.size()-1; endspot++){

            istringstream ( holder[endspot+1] ) >> input;
            Heap.remove(input);
            table.remove(input);
            counter--;

                for(int x = 1; x < counter; x++){
                    temp = Heap.returnval(x);
                    table.adjustments(temp, x);
                }
            Heap.printHeap();
            cout << endl;
            cout << holder[endspot+1] << " was removed." << endl;
            cout << endl;
        }


    for(int x = 2; counter > x;){
            Heap.deleteMin();
            table.removemin();
            for(int j = 1; j < counter; j++){
                temp = Heap.returnval(j);
                table.adjustments(temp, j);
            }
            counter--;

            cout << "After removing the min this is the new min in the Heap " << Heap.retmin() << endl;
            cout << endl;
            Heap.printsorted();
            cout << endl;
    }


}


}
