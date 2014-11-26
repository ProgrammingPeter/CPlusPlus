/************************************************************************
 Title         : Body.h
 Author        : Peter Kamaris
 Created on    : February 13 2013
 Description   : Program is created to organize muscles and complete
		 action, strength, or diagnostic inquiries.
 Purpose       : Assignment1
 Build with    : g++ Body.H
 *************************************************************************/
#ifndef BODY_H
#define BODY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Body
{
    public:
        Body();
        //pre & post - Just a default constructor

        //These 5 set functions are called when reading the file to send the information into
        //the vector and store them
        void set_muscle(string the_muscle);
        void set_origin(string the_origin);
        void set_deep(string the_deep);
        void set_location(string the_location);
        void set_action(string the_action);

        //These five functions are called to retrieve them into main wen called upon
        //they have a int parameter to specifiy where in the vector
        string get_muscle(int i);
        string get_origin(int i);//never used, as far as requirements
        string get_deep(int i);
        string get_location(int i);
        string get_action(int i);

        //Only one of these is really required because they each have the same size
        //but for the sake of being open minded about the program reading another file
        //They each return the size of their respective vector
        int get_location_size();
        int get_muscle_size();
        int get_action_size();

    private:
        //created five vectors to store each information in each slot and to be called
        vector <string> Muscle;
        vector <string> Origin; //Isn't really needed except for storing because it is never used.
        vector <string> Deep;
        vector <string> Location;
        vector <string> Action;
};

#endif
