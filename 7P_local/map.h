// A non-generic Map ADT implemented with a BST data structure
// The BST is not-balanced and non-threaded

#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>

using namespace std;

typedef string KEY_TYPE;
typedef string VALUE_TYPE;

class Map{
    struct Elem; //declaration of an interal structure needed below...

public:
    //---Constructors and destructors---
    Map();               // constructs empty Map
    Map(const Map &rhs); // copy constructor 
    ~Map();              // destructor
    
    // assignment operator
    Map& operator=(const Map &rhs);
    
    // insert an element; return true if successful
    bool insert(KEY_TYPE, VALUE_TYPE);
    
    // remove an element; return true if successful
    bool erase(KEY_TYPE);
    
    // return size of the Map
    int size() const;
    
    // return an iterator pointing to the end if an element is not found,
    // otherwise, return an iterator to the element
    class Iterator;
    Iterator find(KEY_TYPE) const;
    
    // Iterators for accessing beginning and end of collection
    Iterator begin() const;
    Iterator end() const;
    
    // overloaded subscript operator
    VALUE_TYPE& operator[](KEY_TYPE);
    
    // output the undering BST
    ostream& dump(ostream& out) const;
    
    // a simple Iterator, won't traverse the collection
    class Iterator{
    public:
        Iterator(){}
        explicit Iterator(Elem *cur):_cur(cur) {}
        Elem& operator*();
        Elem* operator->();
        // Iterator operator++(int);
        bool operator==(Iterator it) const;
        bool operator!=(Iterator it) const;
    private:
        Elem* _cur;
    };
    
private:
    struct Elem {
        KEY_TYPE key;
        VALUE_TYPE data;
        Elem *left;
        Elem *right;
    };
    Elem *_root;  // a dummy root sentinel 
    int _size;
    
    // helper method for inserting record into tree.
    bool insert(Elem *& root, const KEY_TYPE& key, const VALUE_TYPE& data);
    
    // helper method for print tree
    void printTree(ostream& out, int level, Elem *p) const;
    
    // common code for deallocation
    void destructCode(Elem *& p);
    
    // common code for copy tree
    void copyCode(Elem* &newRoot, Elem* origRoot); 
};

ostream& operator<< (ostream&, const Map&);

#endif
