/************************************************************************
 Title         : QuadraticProbing.h
 Author        : Peter Kamaris
 Created on    : Nov 29 2013
 Description   : Program is designed to show how Hash Tables work
 Purpose       : Assignment
 Build with    : g++ QuadraticProbing.h
 *************************************************************************/

#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

int nextPrime( int n );
int hash( const string & key );
int hash( int key );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings

template <typename HashedObj>
class QHashTable
{
  public:
    explicit QHashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }

    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( int i = 0; i < array.size( ); i++ )
            array[ i ].info = EMPTY;
    }

    bool insert( const HashedObj & x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        array[ currentPos ] = HashEntry( x, ACTIVE );

            // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool alt_insert( const HashedObj & x ) //Custom made for the specifications of assignment4
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        array[currentPos] = HashEntry( x, ACTIVE );
        array[currentPos].pos = currentSize; ///This is the only difference. We are inserting the size into the pos
            // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    //This function is designed to find a specific value in the table, then change its position if needed. All for the purpose of assignment4
    void adjustments(int val, int poss){

        int temp;

        for(int j = 0; j < array.size(); j++){
            if(array[j].element == val){ //Finding a specific value
                array[j].pos = poss;//Changing the poss if it has to be

            }
        }

    }

    bool alt_remove( const HashedObj & x ){ //Another function just modified

        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        array[currentPos].element = -1; //The only two modifications done here, since we can't really delete an int unless its a pointer
        array[currentPos].pos = -1;
        return true;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    void removemin()
    {
        for(int x = 0; x < array.size(); x++){
            if(array[x].pos == 1){
                array[x].info = DELETED;
                array[x].element = -1; //The only two modifications done here, since we can't really delete an int unless its a pointer
                array[x].pos = -1;
            }
        }

    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;
        int pos; //Another variable entered to keep track of positions in the heap
        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
          : element( e ), info( i ) { }
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

          // Assuming table is half-empty, and table length is prime,
          // this loop terminates
        while( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( int j = 0; j < array.size( ); j++ )
            array[ j ].info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldArray.size( ); i++ )
            if( oldArray[ i ].info == ACTIVE )
                insert( oldArray[ i ].element );
    }
    int myhash( const HashedObj & x ) const
    {
        int hashVal = hash( x );

        hashVal %= array.size( );
        if( hashVal < 0 )
            hashVal += array.size( );

        return hashVal;
    }
};



#endif
