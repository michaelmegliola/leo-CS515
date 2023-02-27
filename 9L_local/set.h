// a partial implementation of set ADT with an AVL tree

#ifndef _SET_H_
#define _SET_H_

#include <iostream>
#include <string>
#include <algorithm> // for max()
using namespace std;


template<typename T>
class Set {
 private:
    struct Elem {
        T info;
        Elem *left;
        Elem *right;
        int height;
        
        // Elem constructor
        Elem(const T &theElement, Elem *theLeft, Elem *theRight, int h = 0)
                    : info(theElement), left(theLeft), right(theRight), height(h) {}
        Elem(){}
    };
    
    Elem *_root;
    int _size;

    // common code for deallocation
    void destructCode(Elem *&);
    
    // common copy code for copying a tree recursively
    Elem* copyCode(Elem *);
    
    // helper method for inserting a node
    void insert(T, Elem *&);
    
    // helper method for deleting a node
    void erase(T, Elem *&);

    // helper method for finding a node
    Elem* find(T, Elem *);
    
    // helper method to return the address of the minimum node in the tree
    Elem* findMin(Elem *node);
    
    // print out the tree level by level
    void printTree(int, Elem *) const;
    
    // single right rotation
    void rotateRight(Elem *&);
    
    // single left rotation
    void rotateLeft(Elem *&);
    
    // double right rotation
    void doubleRotateRight(Elem *&);
    
    // double left rotation
    void doubleRotateLeft(Elem *&);
    
    // return the height of a node
    int height(Elem *);

 public:
    
    // default constructor; constructs empty set
    Set();

    // copy constructor
    Set(const Set&);
    
    // destructor
    ~Set();

    // assignment operator
    Set& operator=(const Set&);
    
    // insert an element into the set;
    void insert(T);

    // remove an element from the set; not implemented
    void erase(T);

    // If found, return true
    bool find(T) const;

    // return size of the set
    int size() const;

    // print tree in laying down
    void printTree() const;

};

// outputs using overloaded << operator
template<typename T>
ostream& operator<< (ostream&, const Set<T>&);

#include "set.cpp" 
#endif  // _SET_H_
