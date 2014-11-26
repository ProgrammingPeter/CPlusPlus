/************************************************************************
 Title         : LinearProbing.h
 Author        : Peter Kamaris
 Created on    : Oct 29 2013
 Description   : Program is designed to show how Hash Tables work
 Purpose       : Assignment3
 Build with    : g++ LinearProbing.h
 *************************************************************************/
#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <string>
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
class LHashTable
{
  public:
    explicit LHashTable( int size = 1009 ) : array( nextPrime( size ) )
      { makeEmpty( ); }

    bool contains( const HashedObj & x )
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
        int currentPos = findPos( x );     //The if statement which triggered a rehash was deleted because of instructions given.
        if( isActive( currentPos ) )
            return false;

        array[ currentPos ] = HashEntry( x, ACTIVE );

        return true;
    }

    //This function was created to return the amount of probes counted
    int returnprobe(){

        return total_probes;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
          : element( e ), info( i ) { }
    };

    vector<HashEntry> array;
    int currentSize;
    int total_probes;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x )
    {
        int currentPos = myhash( x );
        int probes = 1; //Created to keep track of probes
        total_probes = 0;

          // Assuming table is half-empty, and table length is prime,
          // this loop terminates
        while( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x )
        {
            currentPos++;  // Compute ith probe
            probes++; //Everytime we come back in this loop looking for a spot it is a probe

            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }
        total_probes = total_probes + probes; //adding probes to total

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

