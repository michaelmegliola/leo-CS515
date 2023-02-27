// set implemented with right-threaded BST with a dummy root node

#ifndef SET_H
#define SET_H
#include <iostream>
#include <string>
#include <limits>
#include <queue>

using namespace std;
typedef int ELEMENT_TYPE;  // a set for int elements

class Set{
private:
    struct Elem {
        ELEMENT_TYPE info;
        Elem *left;
        Elem *right;
        bool rightThread; // if node has the normal right child link or a thread link
    };
    Elem *_root;
    int _size;

    // inserts record into tree.
    bool insert(Elem *& root, const ELEMENT_TYPE &value, Elem * lastLeft);

    // common destruct code
    void destructCode(Elem *&);

    // output set elements
    void printTree(ostream&, int, Elem*);

public:

    // default constructor; constructs empty set
    Set();

    // destructor
    ~Set();

    // insert an element into the set;
    bool insert(ELEMENT_TYPE);

    // return size of the set
    int size() const;

    // Depth first in order traverse
    void depthFirstInOrder();

    // Breadth first traverse
    void breadthFirst();

    ostream& dump(ostream& out);
};

ostream& operator<< (ostream&, Set&);

#endif
