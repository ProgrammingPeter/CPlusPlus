/************************************************************************
 Title         : BinaryHeap.h
 Author        : Peter Kamaris
 Created on    : Nov 29 2013
 Description   : Program is designed to show how Heaps work
 Purpose       : Assignment
 Build with    : g++ BinaryHeap.h
 *************************************************************************/

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "dsexceptions.h"
#include <vector>
#include <limits>
#include <iostream>
using namespace std;

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinaryHeap
{
  public:
    explicit BinaryHeap( int capacity = 100 )
      : array( capacity + 1 ), currentSize( 0 )
    {
    }

    explicit BinaryHeap( const vector<Comparable> & items )
      : array( items.size( ) + 10 ), currentSize( items.size( ) )
    {
        for( int i = 0; i < items.size( ); i++ )
            array[ i + 1 ] = items[ i ];
        buildHeap( );
    }

    bool isEmpty( ) const
      { return currentSize == 0; }

    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw Underflow if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return array[ 1 ];
    }
    /**
     * Insert item x, allowing duplicates.
     */
    void insert( const Comparable & x )
    {
        if( currentSize == array.size( ) - 1 )
            array.resize( array.size( ) * 2 );

            // Percolate up
        int hole = ++currentSize;
        for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
            array[ hole ] = array[ hole / 2 ];
        array[ hole ] = x;
    }

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        array[ 1 ] = array[ currentSize-- ];
        percolateDown( 1 );
    }

    int retmin(){ //Simply returns the smallest position in the heap, or the top node, however you look at it
        return array[1];
    }

    void printsorted(){

        int temparray[currentSize];
        for(int x = 1; x < currentSize+1; x++){ //Transfer all the items into a new temp array
            temparray[x] = array[x];

        }

        for(int start = 1; start < currentSize; start++){
            int x = start;

            for(int curr = start + 1; curr < currentSize; curr++){ //This is selection sort I used for sorting the items
                if(temparray[curr] < temparray[x])
                    x = curr;
            }
            swap(temparray[start], temparray[x]);
        }

        cout << "This is the list in sorted order ";
        for(int x = 1; x < currentSize+1; x++){ //Printing the array in sorted order
        cout << temparray[x] << " ";
        }

    }
    /**
     * Remove the minimum item and place it in minItem.
     * Throws Underflow if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        minItem = array[ 1 ];
        array[ 1 ] = array[ currentSize-- ];
        percolateDown( 1 );
    }

    void makeEmpty( )
      { currentSize = 0; }



    void printHeap(){
        for(int x = 1; x <= currentSize; x++)
            cout << array[x] << " " << endl; //Just printing out the heap for the convenience of the user

    }

    void decreaseKey(Comparable key, Comparable delta){

        int spot; //this is spot
        bool found = false;
        int temp;

        for(int x = 0; x < currentSize+1; x++){ //Searching the array to see if the item we want is in
            if(array[x] == key){
                spot = x;
                found = true;
            }
        }


        if(found == true){ //If it is found we do the math

            array[spot] = array[spot] - delta; //math done here

            while(spot > 1 && array[spot] < array[spot/2]){ //While we are still looking within the tree or array, how ever you want to see it

                temp = array[spot]; //Storing the number in a temp so can use it later
                array[spot] = array[spot/2]; //Swapping parent and child and we know they need to be swapped by the second condition in the while loop
                array[spot/2] = temp; //Final part of the swap
                spot = (spot/2); //and now we are moving up in the tree to keep swapping or percolating, the same thing
            }
        }

    }

    void increaseKey(Comparable key, Comparable delta){

        int spot;
        bool found = false;

        for(int x = 0; x < currentSize+1; x++){
            if(array[x] == key){ //All about finding the spot we need and if it is in the array/tree/Heap
                spot = x;
                found = true;
            }
        }

        if(found == true){ //Boolean is used here for error checking to make sure what we want to delete is found
            array[spot] = array[spot] + delta; //if found then you do the math and percolate
            percolateDown(spot);
        }
    }

    void remove(Comparable key){

    int spot;
    bool found = false;

        for(int x = 0; x < currentSize+1; x++){
            if(array[x] == key){ //find the spot we need
                spot = x;
                found = true;
            }
        }

        if(found == true){
            int fake_infinite_value = std::numeric_limits<int>::max(); //Since you can't really get the value infinite, it just takes the largset possible int
            decreaseKey(key, fake_infinite_value); //Do the arithmetic and then percolate up to make sure its the smallest value to be deleted with deletemin
            deleteMin();
            }
    }

    int returnval(int x){
            //returns the value at the position requested
        return array[x];
        }



  private:
    int                currentSize;  // Number of elements in heap
    vector<Comparable> array;        // The heap array

    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; i-- )
            percolateDown( i );
    }

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    void percolateDown( int hole )
    {
        int child;
        Comparable tmp = array[ hole ];

        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize && array[ child + 1 ] < array[ child ] )
                child++;
            if( array[ child ] < tmp )
                array[ hole ] = array[ child ];
            else
                break;
        }
        array[ hole ] = tmp;
    }

};

#endif
