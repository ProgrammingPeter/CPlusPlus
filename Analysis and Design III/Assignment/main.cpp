/************************************************************************
 Title         : main.cpp
 Author        : Peter Kamaris
 Created on    : Oct 14 2013
 Description   : Designed to see how AVL and BST work
 Purpose       : Assignment2
 Build with    : g++ main.cpp
 *************************************************************************/
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "testDNA.h"
#include "AvlTree.h"
#include "BinarySearchTree.h"

using namespace std;

int main(int argc, char* argv[]){

vector<string> info;

vector<DNA> DNAholder;

int insertcalls = 0;

int value = 0;

int x = 0;

int temp = 0;

string line;

int counter = 0;
int flag;

cout << "0 for AVL, 1 for BST" << endl;
cin >> flag;


if(flag == 0){
ifstream thefile("rebase210.txt");
//ifstream thefile(argv[0]);
BinarySearchTree<DNA> tree;
    if (thefile.is_open()) //Attempting to open the file
    {
            while(thefile.good()) //Attempting to see if file works if opened
            {
                getline(thefile,line);
                counter = 0;
                x = 0;
                temp = 0;
                info.clear();

                    while(counter < 3){

                        temp = line.find_last_of("//");
                        value = line.find_first_of("/"); //Finds spot of first comma and sends # to value
                        info.push_back(line.substr(x, value)); //the variables vector is storing each word
                        line.erase(x, value+1); //This is to take the original line and delete what was stored

                        if(value+1 == temp){
                            counter = 4;            //For counter to leave
                        }

                        counter++;

                    }

                    if(info.size() == 2){
                        DNA temp(info[0], info[1]);
                        DNAholder.push_back(temp);

                    }

                    else if(info.size() == 3){
                            DNA temp1(info[0], info[1]);
                            DNA temp2(info[0], info[2]);

                             DNAholder.push_back(temp1);
                             DNAholder.push_back(temp2);
                    }

            }

                    thefile.close();
        }
    else
        cout << "Unable to open file" << endl; //self explanatory


for(int x = 0; x < DNAholder.size(); x++){

    for(int i = 0; i < DNAholder.size(); i++){

        if(DNAholder[x] == DNAholder[i]){
            DNAholder[x].addEnzyme(DNAholder[i]);
        }
    }
}



for(int x = 0; x < DNAholder.size(); x++){
    tree.insert(DNAholder[x], insertcalls);
}
cout << "After processing the entire file the number of recursive insert calls is " << insertcalls << endl;
cout << endl;
DNAholder.clear();


string lookforsequence;
cout << "Enter the DNA Sequence you are looking for." << endl;
cin >> lookforsequence;
cout << endl;

DNA lookfor(lookforsequence);

int containingcalls = 0;

if(!(tree.contains(lookfor))){
    cout <<lookforsequence << " was not found." << endl;
    cout << endl;
}



int nodesintree = 0;
double iplvalue = 0;
tree.countnode(nodesintree);
cout << "The amount of nodes in the tree is  " << nodesintree << endl;
cout << endl;
cout << "Log " << nodesintree << " in base 2 is " << log2(nodesintree) << endl;
cout << endl;

tree.ipl(iplvalue);
cout << "The average internal path length is " << iplvalue/nodesintree << endl;
cout << endl;
cout << "The ratio of average depth to log n base 2 is " << (log2(nodesintree))/(iplvalue/nodesintree) << endl;
cout << endl;


vector<string> DNAsequences;


ifstream afile("sequences.txt");
//ifstream afile(argv[1]);

    if (afile.is_open()) //Attempting to open the file
    {
            while(afile.good()) //Attempting to see if file works if opened
            {
                getline(afile,line);
                DNAsequences.push_back(line);

            }
                    thefile.close();
        }
    else
        cout << "Unable to open file" << endl; //self explanatory




for(int x = 0; x < DNAsequences.size(); x++){

        DNA temp(DNAsequences[x]);
        tree.doesitcontain(temp, containingcalls);

    }
cout << "The number of recursive containing calls is " << containingcalls << endl;
cout << endl;

int removecalls = 0;

    for(int x = 0; x < DNAsequences.size(); x+=2){
            DNA temp(DNAsequences[x]);
            tree.remove(temp, removecalls);
    }


cout << "The number of recurisve remove calls is " << removecalls << endl;
cout << endl;

nodesintree = 0;
iplvalue = 0;
tree.countnode(nodesintree);
cout << "The amount of nodes in the tree is  " << nodesintree << endl;
cout << endl;
cout << "Log " << nodesintree << " in base 2 is " << log2(nodesintree) << endl;
cout << endl;

tree.ipl(iplvalue);
cout << "The average internal path length is " << iplvalue/nodesintree << endl;
cout << endl;
cout << "The ratio of average depth to log n base 2 is " << (log2(nodesintree))/(iplvalue/nodesintree) << endl;
cout << endl;


containingcalls = 0;


for(int x = 0; x < DNAsequences.size(); x++){

        DNA temp(DNAsequences[x]);
        tree.doesitcontain(temp, containingcalls);

    }
cout << "The number of recursive containing calls is " << containingcalls << endl;
cout << endl;


DNAholder.clear();
DNAsequences.clear();

}

else if(flag == 1){
    ifstream thefile("rebase210.txt");
//ifstream thefile(argv[0]);
AvlTree<DNA> tree;
    if (thefile.is_open()) //Attempting to open the file
    {
            while(thefile.good()) //Attempting to see if file works if opened
            {
                getline(thefile,line);
                counter = 0;
                x = 0;
                temp = 0;
                info.clear();

                    while(counter < 3){

                        temp = line.find_last_of("//");
                        value = line.find_first_of("/"); //Finds spot of first comma and sends # to value
                        info.push_back(line.substr(x, value)); //the variables vector is storing each word
                        line.erase(x, value+1); //This is to take the original line and delete what was stored

                        if(value+1 == temp){
                            counter = 4;            //For counter to leave
                        }

                        counter++;

                    }

                    if(info.size() == 2){
                        DNA temp(info[0], info[1]);
                        DNAholder.push_back(temp);

                    }

                    else if(info.size() == 3){
                            DNA temp1(info[0], info[1]);
                            DNA temp2(info[0], info[2]);

                             DNAholder.push_back(temp1);
                             DNAholder.push_back(temp2);
                    }

            }

                    thefile.close();
        }
    else
        cout << "Unable to open file" << endl; //self explanatory


for(int x = 0; x < DNAholder.size(); x++){

    for(int i = 0; i < DNAholder.size(); i++){

        if(DNAholder[x] == DNAholder[i]){
            DNAholder[x].addEnzyme(DNAholder[i]);
        }
    }
}



for(int x = 0; x < DNAholder.size(); x++){
    tree.insert(DNAholder[x], insertcalls);
}
cout << "After processing the entire file the number of recursive insert calls is " << insertcalls << endl;
cout << endl;
DNAholder.clear();


string lookforsequence;
cout << "Enter the DNA Sequence you are looking for." << endl;
cin >> lookforsequence;
cout << endl;

DNA lookfor(lookforsequence);

int containingcalls = 0;

if(!(tree.contains(lookfor))){
    cout <<lookforsequence << " was not found." << endl;
    cout << endl;
}



int nodesintree = 0;
double iplvalue = 0;
tree.countnode(nodesintree);
cout << "The amount of nodes in the tree is  " << nodesintree << endl;
cout << endl;
cout << "Log " << nodesintree << " in base 2 is " << log2(nodesintree) << endl;
cout << endl;

tree.ipl(iplvalue);
cout << "The average internal path length is " << iplvalue/nodesintree << endl;
cout << endl;
cout << "The ratio of average depth to log n base 2 is " << (log2(nodesintree))/(iplvalue/nodesintree) << endl;
cout << endl;


vector<string> DNAsequences;


ifstream afile("sequences.txt");
//ifstream afile(argv[1]);

    if (afile.is_open()) //Attempting to open the file
    {
            while(afile.good()) //Attempting to see if file works if opened
            {
                getline(afile,line);
                DNAsequences.push_back(line);

            }
                    thefile.close();
        }
    else
        cout << "Unable to open file" << endl; //self explanatory




for(int x = 0; x < DNAsequences.size(); x++){

        DNA temp(DNAsequences[x]);
        tree.doesitcontain(temp, containingcalls);

    }
cout << "The number of recursive containing calls is " << containingcalls << endl;
cout << endl;

int removecalls = 0;

    for(int x = 0; x < DNAsequences.size(); x+=2){
            DNA temp(DNAsequences[x]);
            tree.remove(temp, removecalls);
    }


cout << "The number of recurisve remove calls is " << removecalls << endl;
cout << endl;

nodesintree = 0;
iplvalue = 0;
tree.countnode(nodesintree);
cout << "The amount of nodes in the tree is  " << nodesintree << endl;
cout << endl;
cout << "Log " << nodesintree << " in base 2 is " << log2(nodesintree) << endl;
cout << endl;

tree.ipl(iplvalue);
cout << "The average internal path length is " << iplvalue/nodesintree << endl;
cout << endl;
cout << "The ratio of average depth to log n base 2 is " << (log2(nodesintree))/(iplvalue/nodesintree) << endl;
cout << endl;


containingcalls = 0;


for(int x = 0; x < DNAsequences.size(); x++){

        DNA temp(DNAsequences[x]);
        tree.doesitcontain(temp, containingcalls);

    }
cout << "The number of recursive containing calls is " << containingcalls << endl;
cout << endl;


DNAholder.clear();
DNAsequences.clear();

    }
}

