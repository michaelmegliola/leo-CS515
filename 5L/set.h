// set implemented with doubly and head sentinal linked list

#ifndef SET_H
#define SET_H
#include <iostream>
using namespace std;
typedef int ELEMENT_TYPE;


class Set{
public:
    // constructs empty set
    Set();
  
    // copy constructor (you can call copyCode method)
    Set(const Set &rhs);
   
    // destructor (you can call destructCode method)
    ~Set();
    
    // assignment operator (you can call destructCode and copyCode methods)
    Set& operator=(const Set &rhs);
    
    // insert an int into the set; 
    void insert(ELEMENT_TYPE);
    
    // remove an int from the set; 
    void erase(ELEMENT_TYPE);
    
    // remove all elements from set
    void clear();

    // return size of the set
    int size() const;
  
    // return true if an element is found; false otherwise
    bool find(ELEMENT_TYPE) const;
        
private:
    struct Elem {
        ELEMENT_TYPE info;
        Elem *prev, *next;
    };
    Elem *_head, *_tail;
    int _size;
    
    // common code for copy constructor and assignment operator
    void copyCode(const Set & v);
    
    // common code for deallocation (destructor and assignment operator)
    void destructCode();
    
    // private method for output set elements
    ostream& dump(ostream& out, const Set &v) const;
    
	// friend stand-alone functions
	// logic equlity 
    friend bool operator==(const Set& s1, const Set& s2);
	// output operator
    friend ostream& operator<< (ostream&, const Set&);
};

#endif
