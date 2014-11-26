/************************************************************************
 Title         : ABlist.cpp
 Author        : Peter Kamaris
 Created on    : March 10 2013
 Description   : Program is designed to show us how ABlists exactly work.
 Purpose       : Assignment2
 Build with    : g++ ABlist.cpp
 *************************************************************************/
#ifndef _BRIZAN_ABLIST_H_
#define _BRIZAN_ABLIST_H_

#define LIST_MAX 10

#include "ABCList.hpp"

template <class T>
class ABList : public ABCList<T> {
private:
	T    a [LIST_MAX];
	int  size;

public:
	     ABList ();
    //Pre: Nothing
	//Post: Creates a ABlist with size set to 0;
	virtual bool isEmpty ();
	//Pre: Assumes nothing
	//Post: Tests and checks if the Array is empty
	virtual int  getLength ();
    //Pre: Assumes nothing
	//Post: Retrieves the length of the array and returns it
	virtual void insert (int pos, T item);
    //Pre: Checks if pos is in bounds
	//Post: If so it will be inserted into list
	virtual T    remove (int pos);
    //Pre: Assumes pos is in bounds and there is something in the array
	//Post: Deletes the specified spot in the array and reduces size by 1
	virtual T    retrieve (int pos);
    //Pre: Assumes pos is in bounds and there is something in the array
	//Post: Retrieves data from specified slot
};


template <class T>
ABList<T>::ABList () { //default constructor
	size = 0; //Making size = 0 to begin counting
}

template <class T>
bool ABList<T>::isEmpty () {
	if (size == 0) //If size is bigger than 0 then the list is not empty
		return true;
	return false;
}

template <class T>
int ABList<T>::getLength () {
	return size; //Call the function and it returns the size of the array
}

template <class T>
void ABList<T>::insert(int pos, T item) {
    try{
        if (pos <= 0 || pos > size+1) //First checks if the position inserted by the user is valid
            throw 13; //If not it gets rejected and main prints it was not inserted
       }
       catch(int e){ //If the pos is one of those stated above, the 13 is caught here
           throw 13;
       }
       if((pos-1) < size){

            for(int i = size; (pos-1) < i; i--) //Checking to see we don't overpass array limit
            {
                a[i] = a[i-1]; //Shifting elements to create space for new element
            }
        a[pos-1] = item; //Inserting item into desired slot
       }
        else
        a[pos-1] = item; //If there wasn't a desired spot or its the initial spot we just insert it
           ++size;
}

template <class T>
T ABList<T>::remove (int pos) {

    T a_copy = a[pos-1]; //pos-1 so we access the actual wanted spot instead of the one ahead

    try{
        if (pos <= 0 || pos > size) //Again we try and catch if anything
		throw 13;
    }
    catch(int e){
        throw 13;
    }

    for(int i = pos; i < size; i++){ //shifts the elements in the array and shortens size of array by one
    a[i-1] = a[i];
        }
    size--; //Shortens size by 1
	return a_copy; //Returns element as requested
}

template <class T>
T ABList<T>::retrieve (int pos) {
    try{
        if (pos <= 0 || pos > size) //I think we get the point by now
            throw 13;
    }
    catch(int e){
        throw 13;
    }

	return a[pos - 1]; //Returns the data in the position asked by the user
}

#endif

