/************************************************************************
 Title         : Body.cpp
 Author        : Peter Kamaris
 Created on    : February 13 2013
 Description   : Program is created to organize muscles and complete
		 action, strength, or diagnostic inquiries.
 Purpose       : Assignment1
 Build with    : g++ Body.cpp
 *************************************************************************/
#include "Body.h"

Body::Body()
{
    //Just a default constructor
}
  //These 5 set functions are called when reading the file to send the information into
  //the vector and store them

void Body::set_muscle(string the_muscle)
{
      Muscle.push_back(the_muscle);
}
void Body::set_origin(string the_origin)
{
    Origin.push_back(the_origin);
}
void Body::set_deep(string the_deep)
{
    Deep.push_back(the_deep);
}
void Body::set_location(string the_location)
{
    Location.push_back(the_location);
}
void Body::set_action(string the_action)
{
    Action.push_back(the_action);
}

  //These 5 set functions are called when trying to retriece information and send it to main

string Body::get_muscle(int i)
{
    return Muscle[i];
}
string Body::get_origin(int i)
{
    return Origin[i];
}
string Body::get_deep(int i)
{
    return Deep[i];
}
string Body::get_location(int i)
{
    return Location[i];
}
string Body::get_action(int i)
{
    return Action[i];
}
int Body::get_location_size()
{
    return Location.size();
}
int Body::get_muscle_size()
{
    return Muscle.size();
}
int Body::get_action_size()
{
   return Action.size();
};
