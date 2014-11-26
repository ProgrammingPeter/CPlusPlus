/************************************************************************
 Title         : LinkedList.hpp
 Author        : Peter Kamaris
 Created on    : March 10 2013
 Description   : Program is designed to show us how LinkedList exactly work
 Purpose       : Assignment2
 Build with    : g++ LinkedList.hpp
 *************************************************************************/
#ifndef _KAMARIS_LINKEDLIST_H_
#define _KAMARIS_LINKEDLIST_H_

#include "ABCList.hpp"

template<class T>
struct Node{ //Creating a node so we can have pointers for the class LinkedList
T data;      //The Node will hold data of type T
Node * next; //And a pointer of type Node
};

template<class T>
class LinkedList : public ABCList<T>{
private:
    int count; //This is to keep count of how long the list gets
    Node<T> * head; //Created to be pointing to the start of the list
public:
    LinkedList(); //Constructor
    virtual ~LinkedList(); //Destructor
    LinkedList(LinkedList  &otherList); //Copy constructor

    Node<T> * find(int pos); //Function to find position in list

    virtual bool isEmpty();
    virtual int getLength();
    virtual void insert (int pos, T item); //These five do as their title states
	virtual T remove (int pos);
	virtual T retrieve (int pos);

};

template<class T>
LinkedList<T>::LinkedList(){
    count = 0; //Initializes variable count to 0
    head = NULL; //And head to NULL which is a must and lets us know when we reach the end or if the list is empty
}
template<class T>
LinkedList<T>::~LinkedList(){ //Here we have a destructor

    while(!isEmpty()){ //While true keep removing!
        remove(1); //Calls function and deletes first spot head is pointing to
    }
}
template<class T>
LinkedList<T>::LinkedList(LinkedList  &otherList){ //If we want to make a copy of the list
                                                   //well TADAAAAAA this is what we have
for(int i = 0; i < otherList.getLength(); i++){ //Keeps copying the data into the new created list
    insert(i+1 ,otherList.retrieve(i+1));
    }
}
template<class T>
Node<T> * LinkedList<T>::find(int pos){ //This function is created so we can find a specific spot in the LinkedList
    if(pos <= 0 || pos > count+1)
        throw 13;       //Checking for errors

    Node<T> * temp = head; //temp is now also pointing to where head is pointing too
    int i = 1;

    if(pos == i){
        return temp;
    }

    while(temp != NULL && i++ < pos)
    {
        temp = temp->next; //This will move along the linkedlist until we found what we came for
    }
    return temp; //And finally returned to the function that called it
}

template<class T>
bool LinkedList<T>::isEmpty(){
    if (head == NULL) //If head is pointing to NULL the list is empty
		return true;  //In that case we return true
	return false;
}
template<class T>
int LinkedList<T>::getLength(){
    return count; //Returing the length of the list!!! WOOOO
}

template<class T>
void LinkedList<T>::insert(int pos, T item){
    if(pos <= 0 || pos > count+1) //The awesome part about this is....we both know what it does
        throw 13;

    Node<T> * node = new Node<T>; //Creating a new Node for node
    node->data = item; //inserting item in node->data

    if(pos == 1){ //This is specifically for the beginning
        node->next = head; // node's pointer is pointing to head
        head = node;   //And head is now pointing to the node itself and is officially the first link
    }
    else{
        Node<T> * prev = find(pos-1); //In this instance we find the position we would like to insert it in
        node->next = prev->next; // Have node's next point to previous's next
        prev->next = node; //Then have previous's next point to node so that way it is included in between
    }
        count++;
}
template<class T>
T LinkedList<T>::remove(int pos){

if(pos <= 0 || pos > count +1){ //I think we can both agree we know what it does by now
   throw 13;
}

Node<T> * temp; //Initializing temp of type Node *
T temp_data; //and temp_data of type T

if(pos == 1){ //If we would like to remove the first spot this is what we do
    temp = head; //Temp is now pointing to where head is pointing to.
    temp_data = head->data; //Making a copy of the data in the first node head is pointing and storing it in temp data
    head = head->next; //Making the first node the new head.
}

delete temp; //Deleting so we won't have leaks
temp = NULL; //NULL'ing as a precaution

count--; //Decrementing counter because we deleted one spot in the linked list
return temp_data; //And now returning what we deleted because it is what the user wants to see

}
template<class T>
T LinkedList<T>::retrieve(int pos){ //This is where we send back the variable asked for
    if(pos <= 0 || pos > count+1) //...
        throw 13;

    Node<T> * temp = find(pos); //Finds the specificed spot and sends it to temp and then we return the data
    return temp->data;
}
#endif
