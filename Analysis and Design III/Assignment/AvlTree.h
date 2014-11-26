/************************************************************************
 Title         : AvlTree.h
 Author        : Peter Kamaris
 Created on    : Oct 14 2013
 Description   : Modified AVL tree to take classes and put them in nodes
 Purpose       : Assignment2
 Build with    : g++ AvlTree.h
 *************************************************************************/
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
#include <math.h>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:

    //PRE: Nothing
    //Post: Expecting to have counted the number of nodes in the tree

    void countnode(int &countingnodes){
            countnode(countingnodes, root);
    }

    //PRE: Nothing
    //Post: Assumes we have counted the internal path length of the tree and copying it to temp and sending it back to main

    double ipl(double &temp){
        double value = 0;
        temp = InternalPathLength( root,value);
    }

    //PRE: Nothing
    //Post: Checking if requested nodes are in the tree


     bool doesitcontain( Comparable & x, int &containing )
    {
        doesitcontain(x, root, containing);
    }


    AvlTree( ) : root( NULL )
      { }
    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( Comparable & x)
    {
        return contains( x, root);
    }
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == NULL;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(  Comparable & x, int &insertcalls ) //Added the int &insertcalls to bring data back to main for math
    {
        insert( x, root, insertcalls );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( Comparable & x, int& removecalls ) //Add the int for the same reason
    {
        remove( x, root, removecalls);
    }

    /**
     * Deep copy.
     */
    const AvlTree & operator=( const AvlTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }

  private:

    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;
        bool deleted = false; //////////////////////////////////////////////////


        AvlNode( const Comparable & theElement, AvlNode *lt,
                                                AvlNode *rt, int h = 0 )
          : element( theElement ), left( lt ), right( rt ), height( h ) { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

    void insert(  Comparable & x, AvlNode * & t,int &insertcalls ) //Incrementing insertcalls everytime the function is called
    {
        if( t == NULL ){
            t = new AvlNode( x, NULL, NULL );
            insertcalls++;
        }
        else if( x < t->element )
        {
            insert( x, t->left, insertcalls );
            insertcalls++;
            if( height( t->left ) - height( t->right ) == 2 )
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
        }
        else if( t->element < x )
        {
            insert( x, t->right, insertcalls );
            insertcalls++;
            if( height( t->right ) - height( t->left ) == 2 )
                if( t->right->element < x )
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
        }

        else
            ;
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }


    void remove( Comparable & x, AvlNode * & t, int &removecalls)  //added int&
    {
        if(t == NULL)// if tree is empty
            return; //item not found
        else if (x < t->element){
            removecalls++;
            remove(x,t->left, removecalls);
        }
        else if( t->element < x){
            removecalls++;
            remove(x,t->right, removecalls);
        }
        else
            t->deleted = true; //Lazy deletion does not remove anything but changes the boolean value
    }
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */

    bool contains( Comparable & x, AvlNode *t )
    {
        if( t == NULL ){
            return false;
        }
        else if( x < t->element ){
            return contains( x, t->left );
        }
        else if( t->element < x ){
            return contains( x, t->right );
        }
        else{
            t->element.Printenzymes(); //Printing out the enzymes with the same sequence
            return true;
            }
                // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != NULL )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != NULL )
        {
            printTree( t->left );
            cout << t->element << endl;   /// << overloaded to print variables
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( AvlNode *t ) const
    {
        return t == NULL ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }


    bool doesitcontain( Comparable & x, AvlNode *t, int &containing )
    {
        if( t == NULL ){
            return false;
        }
        else if( x < t->element ){
            containing++;
            return doesitcontain( x, t->left, containing );
        }
        else if( t->element < x ){
            containing++;
            return doesitcontain( x, t->right, containing);
        }
        else{
            return true;
            }
    }

    double InternalPathLength(AvlNode *& t,double value){
        if(t == NULL)
        {
            return 0;
        }
        return (value+InternalPathLength(t->right,value+1)+InternalPathLength(t->left,value+1));
    }

     void countnode(int &countingnodes, AvlNode *& t){

        if(t != NULL){
            countnode(countingnodes, t->left);

            if(t->deleted == false) ///////////////////////////////////////
                countingnodes++;

            countnode(countingnodes ,t->right);
        }
     }






};

#endif
